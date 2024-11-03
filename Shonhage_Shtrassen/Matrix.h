#include <iostream>
#include <vector>

class Matrix 
{
    private:

    std::vector<std::vector<double>> matrix;

    public:

/// @brief конструирует матрицу размерностью num_rows X num_columns)
/// @param num_rows число строк
/// @param num_columns число столбцов
Matrix(size_t num_rows, size_t num_columns);

/**
 * @brief конструирует матрицу по заданному вектору векторов
 * 
 * @param matrix вектор векторов
 */
Matrix(std::vector<std::vector<double>> matrix);

Matrix(std::vector<double> vec);

/**
 * @brief оператор сложения для матриц
 * 
 * @param other другая матрица
 * @return Matrix результат сложения
 */
Matrix operator+(const Matrix& other);

/**
 * @brief оператор вычитания матриц
 * 
 * @param other другая матрица
 * @return Matrix результат вычитания
 */
Matrix operator-(const Matrix& other);

/**
 * @brief оператор умножения для матриц
 * 
 * @param other другая матрица
 * @return Matrix результат умножения
 */
Matrix operator*(const Matrix& other);

/// @brief оператор умножения матрицы на констансту 
/// @param other некоторое вещественное число
/// @return Matrix 
Matrix operator*(const double& other);

/// @brief оператор присваивания копированием
/// @param matrix 
/// @return Matrix
Matrix& operator=(const Matrix& matrix);

// /**
//  * @brief Оператор присаивания перемещением
//  * 
//  * @param other 
//  * @return Matrix 
//  */
// Matrix operator=(const Matrix&& other) noexcept;

/// @brief выводит матрицу
void print();

/// @brief удаляет указанную строчку матрицы
/// @param num_row 
void delete_row(size_t num_row);

/// @brief считает ранг матрицы
/// @return ранг матрицы
size_t rank_matrix();

/// @brief удаляет нулевые строчки
void cut_zero_row();

/// @brief считает количество строк матрицы
/// @return количество строк
size_t get_number_of_row();

/// @brief достаёт матрицу из приватного поля
/// @return матрица
std::vector<std::vector<double>> get_matrix();

/// @brief транспонирует матрицу
/// @return транспонированная матрица
Matrix transposition();

/// @brief выводит обратную матрицу методом ПРИСОЕДИНЁННОЙ матрицы
/// @return обратная матрица
Matrix inverse_matrix();

/// @brief попытка вывести обратную матрицу через ТРЕУГОЛЬНУЮ, однако не вышло
/// @return будет использьзовано в методе ГАУССА
Matrix inverse_matrix_manual();

/// @brief выводит обратную матрицу приводя к ЕДИНИЧНОМУ виду изначальную, отображая эти действия на единичной
/// @return обратная матрица
Matrix inverse_matrix_from_unit();

/// @brief выводит определитель матрицы с помощью приведения изначальной к ТРЕУГОЛЬНОМУ виду
/// @return определитель матрицы
double determinant();

/// @brief выводит определитель матрицы с помощью разложения по МИНОРАМ
/// @return определитель матрицы
double determinant_manual();

/// @brief выводит единичную матрицу заданного порядка
/// @param rank порядок матрицы
/// @return единичная матрица
Matrix get_unit_matrix(int rank);

/// @brief умножение выбранной строчки матрицы на коэффициент
/// @param num_row номер строчки
/// @param k коэффициент
void row_multiplication(size_t num_row, double k);

/// @brief деление выбранной строчки матрицы на коэффициент
/// @param num_row номер строчки
/// @param k коэффициент
void row_division(size_t num_row, double k);

/// @brief суммирование двух выбранных строчек матрицы и записывает результат в первую указанную строчку
/// @param num_row_1 номер первой строки
/// @param num_row_2 номер второй строки
void row_summation(size_t num_row_1, size_t num_row_2);

/// @brief вычитание двух выбранных строчек матрицы и записывает результат в первую указанную строчку
/// @param num_row_1 номер первой строки
/// @param num_row_2 номер второй строки
void row_subtraction(size_t num_row_1, size_t num_row_2);

/// @brief вычитает из одного вектора другой и записывает результат в отдельный вектор
/// @param lha левый аргумент вектор
/// @param rha правый аргумент вектор
/// @return новый вектор равный разности двух
std::vector<double> vector_minus(std::vector<double> lha,std::vector<double> rha);

/// @brief умножает один вектор на коэффициент
/// @param lha левый аргумент вектор
/// @param k коффициент
/// @return новый вектор равный произведению исходного на коэффициент
std::vector<double> vector_mult(std::vector<double> vec, double k);

/// @brief считает присоединённую матрицу
/// @return присоединённая матрица
Matrix convert_to_attached_matrix();

/// @brief приводит матрицу к треугольному виду
/// @return треугольная матрица
Matrix convert_to_triangle_matrix();

/// @brief считает союзную матрицу
/// @return союзная матрица
Matrix convert_to_union_matrix();

/// @brief считает минор порядка x y
/// @param x 
/// @param y 
/// @return матрица без x строчки и y столбца
Matrix minor(size_t x, size_t y);

/// @brief считает алгебраическое дополнения x y порядка
/// @param x 
/// @param y 
/// @return алгебраическое дополнение
double algebraic_addition(size_t x, size_t y);

/// @brief метод Гаусса для нахождения решения СЛАУ
Matrix gauss_method();



Matrix kramer_method();

/// @brief метод Крамера для нахождения решения СЛАУ
/// @param matrix 
/// @param vec_1 
/// @return решение
std::vector<double> kramer_method(Matrix matrix, std::vector<double> vec_1);

std::vector<double> progonic_method();

void spline();

std::vector<double> c_koef_spline();

Matrix get_progonic_matrix(size_t num_point);

Matrix jacobi_method();

Matrix seidel_method();

Matrix get_vandermond(int m, int w, size_t n);

Matrix get_inv_vandermond(int m, int w, size_t n);

Matrix dpf(int m, int w, size_t n);

Matrix odpf(int m, int w, size_t n);

void matrix_mod(int m);

int inv_elem(int elem, int m);

double norma();

std::vector<double> get_vector();
};