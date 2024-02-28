#include "JSONData.hpp"
#include <easylogging++.h>
#include <ostream>
#include <stdexcept>

namespace json {
void JSONData::setOutputFile(std::string &outputfile)
{
    if (outputfile.empty()) {
        LOG(ERROR) << "Tried to set empty outputfile!";
        throw std::invalid_argument("Outputfile cannot be empty");
    }

    if (!this->outputfile.empty()) {
        LOG(ERROR) << "Outputfile already set!";
        throw std::invalid_argument("Outputfile already set");
    }

    if (outputfile.find(".bat") == std::string::npos ||
        outputfile.find(".bat") != outputfile.size() - this->suffixLength) {
        outputfile += ".bat";
        std::cout << "Outputfile does not have .bat suffix, adding it now: "
                  << outputfile << std::endl;
        LOG(WARNING) << "Outputfile does not have .bat suffix, adding it now: "
                     << outputfile;
    }

    this->outputfile = outputfile;
}

void JSONData::setApplication(const std::string &application)
{
    this->application.emplace(application);
}

void JSONData::addCommand(const std::string &command)
{
    if (command.empty()) {
        LOG(ERROR) << "Tried to add emoty command to data object!";
        throw std::invalid_argument("Command cannot be empty");
    }

    this->commands.push_back(command);
}

void JSONData::addEnvironmentVariable(const std::string &name,
                                      const std::string &value)
{
    if (name.empty() || value.empty()) {
        LOG(ERROR) << "Tried to add invalid environment variable to data object!";
        LOG(INFO) << "Envirement variables have to have a name and a value!";
        throw std::invalid_argument("Name and value cannot be empty");
    }

    this->environmentVariables.push_back(std::make_tuple(name, value));
}

void JSONData::addPathValue(const std::string &pathValue)
{
    if (pathValue.empty()) {
        LOG(ERROR) << "Tried to add empty path value to data object!";
        throw std::invalid_argument("Path value cannot be empty");
    }

    this->pathValues.push_back(pathValue);
}
} // namespace json
