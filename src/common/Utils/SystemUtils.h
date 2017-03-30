//
// Created by 云海 on 2017/3/30.
//

#ifndef DUBBOC_SYSTEMUTILS_H
#define DUBBOC_SYSTEMUTILS_H

#include <string>
#include <cstring>

#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif

#include <unistd.h>

namespace DUBBOC {
    namespace COMMON {
        class SystemUtils {
        public:
#ifdef __APPLE__

          static std::string crossPlatformGetExePath() {
                char path[1024] = {0};

                uint32_t size = sizeof(path);
                if (_NSGetExecutablePath(path, &size) != 0) {
                    return "";
                }
                size = static_cast<uint32_t >(strlen(path));
                while (size && path[--size] != '/');
                path[size] = '\0';

                return std::string(path);
            }

#elif __linux
            static std::string crossPlatformGetExePath() {
            char path[1024] = {0};

            size_t result = readlink("/proc/self/exe", path, sizeof(path));
            if (result == -1) {
                return "";
            }

            while (result && path[--result] != '/');
            path[result] = '\0';

            return std::string(path);
        }
#endif

        };
    }
}
#endif //DUBBOC_SYSTEMUTILS_H
