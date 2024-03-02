#include "BatchCreator.hpp"
#include "CliHandler.hpp"
#include "JSONData.hpp"
#include "JSONHandler.hpp"
#include "LoggingWrapper.hpp"
#include "StartupHandler.hpp"

#include <easylogging++.h>
#include <filesystem>
#include <getopt.h>
#include <iostream>
#include <json/json.h>
#include <stdexcept>
#include <string>

/// \note Temporary till logger is fixed
#define FL std::flush

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
  std::cout << cli::CLEAR_TERMINAL;
  utils::StartupHandler::initEasyLogging();
  LOG_INFO << cli::ITALIC << "Starting Application..." << cli::RESET << "\n\n";
  if (argc <= 1) {
    LOG_WARNING << "No arguments provided, exiting!\n";
    return 1;
  }

  std::optional<std::string> filename;

  try {
    filename = utils::StartupHandler::getOptions(argc, argv);
  } catch (const std::invalid_argument &e) {
    LOG_ERROR << "Caught invalid argument: " << e.what() << std::endl;
    return 1;
  }

  if (!filename.has_value()) {
    LOG_ERROR << "No filename provided, exiting!\n";
    return 1;
  }

  OUTPUT << cli::UNDERLINE << "Processing file: " << cli::ITALIC
         << filename.value() << cli::RESET << "\n";

  // Initialize the JSONHandler with the file(name)
  json::JSONHandler jsonHandler(filename.value());
  // Get a JSONData object from the JSONHandler
  std::shared_ptr<json::JSONData> jsonData = jsonHandler.getJSONData();
  // Print the outputfile as a test
  const std::string outputfile = jsonData->getOutputFile();
  OUTPUT << "- Creating Outputfile: " << cli::ITALIC << outputfile << cli::RESET
         << "\n";

  batch::BatchCreator batchCreator(jsonData);
  /// \note maybe close in creator? But this leaves possibility to add more
  /// stuff - why?
  std::shared_ptr<std::ofstream> batchFile = batchCreator.createBatchFile();

  std::filesystem::path path = std::filesystem::current_path();
  OUTPUT << "- Batch file created at: " << cli::ITALIC << path.string() << "/"
         << outputfile << cli::RESET << "\n\n";

  batchFile->close();

  OUTPUT << cli::GREEN_FG << "Done! Exiting application...\n" << cli::RESET;
  return 0;
}
