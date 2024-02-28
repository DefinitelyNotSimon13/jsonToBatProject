#include "StartupHandler.hpp"
#include "easylogging++.h"
#include "json/json.h"

#ifdef IS_WINDOWS
/**
 *  \note
 *  Windows port for getopt from:
 *  https://github.com/Chunde/getopt-for-windows
 **/
#include <xgetopt.h>
#else
#include <getopt.h>
#endif

#include <iostream>
#include <stdexcept>
#include <format>
#include <string>
#include <string_view>
#include <sstream>

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
    Json::Value root;
    std::ifstream file(filename.value());
    Json::Reader reader;
    reader.parse(file, root);
    auto memberNames = root.getMemberNames();
    std::cout << "Memebers: " << std::endl;

    for (auto name : memberNames) {
        std::cout << "    \"" << name << "\" :" << "\n";

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
    constexpr std::string_view exeCommand = "{}&&\\\n";
    constexpr std::string_view envCommand = "set {}={} &&\\\n";
    constexpr std::string_view pathCommand = "set path=%path%;{}";
    constexpr std::string_view additionalPathCommand = "{};\\\n";
    std::stringstream additionalPath;
    int counter = 0;
    std::cout << "Entries:\n";

    batchFile << "@ECHO OFF\nC:\\Windows\\System32\\cmd.exe /k\n\"";

    for (auto entry : root["entries"]) {
        std::cout << "Entry " << counter << ":\n";
        auto keys = entry.getMemberNames();

        for (auto key : keys) {
            std::cout << "    " << key << ": " << entry[key].asString() << "\n";
        }

        if (entry["type"].asString() == "EXE") {
            batchFile << std::format(exeCommand, entry["command"].asString());
        }
        else if (entry["type"].asString() == "ENV") {
            batchFile << std::format(envCommand, entry["key"].asString(),
                                     entry["value"].asString());
        }
        else if (entry["type"].asString() == "PATH") {
            additionalPath << std::format(additionalPathCommand, entry["path"].asString());
        }
        else {
            batchFile << "\nCommand doesnt exist yet\n";
        }

        ++counter;
    }

    if (additionalPath.str() != "") {
        batchFile << std::format(pathCommand, additionalPath.str());
    }

    batchFile << "\"\n@ECHO ON";
    batchFile.close();
    LOG(INFO) << "Application exiting!";
    return 0;
}
