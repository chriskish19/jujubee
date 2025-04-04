/***********************************************
* File: file_logger.hpp
*
* Purpose: save system logs to a file
*
*
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include CODES_INCLUDE_PATH
#include MAIN_INCLUDE_PATH



namespace juju {
	class file_logger {
	public:
		file_logger(const string& file_name,const std::filesystem::path& p);

		juju_codes create();

	protected:

		std::ofstream m_log_file;
		
		fs::path m_log_file_path;
	};
}