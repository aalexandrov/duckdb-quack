#include "storage/ducklake_log_type.hpp"

#include "duckdb/common/types/value.hpp"

namespace duckdb {

constexpr LogLevel DuckLakeMetadataLogType::LEVEL;

DuckLakeMetadataLogType::DuckLakeMetadataLogType() : LogType(NAME, LEVEL, GetLogType()) {
}

LogicalType DuckLakeMetadataLogType::GetLogType() {
	child_list_t<LogicalType> child_list = {
	    {"catalog", LogicalType::VARCHAR},
	    {"query", LogicalType::VARCHAR},
	    {"elapsed_ms", LogicalType::BIGINT},
	};
	return LogicalType::STRUCT(child_list);
}

string DuckLakeMetadataLogType::ConstructLogMessage(const string &catalog_name, const string &query,
                                                    int64_t elapsed_ms) {
	child_list_t<Value> child_list = {
	    {"catalog", Value(catalog_name)},
	    {"query", Value(query)},
	    {"elapsed_ms", Value::BIGINT(elapsed_ms)},
	};
	return Value::STRUCT(std::move(child_list)).ToString();
}

constexpr LogLevel DuckLakeCompactionLogType::LEVEL;

DuckLakeCompactionLogType::DuckLakeCompactionLogType() : LogType(NAME, LEVEL, GetLogType()) {
}

LogicalType DuckLakeCompactionLogType::GetLogType() {
	child_list_t<LogicalType> child_list = {
	    {"catalog", LogicalType::VARCHAR},
	    {"phase", LogicalType::VARCHAR},
	    {"detail", LogicalType::VARCHAR},
	    {"elapsed_ms", LogicalType::BIGINT},
	};
	return LogicalType::STRUCT(child_list);
}

string DuckLakeCompactionLogType::ConstructLogMessage(const string &catalog_name, const string &phase,
                                                      const string &detail, int64_t elapsed_ms) {
	child_list_t<Value> child_list = {
	    {"catalog", Value(catalog_name)},
	    {"phase", Value(phase)},
	    {"detail", Value(detail)},
	    {"elapsed_ms", Value::BIGINT(elapsed_ms)},
	};
	return Value::STRUCT(std::move(child_list)).ToString();
}

} // namespace duckdb
