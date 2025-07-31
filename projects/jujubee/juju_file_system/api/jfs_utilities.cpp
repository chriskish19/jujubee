#include "jfs_utilities.hpp"
/***********************************************
*
* File: jfs_utilities.cpp
*
* Purpose: jfs_utilities.hpp definitions
*
* Project: jujubee
*
************************************************/

#include NAMES_INCLUDE
#include JFS_UTILITIES_INCLUDE_PATH

NTSTATUS DOKAN_CALLBACK juju_create_file(
	LPCWSTR filename, 
	PDOKAN_IO_SECURITY_CONTEXT security_context, 
	ACCESS_MASK desiredaccess, 
	ULONG fileattributes, 
	ULONG, 
	ULONG createdisposition, 
	ULONG createoptions, 
	PDOKAN_FILE_INFO dokanfileinfo)
{
	
}

NTSTATUS DOKAN_CALLBACK juju_read_file(
	LPCWSTR filename, 
	LPVOID buffer, 
	DWORD bufferlength, 
	LPDWORD readlength, 
	LONGLONG offset, 
	PDOKAN_FILE_INFO dokanfileinfo)
{
	
}

NTSTATUS DOKAN_CALLBACK juju_get_file_info(
	LPCWSTR filename, 
	LPBY_HANDLE_FILE_INFORMATION buffer, 
	PDOKAN_FILE_INFO dokanfileinfo)
{
	
}

NTSTATUS DOKAN_CALLBACK juju_write_file(
	LPCWSTR filename, 
	LPCVOID buffer, 
	DWORD number_of_bytes_to_write, 
	LPDWORD number_of_bytes_written, 
	LONGLONG offset, 
	PDOKAN_FILE_INFO dokanfileinfo)
{
	
}
