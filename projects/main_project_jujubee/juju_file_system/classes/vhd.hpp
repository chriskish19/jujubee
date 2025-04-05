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
#pragma pack(push, 1)
    struct VHD_Footer {
        char cookie[8];               // "conectix"
        uint32_t features;            // 0x00000002
        uint32_t version;             // 0x00010000
        uint64_t data_offset;         // 0xFFFFFFFFFFFFFFFF
        uint32_t timestamp;           // seconds since Jan 1, 2000
        char creator_app[4];          // "CUST"
        uint32_t creator_ver;         // 0x00010000
        char creator_os[4];          // "Wi2k"
        uint64_t original_size;       // disk size
        uint64_t current_size;        // disk size
        uint32_t disk_geometry;       // simplified: (e.g., 0x003F0F01)
        uint32_t disk_type;           // 2 = fixed hard disk
        uint32_t checksum;
        uint8_t unique_id[16];        // random GUID
        uint8_t saved_state;          // 0
        uint8_t reserved[427];        // pad to 512 bytes
    };
#pragma pack(pop)
}