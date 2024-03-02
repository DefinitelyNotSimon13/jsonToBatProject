#include "Verbose.hpp"
#include "LoggingWrapper.hpp"

namespace utils {
bool VerboseHandler::isVerbose() const { return this->verboseFlag; }

void VerboseHandler::setVerbose(bool verbose) {
  LOG_INFO << "Setting verbose flag to: " << verbose;
  this->verboseFlag = verbose;
}
} // namespace utils
