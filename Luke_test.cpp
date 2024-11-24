#include <iostream>
#include <vector>
#include "/home/sergey/Programming/Jacobi_elem/Useful_Functions.cpp"


/**
 * @brief Алгоритм для метода Люка проверки числа на простоту
 * 
 * @param n искомое число > 3
 * @param t критерий надёжности
 * @return true число точно простое
 * @return false не гарантируется, что число составное
 */
bool luke_test(int n, int t, std::vector<int> prime_factoring_n);

int main()
{
    if (luke_test(625, 10, {5,5,5,5}))
    {
        std::cout << "Число точно простое" << std::endl;
    }
    else 
    {
        std::cout << "Число вероятно составное" << std::endl;    
    }
    return 0;
}

bool luke_test(int n, int t, std::vector<int> prime_factoring_n)
{
    int a = 2;
    int counter = 0;
    for (size_t i = 0; i < t; ++i)
    {
        if (count_in_pow_at_mod(a, n-1, n) != 1)
        {
            return false;
        }
        for (size_t i = 0; i < prime_factoring_n.size(); ++i)
        {
            if (count_in_pow_at_mod(a, (n-1) / prime_factoring_n[i], n) != 1){}
            {
                counter += 1;
            }
        }
        if (counter == prime_factoring_n.size())
        {
            return true;
        }
        ++a;
    }
    return false;
}