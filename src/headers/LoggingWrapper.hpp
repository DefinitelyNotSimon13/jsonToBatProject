#ifndef LOGANDOUT_HPP
#define LOGANDOUT_HPP

#include <easylogging++.h>
#include <iostream>
#include <sstream>
#include <string>
namespace utils {

#define LOG_INFO utils::log(utils::LogLevel::INFO, "-- ")
#define LOG_ERROR utils::log(utils::LogLevel::ERROR)
#define LOG_WARNING utils::log(utils::LogLevel::WARNING)
#define LOG_DEBUG utils::log(utils::LogLevel::DEBUG)
#define OUTPUT utils::log(utils::LogLevel::OUT, "Output: ")

enum class LogLevel { INFO, WARNING, ERROR, FATAL, DEBUG, 
  OUT, };

/**
 * \note
 * # Bugs and Quirks
 * - Automatically makes new line for cout -- Nevermind?!
 **/
class LoggingWrapper {
public:
  LoggingWrapper(LogLevel newLevel) : level(newLevel) {}
  LoggingWrapper(const std::string &newPrefix, LogLevel newLevel)

      : prefix(newPrefix), level(newLevel) {}

  template <typename T> LoggingWrapper &operator<<(const T &val) {
    buffer << val;
    return *this;
  }

  typedef std::ostream &(*Manipulator)(std::ostream &);
  LoggingWrapper &operator<<(Manipulator manipulator);

  ~LoggingWrapper();

private:
  std::string prefix;
  LogLevel level;
  std::ostringstream buffer;
};
inline LoggingWrapper log() { return LoggingWrapper(LogLevel::INFO); }
inline LoggingWrapper log(const std::string &prefix) {
  return LoggingWrapper(prefix, LogLevel::INFO);
}
inline LoggingWrapper log(LogLevel level) { return LoggingWrapper(level); }
inline LoggingWrapper log(LogLevel level, const std::string &prefix) {
  return LoggingWrapper(prefix, level);
}
} // namespace utils

#endif // LOGANDOUT_HPP
