/***********************************************
* File: logs.hpp
* 
* Purpose: handles base system logging
* 
* 
* 
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include CODES_INCLUDE_PATH

namespace classes {
	class log {
	public:
		log(std::size_t message_length);

		void set_message(const string& message);
		string get_message() { return m_message; }
		void set_time();
	protected:
		// the log message
		string m_message;

		// the time stamp in a string
		string m_stime;

		// the time stamp
		std::chrono::steady_clock::time_point m_time;

		// reserve memory for the length of m_message
		const std::size_t m_message_length_reserved;
	};

	class base_logger {
	public:
		base_logger(std::size_t log_count, std::size_t message_length);
		~base_logger();
	protected:
		const std::size_t m_message_length;
		const std::size_t m_log_count;
		std::vector<log*> m_logs_v;
	};
}



 


