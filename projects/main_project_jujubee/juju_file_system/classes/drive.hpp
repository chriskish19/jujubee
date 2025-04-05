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



namespace juju_file_system {
	// virtual memory
	struct juju128 {
		std::size_t address;
		std::byte memory[JUJU_BYTE];
	};
	
	// virtual file
	struct file_description {

	};
	
	// virtual drive
	class drive {
	public:
		drive(std::size_t drive_size, character drive_letter);

		juju::juju_codes add_file(const file_description& fd);
	protected:
		// raw file data
		std::vector<juju128>* m_drive_data_v_p = nullptr;

		std::vector<file_description> m_files;


	};
}