#include "JSONData.hpp"
#include "LogAndOut.hpp"
#include <easylogging++.h>
#include <ostream>
#include <stdexcept>

namespace json {
void JSONData::setOutputFile(std::string &newOutputfile) {
  LOG_INFO << "Setting outputfile to...";
  if (newOutputfile.empty()) {
    LOG_ERROR << "Tried to set empty outputfile!";
    throw std::invalid_argument("Outputfile cannot be empty");
  }

  if (!this->outputfile.empty()) {
    LOG_ERROR << "Outputfile already set!";
    throw std::invalid_argument("Outputfile already set");
  }

  if (newOutputfile.find(".bat") == std::string::npos ||
      newOutputfile.find(".bat") !=
          newOutputfile.size() - JSONData::suffixLength) {
    newOutputfile += ".bat";
    LOG_WARNING << "Outputfile does not have .bat suffix, adding it now: "
                << newOutputfile;
  }

  this->outputfile = newOutputfile;
  LOG_INFO << "Outputfile set to: " << this->outputfile << "\n";
}

void JSONData::setApplication(const std::string &newApplication) {
  if (newApplication.empty()) {
    return;
  }
  LOG_INFO << "Setting application to: " << newApplication << "\n";
  this->application.emplace(newApplication);
}

void JSONData::addCommand(const std::string &command) {
  if (command.empty()) {
    LOG_ERROR << "Tried to add empty command to data object!";
    throw std::invalid_argument("Command cannot be empty");
  }
  LOG_INFO << "Adding command: " << command << "\n";
  this->commands.push_back(command);
}

void JSONData::addEnvironmentVariable(const std::string &name,
                                      const std::string &value) {
  if (name.empty() || value.empty()) {
    LOG_ERROR << "Tried to add invalid environment variable to data object!";
    LOG_INFO << "Envirement variables have to have a name and a value!";
    throw std::invalid_argument("Name and value cannot be empty");
  }
  LOG_INFO << "Adding environment variable: " << name << "=" << value << "\n";
  this->environmentVariables.emplace_back(name, value);
}

void JSONData::addPathValue(const std::string &pathValue) {
  if (pathValue.empty()) {
    LOG_ERROR << "Tried to add empty path value to data object!";
    throw std::invalid_argument("Path value cannot be empty");
  }
  LOG_INFO << "Adding path value: " << pathValue << "\n";
  this->pathValues.push_back(pathValue);
}
} // namespace json
