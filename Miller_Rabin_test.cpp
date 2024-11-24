#include <iostream>
#include <utility>
#include "/home/sergey/Programming/Jacobi_elem/Useful_Functions.cpp"

/**
 * @brief Тест Миллера-Рабина проверки числа на простоту
 * 
 * @param n нечётное число > 3
 * @param t параметр надёжности
 * @return true число скорее всего простое
 * @return false число точно составное
 */
bool miller_rabin_test(int n, int t);

int main()
{
    if (miller_rabin_test(5472, 10))
    {
        std::cout << "Число возможно простое" << std::endl;
    }
    else 
    {
        std::cout << "Число точно составное" << std::endl;    
    }
    return 0;
}

bool miller_rabin_test(int n, int t)
{
    std::pair<int, int> n_new_view = count_special_view(n);
    int s = n_new_view.first;
    int r = n_new_view.second;
    int b = 2;
    int y;
    int j;
    for (size_t i = 0; i < t; ++i) 
    {
        y = count_in_pow_at_mod(b,r, n);
        if (y != 1 && y != n-1) 
        {
            j = 1;
            while (j < s && y != n-1)
            {
                y = count_in_pow_at_mod(y, 2, n);
                if (y == 1)
                {
                    return false;
                }
                ++j;
            }
            if (y != n - 1)
            return false;
        }
        ++b;
    }
    return 1;
}