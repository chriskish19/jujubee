/***********************************************
* File: juju_except.hpp
*
* Purpose: exception handling layer
*
*
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include PCH_INCLUDE_PATH

namespace juju {

	class exception : public std::exception{
	public:
		exception() = default;
        ~exception();


		void go();
	protected:
		template<typename f_type>
		void except_go(std::function<f_type> run_function);
        
        
	};
	
	
	template<typename f_type>
	inline void exception::except_go(std::function<f_type> run_function)
	{
        try {
            run_function();
        }
        catch (juju::jujubee_error& e) {
            e.vs_output_full_message();
        }
        // Memory allocation failure (e.g., `new` operator failure)
        catch (const std::bad_alloc& e) {
            std::cerr << "Memory allocation error: " << e.what() << '\n';
        }
        // Invalid type conversions (e.g., `dynamic_cast` failure)
        catch (const std::bad_cast& e) {
            std::cerr << "Bad cast error: " << e.what() << '\n';
        }
        // Errors related to type information
        catch (const std::bad_typeid& e) {
            std::cerr << "Bad typeid error: " << e.what() << '\n';
        }
        // Standard logic errors (e.g., `std::invalid_argument`, `std::out_of_range`)
        catch (const std::logic_error& e) {
            std::cerr << "Logic error: " << e.what() << '\n';
        }
        // Standard runtime errors (e.g., `std::runtime_error`, `std::overflow_error`)
        catch (const std::runtime_error& e) {
            std::cerr << "Runtime error: " << e.what() << '\n';
        }
        // Errors from the system API (e.g., file I/O, socket issues)
        catch (const std::system_error& e) {
            std::cerr << "System error: " << e.what() << '\n';
        }
        catch (const std::filesystem::filesystem_error& e) {
            // file system error here
        }
        // C++ standard exception base class (catches any unhandled standard exceptions)
        catch (const std::exception& e) {
            std::cerr << "Standard exception: " << e.what() << '\n';
        }
        // Non-standard exceptions (e.g., custom exceptions or OS errors)
        catch (...) {
            std::cerr << "Unknown exception caught!" << '\n';
        }
	}
}