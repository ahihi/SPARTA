#pragma once

#include "ctimereporter.h"
#include "timereporter.h"

#ifdef __cplusplus
extern "C" {
#endif

	CTimeReporter* TimeReporter_new(const char* host, int port) {
		return (CTimeReporter*)new TimeReporter(host, port);
	}

	void TimeReporter_delete(CTimeReporter* time_reporter) {
		delete (TimeReporter*)time_reporter;
	}

	void TimeReporter_report(const CTimeReporter* time_reporter, const char* tag, int id, int64_t timestamp) {
		return ((TimeReporter*)time_reporter)->report(tag, id, timestamp);
	}

	void TimeReporter_report_now(const CTimeReporter* time_reporter, const char* tag, int id) {
		return ((TimeReporter*)time_reporter)->report_now(tag, id);
	}

	int64_t TimeReporter_get_timestamp() {
		return TimeReporter::get_timestamp();
	}

#ifdef __cplusplus
}
#endif