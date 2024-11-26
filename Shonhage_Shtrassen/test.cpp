#include <cstddef>
#include <iostream>
#include "Matrix.cpp"
#include <vector>

int main()
{
    Matrix matrix_test_0 = Matrix({{2, 5}, {7, 9}});
    Matrix matrix_test_1 = Matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix matrix_test_2 = Matrix({{1, 2, 3, 4}, {4, 5, 6, 7}, {7, 8, 9, 10}, { 11, 12, 13, 15}});
    Matrix matrix_test_4 = Matrix({{1, 2 ,3}, {2, -1, 3}, {3, 4, -1}});
    Matrix matrix_test_5 = Matrix({{-1, 2 ,-2}, {2, -1, 5}, {3, -2, 4}});    
    Matrix matrix_test_6 = Matrix({{1,3,3},{1,2,5}});
    Matrix matrix_test_7 = Matrix({{1,2},{5,6},{4,3}});
    // Matrix m2 = Matrix({{3},{4},{5}});
    Matrix progonic_matrix = Matrix({{2, 1, 0, 0, -5},{1, 10, -5, 0, -18},{0, 1, -5, 2, -40}, {0, 0, 1, 4, -27}});
    // Matrix m3 = Matrix({{2,3, 1},{0,5, 1}});
    // Matrix m4 = Matrix({{1,0,5},{5,6,3},{2,-2,4}});
    // Matrix m5 = m3 + m4;
    // m5.print();

    // std::cout<<matrix_test_0.inv_elem(2,5);
    Matrix a = Matrix({81,135,1,140});
    Matrix dpf = a.dpf(257, -16, 4);
    // Matrix vander = a.get_inv_vandermond(5,2,4);
    dpf.print();

    // Matrix pr = m2.get_progonic_matrix(11);
    // pr.print();
    // progonic_matrix.print();
    // std::vector<double> x = progonic_matrix.progonic_method();
    // for (size_t i = 0; i < x.size(); ++i)
    // {
    //     std::cout << x[i] << "!";
    // }

    // Matrix m3 = Matrix({{2,0,0},{0,0,0},{0,0,10}});
    // m3.print();
    // Matrix m_4 = m3.inverse_matrix_from_unit();
    // m_4.print();
    // Matrix m3 = Matrix({{1,2},{12,9}});
    // double x = m3.determinant();
    // std::cout << x;

    // matrix_test_7.print();
    // matrix_test_6.print();
    // Matrix m3 = matrix_test_6*matrix_test_7;
    // m3.print();
    // matrix_test_5.print();

    // Matrix inv_test = martix_test_7.inverse_matrix();
    // inv_test.print();

    // Matrix m1 = martix_test_7 * m2;
    // m1.print();
    // matrix_test_2.print();
    
    // Matrix matrix_test_3 = matrix_test_1 + matrix_test_2;
    // matrix_test_3.print();
    
    // Matrix matrix_test_4 = matrix_test_1 - matrix_test_2;
    // matrix_test_4.print();

    // Matrix matrix_test_5 = matrix_test_1 * matrix_test_2;
    // matrix_test_5.print();

    // Matrix matrix_transp = matrix_test_0.transposition();
    // matrix_transp.print();

    // Matrix matrix_multiple = matrix_test_1.multiplication_on_number(2);
    // matrix_multiple.print();

    // std::cout << matrix_test_1.determinant();

    // matrix_test_2.print();
    // Matrix triangle_matrix  = matrix_test_2.convert_to_triangle_matrix();
    // triangle_matrix.print();
    // std::cout << triangle_matrix.get_number_of_row() << std::endl;
    // matrix_test_2.print();


    // double a = 1.0 / 24;
    // Matrix multi_matrix = matrix_test_1 * a;
    // multi_matrix.print();

    // std::cout << 1.0 / 24; 

    // double a1 = 1;
    // double b1 = 24;
    // double c1 = a1 / b1;
    // std::cout << "!" << c1 << "!"; 

    // double determ = matrix_test_4.determinant();
    // std::cout << determ;

    // matrix_test_1.transposition().print();

    // std::cout << std::endl << matrix_test_1.determinant() << std::endl;

    // Matrix inverse_test = matrix_test_5.inverse_matrix();
    // inverse_test.print();

    // matrix_test_5.print();

    // Matrix new_matrix = matrix_test_5 * inverse_test ;
    // new_matrix.print();
    
    // Matrix e = matrix_test_0 * inverse_test;
    // e.print();

    // Matrix minor = matrix_test_1.minor(1, 1);
    // minor.print();

    // Matrix attached_matrix = matrix_test_5.convert_to_attached_matrix();
    // attached_matrix.print();
    
    // Matrix matrix_test_5_transpose = matrix_test_5.transposition(); 
    // matrix_test_5_transpose.print();

    // std::cout << matrix_test_5.algebraic_addition(1,1);

    // matrix_test_5.print();

    // Matrix unit_test = get_unit_matrix(5);
    // unit_test.print();

    // matrix_test_2.print();
    // Matrix manual_inverse_matrix = matrix_test_2.inverse_matrix_manual();
    // manual_inverse_matrix.print();


    // matrix_test_2.print();
    // double x = matrix_test_2.determinant_manual();
    // std::cout << x;
    
    // matrix_test_2.print();
    // Matrix m_test = matrix_test_2.inverse_matrix();
    // std::cout << matrix_test_2.rank_matrix();
    // Matrix m1 = matrix_test_2.convert_to_triangle_matrix();
    // m1.print();
    // std::cout << m1.get_number_of_row();
    // m_test.print();

    // Matrix sum = matrix_test_2 * m_test;
    // sum.print();

    // Matrix m3 = matrix_test_6.convert_to_triangle_matrix();
    // m3.print();
    
    // size_t num_rows;
    // size_t num_columns;
    // std::cout << "Введите количество строк: ";
    // std::cin >> num_rows;
    // std::cout << std::endl;

    // std::cout << "Введите количество столбцов: ";    
    // std::cin >> num_columns;
    // std::cout << std::endl;

    // Matrix console_matrix = Matrix(num_rows, num_columns);
    // console_matrix.print();
    
    // Matrix gauss_test = Matrix({{1,2,3},{2,-1,2},{1,1,5}});
    // Matrix res = Matrix({{1},{6},{-1}});
    // Matrix g_1 = gauss_test.gauss_method(res);
    // g_1.print();
    // std::cout<< "Матрица А:" << std::endl;
    // Matrix A = Matrix({{2,3,1},{0,5,2},{-1,1,7}});
    // A.print();
    // std::cout<< "Матрица B:" << std::endl;
    // Matrix B = Matrix({{1,0,5},{5,6,3},{2,-2,4}});
    // B.print();
    // // Matrix x_1 = A*B;
    // // x_1.print();
    // std::cout<< " Матрица 2*A*B - ( A-B ) * 2 A^T + B :" << std::endl;
    // Matrix result = A*B*2 - (A-B)*A.transposition()*2+B;
    // result.print();

    // Matrix points = Matrix ({{22, 278.67},{22.1, 277.24},{22.2, 272.58},{22.3, 275.5},{22.4, 276.69},{22.5, 273.17}
    // ,{22.6,275.78},{22.7,276.5},{22.8,278.366},{22.9,279.733},{23,276.998}});
    // points.print();
    // points.spline();

    // std::vector<double> kramer = Matrix({{1,2,1,4},{2,-1,2,3},{3,1,-2,2}}).kramer_method();
    // for (size_t i = 0; i < kramer.size(); ++i) 
    // {
    //     std::cout << kramer[i] << "!";
    // }

    // Matrix kramer =  Matrix({{1,4,9},{5,-1,3}}).kramer_method();
    // kramer.print();

    // Matrix jacobi = Matrix({{1.1,-0.2,0.1,1.6},{0.1,-1.2,-0.2,2.3},{0.2,-0.1,1.1,1.5}});
    // jacobi.print();
    // jacobi.jacobi_method().print();
    // jacobi.seidel_method().print();
    // std::cout << Matrix({{0, 2/11, -1/11}, {1/12, 0, -1/6}, {-2/12, 1/11, 0}}).norma();

    // Matrix g_matrix = Matrix({{1,2,5, -9}, {1,-1,3,2}, {3,-6,-1,25}});

    // // Matrix g_matrix = Matrix({{1,2,-1,1}, {2,4,-2,0}, {3,0,-2,5}});
    // g_matrix.print();
    // g_matrix.convert_to_triangle_matrix().print();
    // g_matrix.gauss_method().print(); 

    // Matrix s = Matrix({
    //     {1,1,1,2},
    //     {3,-2,5,1},{4,3,-2,7}});
    // s.convert_to_triangle_matrix().print();

    // Matrix A = Matrix({{2,3,1},{0,5,2},{-1,1,7}});
    // Matrix B = Matrix({{1,0,5},{5,6,3},{2,-2,4}});
    // Matrix C = A * B;
    // C.print();
    return 0;
}