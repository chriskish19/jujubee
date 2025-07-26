/***********************************************
* 
* File: drive.hpp
*
* Purpose: virtual drive in jujubee
*
* Project: jujubee
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include CODES_INCLUDE_PATH
#include PATH_INCLUDE_PATH
#include FILE_INCLUDE_PATH
#include FOLDER_INCLUDE_PATH


namespace juju_file_system {
	
	// virtual drive
	class juju_blob {
	public:
		juju_blob(std::size_t size, character letter, const std::filesystem::path& p);
		
		~juju_blob();

		juju::juju_codes add(const file& data);
		juju::juju_codes remove(const file& data);

	protected:
		juju::juju_codes write_to_blob(const file& data);

		// files
		std::unordered_set<file,file_hash,file_equal>* m_files_v_p = nullptr;

		const fstream m_fs_juju_blob;
		const std::filesystem::path m_os_path;
		const std::size_t m_blob_size;
		const character m_juju_drive_letter;
	};
}