/***********************************************
* 
* File: path.hpp
*
* Purpose: handle file paths in jujubee
*
* Project: jujubee
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH

namespace juju_file_system {
    // virtual path
    class path {
    public:
        path() = default;
        path(const string& p);

        bool operator==(const path& other_p) const {
            return this->m_path == other_p.m_path;
        }

        string get_raw_path() const { return m_path; }
    protected:
        string m_path;
    };
}