/***********************************************
*
* File: file.hpp
*
* Purpose: virtual file in jujubee
*
* Project: jujubee
* 
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include PATH_INCLUDE_PATH
#include CODES_INCLUDE_PATH


namespace juju_file_system {
	// virtual file
	class file {
	public:
		file() = default;
		file(std::size_t size, const path& p);
		~file();

		bool operator==(const file& other) const{
			return this->m_file_path == other.m_file_path;
		}

		path get_file_path() const { return m_file_path; }
		std::size_t get_file_size() const { return m_file_size; }
	protected:
		// juju path
		path m_file_path;

		// in bytes
		std::size_t m_file_size;
	};

	struct file_hash {
		size_t operator()(const file& f) const{
			return std::hash<std::string>()(f.get_file_path().get_raw_path());
		}
	};

	struct file_equal {
		bool operator()(const file& a, const file& b) const {
			return a.get_file_path() == b.get_file_path();
		}
	};


}
