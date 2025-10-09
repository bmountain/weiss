#include <print>

void sum1(int n)
{
int sum = 0;
for (int i = 0; i != n; ++i){
    ++sum;
    }
}

void sum2(int n)
{
    int sum = 0;
    for (int i = 0; i != n; ++i){
        for (int j = 0; j != i; ++j){
                ++sum;
        }
    }
}
