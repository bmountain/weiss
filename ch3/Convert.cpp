#include "Convert.h"
#include <sstream>
#include <stdexcept>

namespace ch3
{

struct SymbolAttribute;
SymbolAttribute token_to_type(const std::string& token);
std::unique_ptr<Symbol> symbol_factory(const std::string& token);

enum class SymbolType
{
  Number,
  OpenPar,
  ClosePar,
  Operator,
};

std::string infix_to_postfix(const std::string& input)
{
  std::istringstream is{input};
  std::ostringstream os;
  Stack st;
  std::string token;
  while (is >> token) {
    auto symbol = symbol_factory(token);
    if (symbol->on_read(os, st)) {
      st.push(std::move(symbol));
    }
  }
  while (!st.empty()) {
    st.top()->on_poped(os, st);
    st.pop();
  }
  return os.str();
}

struct SymbolAttribute
{
  SymbolType type;
  int precedence;
};

SymbolAttribute token_to_type(const std::string& token)
{
  using enum SymbolType;
  if (token == "+")
    return {Operator, 1};
  if (token == "-")
    return {Operator, 1};
  if (token == "*")
    return {Operator, 2};
  if (token == "/")
    return {Operator, 2};
  if (token == "^")
    return {Operator, 3};
  if (token == "(")
    return {OpenPar, 100};
  if (token == ")")
    return {ClosePar, 100};
  return {Number, 0};
}

std::unique_ptr<Symbol> symbol_factory(const std::string& token)
{
  auto attr = token_to_type(token);
  SymbolType type = attr.type;
  int precedence = attr.precedence;
  if (type == SymbolType::Number) {
    return std::make_unique<Number>(token, precedence);
  }
  if (type == SymbolType::Operator) {
    return std::make_unique<Operator>(token, precedence);
  }
  if (type == SymbolType::OpenPar) {
    return std::make_unique<OpenPar>(token, precedence);
  }
  if (type == SymbolType::ClosePar) {
    return std::make_unique<ClosePar>(token, precedence);
  }
  throw std::runtime_error("Unknown token type.");
}

} // namespace ch3
