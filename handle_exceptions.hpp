#pragma once
#include "all_stl.hpp"
#include "juju_error_codes.hpp"

class juju_base_exception : public std::exception , public virtual jujubee_errors {
public:
	juju_base_exception() noexcept = default;


protected:
	
};

class juju_window_failure : public juju_base_exception {
public:
	juju_window_failure(const std::initializer_list<codes>& errors) noexcept 
		:jujubee_errors(errors) {
		this->m_protected_main_error_code = codes::window_failure;
	}
	
};


