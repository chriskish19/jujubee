/***********************************************
*
* File: jfs_objects.hpp
*
* Purpose: define class objects for jfs
*
* Project: jujubee
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include CODES_INCLUDE_PATH

namespace juju_file_system {
	class name {
	public:

	protected:
		string m_name;
	};

	class file {
	public:
		
	protected:
		name m_file_name = {};
		std::size_t m_start_index = 0;
		std::size_t m_end_index = 0;
	};

	class blob {
	public:
		blob(std::size_t size, const std::filesystem::path& location);

		juju::juju_codes add_file(const file& new_file);

		juju::juju_codes delete_file(const name& file_name);
	protected:
		std::unordered_map<name, file> m_list;
	};

	class drive {

	};
}