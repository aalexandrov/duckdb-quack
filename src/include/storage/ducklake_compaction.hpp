//===----------------------------------------------------------------------===//
//                         DuckDB
//
// storage/ducklake_compaction.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/execution/operator/persistent/physical_copy_to_file.hpp"

#include "duckdb/execution/physical_operator.hpp"
#include "duckdb/common/index_vector.hpp"
#include "storage/ducklake_stats.hpp"
#include "storage/ducklake_metadata_info.hpp"
#include "storage/ducklake_insert.hpp"
#include <chrono>

namespace duckdb {
class DuckLakeTableEntry;

//! Global sink state for DuckLakeCompaction - adds a start timestamp on top of DuckLakeInsertGlobalState so
//! Finalize() can log how long the actual per-group file read+write took (from the first Sink() call to Finalize).
class DuckLakeCompactionSinkState : public DuckLakeInsertGlobalState {
public:
	explicit DuckLakeCompactionSinkState(DuckLakeTableEntry &table)
	    : DuckLakeInsertGlobalState(table), start_time(std::chrono::steady_clock::now()) {
	}

	std::chrono::steady_clock::time_point start_time;
};

class DuckLakeCompaction : public PhysicalOperator {
public:
	DuckLakeCompaction(PhysicalPlan &physical_plan, const vector<LogicalType> &types, DuckLakeTableEntry &table,
	                   vector<DuckLakeCompactionFileEntry> source_files_p, string encryption_key,
	                   optional_idx partition_id, vector<Value> partition_values, optional_idx row_id_start,
	                   PhysicalOperator &child, CompactionType type);

	DuckLakeTableEntry &table;
	vector<DuckLakeCompactionFileEntry> source_files;
	string encryption_key;
	optional_idx partition_id;
	vector<Value> partition_values;
	optional_idx row_id_start;
	CompactionType type;

public:
	// // Source interface
	SourceResultType GetDataInternal(ExecutionContext &context, DataChunk &chunk,
	                                 OperatorSourceInput &input) const override;

	unique_ptr<GlobalSourceState> GetGlobalSourceState(ClientContext &context) const override;

	bool IsSource() const override {
		return true;
	}

public:
	// Sink interface
	SinkResultType Sink(ExecutionContext &context, DataChunk &chunk, OperatorSinkInput &input) const override;
	SinkFinalizeType Finalize(Pipeline &pipeline, Event &event, ClientContext &context,
	                          OperatorSinkFinalizeInput &input) const override;
	unique_ptr<GlobalSinkState> GetGlobalSinkState(ClientContext &context) const override;

	bool IsSink() const override {
		return true;
	}

	bool ParallelSink() const override {
		return false;
	}

	string GetName() const override;
};

} // namespace duckdb
