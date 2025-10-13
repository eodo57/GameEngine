#include "core/Application.h"
#include "core/Logger.h"

#include <cstdlib>    // For EXIT_SUCCESS and EXIT_FAILURE
#include <exception>  // For std::exception, which is a better fit here

int main() {
    // The Logger is a static class and does not require initialization
    
    // Create the main application instance
    Application app{};

    try {
        // Run the application's main loop
        app.run();
    } catch (const std::exception& e) {
        // Log any uncaught exceptions using the 'error' severity level
        Logger::error(e.what());
        return EXIT_FAILURE;
    }

    // Clean shutdown
    Logger::info("Application shutting down successfully.");
    return EXIT_SUCCESS;
}

