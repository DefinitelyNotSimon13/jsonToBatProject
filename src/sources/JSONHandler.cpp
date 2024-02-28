#include "JSONHandler.hpp"
#include "JSONData.hpp"
#include <fstream>
#include <json/json.h>
#include <easylogging++.h>

namespace json {
JSONHandler::JSONHandler(const std::string &filename)
{
    this->root = parseFile(filename);
}

std::shared_ptr<Json::Value> JSONHandler::parseFile(const std::string
                                                    &filename)
{
    std::ifstream file(filename);
    Json::Value root;
    Json::Reader reader;
    reader.parse(file, root);
    return std::make_shared<Json::Value>(root);
}

std::shared_ptr<JSONData> JSONHandler::getJSONData()
{
    return this->createJSONData();
}

std::shared_ptr<JSONData> JSONHandler::createJSONData()
{
    this->data = std::make_shared<JSONData>();
    this->assignOutputFile();
    this->assignHideShell();
    this->assignApplication();
    this->assignEntries();
    this->assignEntries();
    return this->data;
}
void JSONHandler::assignOutputFile()
{
    std::string outputFile = this->root->get("outputfile", "").asString();
    this->data->setOutputFile(outputFile);
}

void JSONHandler::assignHideShell()
{
    /// \todo: Error handling if not found
    /// \note: default to false
    bool hideShell = this->root->get("hideShell", false).asBool();
    this->data->setHideShell(hideShell);
}

void JSONHandler::assignApplication()
{
    std::string application = this->root->get("application", "").asString();
    this->data->setApplication(application);
}

void JSONHandler::assignEntries()
{
    for (auto entry : this->root->get("entries", "")) {
        std::string entryType = entry.get("type", "").asString();

        if (entryType == "EXE") {
            this->assignCommand(entry);
        }
        else if (entryType == "ENV") {
            this->assignEnvironmentVariable(entry);
        }
        else if (entryType == "PATH") {
            this->assignPathValue(entry);
        }
        else {
            LOG(ERROR) << "Unknown entry type";
            throw std::runtime_error("Unknown entry type");
        }
    }
}

void JSONHandler::assignCommand(const Json::Value &entry)
{
    std::string command = entry.get("command", "").asString();
    this->data->addCommand(command);
}

void JSONHandler::assignEnvironmentVariable(const Json::Value &entry)
{
    std::string key = entry.get("key", "").asString();
    std::string value = entry.get("value", "").asString();
    this->data->addEnvironmentVariable(key, value);
}

void JSONHandler::assignPathValue(const Json::Value &entry)
{
    std::string pathValue = entry.get("path", "").asString();
    this->data->addPathValue(pathValue);
}
} // namespace json
