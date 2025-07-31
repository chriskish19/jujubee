/***********************************************
* 
* File: jfs_utilities.hpp
* 
* Purpose: utilites for the file system
* 
* Project: jujubee
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include CODES_INCLUDE_PATH

#include <dokan/dokan.h>

extern "C" {

	NTSTATUS DOKAN_CALLBACK juju_create_file(
		LPCWSTR filename, 
		PDOKAN_IO_SECURITY_CONTEXT security_context,
		ACCESS_MASK desiredaccess,
		ULONG fileattributes,
		ULONG /*shareaccess*/, 
		ULONG createdisposition,
		ULONG createoptions, 
		PDOKAN_FILE_INFO dokanfileinfo);

	NTSTATUS DOKAN_CALLBACK juju_read_file(
		LPCWSTR filename, 
		LPVOID buffer,
		DWORD bufferlength,
		LPDWORD readlength,
		LONGLONG offset,
		PDOKAN_FILE_INFO dokanfileinfo);

	NTSTATUS DOKAN_CALLBACK juju_get_file_info(
		LPCWSTR filename, 
		LPBY_HANDLE_FILE_INFORMATION buffer,
		PDOKAN_FILE_INFO dokanfileinfo);

	NTSTATUS DOKAN_CALLBACK juju_write_file(
		LPCWSTR filename,
		LPCVOID buffer,
		DWORD number_of_bytes_to_write,
		LPDWORD number_of_bytes_written,
		LONGLONG offset,
		PDOKAN_FILE_INFO dokanfileinfo);
}


namespace juju_file_system {
	std::unordered_map<string, file> glb_drive;


}
