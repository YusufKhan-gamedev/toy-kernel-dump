#include <system/syscalls.h>
#include "../../../kernel/src/fs/vfs.h"

int open(const char *pathname) {
    return (int)vfs::open("/", pathname);
}

int close(int fd) {
    return (int)vfs::close((uint64_t)fd);
}