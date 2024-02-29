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
class LogAndOut {
public:
  LogAndOut(LogLevel newLevel) : level(newLevel) {}
  LogAndOut(const std::string &newPrefix, LogLevel newLevel)

      : prefix(newPrefix), level(newLevel) {}

  template <typename T> LogAndOut &operator<<(const T &val) {
    buffer << val;
    return *this;
  }

  typedef std::ostream &(*Manipulator)(std::ostream &);
  LogAndOut &operator<<(Manipulator manipulator);

  ~LogAndOut();

private:
  std::string prefix;
  LogLevel level;
  std::ostringstream buffer;
};
inline LogAndOut log() { return LogAndOut(LogLevel::INFO); }
inline LogAndOut log(const std::string &prefix) {
  return LogAndOut(prefix, LogLevel::INFO);
}
inline LogAndOut log(LogLevel level) { return LogAndOut(level); }
inline LogAndOut log(LogLevel level, const std::string &prefix) {
  return LogAndOut(prefix, level);
}
} // namespace utils

#endif // LOGANDOUT_HPP
