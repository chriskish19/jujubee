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

namespace juju {
	class log {
	public:
		// message_length : this is used to reserve memory for
		// m_message
		log(std::size_t message_length);

		// sets m_message to message
		void set_message(const string& message);

		// get a copy of m_message
		string get_message_copy();

		// if message is large and since copying is expensive
		// return a pointer to the message
		// (unsafe for multithreading)
		string* get_message_p() { return &m_message; }

		// sets m_stime to the current time and prefixes it to m_message
		void set_time();

		// returns the length of the m_stime string
		std::size_t get_time_length() { return m_stime.length(); }
	protected:
		// the log message
		string m_message;

		// the time stamp in a string
		string m_stime;

		// reserve memory for the length of m_message
		const std::size_t m_message_length_reserved;


		std::mutex m_message_mtx;
	};

	class base_logger {
	public:
		// log_count : number of log messages (reserves memory in m_logs_vp)
		// message_length : each message length (reserves memory in each log object)
		base_logger(std::size_t log_count, std::size_t message_length);

		// deallocate pointers/memory
		~base_logger();

		// add message using an index position
		juju_codes add_message(const string& message, std::size_t index);

		// add message using m_log_pos as the index
		juju_codes add_message(const string& message);

		// get a pointer to the logs vector
		std::vector<log*>* get_logs_vec_pointer() { return m_logs_vp; }
	protected:
		// current log position in vector (m_logs_vp)
		std::size_t m_log_pos = 0;

		// each log message max length to maintain performance
		// if a log message exceeds this, memory will have to be allocated
		const std::size_t m_message_length;

		// number of log messages in the m_logs_vp
		const std::size_t m_log_count;

		// we reserve memory for this vector to the amount of
		// log messages (m_log_count)
		std::vector<log*>* m_logs_vp = new std::vector<log*>;
	};
}



 


