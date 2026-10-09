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

namespace get_cpu_stats {

    struct CPU_stats {
        int user;
        int nice;
        int system;
        int idle;
        int iowait;
        int irq;
        int softirq;
        int steal;
        int guest;
        int guest_nice;

        int get_total_idle() const { return idle + iowait; }
        int get_total_active() const { return user + nice + system + irq + softirq + steal + guest + guest_nice; }
    };

    inline CPU_stats read_cpu_data() {
        CPU_stats result;
        std::ifstream proc_stat("/proc/stat");

        if(proc_stat.good()) {
            std::string line;
            getline(proc_stat, line);

            unsigned int *stats_p = (unsigned int *)&result;
            std::stringstream iss(line);
            std::string cpu;
            iss >> cpu;
            while(iss >> *stats_p) {
                stats_p++;
            };
        }
        proc_stat.close();

        return result;
    }

    inline float get_cpu_usage(const CPU_stats &first, const CPU_stats &second) {
        const float active_time = static_cast<float>(second.get_total_active() - first.get_total_active());
        const float idle_time = static_cast<float>(second.get_total_idle() - first.get_total_idle());
        const float total_time = active_time + idle_time;
        return active_time / total_time;
    }

    inline int find_thermalzone_index() {
        int result = 0;
        bool stop = false;

        for(int i = 0; !stop && i < 20; i++) {
            std::ifstream thermal_file("/sys/class/thermal/cooling_device" + std::to_string(i) + "/type");

            if(thermal_file.good()) {
                std::string line;
                getline(thermal_file, line);

                if(line.compare("x86_pkg_temp")) {
                    result = i;
                    stop = true;
                }
            }
            else {
                stop = true;
            }

            thermal_file.close();
        }
        return result;
    }

    inline int get_thermal_zone_temperature(int thermal_index) {
        int result = -1;
        std::ifstream thermal_file("/sys/class/thermal/thermal_zone" + std::to_string(thermal_index) + "/temp");

        if(thermal_file.good()) {
            std::string line;
            getline(thermal_file, line);

            std::stringstream iss(line);
            iss >> result;
        }
        else {
            throw std::invalid_argument(std::to_string(thermal_index) + "doesn't refer to a valid thermal zone");
        }

        thermal_file.close();
        return result;
    }

    //CPU name
    inline std::string get_CPU_name() {
        std::ifstream CPU_file("/proc/cpuinfo");
        std::string line;

        //Search for cpu model name
        while(std::getline(CPU_file, line)) {
            if(line.rfind("model name", 0) == 0) {
                //Copies everything after ":" and returns it
                auto pos = line.find(':');
                if(pos != std::string::npos) {
                    return line.substr(pos + 2);
                }
            }
        }
        //If unseccessful
        return "Unknown CPU";
    }

    inline int get_cpu_physical_core_count() {
        namespace fs = std::filesystem;

        std::set<std::pair<int, int>> cores;

        const fs::path cpu_root{"/sys/devices/system/cpu"};

        //Searches every entry which has cpu in it
        for(const auto& entry : fs::directory_iterator(cpu_root)) {
            const std::string name = entry.path().filename().string();

            //Sort out entries which are not called cpu0, cpu1 and so on
            if(name.size() < 4 || name.compare(0, 3, "cpu") != 0)
                continue;

            if(!std::all_of(name.begin() + 3, name.end(),
                [](unsigned char c) { return c >= '0' && c <= '9'; }))
                continue;

            //Gets core id and physical package id
            const fs::path topology = entry.path() / "topology";
            std::ifstream package_file(topology / "physical_package_id");
            std::ifstream core_file(topology / "core_id");

            //If values were successfully red, pair comes in set. If multiple cores have the same packet and core id it will be saved only once
            int package_id, core_id;
            if(package_file >> package_id && core_file >> core_id)
                cores.emplace(package_id, core_id);
        }

        //Gets the count of all pairs
        return cores.size();
    }

    inline int get_cpu_logical_core_count() {
        return std::thread::hardware_concurrency();
    }
}
