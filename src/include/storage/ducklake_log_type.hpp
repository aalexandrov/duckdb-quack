//===----------------------------------------------------------------------===//
//                         DuckDB
//
// storage/ducklake_log_type.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/logging/log_type.hpp"

namespace duckdb {

class DuckLakeMetadataLogType : public LogType {
public:
	static constexpr const char *NAME = "DuckLakeMetadata";
	static constexpr LogLevel LEVEL = LogLevel::LOG_DEBUG;

	DuckLakeMetadataLogType();

	static LogicalType GetLogType();
	static string ConstructLogMessage(const string &catalog_name, const string &query, int64_t elapsed_ms);
};

//! Logs timing information for the ducklake_merge_adjacent_files / ducklake_rewrite_data_files workflow:
//! candidate discovery, the actual per-group file merge, and the transaction commit/retry loop.
class DuckLakeCompactionLogType : public LogType {
public:
	static constexpr const char *NAME = "DuckLakeCompaction";
	static constexpr LogLevel LEVEL = LogLevel::LOG_DEBUG;

	DuckLakeCompactionLogType();

	static LogicalType GetLogType();
	static string ConstructLogMessage(const string &catalog_name, const string &phase, const string &detail,
	                                  int64_t elapsed_ms);
};

} // namespace duckdb
