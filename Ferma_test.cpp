#include <iostream>
#include "/home/sergey/Programming/Jacobi_elem/Useful_Functions.cpp"

/**
 * @brief функция реализует вероятностный тест ферма на проверку простоты числа
 * 
 * @param n число, простоту которого, проверяем
 * @param t параметр надёжности
 * @return true - число возможно простое(псевдопростое по некоторому основанию)
 * @return false - число составное
 */
bool Ferma(int n, size_t t);

int main()
{
    if (Ferma(561, 6))
    {
        std::cout << "Число возможно простое" << std::endl;
    }
    else 
    {
        std::cout << "Число точно составное" << std::endl;    
    }
    return 0;
}

bool Ferma(int n, size_t t)
{
    int a = 2;
    int r;

    for(size_t i = 0; i < t; ++i)
    {
        if (count_in_pow_at_mod(a, n-1, n) != 1)
        {
            return false;
        }
        ++a;
    }
    return true;
}
