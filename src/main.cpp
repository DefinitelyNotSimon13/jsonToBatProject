#include "easylogging++.h"
#include <iostream>

//! Includes for test
#include "json/json.h"
#include "catch2/catch_all.hpp"

INITIALIZE_EASYLOGGINGPP

namespace WIP {
void exampleEasyLogging();
}

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
int main(int argc, char *argv[]) {
  WIP::exampleEasyLogging();
  std::cout << "Hello, World!" << std::endl;
  return 0;
}

/**
 * \brief Namespace for work in progress
 *
 * \details
 * - This namespace is for code that is not finished yet
 * - It is used to keep the main namespace clean
 **/
namespace WIP {
/**
 * \brief Example of how to use easylogging with a configuration file
 *
 * \details
 * - This function is an example of how to use easylogging
 * - The configuration file is located in ../conf
 * - Before proper integration, config has to be done properly
 *
 * \todo 
 * - Configure easylogging properly
 * - outsource easylogging config
 *  - e.g. startup class?
 **/
void exampleEasyLogging() {
  el::Configurations conf("conf/easylogging.conf");
  el::Loggers::reconfigureLogger("default", conf);
  el::Loggers::reconfigureAllLoggers(conf);

  LOG(INFO) << "My first info log using default logger";
}
} // namespace WIP
