#ifndef BBT_BASE_STR_UTIL_H_
#define BBT_BASE_STR_UTIL_H_

#include <vector>
#include <string>

#include "bbt/base/string_view.h"

namespace bbt {

std::vector<std::string> StrSplit(const std::string& text, char delimiter);

/// @brief 移除左侧的空格、换行符和制表符
std::string StrTrimLeft(const std::string& s, const std::string& cutset);

/// @brief 移除右侧的空格、换行符和制表符
std::string StrTrimRight(const std::string& s, const std::string& cutset);

/// @brief 移除左右两侧的空格、换行符和制表符
std::string StrTrim(const std::string& s, const std::string& cutset);


//
// Match
//

// StrContains()
//
// Returns whether a given string `haystack` contains the substring `needle`.
inline bool StrContains(string_view haystack,
                        string_view needle) noexcept {
  return haystack.find(needle, 0) != haystack.npos;
}

inline bool StrContains(string_view haystack, char needle) noexcept {
  return haystack.find(needle) != haystack.npos;
}

// StartsWith()
//
// Returns whether a given string `text` begins with `prefix`.
inline bool StartsWith(string_view text,
                       string_view prefix) noexcept {
  return prefix.empty() ||
         (text.size() >= prefix.size() &&
          memcmp(text.data(), prefix.data(), prefix.size()) == 0);
}

// EndsWith()
//
// Returns whether a given string `text` ends with `suffix`.
inline bool EndsWith(string_view text,
                     string_view suffix) noexcept {
  return suffix.empty() ||
         (text.size() >= suffix.size() &&
          memcmp(text.data() + (text.size() - suffix.size()), suffix.data(),
                 suffix.size()) == 0);
}

// EqualsIgnoreCase()
//
// Returns whether given ASCII strings `piece1` and `piece2` are equal, ignoring
// case in the comparison.
bool EqualsIgnoreCase(string_view piece1,
                      string_view piece2) noexcept;

// StartsWithIgnoreCase()
//
// Returns whether a given ASCII string `text` starts with `prefix`,
// ignoring case in the comparison.
bool StartsWithIgnoreCase(string_view text,
                          string_view prefix) noexcept;

// EndsWithIgnoreCase()
//
// Returns whether a given ASCII string `text` ends with `suffix`, ignoring
// case in the comparison.
bool EndsWithIgnoreCase(string_view text,
                        string_view suffix) noexcept;


}  // namespace bbt

#endif  // BBT_BASE_STR_UTIL_H_
