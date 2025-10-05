#include "utils.h"

#include <ctime>
#include <iomanip>
#include <sstream>
#include <chrono>

//gets current time to use as a timestamp for events
std::string getCurrentTime() {
    auto now = std::chrono::system_clock::now(); // get current time as a time point

    std::time_t current_time = std::chrono::system_clock::to_time_t(now); // convert it for better formatting

    std::tm* tm_ptr = std::localtime(&current_time); // tm struct
    
    std::ostringstream oss;
    oss << std::put_time(tm_ptr, "%Y-%m-%d %H:%M:%S");

    return oss.str();
}