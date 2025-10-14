#include "Ch3.h"
#include <iostream>
#include <iterator>
#include <map>
#include <print>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>

/**
 * @brief Check balancedness of the language consisting of begin/end, (), [], {}
 */
bool ch3::isBalancedPascal(std::string_view sv, Language lang)
{
  std::map<std::string, std::string> balanceMap;
  if (lang == Language::Pascal) {
    balanceMap = {{"end", "begin"}, {")", "("}, {"]", "["}, {"}", "{"}};
  }
  if (lang == Language::Cpp) {
    balanceMap = {{"*/", "/*"}, {")", "("}, {"]", "["}, {"}", "{"}};
  }

  std::istringstream ss{std::string{sv}};
  std::stack<std::string> st;
  for (std::istream_iterator<std::string> it(ss); it != std::istream_iterator<std::string>(); ++it) {
    if (!st.empty() && balanceMap.contains(*it) && st.top() == balanceMap.at(*it)) {
      st.pop();
      continue;
    }
    st.push(*it);
  }
  if (st.empty()) {
    return true;
  } else {
    return false;
  }
}