#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

std::vector<int> splitting_digits(int a, int b)
{
    std::vector<int> a_r;

    while (a != 0)
    {
        a_r.push_back(a % b);
        a /= b;
    }

    if (a_r.size() % 2 != 0)
    {
        a_r.push_back(0);
    }
    std::reverse(a_r.begin(), a_r.end());   
    return a_r;
}

int karatsuba(int u, int v, int b)
{
    std::vector<int> u_r;
    std::vector<int> v_r;

    u_r = splitting_digits(u, b);
    v_r = splitting_digits(v, b);

    int n = u_r.size()/2;

    int v_0 = 0;
    int v_1 = 0; 
    int u_0 = 0;
    int u_1 = 0;

    for (size_t i = 0; i < n; ++i)
    {
        u_1 += u_r[n - i - 1] * pow(b, i);
    }
    for (size_t i = 0; i < n; ++i)
    {
        u_0 += u_r[2*n - i  - 1] * pow(b, i);
    }
    for (size_t i = 0; i < n; ++i)
    {
        v_1 += v_r[n-i - 1] * pow(b, i);
    }
    for (size_t i = 0; i < n; ++i)
    {
        v_0 += v_r[2*n - i - 1] * pow(b, i);
    }

    int A = v_1 * u_1;
    int B = v_0 * u_0;
    int C = (u_1 + u_0) * (v_1 + v_0);
    int y = (A * pow(b, n + n)) + ((C-A-B) * pow(b, n)) + B;
    return y;   
}

int main()
{
    std::cout << karatsuba(1234, 5678, 10);
    return 0;
}