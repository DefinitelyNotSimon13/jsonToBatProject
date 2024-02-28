#ifndef STARTUPHANDLER_HPP
#define STARTUPHANDLER_HPP

#include <getopt.h>
#include <optional>
#include <string>

/**
 * \brief Namespace for utility functions
 *
 * \details
 * This namespace contains utility functions for the application.
 * Currently, it contains the StartupHandler class.
 **/
namespace utils {
/**
 * \brief Handles startup task for the application.
 *
 * \details
 * This class provides functionality for the startup of the application.
 * Currently it initializes easylogging and parses given options.
 *
 * \note I think this class should stay static - Simon
 *
 **/
class StartupHandler {
  public:
    /**
     * \brief Initialize easylogging
     *
     * \details
     * This function initializes easylogging with the configuration file
     * "$SOURCE/conf/easylogging.conf".
     *
     * \todo
     * - Improve easylogging configuration
     *
     * \bug
     * Easylogging conf only recognized when running application
     *from source dir
     **/
    static void initEasyLogging();

    /**
    * \brief Get options from command line
    *
    * \details
    * This function parses the command line options and returns the filename
    * given as an argument. It can hadle short, long and "regular" arguments.
    * Currently, the following options are supported:
    * - -h, --help: Show help
    * - -V, --version: Show version
    * - --verbose: Set verbose flag
    * - --brief: Unset verbose flag
    * - --test: Test
    *
    * \todo
    * - Implement functionality for the options.
    * - Implement/Add more options.
    * - Shorten function and outsource functionality to other functions.
    *
    * \bug
    * Global verbose flag is not working.
    *
    * \param argc Number of arguments
    * \param argv Arguments
    *
    * \return Returns either the filename or nothing.
    *
    * \throws std::invalid_argument If more than one filename is given.
    **/
    static std::optional<std::string> getOptions(int argc, char* argv[]);

  private:
    /**
     * \brief Constructor (private)
     *
     * \details
     * This class should not be instantiated.
     **/
    StartupHandler() = default;

    /**
     * \brief Copy constructor (deleted)
     *
     * \details
     * This class should not be instantiated.
     **/
    StartupHandler(const StartupHandler &) = delete;

    /**
     * \brief Assignment operator (deleted)
     *
     * \details
     * This class should not be instantiated.
     **/
    StartupHandler &operator=(const StartupHandler &) = delete;

};
} // namespace utils
#endif // STARTUPHANDLER_HPP
