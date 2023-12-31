#include "cppboot/adv/bus/context.h"
#include "cppboot/net/buffer.h"
#include "cppboot/adv/bus/msg.h"
#include "cppboot/adv/bus/msg_packer.h"

namespace cppboot {

BusContext::BusContext() : state_(kHeader) {}

BusContext::Result BusContext::Parse(Buffer* buf, Msg* msg) {
  if (state_ == kHeader) {
    if (buf->ReadableBytes() < sizeof(header_)) {
      return kContinue;
    }

    memcpy(&header_, buf->Peek(), sizeof(header_));
    buf->Retrive(sizeof(header_));
    state_ = kBody;

    if (header_.magic != kMsgMagic) {
      return kBad;
    }
  }

  if (state_ == kBody) {
    if (buf->ReadableBytes() < header_.length) {
      return kContinue;
    }

    // TODO: 性能优化
    std::string body(buf->Peek(), header_.length);
    buf->Retrive(header_.length);
    state_ = kHeader;

    JsonPacker p;

    auto st = p.Unpack(body, msg);
    if (!st) {
      return kBad;
    }
  }
  return kGood;
}

}  // namespace cppboot