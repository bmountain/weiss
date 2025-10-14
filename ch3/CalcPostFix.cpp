#include "Ch3.h"
#include <functional>
#include <iterator>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <variant>

using Operand = std::variant<int, std::plus<int>, std::minus<int>, std::multiplies<int>, std::divides<int>>;

Operand getOperand(std::string word)
{
  if (word == "+") {
    return std::plus<int>();
  }
  if (word == "-") {
    return std::minus<int>();
  }
  if (word == "*") {
    return std::multiplies<int>();
  }
  if (word == "/") {
    return std::divides<int>();
  }
  return std::stoi(word);
}

struct OperationVisitor
{
  std::stack<Operand>& st_;
  OperationVisitor(std::stack<Operand>& st)
  : st_{st}
  {
  }

  void operator()(int n)
  {
    st_.push(n);
  }
  void operator()(auto&& op)
  {
    auto [left, right] = getNumbers();
    st_.push(op(left, right));
  }

private:
  std::pair<int, int> getNumbers()
  {
    int right = std::get<0>(st_.top());
    st_.pop();
    int left = std::get<0>(st_.top());
    st_.pop();
    return std::make_pair(left, right);
  }
};

int ch3::calcPostFix(std::string_view sv)
{
  std::istringstream ss{std::string{sv}};

  std::stack<Operand> st;
  OperationVisitor visitor{st};

  std::string word;
  try {
    while (ss >> word) {
      Operand op = getOperand(word);
      std::visit(visitor, op);
    }
    if (st.size() == 1) {
      return std::get<0>(st.top());
    }
    throw std::runtime_error("Stack is not empty at the end of the expression.");
  } catch (const std::exception& e) {
    std::println("Invalid expression. {}", e.what());
    throw;
  }
}