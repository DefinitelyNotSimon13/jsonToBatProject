#ifndef VERBOSE_HANDLER_HPP
#define VERBOSE_HANDLER_HPP

#include <optional>
namespace utils {
class VerboseHandler {
public:
  static VerboseHandler &getInstance() {
    static VerboseHandler instance;
    return instance;
  }

  bool isVerbose() const;

  void setVerbose(bool verbose);

private:
  VerboseHandler() = default;
  VerboseHandler(const VerboseHandler &) = delete;
  VerboseHandler &operator=(const VerboseHandler &) = delete;

  bool verboseFlag = false;
};
}

#endif
