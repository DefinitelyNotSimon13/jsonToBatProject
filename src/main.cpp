#include "JSONData.hpp"
#include "StartupHandler.hpp"
#include "JSONHandler.hpp"
#include "BatchCreator.hpp"

#include <easylogging++.h>
#include <getopt.h>
#include <iostream>
#include <json/json.h>
#include <sstream>
#include <stdexcept>
#include <string>

/// \bug Initielizes to early for config file to be loaded
INITIALIZE_EASYLOGGINGPP

/**
 * \brief Main function
 *
 * \details
 * This is the main function for the application, The application is designed
 * to parse a json file and create a batch file from it.
 * Further more it provides a CLI to help the user to interact with the
 * application.
 *
 *
 *  \bug Getopt is not working on Windows.
 **/
int main(int argc, char *argv[]) {
    std::cout << "Starting Application..." << std::endl;
    utils::StartupHandler::initEasyLogging();

    if (argc <= 1) {
        LOG(WARNING) << "No arguments provided, exiting!";
        std::cout << "No arguments provided, exiting!\n";
        return 1;
    }

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

    // Initialize the JSONHandler with the file(name)
    json::JSONHandler jsonHandler(filename.value());
    // Get a JSONData object from the JSONHandler
    std::shared_ptr<json::JSONData> jsonData = jsonHandler.getJSONData();
    // Print the outputfile as a test
    std::cout << "Outputfile: " << jsonData->getOutputFile() << std::endl;

    batch::BatchCreator batchCreator(jsonData);
    /// \note maybe close in creator? But this leaves possibility to add more
    /// stuff - why?
    std::shared_ptr<std::ofstream> batchFile = batchCreator.createBatchFile();
    batchFile->close();

    LOG(INFO) << "Application exiting!";
    return 0;
}
