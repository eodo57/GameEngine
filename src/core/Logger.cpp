#include "Logger.h"
#include <iostream>
#include <chrono>
#include <iomanip>

// } // end namespace core
// Ensure the implementation is in the same namespace as the declaration, if any.
// For example, if Logger is in the 'core' namespace, wrap the following code:

// namespace core {

void Logger::log(LogLevel level, const std::string& message) {
    // Select the appropriate output stream (std::cout for info, std::cerr for others)
    std::ostream& stream = (level == LogLevel::Info) ? std::cout : std::cerr;

    // Output the formatted log message
    switch (level) {
        case LogLevel::Info:
            stream << "[INFO] ";
            break;
        case LogLevel::Warning:
            stream << "[WARNING] ";
            break;
        case LogLevel::Error:
            stream << "[ERROR] ";
            break;
    }
    stream << "[" << getCurrentTime() << "] " << message << std::endl;
}

void Logger::info(const std::string& message) {
    log(LogLevel::Info, message);
}

void Logger::warn(const std::string& message) {
    log(LogLevel::Warning, message);
}

void Logger::error(const std::string& message) {
    log(LogLevel::Error, message);
}

// --- Implementation for the LogStream subclass ---

Logger::LogStream::LogStream(LogLevel lvl) : level(lvl) {}

// When the LogStream object is destroyed (goes out of scope),
// it flushes its buffered message to the main log function.
Logger::LogStream::~LogStream() {
    Logger::log(level, buffer.str());
}

// This is the static method that kicks off the stream-based logging.
Logger::LogStream Logger::log(LogLevel level) {
    return LogStream(level);
}


std::string Logger::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}
