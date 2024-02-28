#include "JSONData.hpp"
#include "StartupHandler.hpp"
#include "JSONHandler.hpp"

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
int main(int argc, char* argv[])
{
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
    /**
     * \note json parsing seems simple
     * edgecases?
     * basically just treat as array/map
     **/
    // Initialize the JSONHandler with the file(name)
    json::JSONHandler jsonHandler(filename.value());
    // Get a JSONData object from the JSONHandler
    std::shared_ptr<json::JSONData> jsonData = jsonHandler.getJSONData();
    // Print the outputfile as a test
    std::cout << "Outputfile: " << jsonData->getOutputFile() << std::endl;
    // \note Code below only for me to see how I did it this morning
    /*
    for (auto name : memberNames) {
      std::cout << "    \"" << name << "\" :"
                << "\n";

      switch (root[name].type()) {
      case Json::ValueType::arrayValue:
        std::cout << "          Type: array\n";
        break;

      case Json::ValueType::booleanValue:
        std::cout << "          Type: boolean\n";
        break;

      case Json::ValueType::intValue:
        std::cout << "          Type: int\n";
        break;

      case Json::ValueType::realValue:
        std::cout << "          Type: real\n";
        break;

      case Json::ValueType::stringValue:
        std::cout << "          Type: string\n";
        break;

      case Json::ValueType::uintValue:
        std::cout << "          Type: uint\n";
        break;

      case Json::ValueType::nullValue:
        std::cout << "          Type: null\n";
        break;

      default:
        std::cout << "          Type: unknown\n";
        break;
      }
    }

    // Not error proof
    std::cout << "Outputfile: " << root["outputfile"].asString() << "\n";
    std::string outputfile = "output/" + root["outputfile"].asString();
    std::fstream batchFile;
    batchFile.open(outputfile, std::ios::out);
    batchFile << "#This is a test\n";
    // Very not error proof
    std::stringstream additionalPath;
    int counter = 0;
    std::cout << "Entries:\n";

    batchFile << "@ECHO OFF\nC:\\Windows\\System32\\cmd.exe /k\n\"";

    for (const auto entry : root["entries"]) {
      std::cout << "Entry " << counter << ":\n";

      for (const auto key : entry.getMemberNames()) {
        std::cout << "    " << key << ": " << entry[key].asString() << "\n";
      }

      if (entry["type"].asString() == "EXE") {
        batchFile << entry["command"].asString() << "&&\\\n";
      } else if (entry["type"].asString() == "ENV") {
        batchFile << "set " << entry["key"].asString() << "="
                  << entry["value"].asString() << "&&\\\n";
      } else if (entry["type"].asString() == "PATH") {
        additionalPath << entry["path"].asString() << ";\\\n";
      } else {
        batchFile << "\nCommand doesnt exist yet\n";
      }

      ++counter;
    }

    if (additionalPath.str() != "") {
      batchFile << "set path=%path%" << additionalPath.str();
    }

    batchFile << "\"\n@ECHO ON";
    batchFile.close();
    */
    LOG(INFO) << "Application exiting!";
    return 0;
}
