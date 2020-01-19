#pragma once

#include <ostream>


enum class Priority {
    Info, Warning, Error, Critical
};

class Logger {
public:
    Logger(Priority priority);

    std::ostream& operator<<(const std::string& msg);

private:
    Priority m_priority;
};