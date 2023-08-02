#include "table.h"

namespace bbt {
namespace html {

void Table::Dump(std::stringstream& ss, int depth) {
  /*
  <table>
      <tr>
          <th>Company</th>
          <th>Contact</th>
          <th>Country</th>
      </tr>
      <tr>
          <td>Alfreds Futterkiste</td>
          <td>Maria Anders</td>
          <td>Germany</td>
      </tr>
      <tr>
          <td>Centro comercial Moctezuma</td>
          <td>Francisco Chang</td>
          <td>Mexico</td>
      </tr>
      </table>
  */

  std::string prefix(depth, '\t');
  ss << prefix << "<table>\n";

  if (!head_.empty()) {
    ss << prefix << "\t<tr>\n";
    for (size_t i = 0; i < columns_ && i < head_.size(); i++) {
      ss << prefix << "\t\t<th>" << head_[i] << "</th>\n";
    }
    ss << prefix << "\t</tr>\n";
  }

  for (auto row : data_) {
    ss << prefix << "\t<tr>\n";
    for (size_t i = 0; i < columns_ && i < row.size(); i++) {
      ss << prefix << "\t\t<td>" << row[i] << "</td>\n";
    }
    ss << prefix << "\t</tr>\n";
  }
  ss << prefix << "</table>\n";
}

}  // namespace html
}  // namespace bbt