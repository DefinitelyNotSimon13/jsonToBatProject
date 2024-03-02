#include "LoggingWrapper.hpp"
#include "CliHandler.hpp"
#include "Verbose.hpp"

namespace utils {
LoggingWrapper::~LoggingWrapper() {
  switch (this->level) {
  case LogLevel::OUT:
    std::cout << this->buffer.str();
    LOG(INFO) << this->prefix << this->buffer.str();
    break;
  case LogLevel::INFO:
    if (VerboseHandler::getInstance().isVerbose()) {
      std::cout << this->prefix << this->buffer.str();
    }
    LOG(INFO) << this->prefix << this->buffer.str();
    break;
  case LogLevel::WARNING:
    std::cout << cli::YELLOW_FG << this->buffer.str() << cli::RESET;
    LOG(WARNING) << this->prefix << this->buffer.str();
    break;
  case LogLevel::ERROR:
    std::cerr << cli::ERROR << this->prefix << this->buffer.str() << cli::RESET;
    LOG(ERROR) << this->prefix << this->buffer.str();
    break;
  case LogLevel::FATAL:
    std::cerr << cli::BLACK_FG << cli::RED_BG << this->prefix
              << this->buffer.str() << cli::RESET;
    LOG(FATAL) << this->prefix << this->buffer.str();
    break;
  case LogLevel::DEBUG:
    std::cout << cli::ITALIC << cli::CYAN_FG << this->prefix
              << this->buffer.str() << cli::RESET;
    LOG(DEBUG) << this->prefix << this->buffer.str();
    break;
  }
}
LoggingWrapper &LoggingWrapper::operator<<(Manipulator manipulator) {
  manipulator(std::cout);
  this->buffer << manipulator;
  return *this;
}
} // namespace utils
