#include<iostream> 
#include "/home/sergey/Programming/Jacobi_elem/Useful_Functions.cpp"

/**
 * @brief Тест Соловея-Шграссена проверки числа на простоту
 * 
 * @param n число, которое проверяем
 * @param t критерий надёжности
 * @return true число простое
 * @return false число составное
 */
bool solovey_strassen_test(int n, int t);

int main()
{
    if (solovey_strassen_test(1153, 10))
    {
        std::cout << "Число возможно простое" << std::endl;
    }
    else 
    {
        std::cout << "Число точно составное" << std::endl;    
    }
    return 0;
}

bool solovey_strassen_test(int n, int t)
{
    if (n <= 1)
    {
        return false;
    }
    int a = 2;
    int r;
    int s;
    for(size_t i = 0; i < t; ++i)
    {
        r = count_in_pow_at_mod(a, (n - 1)/2, n);
        if (r != 1 && r != n - 1) 
        {
            return false;
        }

        s = jacobi_elem(a, n);

        if (r - n != s && r != s)
        {
            return false;
        }
        ++a;
    }
    return true;
}
