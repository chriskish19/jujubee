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

namespace juju_file_system {
	// copy a file from os file system into juju file system
	file file_copy(const path<string>& to_juju_p, const std::filesystem::path& from_os_p);



}
