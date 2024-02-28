#include "StartupHandler.hpp"
#include "easylogging++.h"

//https://github.com/Chunde/getopt-for-windows
#ifdef IS_WINDOWS
#include <xgetopt.h>
#else
#include <getopt.h>
#endif

#include <iostream>
#include <stdexcept>

INITIALIZE_EASYLOGGINGPP

namespace WIP {
void exampleEasyLogging();
}

#define OS @OS@

/**
 * \brief Main function
 *
 * \details
 * Codeconvention:
 * - Formatter: astyle
 *
 * \todo
 * - Github
 * - "Dev-Ops"
 * - Doxygen settings
 * - Template-Comment
 * - Template-Header-Comment
 **/
int main(int argc, char* argv[])
{
    /// \note Debug
#ifdef IS_LINUX
    std::cout << "Linux\n\n" << std::endl;
#elif IS_WINDOWS
    std::cout << "Windows\n\n" << std::endl;
#else
    std::cout << "Unknown OS\n\n" << std::endl;
#endif
    utils::StartupHandler::initEasyLogging();

    if (argc <= 1) {
        LOG(WARNING) << "No arguments provided, exiting!";
        std::cout << "No arguments provided, exiting!\n";
        return 1;
    }

    std::cout << "Hello, World!" << std::endl;
    std::optional<std::string> filename;

    try {
        filename = utils::StartupHandler::getOptions(argc, argv);
    }
    catch (const std::invalid_argument &e) {
        LOG(WARNING) << "Caught invalid argument: " << e.what();
        std::cout << "Invalid argument: " << e.what() << std::endl;
    }

    if (!filename.has_value()) {
        LOG(ERROR) << "No filename given! Exiting...";
        std::cerr << "No filename given!\nExiting...\n";
        return 1;
    }

    LOG(INFO) << "Filename received: " << filename.value();
    std::cout << "Filename: " << filename.value() << std::endl;
    LOG(INFO) << "Further processing...";
    std::cout << "Further processing..." << std::endl;
    LOG(INFO) << "Application exiting!";
    return 0;
}
