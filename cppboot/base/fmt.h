/**
 * fmt 10.0.0
 * A modern formatting library
 * website: https://github.com/fmtlib/fmt
 * api: https://fmt.dev/latest/api.html
 * Format String Syntax: https://fmt.dev/latest/syntax.html
 *
 */
#ifndef CPPBOOT_BASE_FMT_H_
#define CPPBOOT_BASE_FMT_H_

#define FMT_HEADER_ONLY 1

#include "internal/fmt/core.h"
#include "internal/fmt/format.h"
#include "internal/fmt/format-inl.h"
#include "internal/fmt/ranges.h"
#include "internal/fmt/chrono.h"
#include "internal/fmt/os.h"

#include "string_view.h"
#include "status.h"

FMT_BEGIN_NAMESPACE

FMT_FORMAT_AS(cppboot::StatusCode, int);

FMT_END_NAMESPACE

// string_view
template <>
struct fmt::formatter<cppboot::string_view> {
  auto parse(format_parse_context& ctx) -> format_parse_context::iterator {
    return ctx.begin();
  }

  auto format(const cppboot::string_view& sv, format_context& ctx) const
      -> format_context::iterator {
    auto result = fmt::format_to_n(ctx.out(), sv.size(), "{:s}", sv.data());
    return result.out;
  }
};

// Status
template <>
struct fmt::formatter<cppboot::Status> {
  auto parse(format_parse_context& ctx) -> format_parse_context::iterator {
    return ctx.begin();
  }

  auto format(const cppboot::Status& s, format_context& ctx) const
      -> format_context::iterator {
    return fmt::format_to(ctx.out(), "{}", s.ToString());
  }
};

namespace cppboot {

using fmt::format;
using fmt::format_error;
using fmt::format_string;
using fmt::print;
using fmt::println;
using fmt::vformat;

}  // namespace cppboot

#endif  // CPPBOOT_BASE_FMT_H_
