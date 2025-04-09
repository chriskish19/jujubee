#include NAMES_INCLUDE
#include DRIVE_INCLUDE_PATH


juju_file_system::juju_blob::juju_blob(std::size_t size, character letter, const std::filesystem::path& p) 
:
	m_blob_size(size),
	m_juju_drive_letter(letter),
	m_os_path(p),
	m_fs_juju_blob(fstream(m_os_path, std::ios::binary))
{

}

juju::juju_codes juju_file_system::juju_blob::add_file(const juju_file_system::file& data) {
	return juju::juju_codes::success;
}

juju::juju_codes jfs::juju_blob::remove_file(const jfs::file& data) {
	return juju::juju_codes::success;
}

