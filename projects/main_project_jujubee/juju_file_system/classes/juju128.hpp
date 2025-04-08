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




namespace juju_file_system {
	// virtual memory
	class juju128 {
	public:


	protected:
		// 64bit address
		std::size_t address;

		// 128bits
		std::byte memory[JUJU_BYTE];
	};
}