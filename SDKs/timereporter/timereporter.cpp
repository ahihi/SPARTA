#pragma once

#include "timereporter.h"

TimeReporter::TimeReporter(const std::string& host, int port)
#ifdef TIMEREPORTER_JUCE_OSC
: osc_message(TIMEREPORTER_ADDR) {
	osc_sender.connect(host, port);
	mem_block.setSize(sizeof(int64_t), false);
}
#else
: transmit_socket(IpEndpointName(host.c_str(), port))
, osc_stream(buffer, TIMEREPORTER_OUTPUT_BUF_SIZE) {}
#endif

TimeReporter::TimeReporter() : TimeReporter("localhost", 8765) {}

void TimeReporter::report(const std::string& tag, int id, int64_t timestamp) {
#ifdef TIMEREPORTER_JUCE_OSC
	juce::MemoryBlock timestamp_bytes = mem_block;
#else
	char timestamp_bytes[sizeof(int64_t)] = { 0 };
#endif

	for (size_t i = 0; i < sizeof(int64_t); i++) {
		timestamp_bytes[i] = (timestamp >> (i * 8)) & 0xFF;
	}

#ifdef TIMEREPORTER_JUCE_OSC
	osc_message.clear();
	osc_message.addInt32(id);
	osc_message.addString(tag);
	osc_message.addBlob(timestamp_bytes);
	osc_sender.send(osc_message);
#else
	osc_stream.Clear();
	osc_stream << osc::BeginMessage(TIMEREPORTER_ADDR)
		<< id
		<< tag.c_str()
		<< osc::Blob(timestamp_bytes, sizeof(timestamp_bytes))
		<< osc::EndMessage;
	transmit_socket.Send(osc_stream.Data(), osc_stream.Size());
#endif
}

void TimeReporter::report_now(const std::string& tag, int id) {
	report(tag, id, TimeReporter::get_timestamp());
}

int64_t TimeReporter::get_timestamp() {
	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}