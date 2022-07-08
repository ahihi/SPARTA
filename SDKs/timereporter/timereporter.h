#pragma once

#include <chrono>
#include <cstdint>
#include <string>
#ifdef TIMEREPORTER_JUCE_OSC
#include <JuceHeader.h>
#else
#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"
#define TIMEREPORTER_OUTPUT_BUF_SIZE 512
#endif

#define TIMEREPORTER_ADDR "/time"

class TimeReporter {
public:
	TimeReporter(const std::string& host, int port);
	TimeReporter();

	void report(const std::string& tag, int id, int64_t timestamp);
	void report_now(const std::string& tag, int id);
	static int64_t get_timestamp();

private:
#ifdef TIMEREPORTER_JUCE_OSC
	juce::OSCSender osc_sender;
	juce::OSCMessage osc_message;
	juce::MemoryBlock mem_block;
#else
	UdpTransmitSocket transmit_socket;
	char buffer[TIMEREPORTER_OUTPUT_BUF_SIZE];
	osc::OutboundPacketStream osc_stream;
#endif
};
