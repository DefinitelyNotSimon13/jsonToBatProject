#ifndef JSONHANDLER_HPP
#define JSONHANDLER_HPP

#include "JSONData.hpp"
#include "json/value.h"
#include <memory>

/**
 * \brief json namespace
 * \details
 * The json namespace contains all classes and functions related to the json
 * parsing and handling.
 *
 * \bug
 * Name to similiar to "Json" namespace from the json library.
 **/
namespace json {

/**
 * \brief JSONHandler class
 *
 * \details
 * The JSONHandler class is responsible for parsing a json file and creating a
 * JSONData object from it when requested.
 * It assigns all necessary values to the JSONData object. Most of the error
 * handling is done in the JSONData object.
 *
 **/
class JSONHandler {
  public:
    /**
     * \brief Constructor
     *
     * \details
     * The constructor calls the parseFile function to parse the file and adds it
     * to the corresponding member variable.
     *
     * \param filename The filename to parse
     **/
    JSONHandler(const std::string &filename);

    /**
     * \brief Retrieve the JSONData object
     *
     * \details
     * The function takes the necesarry steps to create a JSONData object and
     * then returns it
     *
     * \return std::shared_ptr<JSONData> The JSONData object
     **/
    std::shared_ptr<JSONData> getJSONData();

  private:
    /**
     * \brief Parse a file
     *
     * \details
     * The function takes a filename and parses the file into a Json::Value
     * object.
     *
     * \param filename The filename to parse
     * \return std::shared_ptr<Json::Value> The parsed file
     **/
    std::shared_ptr<Json::Value> parseFile(const std::string &filename);

    /**
     * \brief Assigns the output file to the JSONData object
     *
     * \note
     * Error handling is done in the JSONData object
     **/
    void assignOutputFile();

    /**
     * \brief Assigns the hide shell value to the JSONData object
     *
     * \note
     * There is no real error handling for this value, it defaults to false
     **/
    void assignHideShell();

    /**
     * \brief Assigns the application to the JSONData object
     *
     * \note
     * How should error handling be done? Value can be empty, but what about
     * null vs ""?
     **/
    void assignApplication();

    /**
     * \brief Assigns the entries to the JSONData object
     *
     * \details
     * The function loops through the entries and calls the corresponding
     * function to assign the entry to the JSONData object
     *
     * \throws std::runtime_error If the entry type is unknown
     * \note
     * Other error handling is done in the JSONData object
     **/
    void assignEntries();

    /**
     * \brief Assigns a command to the JSONData object
     *
     * \details
     * The function takes a Json::Value object and assigns the command to the
     * JSONData object
     *
     * \param entry The entry to assign
     *
     * \note
     * Error handling is done in the JSONData object
     **/
    void assignCommand(const Json::Value &entry);

    /**
     * \brief Assigns an environment variable to the JSONData object
     *
     * \details
     * The function takes a Json::Value object and assigns a tuple of the
     * environment variable to the JSONData object
     *
     * \param entry The entry to assign
     *
     * \note
     * Error handling is done in the JSONData object
     **/
    void assignEnvironmentVariable(const Json::Value &entry);

    /**
     * \brief Assigns a path value to the JSONData object
     *
     * \details
     * The function takes a Json::Value object and assigns the path value to the
     * JSONData object
     *
     * \param entry The entry to assign
     *
     * \note
     * Error handling is done in the JSONData object
     **/
    void assignPathValue(const Json::Value &entry);

    /**
     * \brief Creates a JSONData object
     *
     * \details
     * The function creates the JSONData object and calls all the necessary
     * methods to assign the values to the object.
     *
     * \return std::shared_ptr<JSONData> The JSONData object
     **/
    std::shared_ptr<JSONData> createJSONData();

    std::shared_ptr<Json::Value> root;
    std::shared_ptr<JSONData> data;
};
} // namespace json

#endif // JSONHANDLER_HPP
