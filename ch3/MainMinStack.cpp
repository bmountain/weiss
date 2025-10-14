#include "Ch3.h"
#include "measure.h"

using stack = ch3::MinStack<int>;

void run(size_t n)
{
  stack st;
  for (size_t i = 0; i != n; ++i) {
    st.push(i);
    st.top();
    st.findMin();
  }
  for (size_t i = 0; i != n; ++i) {
    st.pop();
  }
}

int main()
{
  auto func = make_function_list(run);
  auto data = make_param_list<size_t>({{10000}, {100000}, {1000000}});
  performance_measure(func, data);
}