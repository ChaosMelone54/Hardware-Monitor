/*Copyright (C) <2026>  <ChaosMelone54>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

Code used from: https://github.com/improvess/cpp-linux-system-stats
*/

#pragma once

#include "include.h"

namespace get_disk_stats {
    inline float get_disk_usage(const std::string & disk) {
        struct statvfs diskData;

        statvfs(disk.c_str(), &diskData);

        auto total = diskData.f_blocks;
        auto free = diskData.f_bfree;
        auto diff = total - free;

        float result = static_cast<float>(diff) / total;

        return result;
    }
}

namespace get_memory_stats {
    struct Memory_stats {
        int total_memory;
        int available_memory;
        int total_swap;
        int free_swap;

        float get_memory_usage() const {
            const float result = static_cast<float>(total_memory - available_memory) / total_memory;
            return result;
        }

        float get_swap_usage() const {
            const float result = static_cast<float>(total_swap - free_swap) / total_swap;
            return result;
        }
    };

    inline int get_val(const std::string &target, const std::string content) {
        int result = -1;
        std::size_t start = content.find(target);

        if(start != std::string::npos) {
            int begin = start + target.length();
            std::size_t end = content.find("kB", start);
            std::string substr = content.substr(begin, end - begin);
            result = std::stoi(substr);
        }
        return result;
    }

    inline Memory_stats read_memory_data() {
        Memory_stats result;
        std::ifstream proc_mem("/proc/meminfo");

        if(proc_mem.good()) {
            std::string content((std::istreambuf_iterator<char>(proc_mem)),
                                std::istreambuf_iterator<char>());

            result.total_memory = get_val("MemTotal:", content);
            result.total_swap = get_val("SwapTotal:", content);
            result.free_swap = get_val("SwapFree:", content);
            result.available_memory = get_val("MemAvailable:", content);
        }
        proc_mem.close();

        return result;
    }
}
