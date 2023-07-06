#include "bbt/appkit/env.h"

#include <map>
#include <string>
#include <mutex>

#include "bbt/appkit/object.h"

namespace bbt {

class ObjectEnv {
 public:
  Status Insert(Object* obj) {
    if (!obj) return InvalidArgumentError("no service");
    const char* name = obj->service_name();
    if (!name || !*name) return InvalidArgumentError("no name");

    std::lock_guard<std::mutex> lock(mutex_);

    if (objs_.find(name) != objs_.end()) return AlreadyExistsError(name);

    obj->AddRefManually();
    objs_[name] = obj;
    return OkStatus();
  }

  Status Remove(Object* obj) {
    if (!obj) return InvalidArgumentError("no service");
    const char* name = obj->service_name();
    if (!name || !*name) return InvalidArgumentError("no name");

    std::lock_guard<std::mutex> lock(mutex_);

    auto it = objs_.find(name);
    if (it == objs_.end()) {
      return NotFoundError(name);
    }
    if (it->second != obj) {
      return UnknownError("same name, but service object different");
    }

    objs_.erase(it);
    obj->Release();
    return OkStatus();
  }

  Status Get(const char* name, Object** pobj) {
    if (!name || !*name) return InvalidArgumentError("no name");
    if (!pobj) return InvalidArgumentError("no receiver");

    auto it = objs_.find(name);
    if (it == objs_.end()) {
      return NotFoundError(name);
    }

    Object* obj = it->second;
    obj->AddRefManually();
    *pobj = obj;
    return OkStatus();
  }

 private:
  std::mutex mutex_;
  std::map<std::string, Object*> objs_;
};

class StringEnv {
 public:
  void Insert(const char* key, const char* value) {
    if (key && *key) {
      std::lock_guard<std::mutex> lock(mutex_);
      ss_[key] = value ? value : "";
    }
  }

  void Remove(const char* key) {
    if (key && *key) {
      std::lock_guard<std::mutex> lock(mutex_);
      ss_.erase(key);
    }
  }

  std::string Get(const char* key) {
    if (key && *key) {
      std::lock_guard<std::mutex> lock(mutex_);
      auto it = ss_.find(key);
      if (it != ss_.end()) return it->second;
    }
    return "";
  }

 private:
  std::mutex mutex_;
  std::map<std::string, std::string> ss_;
};

class GlobalEnvImpl : public GlobalEnv {
 public:
  GlobalEnvImpl() {}
  ~GlobalEnvImpl() {}

  Status InsertObject(Object* obj) { return obj_env_.Insert(obj); }
  Status RemoveObject(Object* obj) { return obj_env_.Remove(obj); }
  Status GetObject(const char* name, Object** pobj) {
    return obj_env_.Get(name, pobj);
  }

  void InsertString(const char* key, const char* value) {
    str_env_.Insert(key, value);
  }
  void RemoveString(const char* key) { str_env_.Remove(key); }
  std::string GetString(const char* key) { return str_env_.Get(key); }

 private:
  ObjectEnv obj_env_;
  StringEnv str_env_;
};

GlobalEnv* GlobalEnv::New() { return new GlobalEnvImpl(); }
void GlobalEnv::Release(GlobalEnv* env) { delete env; }

}  // namespace bbt