#include "StartupHandler.hpp"
#include "easylogging++.h"

#include <getopt.h>
#include <memory>
#include <optional>
#include <stdexcept>

namespace utils {

    static int verbose = 0;

    void StartupHandler::initEasyLogging() {
        el::Configurations conf("conf/easylogging.conf");
        el::Loggers::reconfigureLogger("default", conf);
        el::Loggers::reconfigureAllLoggers(conf);
        LOG(INFO) << "Easylogging initialized!";
    }

    std::optional<std::string> StartupHandler::getOptions(int argc, char *argv[]) {
        LOG(INFO) << "Parsing options...";
        static const struct option long_options[] = {
                /* These options set a flag. */
                {"verbose", no_argument, &verbose, 1},
                {"brief", no_argument, &verbose, 0},
                {"help", no_argument, nullptr, 'h'},
                {"version", no_argument, nullptr, 'V'},
                {"test", required_argument, nullptr, 0},
                nullptr
        };

        do {
            int optIndex = -1;
            std::unique_ptr<struct option> opt = nullptr;
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
                default:
                    std::cout << "I shouldnt have been here!\n";
                    break;
            }
        } while (true);

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
