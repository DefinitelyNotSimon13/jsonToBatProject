#include "StartupHandler.hpp"
#include "LoggingWrapper.hpp"
#include "Verbose.hpp"

#include <getopt.h>
#include <memory>
#include <optional>
#include <stdexcept>

namespace utils {

void StartupHandler::initEasyLogging() {
  el::Configurations conf("conf/easylogging.conf");
  el::Loggers::reconfigureLogger("default", conf);
  el::Loggers::reconfigureAllLoggers(conf);
  LOG_INFO << "Easylogging++ initialized\n";
}

std::optional<std::string> StartupHandler::getOptions(int argc, char *argv[]) {
  LOG_INFO << "Parsing options...\n";
  int verbose = 0;
  static const struct option long_options[] = {
      /* These options set a flag. */
      {"verbose", no_argument, &verbose, 1},
      {"brief", no_argument, &verbose, 0},
      {"help", no_argument, nullptr, 'h'},
      {"version", no_argument, nullptr, 'V'},
      {"test", required_argument, nullptr, 0},
      nullptr};

  do {
    int optIndex = -1;
    std::unique_ptr<struct option> opt = nullptr;
    auto result = getopt_long(argc, argv, "hV", long_options, &optIndex);

    if (result == -1) {
      break;
    }

    switch (result) {
    case '?':
      LOG_INFO << "Unknown option given\n";
      break;

    case 'h':
      LOG_INFO << "Help option given\n";
      break;

    case 'V':
      LOG_INFO << "Version option given\n";
      std::cout << "long V\n";

    case 0:
      LOG_INFO << "Option without short version given...\n";
      opt = std::make_unique<struct option>(long_options[optIndex]);
      LOG_INFO << "Option " << opt->name << " given\n";

      if (opt->has_arg == required_argument) {
        LOG_INFO << "Argument: " << optarg << "\n";
      }
      break;
    default:
      utils::log(utils::LogLevel::FATAL) << "Default case reached\n";
      break;
    }
  } while (true);

  LOG_INFO << "Parsing options done\n";
  LOG_INFO << "Setting verbose flag...\n";
  VerboseHandler::getInstance().setVerbose(verbose);

  LOG_INFO << "Parsing other arguments ...\n";
  std::optional<std::string> filename = {};
  while (optind < argc) {
    if (filename.has_value()) {
      LOG_ERROR << "Only one filename can be given right now!\n";
      throw std::invalid_argument("Only one filename can be given!\n");
    }

    LOG_INFO << "Filename set to: " << argv[optind] << "\n";
    filename = std::string(argv[optind++]);
  }

  return filename;
}
} // namespace utils
