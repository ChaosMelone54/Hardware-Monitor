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


#include "include.h"
#include "monitor_cpu.h"
#include "monitor_storage_memory.h"

using namespace get_cpu_stats;
using namespace get_disk_stats;
using namespace get_memory_stats;

int main() {
    CPU_stats t1 = read_cpu_data();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    CPU_stats t2 = read_cpu_data();


    std::cout << "CPU: " << get_CPU_name() << std::endl;
    std::cout << "CPU physical cores: " << get_cpu_physical_core_count() << std::endl;
    std::cout << "CPU logical cores: " << get_cpu_logical_core_count() << std::endl;
    std::cout << "CPU usage is: " << (100.0f * get_cpu_usage(t1, t2)) << "%\n";
    //std::cout << "CPU temperature: " << get_thermal_zone_temperature(find_thermalzone_index()) << std::endl;

    auto memory_data = read_memory_data();
    std::cout << "Memory\nSwap Usage: " << (100.0f * memory_data.get_swap_usage()) << "%\n";
    std::cout << "Memory usage: " << (100.0f * memory_data.get_memory_usage()) << "%\n";

    std::cout << "Disk\nDisk usage: " << (100.0f * get_disk_usage("/")) << "%\n";
}
