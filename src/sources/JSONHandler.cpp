#include "JSONHandler.hpp"
#include "JSONData.hpp"
#include <fstream>
#include <json/json.h>
#include <easylogging++.h>
#include <stdexcept>

namespace json {
    JSONHandler::JSONHandler(const std::string &filename) {
        this->root = parseFile(filename);
    }

    std::shared_ptr<Json::Value> JSONHandler::parseFile(const std::string
                                                        &filename) const {
        std::ifstream file(filename);
        Json::Value newRoot;
        Json::Reader reader;
        reader.parse(file, newRoot);
        return std::make_shared<Json::Value>(newRoot);
    }

    std::shared_ptr<JSONData> JSONHandler::getJSONData() {
        return this->createJSONData();
    }

    std::shared_ptr<JSONData> JSONHandler::createJSONData() {
        this->data = std::make_shared<JSONData>();
        this->assignOutputFile();
        this->assignHideShell();
        this->assignApplication();
        this->assignEntries();
        return this->data;
    }

    void JSONHandler::assignOutputFile() const {
        std::string outputFile = this->root->get("outputfile", "").asString();
        this->data->setOutputFile(outputFile);
    }

    void JSONHandler::assignHideShell() const {
        /// \todo: Error handling if not found
        /// \note: default to false
        bool hideShell = this->root->get("hideshell", false).asBool();
        this->data->setHideShell(hideShell);
    }

    void JSONHandler::assignApplication() const {
        std::string application = this->root->get("application", "").asString();
        this->data->setApplication(application);
    }

    void JSONHandler::assignEntries() const {
        for (const auto &entry: this->root->get("entries", "")) {
            std::string entryType = entry.get("type", "").asString();

            if (entryType == "EXE") {
                this->assignCommand(entry);
            } else if (entryType == "ENV") {
                this->assignEnvironmentVariable(entry);
            } else if (entryType == "PATH") {
                this->assignPathValue(entry);
            } else {
                LOG(ERROR) << "Unknown entry type";
                throw std::invalid_argument("Unknown entry type");
            }
        }
    }

    void JSONHandler::assignCommand(const Json::Value &entry) const {
        std::string command = entry.get("command", "").asString();
        this->data->addCommand(command);
    }

    void JSONHandler::assignEnvironmentVariable(const Json::Value &entry) const {
        std::string key = entry.get("key", "").asString();
        std::string value = entry.get("value", "").asString();
        this->data->addEnvironmentVariable(key, value);
    }

    void JSONHandler::assignPathValue(const Json::Value &entry) const {
        std::string pathValue = entry.get("path", "").asString();
        this->data->addPathValue(pathValue);
    }
} // namespace json
