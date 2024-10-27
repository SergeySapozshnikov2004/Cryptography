#include <cstddef>
#include <vector>

class Polynom
{
    private:
    std::vector<long double> polynom;

    public:

Polynom();


std::vector<long double> get_poly();

Polynom& operator=(const Polynom& poly);

Polynom& operator+=(const Polynom& rhs);

Polynom(std::vector<long double> polynom);

void print();

Polynom operator+(const Polynom& other);

Polynom operator-(const Polynom& other);

Polynom operator*(Polynom& other);

double operator[](const size_t num);

std::vector<long double> x_multi(double koef, size_t degree);

std::vector<long double> vec_sum(std::vector<long double> lha, std::vector<long double> rha);

Polynom negative_polynom(const Polynom other);

long double value_at_point(long double x);

Polynom chebyshev(size_t num);

size_t size();

Polynom power_series(size_t num);                                                           

};