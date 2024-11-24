#include <utility>
#include <cstddef>

/**
 * @brief Даёт ответ, является ли число степенью двойки
 * 
 * @param count искомое число
 * @return true является степенью двойки
 * @return false не является степенью двойки
 */
bool is_pow_of_two(int count)
{
    if( count == 2)
    {
        return true;
    }
    
    if (count % 2 == 0)
    {
        count /= 2;
        return is_pow_of_two(count);
    }
    else 
    {
        return false;
    }
}

/**
 * @brief даёт такое число, двойка в степени которого будет больше либо равна введённому числу
 * 
 * @param count число на ввод
 * @return int степень двойки
 */
int pow_of_two(int count)
{
    int power = 0;
    while (count != 1)
    {
        count /= 2;
        power += 1;
    }
    return power;
}

/**
 * @brief преобразует число "a" к виду "2^k * a1" где "a1" нечётное
 * @param int "a" число, которое будем преобразовать
 * @return std::pair<int, int> пара, где первый параметр степень двойки - "k", второй параметр - "a1"
 */
std::pair<int, int> a_in_mult(int a)
{
    if (is_pow_of_two(a))
    {
        return std::make_pair(pow_of_two(a), 1);
    }
    else
    {
        if ( a % 2 != 0)
        {
            return std::make_pair(0, a);
        }
        else 
        {
            int k = 0;
            a /= 2;
            k += 1;
            std::pair<int, int> ret_pair = a_in_mult(a);
            ret_pair.first += k;
            return ret_pair;
        }                               
    }
}

/**
 * @brief Выводит символ Якоби
 * 
 * @param a 
 * @param n 
 * @return int 
 */
int jacobi_elem(int a, int n)
{
    if (a == 0)
        return 0;
    if (a == 1)
        return 1;
    std::pair<int, int> a_transform = a_in_mult(a);
    int s;

    if (a_transform.first % 2 == 0)
    {
        s = 1;
    }
    else if (n%8 == 1 || n%8 == 7) 
    {
        s = 1;
    }
    else 
    {
        s = -1;
    }

    if (n%4 == 3 && a_transform.second%4 == 3)
    {
        s = -1 * s;
    }

    if (a_transform.second == 1)
    {
        return s;
    }
    else
    {
        return s*jacobi_elem(n%a_transform.second, a_transform.second);
    }
    return 0;
}

/**
 * @brief Функция призвана экономично считать число в некоторой степени, по модулю
 * 
 * @param count само число
 * @param pow степень числа
 * @param mod модуль числа
 * @return int число возведённое в степень, взятое по модулю
 */
int count_in_pow_at_mod(const int count, int pow, int mod)
{
    int count_0 = count;
    for (size_t i = 1; i < pow; ++i)
    {
        count_0 = count_0 * count;
        count_0 %= mod;
    }
    return count_0;

}

/**
 * @brief преобразует число к виду "2^s * r + 1" где "r" нечётное
 * @param int число, которое будем преобразовать
 * @return std::pair<int, int> пара, где первый параметр степень двойки - "s", второй параметр - "r"
 */
std::pair<int, int> count_special_view(int count)
{
    count -= 1;
    if (is_pow_of_two(count))
    {
        return std::make_pair(pow_of_two(count), 1);
    }
    else
    {
        if ( count % 2 != 0)
        {
            return std::make_pair(0, count);
        }
        else 
        {
            int k = 0;
            count /= 2;
            k += 1;
            std::pair<int, int> ret_pair = a_in_mult(count);
            ret_pair.first += k;
            return ret_pair;
        }                               
    }
}