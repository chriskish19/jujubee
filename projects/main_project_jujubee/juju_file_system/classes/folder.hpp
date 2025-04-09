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
#include CODES_INCLUDE_PATH


namespace juju_file_system {
	class folder {
	public:
		folder() = default;


	protected:
		path<string> m_p;

		string m_name;

	};
}