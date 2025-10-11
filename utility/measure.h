/**
 * @file measure.h
 * @brief Templates for measuring performance of functions
 */

#ifndef MEASURE__H
#define MEASURE__H

#include <chrono>
#include <functional>
#include <print>
#include <string>
#include <tuple>
#include <utility>

/*************** printing time unit ***************/

/**
 * @brief Get time unit as string
 */
template <typename TimeUnit>
std::string time_unit();

template <>
std::string time_unit<std::chrono::seconds>()
{
  return "s";
}

template <>
std::string time_unit<std::chrono::milliseconds>()
{
  return "ms";
}

template <>
std::string time_unit<std::chrono::microseconds>()
{
  return "us";
}

template <>
std::string time_unit<std::chrono::nanoseconds>()
{
  return "ns";
}

/*************** data class of performance measure ***************/

/**
 * @brief Store time duration and return value of a function call
 */
template <typename Duration, typename Value>
struct Result
{
  Duration time;
  Value value;
};

template <typename Duration, typename Value>
Result(Duration, Value) -> Result<Duration, Value>;

/**
 * @brief Partial specialization in case a function returns void
 */
template <typename Duration>
struct Result<Duration, void>
{
  Duration time;
};

template <typename Duration>
Result(Duration) -> Result<Duration, void>;

/*************** performance measure ***************/

/**
 * @brief Call a function and measure its performance
 */
template <typename TimeUnit = std::chrono::nanoseconds, typename Function, typename... Args>
auto performance_measure_impl(Function&& func, Args&&... args) -> Result<TimeUnit, std::invoke_result_t<Function, Args...>>
{
  using R = std::invoke_result_t<Function, Args...>;
  using FinalResult = Result<TimeUnit, R>;
  using Clock = std::chrono::steady_clock;

  if constexpr (std::is_void_v<R>) {
    Clock::time_point start = Clock::now();
    std::invoke(std::forward<Function>(func), std::forward<Args>(args)...);
    Clock::time_point end = Clock::now();
    return FinalResult{std::chrono::duration_cast<TimeUnit>(end - start)};
  } else {
    Clock::time_point start = Clock::now();
    auto value = std::invoke(std::forward<Function>(func), std::forward<Args>(args)...);
    Clock::time_point end = Clock::now();
    return FinalResult{std::chrono::duration_cast<TimeUnit>(end - start), value};
  }
}

template <typename TimeUnit = std::chrono::milliseconds, typename R, typename... Args>
auto performance_measure(const std::vector<std::function<R(Args...)>>& func_list, const std::vector<std::tuple<Args...>>& arg_list)
{
  using ImplResult = Result<std::chrono::nanoseconds, R>;

  for (size_t i = 0; i != func_list.size(); ++i) {
    auto func = func_list[i];
    std::println("Function {}:", i);
    ImplResult baseline{};
    for (size_t j = 0; j != arg_list.size(); ++j) {
      auto result = std::apply(
          [func](auto... args) -> ImplResult
          {
            return performance_measure_impl(func, args...);
          },
          arg_list[j]);
      if (j == 0) {
        baseline = result;
      }

      auto time_count = std::chrono::duration_cast<TimeUnit>(result.time).count();
      std::string unit = time_unit<TimeUnit>();
      double ratio = static_cast<double>(result.time.count()) / baseline.time.count();

      std::println("    Case {}: {:>9}{} ({:.1f})", j, time_count, unit, ratio);
    }
    std::println("");
  }
}

/*************** utility ***************/

/**
 * @brief Convert function pointer into std::function
 */
template <typename T>
struct function_signature;

template <typename R, typename... Args>
struct function_signature<R (*)(Args...)>
{
  using type = std::function<R(Args...)>;
};

/**
 * @brief Make function list
 */
template <typename Head, typename... Tail>
auto make_function_list(Head&& head, Tail&&... tail)
{
  using FuncPtrType = std::decay_t<Head>;
  using SigType = typename function_signature<FuncPtrType>::type;

  std::vector<SigType> list;
  list.emplace_back(std::forward<Head>(head));
  (list.emplace_back(std::forward<Tail>(tail)), ...);
  return list;
}

/**
 * @brief Make list of parameters passed to functions
 * @note Works only when template parameters are explicitly designated
 */
template <typename... Params>
auto make_param_list(std::initializer_list<std::tuple<Params...>> params) -> std::vector<std::tuple<Params...>>
{
  return std::vector<std::tuple<Params...>>{params};
}

#endif /* MEASURE__H */
