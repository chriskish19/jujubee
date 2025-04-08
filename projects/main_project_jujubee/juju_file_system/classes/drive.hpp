/***********************************************
* File: drive.hpp
*
* Purpose: virtual drive in jujubee
*
*
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include CODES_INCLUDE_PATH
#include PATH_INCLUDE_PATH
#include DRIVE_INCLUDE_PATH
#include FILE_INCLUDE_PATH


namespace juju_file_system {
	
	// virtual drive
	class juju_blob {
	public:
		// size: file count
		juju_blob(std::size_t size, character letter);

		juju::juju_codes add_file(const file& data);

		juju::juju_codes remove_file(const file& data);
	protected:
		// files
		std::unordered_set<file>* m_files_v_p = nullptr;
	};
}