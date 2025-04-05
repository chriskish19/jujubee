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
#include VHD_INCLUDE_PATH





namespace juju_file_system {
    // The bswap32 and bswap64 functions are used to swap the byte order of a 32-bit and 64-bit integer, 
    // respectively. This process is also known as "byte swapping" or "endianness conversion".
    // Endianness refers to the order of bytes in a multi - byte number.
    uint32_t bswap32(uint32_t x);
    uint64_t bswap64(uint64_t x);

    // CRC checksum for the VHD footer
    uint32_t vhd_checksum(const uint8_t* buffer, size_t size);

    // make a vhd
    void write_fixed_vhd(const std::string& path, size_t size_mb);
}
