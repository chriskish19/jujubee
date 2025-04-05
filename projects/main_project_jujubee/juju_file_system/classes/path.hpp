/***********************************************
* File: path.hpp
*
* Purpose: handle file paths in jujubee
*
*
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH

namespace juju_file_system {
	template<typename type>
	concept path_type = std::is_same_v<type, jfs::string> or
		std::is_same_v<type,character*> or
		std::is_same_v<type,std::vector<character>>;
	
	template<typename path_type>
	class path {
	public:
		path(path_type p);
		

		// formatted for windows paths
		// (C:\\folder\\file.txt)
		path windows();

		// (C:/folder/file.txt)
		path linux();
	protected:
		std::vector<character> m_path_v = {};
	};
	
	
    template<typename path_type>
    inline path<path_type>::path(path_type p)
    {
        if constexpr (std::is_same_v<path_type, jfs::string>) {
            m_path_v.assign(p.begin(), p.end());
        } else if constexpr (std::is_same_v<path_type, character*>) {
            m_path_v.assign(p, p + std::char_traits<character>::length(p));
        } else if constexpr (std::is_same_v<path_type, std::vector<character>>) {
            m_path_v = std::move(p);
        } else {
            static_assert(always_false<path_type>::value, "Unsupported path type");
        }
    }

    template<typename path_type>
    inline path<path_type> path<path_type>::windows()
    {
        for (auto& ch : m_path_v) {
            if (ch == '/') {
                ch = '\\';
            }
        }
        return *this;
    }
    
    
    template<typename path_type>
    inline path<path_type> path<path_type>::linux()
    {
        for (auto& ch : m_path_v) {
            if (ch == '\\') {
                ch = '/';
            }
        }
        return *this;
    }
}