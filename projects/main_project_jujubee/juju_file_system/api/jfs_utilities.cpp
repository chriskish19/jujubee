#include NAMES_INCLUDE
#include JFS_UTILITIES_INCLUDE_PATH

uint32_t juju_file_system::bswap32(uint32_t x)
{
    x = (x >> 24) |
        ((x << 8) & 0x00FF0000) |
        ((x >> 8) & 0x0000FF00) |
        (x << 24);
    return x;
}

uint64_t juju_file_system::bswap64(uint64_t x)
{
    x = (x >> 56) |
        ((x << 40) & 0x00FF000000000000) |
        ((x << 24) & 0x0000FF0000000000) |
        ((x << 8) & 0x000000FF00000000) |
        ((x >> 8) & 0x00000000FF000000) |
        ((x >> 24) & 0x0000000000FF0000) |
        ((x >> 40) & 0x000000000000FF00) |
        (x << 56);
    return x;
}

uint32_t juju_file_system::vhd_checksum(const uint8_t* buffer, size_t size)
{
    uint32_t sum = 0;
    for (size_t i = 0; i < size; ++i)
        sum += buffer[i];
    return ~sum;
}

void juju_file_system::write_fixed_vhd(const std::string& path, size_t size_mb) {
    const size_t size = size_mb * 1024 * 1024;
    VHD_Footer footer = {};

    // Fill footer fields
    std::memcpy(footer.cookie, "conectix", 8);
    footer.features = bswap32(0x00000002);
    footer.version = bswap32(0x00010000);
    footer.data_offset = bswap64(0xFFFFFFFFFFFFFFFF);
    footer.timestamp = bswap32(static_cast<uint32_t>(std::time(nullptr) - 946684800)); // seconds since 2000
    std::memcpy(footer.creator_app, "CUST", 4);
    footer.creator_ver = bswap32(0x00010000);
    std::memcpy(footer.creator_os, "Wi2k", 4);
    footer.original_size = bswap64(size);
    footer.current_size = bswap64(size);
    footer.disk_geometry = bswap32(0x003F0F01); // fake CHS geometry
    footer.disk_type = bswap32(2); // fixed disk
    std::memset(footer.unique_id, 0xA5, 16); // dummy GUID
    footer.saved_state = 0;

    // Compute checksum (must be calculated with checksum = 0)
    footer.checksum = 0;
    footer.checksum = bswap32(vhd_checksum(reinterpret_cast<uint8_t*>(&footer), 512));

    std::ofstream file(path, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file.\n";
        return;
    }

    // Write empty data block (just zeroes)
    std::vector<uint8_t> zero_block(size, 0);
    file.write(reinterpret_cast<char*>(zero_block.data()), zero_block.size());

    // Write footer
    file.write(reinterpret_cast<const char*>(&footer), sizeof(VHD_Footer));
    file.close();

    std::cout << "VHD file created: " << path << "\n";
}
