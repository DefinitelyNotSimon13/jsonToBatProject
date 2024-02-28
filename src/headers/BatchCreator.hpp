#ifndef BATCHCREATOR_HPP
#define BATCHCREATOR_HPP

#include "JSONData.hpp"
#include <memory>
#include <fstream>

namespace batch {
/// \bug HideShell is not implemented correctly
    class BatchCreator {
    public:
        explicit BatchCreator(std::shared_ptr<json::JSONData> jsonData);

        std::shared_ptr<std::ofstream> createBatchFile();

    private:
        std::shared_ptr<json::JSONData> jsonData;
        std::shared_ptr<std::ofstream> batchFile = nullptr;

        void writeHideShellStart();

        void writeHideShellEnd();

        void writeShell();

        void writeCommands();

        void writeEnvironmentVariables();

        void writePathValue();

        void writeApplication();


    };
} // namespace batch


#endif // BATCHCREATOR_HPP
