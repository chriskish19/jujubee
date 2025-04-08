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



namespace juju_file_system {
	// virtual memory
	struct juju128 {
		// 64bit address
		std::size_t address;

		// 128bits
		std::byte memory[JUJU_BYTE];
	};

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

		// file data
		std::vector<juju128>* m_file_data_v_p = nullptr;
	};
}