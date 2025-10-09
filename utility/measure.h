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

/**
 * @brief Partial specialization in case a function returns void
 */
template <typename Duration>
struct Result<Duration, void>
{
  Duration time;
};

/*************** performance measure ***************/

/**
 * @brief Call a function and measure its performance
 */
template <typename Function, typename... Args, typename TimeUnit = std::chrono::milliseconds>
auto performance_measure_impl(Function&& func, Args&&... args)
{
  using R = std::invoke_result_t<Function, Args...>;
  using Clock = std::chrono::system_clock;

  if constexpr (std::is_void_v<R>) {
    Clock::time_point start = Clock::now();
    std::invoke(std::forward<Function>(func), std::forward<Args>(args)...);
    Clock::time_point end = Clock::now();
    return Result{std::chrono::duration_cast<TimeUnit>(end - start)};
  }

  Clock::time_point start = Clock::now();
  auto value = std::invoke(std::forward<Function>(func), std::forward<Args>(args)...);
  Clock::time_point end = Clock::now();
  return Result{std::chrono::duration_cast<TimeUnit>(end - start), value};
}

template <typename R, typename... Args, typename TimeUnit = std::chrono::milliseconds>
auto performance_measure(const std::vector<std::function<R(Args...)>>& func_list, const std::vector<std::tuple<Args...>>& arg_list)
{
  for (size_t i = 0; i != func_list.size(); ++i) {
    auto func = func_list[i];
    std::println("Function {}:", i);
    for (size_t j = 0; j != arg_list.size(); ++j) {
      auto result = std::apply(
          [&func](const auto&... args)
          {
            return performance_measure_impl(func, args...);
          },
          arg_list[j]);
      std::println("    Case {}: {}{}", j, result.time.count(), time_unit<TimeUnit>());
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
