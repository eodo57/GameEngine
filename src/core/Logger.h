#pragma once

#include <string>
#include <sstream>

// Enum to represent different levels of logging severity.
enum class LogLevel {
    Info,
    Warning,
    Error
};

class Logger {
public:
    // The main logging function.
    static void log(LogLevel level, const std::string& message);

    // Convenience functions for each log level.
    static void info(const std::string& message);
    static void warn(const std::string& message);
    static void error(const std::string& message);

    // A more advanced version that allows for stream-based logging like std::cout.
    // Example: Logger::log(LogLevel::Info) << "Value is " << 5;
    class LogStream {
    public:
        LogStream(LogLevel level);
        ~LogStream();

        template<typename T>
        LogStream& operator<<(const T& value) {
            buffer << value;
            return *this;
        }

    private:
        LogLevel level;
        std::stringstream buffer;
    };

    // The static method that returns a LogStream object.
    static LogStream log(LogLevel level);

private:
    // Helper function to get the current timestamp as a string.
    static std::string getCurrentTime();
};
