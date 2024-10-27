#include "Polynom_2/Polynom.cpp"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

std::vector<long double> splitting_digits(int a, int b)
{       
    std::vector<long double> a_r;

    while (a != 0)
    {
        a_r.push_back(a % b);
        a /= b;
    }

    std::reverse(a_r.begin(), a_r.end());   
    return a_r;
}

std::vector<long double> difference_vector(std::vector<long double> input_vec, size_t i_0)
{
    std::vector<long double> dif_vec;
    for (size_t i = 0; i < input_vec.size() - 1; ++i)
    {
        dif_vec.push_back((input_vec[i+1] - input_vec[i]) / (i_0));
        // std::cout << dif_vec[i] << std::endl;
    }
    return dif_vec;   
}   

std::vector<long double> newton_coefficients(std::vector<long double> w_at_point)
{
    std::vector<long double> coef;
    std::vector<long double> dif_vec;
    dif_vec = w_at_point;
    // coef.push_back(w_at_point[0]);
    for (size_t i = 0; i < w_at_point.size(); ++i)
    {
        coef.push_back(dif_vec[0]);
        // if(w_at_point.size() == 1)
        // {
        //     break;
        // }
        dif_vec = difference_vector(dif_vec, i + 1);
    }

    // for (size_t i = 0; i < coef.size(); ++i)
    // {
    //     std::cout << coef[i] << std::endl;
    // }
    
    return coef;
}

int toom_coock(int u, int v, int b, int r)
{
    Polynom u_x = Polynom(splitting_digits(u, b));
    Polynom v_x = Polynom(splitting_digits(v, b));

    std::vector<long double> w_at_point;  
    for (size_t i = 0; i <= 2 * r; ++i)
    {
        w_at_point.push_back(u_x.value_at_point(i) * v_x.value_at_point(i));
        // std::cout << u_x.value_at_point(i) * v_x.value_at_point(i) << std::endl;
    } 
    std::vector<long double> coef = newton_coefficients(w_at_point);
    // for(size_t i = 0; i < coef.size(); ++i)
    // {
    //     std::cout<<coef[i]<< std::endl;
    // }

    Polynom w_r;
    for (size_t i = 0; i < coef.size(); ++i)
    {
        Polynom power_i = w_r.power_series(i);
        w_r += Polynom({coef[i]}) * power_i;
    }

    long double y = 0;
    for(size_t i = 0; i < w_r.size(); ++i)
    {
        y += w_r[w_r.size() - 1 - i] * pow(b, i);
    }   
    return int(y);
}   

int main()
{
    std::cout << "y = " << toom_coock(111, 555, 10, 2);
    return 0;                                       
}               