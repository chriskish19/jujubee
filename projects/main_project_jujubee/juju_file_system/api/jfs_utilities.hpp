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
#include FILE_INCLUDE_PATH
#include CODES_INCLUDE_PATH
#include DRIVE_INCLUDE_PATH
#include FOLDER_INCLUDE_PATH




namespace juju_file_system {
	// copy a file from os file system into juju file system
	file file_copy(const path<string>& to_juju_p, const std::filesystem::path& from_os_p);


	// create a new folder on a juju blob drive
	juju::juju_codes create_folder(const juju_blob& drive, const folder& new_folder);

	// create a collection of new folders
	juju::juju_codes create_folders(const juju_blob& drive, const std::vector<folder>& folders);


}
