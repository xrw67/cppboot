#ifndef BBT_BUS_MSG_H_
#define BBT_BUS_MSG_H_

#include <stdint.h>
#include <string>
#include <map>
#include <memory>

#include "bbt/base/status.h"

namespace bbt {
namespace bus {

class Msg {
 public:
  typedef uint32_t Id;
  typedef std::map<std::string, std::string> Type;

  Msg() : id_(0) {}
  Msg(Id id) : id_(id) {}

  Id id() const { return id_; }
  void set_id(Id id) { id_ = id; }
  std::string method() const { return method_; }
  void set_method(const std::string& method) { method_ = method; }
  bool Has(const std::string& key) const;
  void Set(const std::string& key, const std::string& value);
  std::string Get(const std::string& key) const;

  const Type& data() const { return values_; }

 private:
  Id id_;
  std::string method_;
  Type values_;
};

typedef std::shared_ptr<Msg> MsgPtr;

}  // namespace bus
}  // namespace bbt

#endif  // BBT_BUS_MSG_H_