#ifndef CONVERT_H
#define CONVERT_H

/**
 * @file Convert.h
 * @brief Convert infix expression into postfix expression
 */
#include <iostream>
#include <map>
#include <memory>
#include <stack>
#include <string>

namespace ch3
{
class Symbol;
using Stack = std::stack<std::unique_ptr<Symbol>>;

/**
 * @brief Convert infix expression into postfix expression
 */
std::string infix_to_postfix(const std::string& input);

class Symbol
{
protected:
  std::string token_;
  int precedence_;

public:
  Symbol(const std::string& token, int precedence)
  : token_{token}
  , precedence_{precedence}
  {
  }

  virtual ~Symbol() = default;
  std::string token() const
  {
    return token_;
  }
  virtual bool is_open_par() const
  {
    return false;
  }
  int precedence() const
  {
    return precedence_;
  }
  /**
   * @return If the symbol should be pushed
   */
  virtual bool on_read(std::ostream& os, Stack& st) = 0;
  virtual void on_poped(std::ostream& os, Stack& st) = 0;
};

class Number : public Symbol
{
public:
  using Symbol::Symbol;
  ~Number() = default;

  bool on_read(std::ostream& os, [[maybe_unused]] Stack& st) override
  {
    os << token() << " ";
    return false;
  }
  void on_poped([[maybe_unused]] std::ostream& os, [[maybe_unused]] Stack& st) override
  {
    return;
  }
};

class OpenPar : public Symbol
{
public:
  using Symbol::Symbol;
  ~OpenPar() = default;
  bool is_open_par() const override
  {
    return true;
  }
  bool on_read([[maybe_unused]] std::ostream& os, [[maybe_unused]] Stack& st) override
  {
    return true;
  }
  void on_poped([[maybe_unused]] std::ostream& os, [[maybe_unused]] Stack& st) override
  {
    return;
  }
};

class ClosePar : public Symbol
{
public:
  using Symbol::Symbol;
  ~ClosePar() = default;
  bool on_read(std::ostream& os, Stack& st) override
  {
    while (true) {
      auto& symbol = st.top();
      auto isEnd = symbol->is_open_par();
      symbol->on_poped(os, st);
      st.pop();
      if (isEnd) {
        break;
      }
    }
    return false;
  }
  void on_poped([[maybe_unused]] std::ostream& os, [[maybe_unused]] Stack& st) override
  {
    return;
  }
};

class Operator : public Symbol
{
public:
  using Symbol::Symbol;
  ~Operator() = default;
  bool on_read(std::ostream& os, Stack& st) override
  {
    while (!st.empty()) {
      auto& symbol = st.top();
      if (symbol->precedence() >= this->precedence() && !symbol->is_open_par()) {
        symbol->on_poped(os, st);
        st.pop();
      } else {
        break;
      }
    }
    return true;
  }
  void on_poped(std::ostream& os, [[maybe_unused]] Stack& st) override
  {
    os << token() << " ";
  }
};
} // namespace ch3

#endif /* CONVERT_H */