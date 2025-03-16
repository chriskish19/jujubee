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
		log() = default;

		void set_message(const string& message);
		string get_message() { return m_message; }
		std::chrono::steady_clock::time_point get_time();
		void set_time();
	protected:
		string m_message;
		std::chrono::steady_clock::time_point m_time;
	};

	class base_logger {
	public:
		base_logger(std::size_t log_count);

	protected:
		const std::size_t m_log_count = 0;
		std::vector<log*> m_logs_v;
	};
}



 


