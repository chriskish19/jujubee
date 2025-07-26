#######################################
# CMake lists file for jujubee project
#######################################


cmake_minimum_required(VERSION 3.18)

# main project exe
set(jujubee "jujubee")
project(${jujubee})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(MSVC_compiler_id "MSVC")
set(CLANG_compiler_id "Clang")
set(GCC_compiler_id "GNU")

set(is_using_MSVC_compiler OFF)
set(is_using_CLANG_compiler OFF)
set(is_using_GCC_compiler OFF)

string(COMPARE EQUAL ${CMAKE_CXX_COMPILER_ID} ${MSVC_compiler_id} is_using_MSVC_compiler)
string(COMPARE EQUAL ${CMAKE_CXX_COMPILER_ID} ${CLANG_compiler_id} is_using_CLANG_compiler)
string(COMPARE EQUAL ${CMAKE_CXX_COMPILER_ID} ${GCC_compiler_id} is_using_GCC_compiler)

if(NOT (is_using_MSVC_compiler OR is_using_CLANG_compiler OR is_using_GCC_compiler))
    message(FATAL_ERROR "Compiler not supported, You are using: ${CMAKE_CXX_COMPILER_ID}")
endif()



# switch for unicode
set(UNICODE_DEFINED ON)

if(${UNICODE_DEFINED})
    # define UNICODE to the compiler
    add_compile_definitions(-DUNICODE -D_UNICODE)
endif()




file(GLOB_RECURSE cpp_source_files "../projects/jujubee/*.cpp")
file(GLOB_RECURSE cpp_header_files "../projects/jujubee/*.hpp")
file(GLOB_RECURSE juju_resources "../projects/jujubee/resources/*")

include_directories("../projects")

# NOTE: need to install dokan lib first
# https://github.com/dokan-dev/dokany/releases
set(DOKAN_ROOT "C:/Program Files/Dokan/DokanLibrary-2.3.0")
include_directories("${DOKAN_ROOT}/include")
link_directories("${DOKAN_ROOT}/lib")


# creates macros for each hpp file include path
# very handy for name changes and file moves
foreach(HEADER_FILE ${cpp_header_files})
    get_filename_component(FILE_NAME ${HEADER_FILE} NAME_WE)
    set(FILE_NAME_HPP "${FILE_NAME}_hpp")
    set(HEADER_FILE_PATH "\"${HEADER_FILE}\"")
    add_compile_definitions(-D${FILE_NAME_HPP}=${HEADER_FILE_PATH})
    
    # for file name changes in the project
    # their is a file called names.hpp that manages all file name changes in the project
    if(${FILE_NAME} STREQUAL "names")
        add_compile_definitions(-DNAMES_INCLUDE=${FILE_NAME_HPP})
    endif()
endforeach()

# creates macros for each resource (full file path)
foreach(JUJU_RESOURCE ${juju_resources})
    # gets the name from JUJU_RESOURCE, JUJU_RESOURCE is the full path from C:
    get_filename_component(FILE_NAME ${JUJU_RESOURCE} NAME_WE)
    
    # gets the extension from JUJU_RESOURCE
    get_filename_component(FILE_EXT ${JUJU_RESOURCE} EXT)
    
    if(${UNICODE_DEFINED} AND NOT (${FILE_EXT} STREQUAL ".h" OR ${FILE_EXT} STREQUAL ".hpp"))
        # full file path in the variable JUJU_RESOURCE_FILE_PATH
        set(JUJU_RESOURCE_FILE_PATH "L\"${JUJU_RESOURCE}\"")
    else()
        # full file path in the variable JUJU_RESOURCE_FILE_PATH
        set(JUJU_RESOURCE_FILE_PATH "\"${JUJU_RESOURCE}\"")
    endif()

    # get rid of the dot and replace it with _
    string(REPLACE "." "_" FILE_EXT ${FILE_EXT})

    # the macro name
    set(JUJU_RESOURCE_NAME "${FILE_NAME}${FILE_EXT}")
    
    # set the macro to the file path
    add_compile_definitions(-D${JUJU_RESOURCE_NAME}=${JUJU_RESOURCE_FILE_PATH})
endforeach()



# this is primarly for using cmake in within an ide enviroment
# in an Open folder config, otherwise cmake will generate an ide specific solution
# that usually defines these macros anyway
if(DEFINED BUILD_TYPE)
    message("Build Type: ${BUILD_TYPE}")
    if(BUILD_TYPE STREQUAL "Debug")
        add_definitions(-DDEBUG)
        add_executable(${jujubee} WIN32 ${cpp_source_files} ${cpp_header_files})
        target_link_libraries(${jujubee} PUBLIC dokan2)
    elseif(BUILD_TYPE STREQUAL "Release")
        add_definitions(-DRELEASE)
        add_executable(${jujubee} WIN32 ${cpp_source_files} ${cpp_header_files})
        target_link_libraries(${jujubee} PUBLIC dokan2)
    elseif(BUILD_TYPE STREQUAL "Test")
        # I use the terminal window for logging when running tests
    
        add_definitions(-DTEST)
        add_definitions(-DDEBUG)
        
        add_executable(${jujubee} ${cpp_source_files} ${cpp_header_files})

        # Link required Win32 libraries
        target_link_libraries(${jujubee} PUBLIC
            user32
            kernel32
            gdi32
            winmm
            comdlg32
            advapi32
            shell32
            ole32
            oleaut32
            dokan2
        )
    endif()
endif()









