#include "Polynom.cpp"

int main()
{
    Polynom p_1 = Polynom({9, 0, 3});
    Polynom p_2 = Polynom({4, 1, 1});
    Polynom p_n = p_1.negative_polynom(p_1);
    std::vector<long double> x = p_1.get_poly();
    long double y = p_2.value_at_point(-2);
    
    Polynom power_poly = p_1.power_series(2);
    power_poly.print();

    // p_1.print();
    // p_2.print();
    // Polynom p_sum = p_2 - p_1;
    // p_sum.print();
    // Polynom p_mult =  Polynom(p_sum.x_multi(5, 35));
    // p_mult.print();
    //     p_sum.print();
    //     p_1.print();
    // p_2.print();
    // Polynom p_mult = p_1 * p_2;
    // p_mult.print();
    // std::vector<double> vec_2 = { 0, 0, 1};
    // std::vector<double> vec_1 = {3, 0, 0, 0, 2};
    // std::vector<double> vec_sum = p_1.vec_sum(vec_1, vec_2);
    // Polynom(vec_sum).print();

    // Polynom chebyshev_8 = p_1.chebyshev(99999999);
    // Polynom chebyshev_7 = p_1.chebyshev(7);
    // Polynom chebyshev_6 = p_1.chebyshev(6);
    // Polynom chebyshev_5 = p_1.chebyshev(5);
    // Polynom chebyshev_4 = p_1.chebyshev(4);
    // Polynom chebyshev_3 = p_1.chebyshev(3);
    // Polynom chebyshev_2 = p_1.chebyshev(2);
    // Polynom chebyshev_1 = p_1.chebyshev(1);
    // chebyshev_8.print();
    // chebyshev_7.print();
    // chebyshev_6.print();
    // chebyshev_5.print();
    // chebyshev_4.print();
    // chebyshev_3.print();
    // chebyshev_2.print();
    // chebyshev_1.print();
}
