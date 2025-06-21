#include "drive.hpp"
/***********************************************
*
* File: drive.cpp
*
* Purpose: drive.hpp definitions
*
* Project: jujubee
*
************************************************/

#include NAMES_INCLUDE
#include DRIVE_INCLUDE_PATH


juju_file_system::juju_blob::juju_blob(std::size_t size, character letter, const std::filesystem::path& p) 
:
	m_blob_size(size),
	m_juju_drive_letter(letter),
	m_os_path(p),
	m_fs_juju_blob(fstream(m_os_path, std::ios::binary))
{
	m_files_v_p = new std::unordered_set<file, file_hash, file_equal>;
}

juju_file_system::juju_blob::~juju_blob()
{
	if (m_files_v_p != nullptr) {
		delete m_files_v_p;
		m_files_v_p = nullptr;
	}
}

juju::juju_codes juju_file_system::juju_blob::add(const file& data)
{
	auto exists = m_files_v_p->emplace(data);
	if (exists.second == false) {
		// didnt insert file name exists already
		return juju::juju_codes::file_exists;
	}
	else {
		return juju::juju_codes::success;
	}
	
	return juju::juju_codes();
}

juju::juju_codes juju_file_system::juju_blob::remove(const file& data)
{
	auto found = m_files_v_p->find(data);
	if (found != m_files_v_p->end()) {
		// file was found
		m_files_v_p->erase(found);
	}
	else {
		// file doesnt exist in the drive
		return juju::juju_codes::no_such_file_or_directory;
	}

	return juju::juju_codes::success;
}

juju::juju_codes juju_file_system::juju_blob::write_to_blob(const file& data)
{
	
	
	
	return juju::juju_codes();
}



