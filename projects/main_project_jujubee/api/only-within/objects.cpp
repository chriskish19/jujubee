#include NAMES_INCLUDE
#include OBJECTS_INCLUDE_PATH

namespace juju_api {
	juju::window_logger* wl_sys_logger = nullptr;

	std::thread* wl_thread_p = nullptr;

	std::unordered_set<jfs::character>* jfs_drive_letters = nullptr;
}