/***********************************************
*
* File: juju_except.cpp
*
* Purpose: juju_except.hpp definitions
*
* Project: jujubee
*
************************************************/


#include NAMES_INCLUDE
#include EXCEPT_INCLUDE_PATH

juju::exception::~exception()
{
    
}

void juju::exception::go()
{
    juju::window* main_window = new juju::window;
    auto bind_mainwindow_go = std::bind(&juju::window::go, main_window);
    std::function<void()> go_test(bind_mainwindow_go);

    std::thread launcher([this,go_test]() { except_go<void()>(go_test); });


    if (launcher.joinable()) {
        launcher.join();
    }


    if (main_window != nullptr) {
        delete main_window;
    }
}
