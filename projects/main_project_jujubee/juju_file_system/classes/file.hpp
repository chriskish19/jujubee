/***********************************************
*
*
*
*
*
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include PATH_INCLUDE_PATH
#include CODES_INCLUDE_PATH


namespace juju_file_system {
	

	// virtual file
	class file {
	public:
		file() = default;
		file(std::size_t size, const path<string>& p);
		~file();

		
	protected:
		// juju path
		path<string> m_file_path;

		// in bytes
		std::size_t m_file_size;
	};
}