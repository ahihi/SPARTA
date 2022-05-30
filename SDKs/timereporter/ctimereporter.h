#pragma once

#include <stdint.h>

typedef void CTimeReporter;

#ifdef __cplusplus
extern "C" {
#endif

	CTimeReporter* TimeReporter_new(const char* host, int port);
	void TimeReporter_delete(CTimeReporter* time_reporter);
	void TimeReporter_report(const CTimeReporter* time_reporter, const char* tag, int id, int64_t timestamp);
	void TimeReporter_report_now(const CTimeReporter* time_reporter, const char* tag, int id);
	int64_t TimeReporter_get_timestamp();

#ifdef __cplusplus
}
#endif