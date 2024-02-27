#include "StartupHandler.hpp"
#include "easylogging++.h"
#include "globals.cpp"
#include <getopt.h>
#include <memory>
#include <optional>
#include <stdexcept>

namespace utils {
void StartupHandler::initEasyLogging()
{
    el::Configurations conf("conf/easylogging.conf");
    el::Loggers::reconfigureLogger("default", conf);
    el::Loggers::reconfigureAllLoggers(conf);
    LOG(INFO) << "Easylogging initialized!";
}


std::optional<std::string> StartupHandler::getOptions(int argc, char* argv[])
{
    LOG(INFO) << "Parsing options...";
    static const struct option long_options[] = {
        /* These options set a flag. */
        {"verbose", no_argument, &globals::verbose, 1},
        {"brief", no_argument, &globals::verbose, 0},
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'V'},
        {"test", required_argument, 0, 0},
        0
    };

    do {
        int optIndex = -1;
        std::unique_ptr<struct option> opt = 0;
        auto result = getopt_long(argc, argv, "hV", long_options, &optIndex);

        if (result == -1) {
            break;
        }

        switch (result) {
            case '?':
                LOG(INFO) << "Unknown option given";
                std::cout << "Not know\n";
                break;

            case 'h':
                LOG(INFO) << "Help option given";
                std::cout << "long h\n";
                break;

            case 'V':
                LOG(INFO) << "Version option given";
                std::cout << "long V\n";

            case '0':
                opt = std::make_unique<struct option>(long_options[optIndex]);
                LOG(INFO) << "Option " << opt->name << " given";

                if (opt->has_arg == required_argument) {
                    LOG(INFO) << "Argument: " << optarg;
                }

                break;
        }
    } while (1);

    LOG(INFO) << "Parsing options done";
    std::optional<std::string> filename = {};
    LOG(INFO) << "Parsing other arguments...";

    while (optind < argc) {
        if (filename.has_value()) {
            LOG(ERROR) << "Only one filename can be given!";
            throw std::invalid_argument("Only one filename can be given!\n");
        }

        LOG(INFO) << "Filename set to: " << argv[optind];
        filename = std::string(argv[optind++]);
    }

    return filename;
}
} // namespace utils
