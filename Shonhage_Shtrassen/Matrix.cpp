#include "Matrix.h"
#include <cstddef>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>
#include <numbers>
#include <vector>


Matrix::Matrix(size_t num_rows, size_t num_columns)
{
    if (num_rows <= 0 || num_columns <= 0)
    {
        throw std::logic_error("Размер должен быть положительным");
    
    } 
    for (size_t i = 0; i < num_rows; ++i)
    {
        matrix.push_back({});
        for (size_t j = 0; j < num_columns; ++j)
        {
            std::cout << "Введите " << j+1 << "-ый элемент " << i+1 << "-ой строки" << std::endl;
            double param;
            std::cin >> param;
            std::cout << std::endl;
            matrix[i].push_back(param);
        }
    }
}

Matrix::Matrix(std::vector<double> vec)
{
    for (size_t i = 0; i < vec.size(); ++i)
    {
        matrix.push_back({vec[i]});
    }
}


Matrix::Matrix(std::vector<std::vector<double>> matrix)
{
    this->matrix = matrix;
}

Matrix Matrix::operator+(const Matrix &other)
{
    if (matrix.size() != other.matrix.size())
    {
        throw std::logic_error("Размер матриц должен быть одинаковым");
    }
    std::vector<std::vector<double>> new_matrix;
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        new_matrix.push_back({});
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            new_matrix[i].push_back(matrix[i][j] + other.matrix[i][j]);
        }
    }
    return Matrix(new_matrix);
}

Matrix Matrix::operator-(const Matrix &other)
{
    if (matrix.size() != other.matrix.size())
    {
        throw std::logic_error("Размер матриц должен быть одинаковым");
    }
    std::vector<std::vector<double>> new_matrix;
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        new_matrix.push_back({});
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            new_matrix[i].push_back(matrix[i][j] - other.matrix[i][j]);
        }
    }
    return Matrix(new_matrix);
}

Matrix Matrix::operator*(const Matrix &other)
{
    const double eps = 1e-12;
    if (other.matrix.size() != matrix[0].size())
    {
        throw std::logic_error("Количество столбцов первой матрицы должно равняться количеству строк второй матрицы");
    }

    std::vector<std::vector<double>> new_matrix;
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        new_matrix.push_back({});    
        for (size_t j = 0; j < other.matrix[i].size(); j++)
        {
            double new_el = 0;
            for (size_t j_2 = 0; j_2 != matrix[i].size(); ++j_2)
            {
                new_el = new_el + matrix[i][j_2] * other.matrix[j_2][j];
            }
            if (std::abs(new_el) < eps)
            {
                new_el=0.0;
            }    
            new_matrix[i].push_back(new_el);
        }
    }
     return Matrix(new_matrix);
}

void Matrix::delete_row(size_t num_row)
{
    std::vector<std::vector<double>> new_matrix;
    for (size_t i = 0; i < matrix.size(); i++)
    {
        if (i != num_row)
        {
        new_matrix.push_back(matrix[i]);
        }    
    }
    matrix = new_matrix;
}

size_t Matrix::rank_matrix()
{
    Matrix m1 = Matrix(matrix);
    Matrix m2 = m1.convert_to_triangle_matrix();
    size_t rank = m2.get_number_of_row();
    return rank;
}

void Matrix::cut_zero_row()
{
    for (size_t i = 0; i < matrix.size(); i++)
    {
        double counter = 0;
        for (size_t j = 0; j < matrix[0].size(); j++)
        {
            if (matrix[i][j] == 0)
            {
                counter += 1;
            }
        }
        if ( counter == matrix[0].size())
        {
            delete_row(i);
        }
    }
}

size_t Matrix::get_number_of_row()
{
    return matrix.size();
}

Matrix Matrix::operator*(const double &other)
{
    double c = other;
    std::vector<std::vector<double>> new_matrix;
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        new_matrix.push_back({});
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            double a = matrix[i][j];
            double x = a * c;
            new_matrix[i].push_back(x);
        }
    }
    return Matrix(new_matrix);
}

Matrix Matrix::inverse_matrix()
{
    if (matrix.size() != matrix[0].size())
    {
        throw std::logic_error("Матрица должна быть квадратной");
    }
    if (rank_matrix() != matrix.size())
    {
        throw std::logic_error("Ранг матрицы не совпадает с её размерностью");
    }
    Matrix new_matrix = Matrix(matrix);
    double x = 1.0 / new_matrix.determinant();
    Matrix at = new_matrix.convert_to_attached_matrix();
    at.transposition();
    at.transposition();
    return Matrix(at * x);
}

Matrix Matrix::inverse_matrix_from_unit()
{
    if (matrix.size() != matrix[0].size())
    {
        throw std::logic_error("Матрица должна быть квадратной");
    }
    if (rank_matrix() != matrix.size())
    {
        throw std::logic_error("Ранг матрицы не совпадает с её размерностью");
    }
    Matrix matrix_1 = Matrix(matrix);
    Matrix inverse_matrix = get_unit_matrix(matrix.size()+1);
    for(size_t i0 = 0; i0 < matrix.size(); ++i0)
    {
        inverse_matrix.row_division(i0, matrix_1.matrix[i0][i0]);
        matrix_1.row_division(i0, matrix_1.matrix[i0][i0]);
        for (size_t i = 0; i < matrix.size(); ++i)
        {
            if( i != i0)
            {
                inverse_matrix.matrix[i] = vector_minus(inverse_matrix.matrix[i], vector_mult(inverse_matrix.matrix[i0], matrix_1.matrix[i][i0]));
                matrix_1.matrix[i] = vector_minus(matrix_1.matrix[i], vector_mult(matrix_1.matrix[i0], matrix_1.matrix[i][i0]));
            }
        }
    }                           
    return inverse_matrix;      
}

double Matrix::determinant_manual()
{
    if (matrix.size() != matrix[0].size())
    {
        throw std::logic_error("Матрица должна быть квадратной");
    }
    if (rank_matrix() != matrix.size())
    {
        throw std::logic_error("Ранг матрицы не совпадает с её размерностью");
    }
    double determinant = 0;
    if (matrix.size() == 2)
    {
        determinant = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    else
    {
        for(size_t i = 0; i < matrix.size(); ++i)
        {
        determinant += pow(-1.0, i) * matrix[0][i] * minor(1,i+1).determinant_manual();
        }
    }
    return determinant;
}

Matrix Matrix::get_unit_matrix(int rank)
{
    std::vector<std::vector<double>> unit_matrix;
    for (size_t i = 0; i < rank-1; ++i)
    {
        unit_matrix.push_back({});
        for (size_t j = 0; j < rank-1; ++j)
        {
            if (i == j)
            {
                unit_matrix[i].push_back(1.0);
            }
            else
            {
                unit_matrix[i].push_back(0);
            }
        }
    }
    return Matrix(unit_matrix);
}

void Matrix::row_multiplication(size_t num_row, double k)
{
    const double e = 1e-10;
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        if (std::abs(matrix[num_row][i]*k) < e)
        {
            matrix[num_row][i] = 0.0;
        }
        else
        {
            matrix[num_row][i] = 1.0*k * matrix[num_row][i];
        }
    }
}

void Matrix::row_division(size_t num_row, double k)
{
    const double e = -1e-10;
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        if (std::abs(1.0/matrix[num_row][i]*k) < e)
        {
            matrix[num_row][i] = 0.0;
        }
        else
        {
            matrix[num_row][i] = 1.0 / k * matrix[num_row][i];
        }
    }
}

void Matrix::row_subtraction(size_t num_row_1, size_t num_row_2)
{
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        matrix[num_row_1][i] = matrix[num_row_1][i] - matrix[num_row_2][i];
    }
}

void Matrix::row_summation(size_t num_row_1, size_t num_row_2)
{
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        matrix[num_row_1][i] = matrix[num_row_1][i] + matrix[num_row_2][i];
    }
}

std::vector<double> Matrix::vector_minus(std::vector<double> lha, std::vector<double> rha)
{
    std::vector<double> result;
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        result.push_back(lha[i] - rha[i]);
    }
    return result;
}

std::vector<double> Matrix::vector_mult(std::vector<double> vec, double k)
{
    for (size_t i = 0; i < matrix.size(); i++)
    {
        vec[i] = vec[i] * k;
    }
    return vec;
}

Matrix Matrix::transposition()
{
    std::vector<std::vector<double>> return_matrix;
    for (size_t j = 0; j < matrix[0].size(); j++)
    {
        return_matrix.push_back({});
        for (size_t i = 0; i < matrix.size(); ++i)
        {
            return_matrix[j].push_back(matrix[i][j]);
        }
    }
    return Matrix(return_matrix);
}

std::vector<std::vector<double>> Matrix::get_matrix()
{
    return matrix;
}

double Matrix::determinant()
{
    if (matrix.size() != matrix[0].size())
    {
        throw std::logic_error("Матрица должна быть квадратной");
    }
    if (rank_matrix() != matrix.size())
    {
        throw std::logic_error("Ранг матрицы не совпадает с её размерностью");
    }
    Matrix new_matrix = Matrix(matrix);
    Matrix return_matrix = new_matrix.convert_to_triangle_matrix();
    double determ = return_matrix.matrix[0][0];
    for (size_t i = 1; i < matrix.size(); ++i)
    {
        determ = determ * return_matrix.matrix[i][i];
    }
    return determ;
}

Matrix &Matrix::operator=(const Matrix &matrix)
{
    if (&matrix != this)
        {
            this->matrix = matrix.matrix;
        }
    return *this;
}

void Matrix::print()
{
    std::vector<double> empty = {};
    for(size_t i = 0; i < matrix.size(); ++i)
    {
        if (matrix[i] != empty)
        {
            for(size_t j = 0; j < matrix[i].size(); ++j)
            {
                std::cout << std::setprecision(10) << matrix[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

Matrix Matrix::convert_to_attached_matrix()
{
    std::vector<std::vector<double>> attached_matrix;
    Matrix old_matrix = Matrix(matrix);
    old_matrix.transposition();
    transposition();
    for (size_t i = 0; i < matrix.size(); ++i)
        {
        attached_matrix.push_back({});
        for(size_t j = 0; j < matrix[0].size(); ++j)
            {
                attached_matrix[i].push_back(algebraic_addition(j, i));
            }
            matrix = old_matrix.matrix;
        }    
    return Matrix(attached_matrix);
}

Matrix Matrix::minor(size_t x, size_t y)
{
    x = x-1;
    y = y-1;
    size_t i1 = 0;
    size_t j1 = 0;
    std::vector<std::vector<double>> minor;
    for(size_t i = 0; i < matrix.size() - 1; ++i)
    {
        minor.push_back({});
        for(size_t j = 0; j < matrix[0].size() - 1; ++j)
        {
            if (i1 == x and j1 == y)
            {
                i1 += 1;
                j1 += 1;
            }

            if (i1 != x and j1 == y)
            {
                j1 += 1;
            }

            if (i1 == x and j1 != y)
            {
                i1 += 1;
            }

            minor[i].push_back(matrix[i1][j1]);
            j1 += 1;
        }
        j1 = 0;
        i1 += 1;
    }
    return Matrix(minor);
}

Matrix Matrix::convert_to_triangle_matrix()
{
    std::vector<std::vector<double>> my_matrix = matrix;
    std::vector<std::vector<double>> new_matrix = matrix;
    for (size_t i0 = 0; i0 < matrix.size() - 1; ++i0)
    {   
        for (size_t i = i0; i < matrix.size() - 1; ++i)
        {
            for(size_t j = i0; j < matrix[i0].size(); ++j)
            {
                if(new_matrix[i0][i0] != 0)
                {
                new_matrix[i+1][j] = my_matrix[i+1][j] - (my_matrix[i0][j] * my_matrix[i+1][i0]/my_matrix[i0][i0]);
                }
            }
            my_matrix = new_matrix;
        }
    }
    Matrix m1 = Matrix(new_matrix);
    m1.cut_zero_row();
    return m1;
}

Matrix Matrix::convert_to_union_matrix()
{
    Matrix attached_matrix = convert_to_attached_matrix();
    return attached_matrix.transposition();
}

double Matrix::algebraic_addition(size_t x, size_t y)
{
    x += 1;
    y += 1;
    Matrix minor_1 = minor(x, y);
    double result = minor_1.determinant();
    return pow(-1, x+y) * result;
}

Matrix Matrix::inverse_matrix_manual()
{
    if (matrix.size() != matrix[0].size())
    {
        throw std::logic_error("Матрица должна быть квадратной");
    }
    if (rank_matrix() != matrix.size())
    {
        throw std::logic_error("Ранг матрицы не совпадает с её размерностью");
    }
    Matrix unit_matrix = get_unit_matrix(matrix.size()+1);
    std::vector<std::vector<double>> inverse_matrix = unit_matrix.matrix;
    std::vector<std::vector<double>> new_matrix = matrix;
    for (size_t i0 = 0; i0 < matrix.size() - 1; ++i0)
    {
        for (size_t i = i0; i < matrix.size() - 1; ++i)
        {
            for(size_t j = i0; j < matrix[i0].size(); ++j)
            {
                if(new_matrix[i0][i0] != 0)
                {
                    inverse_matrix[i+1][j] = unit_matrix.matrix[i+1][j] - (unit_matrix.matrix[i0][j] *  matrix[i+1][i0]/matrix[i0][i0]);
                    new_matrix[i+1][j] = matrix[i+1][j] - (matrix[i0][j] * matrix[i+1][i0]/matrix[i0][i0]);
                }
            }
            unit_matrix.matrix = inverse_matrix;
            matrix = new_matrix;
        }
    }
    Matrix inversive_matrix = Matrix(inverse_matrix);
    Matrix new_matrix_1 = Matrix(new_matrix);
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        int i2 = matrix.size() - i - 1;
        for(size_t j = i; j < matrix[0].size(); ++j)
        {
            int j2 = matrix.size() - 1 - j;
            if (new_matrix_1.matrix[j2][i2] == 0)
            {
                j2 += 1;
            }
                inversive_matrix.row_division(j2, new_matrix_1.matrix[j2][i2]);
                new_matrix_1.row_division(j2, new_matrix_1.matrix[j2][i2]);
                if (j2 != i2)
                {
                    inversive_matrix.row_subtraction(j2, i2);
                    new_matrix_1.row_subtraction(j2, i2);
                }
        }
    }
    return inversive_matrix;
}


// void Matrix::gauss_method()
// {
//     for (size_t i_1 = 0; i_1 < matrix.size(); ++i_1)
//     {
//     for (size_t i = 1; i < matrix.size(); ++i)
//     {
//         for (size_t j = 1; j < matrix[i].size(); j++)
//         {
//             if (matrix[i][i] != 0)
//             {
//             matrix[i][j] = matrix[i][j] / matrix[i][i];  
//             matrix[i][i] = 1; 
//             }
//             else
//             {
                
//             }
//         }
        
//         for (size_t i_2= 0; i_2 < matrix.size(); ++i_2)
//         {
//              matrix[i][i_2] = matrix[i][i_2] - matrix[i_1][i_2];;
//         }
//     }
//     }   
// }

Matrix Matrix::kramer_method()
{
    std::vector<std::vector<double>> new_matrix = matrix;
    std::vector<double> f_i;
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        f_i.push_back(matrix[i][matrix.size()]);
        new_matrix[i].pop_back();
    }

    matrix = new_matrix;
    double det = Matrix(new_matrix).determinant();
    std::vector<double> det_i;
    // for (size_t i_0 = 0; i_0 < matrix.size(); ++i_0)
    // {
    //     new_matrix.clear();
    //     for (size_t i = 0; i < matrix.size(); ++i)
    //     {
    //         new_matrix.push_back({});
    //         for (size_t j = 0; j < matrix.size(); ++j)
    //         {
    //             if (j == i)
    //             {
    //                 new_matrix[i].push_back(f_i[j]);
    //             }
    //             else 
    //             {
    //                 new_matrix[i].push_back(matrix[i][j]);
    //             }
    //         }
    //     }
    //     det_i.push_back(Matrix(new_matrix).determinant());
    // }

    // for (size_t i = 0; i < det_i.size(); ++i)
    // {
    //     result.push_back(det_i[i] / det);
    // }
    Matrix inverse = Matrix(new_matrix).inverse_matrix_from_unit();
    Matrix result = inverse * Matrix(f_i); 
    return result;
}

// Matrix Matrix::gauss_method()
// {
//     if (matrix.size() != matrix[0].size())
//     {
//         throw std::logic_error("Матрица должна быть квадратной");
//     }
//     if (rank_matrix() != matrix.size())
//     {
//         throw std::logic_error("Ранг матрицы не совпадает с её размерностью");
//     }
//     Matrix result_matrix = Matrix(matrix);
//     Matrix matrix_1 = Matrix(matrix);
//     for(size_t i0 = 0; i0 < matrix.size(); ++i0)
//     {
//         result_matrix.row_division(i0, matrix_1.matrix[i0][i0]);
//         matrix_1.row_division(i0, matrix_1.matrix[i0][i0]);
//         for (size_t i = 0; i < matrix.size(); ++i)
//         {
//             if( i != i0)
//             {
//                 result_matrix.matrix[i] = vector_minus(result_matrix.matrix[i], vector_mult(result_matrix.matrix[i0], matrix_1.matrix[i][i0]));
//                 matrix_1.matrix[i] = vector_minus(matrix_1.matrix[i], vector_mult(matrix_1.matrix[i0], matrix_1.matrix[i][i0]));
//             }
//         }
//     }
//     return matrix_1;
// }

Matrix Matrix::gauss_method()
{
    std::vector<std::vector<double>> check;
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        check.push_back({});
        for(size_t j = 0; j < matrix.size(); ++j)
        {
            check[i].push_back(matrix[i][j]);
        }
    }

    if (Matrix(check).rank_matrix() != matrix.size())
    {
        throw std::logic_error("Ранг матрицы не совпадает с её размерностью");
    }
    std::vector<double> x_res;
    std::vector<std::vector<double>> tr_matrix = Matrix(matrix).convert_to_triangle_matrix().matrix;
    std::vector<std::vector<double>> A;
    
    for (size_t i = 0; i < tr_matrix.size(); ++i)
    {
        A.push_back({});
        for(size_t j = 0; j < tr_matrix.size(); ++j)
        {
            A[i].push_back(tr_matrix[i][j]);
        }
    }
    
    std::vector<double> b;
    for(size_t j = 0; j < tr_matrix.size(); ++j)
        {
            b.push_back(tr_matrix[j][tr_matrix.size()]);
        }

    double x_n = tr_matrix[tr_matrix.size() - 1][tr_matrix.size()] / tr_matrix[tr_matrix.size() - 1][tr_matrix.size() - 1];
    x_res.push_back(x_n);
    double x = 0;
    for(size_t i = 1; i < matrix.size(); ++i)
        {
            size_t i_0 = tr_matrix.size() - 1 - i;
            x = b[i_0];
            for(size_t j = 0; j < matrix.size(); ++j)
            {
                size_t j_0 = tr_matrix.size() - 1 - j;
                if(j > i_0)
                {
                    x = x - x_res[j_0] * A[i_0][j]; 
                }
            }
            x_res.push_back(x / A[i_0][i_0]);
        }
    std::vector<double> x_r;
    for(size_t i = 0; i < x_res.size(); ++i)
    {
        size_t i_0 = x_res.size() - 1 - i; 
        x_r.push_back(x_res[i_0]);
    }
    return  Matrix(x_r);
}

std::vector<double> Matrix::progonic_method()
{
    std::vector<double> a_koef;
    std::vector<double> b_koef;
    std::vector<double> x_result;
    double a_2 = -1.0 * matrix[0][1] / matrix[0][0];
    double b_2 = matrix[0][matrix[0].size() - 1] / matrix[0][0];
    a_koef.push_back(a_2);
    b_koef.push_back(b_2);
    for (size_t i = 1; i < matrix.size() - 1; ++i)
    {

        a_koef.push_back(-1.0 * matrix[i][i+1] / (matrix[i][i-1] * a_koef[a_koef.size() - 1] + matrix[i][i]));
        b_koef.push_back(((matrix[i][matrix[0].size() - 1] - matrix[i][i-1] * b_koef[b_koef.size() - 1]) / (a_koef[a_koef.size() - 2] * 
        matrix[i][i-1] + matrix[i][i])));
    }

    double x_n = (matrix[matrix.size() - 1][matrix.size()] - matrix[matrix.size() - 1][matrix.size() - 2] * b_koef[b_koef.size() - 1]) /
    (a_koef[a_koef.size() - 1] * matrix[matrix.size() - 1][matrix.size() - 2] + matrix[matrix.size() - 1][matrix.size() - 1]);
    x_result.push_back(x_n);

    for(size_t i = 1; i < matrix.size(); ++i)
    {
        size_t j =  matrix.size() - 1 - i;
        x_result.push_back(a_koef[j] * x_result[x_result.size() - 1] + b_koef[j]);
    }
    std::vector<double> ret_x;
    x_result.push_back(0);
    for (size_t j = x_result.size(); j > 0; j--)
    {
        ret_x.push_back(x_result[j-1]);
    }
    ret_x.push_back(0);
    return ret_x;
}

void Matrix::spline()
{
    double h = matrix[1][0] - matrix[0][0];
    std::vector<double> a_koef;
    for(size_t i = 1; i < matrix.size(); ++i)
    {
        a_koef.push_back(matrix[i][1]);
    }

    std::vector<double> c_koef = c_koef_spline();

    std::vector<double> d_koef;
    for(size_t i = 1; i < matrix.size(); ++i)
    {
        d_koef.push_back((c_koef[i] - c_koef[i-1]) / h);
    }

    std::vector<double> b_koef;
    for(size_t i = 1; i < matrix.size(); ++i)
    {
            b_koef.push_back((0.5 * c_koef[i] * h) - (1.0 / 6.0 * h * h * d_koef[i-1]) + ((matrix[i][1] - matrix[i-1][1]) / h));
    }

    for(size_t i = 1; i < matrix.size(); ++i)
    {
        std::cout << "S_" << i << " = " << a_koef[i - 1] << " + (" << b_koef[i - 1]  << ") * (x - " << matrix[i][0] << ") + (" << c_koef[i] * 0.5 
        << ") * (x - " << matrix[i][0] << ")^2 + (" << d_koef[i - 1] / 6.0 << ") * (x - " << matrix[i][0] << ")^3" << std::endl;
    }
}

std::vector<double> Matrix::c_koef_spline()
{
    std::vector<double> c_coef;
    Matrix progonic_matrix = get_progonic_matrix(matrix.size()); 
    double h = matrix[0][0] - matrix[1][0];
    for (size_t i = 0; i < progonic_matrix.matrix.size(); ++i)
    {
        progonic_matrix.matrix[i].push_back((6.0 / (h * h)) * (matrix[i][1] - 2.0 * matrix[i+1][1] + matrix[i+2][1]));
    }
    return progonic_matrix.progonic_method();
}

Matrix Matrix::get_progonic_matrix(size_t num_point)
{
    std::vector<std::vector<double>> return_matrix;
    size_t size = num_point - 2;
    for(size_t i = 0; i < size; ++i)
    {
        return_matrix.push_back({});
        for(size_t j = 0; j < size; ++j)
        {
            if (j == i)
            {
                return_matrix[i].push_back(4);
            }
            if (j == i + 1 or j == i - 1)
            {
                return_matrix[i].push_back(1);
            }
            if (j != i + 1 and j != i and j != i - 1)
            {
                return_matrix[i].push_back(0);
            }
        }    
    }
    return Matrix(return_matrix);
}

Matrix Matrix::jacobi_method()
{
    std::vector<std::vector<double>> B;
    std::vector<double> d;

    for(size_t i = 0; i < matrix.size(); ++i)
    {
        B.push_back({});
        for(size_t j = 0; j < matrix.size(); ++j)
        {
            if (j == i)
            {
                B[i].push_back(0);
            }
            else 
            {
                B[i].push_back(-1.0 * matrix[i][j] / matrix[i][i]);
            }
        }
    }

    for(size_t i = 0; i < matrix.size(); ++i)
    {    
        d.push_back(matrix[i][matrix.size()] / matrix[i][i]);
    }

    Matrix x_0 = Matrix(d);
    size_t R = 7;
    for (size_t i = 0; i < R; ++i)
    {
        Matrix x_res = Matrix(B) * x_0 + Matrix(d);
        x_0 = x_res;
    }
    return  x_0;
}

Matrix Matrix::seidel_method()
{
    std::vector<std::vector<double>> B;
    std::vector<double> d;

    for(size_t i = 0; i < matrix.size(); ++i)
    {
        B.push_back({});
        for(size_t j = 0; j < matrix.size(); ++j)
        {
            if (j == i)
            {
                B[i].push_back(0);
            }
            else 
            {
                B[i].push_back(-1.0 * matrix[i][j] / matrix[i][i]);
            }
        }
    }

    for(size_t i = 0; i < matrix.size(); ++i)
    {    
        d.push_back(matrix[i][matrix.size()] / matrix[i][i]);
    }
    
    std::vector<double> x_n;
    std::vector<double> x_n_prev = d;
    double x = 0.0;
    size_t N = 7;
    for (size_t i_0 = 0; i_0 < N; ++i_0)
    {
        for(size_t i = 0; i < matrix.size(); ++i)
        {
            for(size_t j = 0; j < matrix.size(); ++j)
            {
                if (j<i)
                {
                    x += B[i][j] * x_n[j];
                }
                if (j>=i)
                {
                    x += B[i][j] * x_n_prev[j];
                }
            }  
            x_n.push_back(x + d[i]);
            x = 0;
        }
        x_n_prev = x_n;
        x_n.clear();
    }
    return  Matrix(x_n_prev);
}

double Matrix::norma()
{
    std::vector<double> n;
    double x;
    for(size_t i = 0; i < matrix.size(); ++i)
    {
        for(size_t j = 0; j < matrix.size(); ++j)
        {
        x += matrix[i][j];
        }
        n.push_back(x);
        x=0;
    }
    return n[1];
    
}

Matrix Matrix::get_vandermond(int m, int w, size_t n) 
{
    std::vector<std::vector<double>> return_matrix;
    for(size_t i = 0; i < n; ++i)
    {
        return_matrix.push_back({});
        for(size_t j = 0; j < n; ++j)
        {   
            if (j == n - 1)
            {
                return_matrix[i].push_back(return_matrix[i][1] * return_matrix[i][n-2]);
            }
            else 
            {
                return_matrix[i].push_back(int(pow(w, i * j))%m);
            }
        }
    }
    // matrix = return_matrix;
    Matrix m1 = Matrix(return_matrix);
    m1.matrix_mod(m);
    // m1.print();
    return m1;
}

Matrix Matrix::get_inv_vandermond(int m, int w, size_t n) 
{
    std::vector<std::vector<double>> return_matrix;
    int inv_w = inv_elem(w, m);
    int inv_n = inv_elem(n, m);
    for(size_t i = 0; i < n; ++i)
    {
        return_matrix.push_back({});
        for(size_t j = 0; j < n; ++j)
        {
            return_matrix[i].push_back(int(pow( inv_w, i * j)) % m);
        }
    }
    return  Matrix(return_matrix) * double(inv_n) ;
}

int Matrix::inv_elem(int elem, int m)
{
    for (size_t i = 1; i < m; ++i)
    {
        if ((int(i) * elem)% m == 1)
        {
        return i;
        }
    }
}

void Matrix::matrix_mod(int m)
{
    for(size_t i = 0; i < matrix.size(); ++i)
    {
        for(size_t j = 0; j < matrix[i].size(); ++j)
        {
            if (double(int(matrix[i][j]) % m) < 0)
            {
                matrix[i][j] = double(int(matrix[i][j]) % m) + m;
            }
            else
            {
                matrix[i][j] = double(int(matrix[i][j]) % m); 
            }
            // std::cout << 'q133q';
        }
    } 
}

Matrix Matrix::dpf(int m, int w, size_t n)
{
    Matrix var = get_vandermond(m, w, n);
    Matrix matrix_1 = var * Matrix(matrix);
    matrix_1.matrix_mod(m);
    // matrix_1.transposition();
    return matrix_1;
}

Matrix Matrix::odpf(int m, int w, size_t n)
{
    Matrix var = get_inv_vandermond(m, w, n);
    Matrix matrix_1 = var * Matrix(matrix);
    matrix_1.matrix_mod(m);
    return matrix_1;
}

std::vector<double> Matrix::get_vector()
{
    return matrix[0];
}