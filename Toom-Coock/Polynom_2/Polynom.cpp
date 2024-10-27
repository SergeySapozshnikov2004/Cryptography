#include "Polynom.h"
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector> 
#include <cmath>

Polynom::Polynom()
{
    polynom = {};
}

Polynom::Polynom(std::vector<long double> polynom)
{
    this->polynom=polynom;
}

Polynom& Polynom::operator=(const Polynom& poly)//перегрузка
{
    polynom.clear();
    for (size_t i = 0; i < poly.polynom.size(); ++i)
    {
        polynom.push_back(poly.polynom[i]);
    }
    return *this;//возвращаем ссылку на текущий объект
}

Polynom& Polynom::operator+=(const Polynom& rhs)
{
    Polynom p_1 = *this; 
    polynom = (p_1 + rhs).polynom;
    return *this;
}

void Polynom::print()
{
    for(size_t i = 0; i < polynom.size(); ++i)
    {   
        size_t j = polynom.size() - 1 - i;
        if (i != 0)
        {
            if (polynom[i] < 0)
            {
                std::cout<< " - " << std::setprecision(30) << -1.0*polynom[i] << "*x^" << j;
            }
            if (polynom[i] > 0)
            {
                std::cout << " + " <<std::setprecision(30) << polynom[i] << "*x^" << j ;
            }
        } 
        if (i==0)
        {

            std::cout<< std::setprecision(30) << polynom[i] << "*x^" << j;

        }   
    }
    std::cout << std::endl;
}

Polynom Polynom::operator+(const Polynom& other)
{
    std::vector<long double> new_polynom;
    int delta = polynom.size() - other.polynom.size();
    if (polynom.size() > other.polynom.size())
    {
        for(size_t i = 0; i < polynom.size(); ++i)
        {
            if (i < delta)
            {
                new_polynom.push_back(polynom[i]);
            }
            else 
            {
            new_polynom.push_back(polynom[i] + other.polynom[i-delta]);         
            }
        }
    }
    if (polynom.size() < other.polynom.size())
    {
        for(size_t i = 0; i < other.polynom.size(); ++i)
        {
            if (i < -delta)
            {
                new_polynom.push_back(other.polynom[i]);
            }
            else 
            {
                new_polynom.push_back(other.polynom[i] + polynom[i+delta]);
            }
        }   
    }
    if (polynom.size() == other.polynom.size())
    {
        for (size_t i = 0; i < polynom.size(); ++i)
        {
            new_polynom.push_back(other.polynom[i] + polynom[i]);
        }
    }
    return Polynom(new_polynom);
}

Polynom Polynom::negative_polynom(const Polynom other)
{
    std::vector<long double> neg_poly;
    for (size_t i = 0; i < other.polynom.size(); ++i)
    {
        neg_poly.push_back(-1.0 * other.polynom[i]);
    }
    return Polynom(neg_poly); 
}

Polynom Polynom::operator-(const Polynom& other_0)
{
    Polynom return_poly = Polynom(polynom) + negative_polynom(other_0); 
    return return_poly;
}



Polynom Polynom::operator*(Polynom& other)
{
    Polynom return_poly = Polynom();
    Polynom sum_poly = Polynom();
    for (size_t i = 0; i < polynom.size(); ++i)
    {
        size_t i_r = polynom.size() - 1 - i;
        return_poly = return_poly + Polynom(other.x_multi(polynom[i], i_r));
        sum_poly = return_poly;
    }
    return return_poly;
}

std::vector<long double> Polynom::x_multi(double koef, size_t degree)
{
    std::vector<long double> new_polynom;
    for (size_t i = 0; i < polynom.size(); ++i)
    {
        new_polynom.push_back(polynom[i] * koef);
    }
    for (size_t i = polynom.size(); i < polynom.size() + degree; ++i)
    {
        new_polynom.push_back(0);
    }

    return new_polynom;
}


std::vector<long double> Polynom::vec_sum(std::vector<long double> lha, std::vector<long double> rha)
{
    std::vector<long double> new_polynom;
    int delta = lha.size() - rha.size();
    if (lha.size() > rha.size())
    {
        int delta = lha.size() - rha.size();
        for(size_t i = 0; i < lha.size(); ++i)
        {
            if (i < delta)
            {
                new_polynom.push_back(lha[i]);
            }
            else 
            {
            new_polynom.push_back(lha[i] + rha[i-delta]);
            }
        }
    }
    if (lha.size() < rha.size())
    {
        int delta = rha.size() - lha.size();
        for(size_t i = 0; i < rha.size(); ++i)
        {
            if (i < delta)
            {
                new_polynom.push_back(rha[i]);
            }
            else 
            {
                new_polynom.push_back(rha[i] + lha[i-delta]);
            }
        }   
    }
    else
    {
        for (size_t i = 0; i < polynom.size(); ++i)
        {
            new_polynom.push_back(rha[i] + lha[i]);
        }
    }
    return new_polynom;
}

double Polynom::operator[](const size_t num)
{
    return polynom[num];
}

Polynom Polynom::chebyshev(size_t num)
{
    Polynom t_n_minus_1 = Polynom({1});
    Polynom t_n = Polynom({1,0});
    Polynom two_x = Polynom({2,0}); 
    Polynom t_n_plus_1 = Polynom();
    for(size_t i = 0; i < num-1; ++i)
    {
        t_n_plus_1 = two_x * t_n;
        t_n_plus_1 = t_n_plus_1 - t_n_minus_1;
        t_n_minus_1 = t_n;
        t_n = t_n_plus_1; 
    }
    return t_n_plus_1;
}

std::vector<long double> Polynom::get_poly()
{
    return polynom;
}

long double Polynom::value_at_point(long double x)
{
    long double y = 0.0;
    for(size_t i = 0; i < polynom.size(); ++i)
    {
        y += polynom[i] * pow(x, polynom.size() - 1 - i);
    }
    return y;
}

size_t Polynom::size()
{
    return polynom.size();
}

Polynom Polynom::power_series(size_t num)
{
    if(num == 0)
    {
        return Polynom({1});
    }
    if(num == 1)
    {
        return Polynom({1,0});
    }
    Polynom poly_1 = Polynom({1, -1.0 * (num - 1)});
    Polynom poly_2 = power_series(num - 1);
    return poly_1 * poly_2;
}