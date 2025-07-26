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
	class memory {
	public:


	protected:
		// 64bit address
		std::size_t address;

		// 128bits
		std::byte m_data[JUJU_BYTE];
	};
}