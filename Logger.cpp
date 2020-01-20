#include "Logger.h"

#include <iostream>


Logger::Logger(Priority priority): m_priority(priority) {}

std::ostream& Logger::operator<<(const std::string& msg)
{
    switch (m_priority) {
        case Priority::Info:
            std::cout << "INFO: " << msg;
            return std::cout;
        case Priority::Warning:
            std::cerr << "WARN: " << msg;
            break;
        case Priority::Error:
            std::cerr << "ERROR: " << msg;
            break;
        case Priority::Critical:
            std::cerr << "FATAL: " << msg;
            break;
    }
    return std::cerr;
}


