/**
 * @file measure.h
 * @brief Templates for measuring performance of functions
 */

#ifndef MEASURE__H
#define MEASURE__H

#include <chrono>
#include <cmath>
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
const char* time_unit();

template <>
const char* time_unit<std::chrono::seconds>()
{
  return "s";
}

template <>
const char* time_unit<std::chrono::milliseconds>()
{
  return "ms";
}

template <>
const char* time_unit<std::chrono::microseconds>()
{
  return "us";
}

template <>
const char* time_unit<std::chrono::nanoseconds>()
{
  return "ns";
}
/*************** performance measure ***************/

/**
 * @brief Call a function and measure its performance
 */
template <typename TimeUnit = std::chrono::nanoseconds, typename Function, typename... Args>
auto measure_one_case(Function&& func, Args&&... args)
{
  using Clock = std::chrono::steady_clock;

  Clock::time_point start = Clock::now();
  std::invoke(std::forward<Function>(func), std::forward<Args>(args)...);
  Clock::time_point end = Clock::now();
  return std::chrono::duration_cast<TimeUnit>(end - start);
}

template <typename InternalTimeUnit>
using Result = std::vector<std::vector<InternalTimeUnit>>;

template <typename InternalTimeUnit = std::chrono::nanoseconds, typename R, typename... Args>
auto measure_all_case(const std::vector<std::function<R(Args...)>>& func_list, const std::vector<std::tuple<Args...>>& arg_list)
{
  Result<InternalTimeUnit> result(func_list.size());

  for (size_t i = 0; i != func_list.size(); ++i) {
    auto func = func_list[i];
    for (size_t j = 0; j != arg_list.size(); ++j) {
      auto time_ellapsed = std::apply(
          [func](auto... args)
          {
            return measure_one_case<InternalTimeUnit>(func, args...);
          },
          arg_list[j]);

      result[i].push_back(time_ellapsed);
    }
  }
  return result;
}

/*************** printing result ***************/

std::pair<double, const char*> time_to_string(std::chrono::nanoseconds time)
{
  using namespace std::chrono;

  double count = static_cast<double>(time.count());

  if (count >= 1'000'000'000.0) { // >= 1 second
    auto d = duration_cast<duration<double>>(time);
    return {d.count(), time_unit<std::chrono::seconds>()};
  } else if (count >= 1'000'000.0) { // >= 1 millisecond
    auto d = duration_cast<duration<double, std::milli>>(time);
    return {d.count(), time_unit<std::chrono::milliseconds>()};
  } else if (count >= 1000.0) { // >= 1 microsecond
    auto d = duration_cast<duration<double, std::micro>>(time);
    return {d.count(), time_unit<std::chrono::microseconds>()};
  } else { // nanosecond
    return {count, time_unit<std::chrono::nanoseconds>()};
  }
}
template <typename R, typename... Args>
void performance_measure(const std::vector<std::function<R(Args...)>>& func_list, const std::vector<std::tuple<Args...>>& arg_list)
{
  Result<std::chrono::nanoseconds> result = measure_all_case(func_list, arg_list);
  for (size_t i = 0; i != func_list.size(); ++i) {
    auto [min_it, max_it] = std::minmax_element(result[i].begin(), result[i].end(),
                                                [](const std::chrono::nanoseconds left, const std::chrono::nanoseconds right)
                                                {
                                                  return left.count() < right.count();
                                                });
    std::chrono::nanoseconds min = *min_it, max = *max_it;

    std::vector<double> ratio;
    for (const auto& time : result[i]) {
      ratio.push_back(static_cast<double>(time.count()) / min.count());
    }

    std::println("Function {}", i);
    for (size_t j = 0; j != result[i].size(); ++j) {
      auto [time_value, unit_str] = time_to_string(result[i][j]);

      std::println("  {:>6.1f} {:<2} ({:>5.1f})", time_value, unit_str, ratio[j]);
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
