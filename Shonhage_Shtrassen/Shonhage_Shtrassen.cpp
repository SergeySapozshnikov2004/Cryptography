#include "Matrix.cpp"
#include <cstddef>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

std::vector<double> vec_in_mod (std::vector<double> v, int m)
{
    for(size_t j = 0; j < v.size(); ++j)
        {
            v[j] = double(int(v[j]) % m); 
        }
    return v;
}

// std::vector<double> negative_wrapped_convolution(std::vector<double> u, std::vector<double> v, int K) {
//     std::vector<double> return_vec;
//     int left_arg = 0;
//     int right_arg = 0;


//     for (int i = 0; i < K; ++i) {
//         for (int j = 0; j < K; j++) {
//             left_arg += u[(i - j + K) % K] * v[j]; 
//         }

//         for (int j = 0; j < std::min(i, K); j++) { 
//             right_arg += u[(i - j)] * v[j]; 
//         }
//         return_vec.push_back(double(left_arg - right_arg));
//         left_arg = 0;
//         right_arg = 0;
//     }
//     std::vector<double> v_1 = vec_in_mod(return_vec, K);
//     return v_1;
// }

std::vector<double> negative_wrapped_convolution(std::vector<double> u,std::vector<double> v, int K)
{
    std::vector<double> return_vec;

    int left_arg = 0;
    int right_arg = 0;
    for (size_t i = 0; i < K ; ++i) 
    {
        for (int j = 0; j < K; j++)
        {
            left_arg += u[(i - j + K) % K] * v[j];
        }

        for (int j = 0; j < i; j++)
        {
            right_arg += u[(i - j)] * v[j];
        }
        return_vec.push_back(double(left_arg - right_arg));
        left_arg = 0;
        right_arg = 0;
    }

    std::vector<double> v_1 = vec_in_mod(return_vec, K);
    return v_1;
}



double vec_in_num(std::vector<double> vec)
{
    double a = 0;
    for(size_t i = 0; i < vec.size(); ++i)
    {
        a += vec[i] * pow(2, vec.size() - i - 1);
    }
    return a;
}

std::vector<double> clustering_vec(std::vector<double> bin_vec, int K, int L)
{
    std::vector<double> cluster;
    std::vector<std::vector<double>> all_vec; 
    for (size_t i = 0; i < K; ++i)
    {
        for(size_t j = i * K; j < i * K + L ; ++j)
        {
            cluster.push_back(bin_vec[j]);
            // std::cout << bin_vec[j] << "!";
        }
        all_vec.push_back(cluster);
        cluster.clear();
    }

    std::vector<double> return_vec;
    for(size_t i = 0; i < all_vec.size(); ++i)
    {
        return_vec.push_back(vec_in_num(all_vec[i]));
        // std::cout<<vec_in_num(all_vec[i]);
    }
    // std::reverse(return_vec.begin(), return_vec.end());
    return return_vec;
}

std::vector<double> convert_to_binary(int a)
{
    std::vector<double> binary_vec;
    while (a != 1)
    {
        binary_vec.push_back(a % 2);
        a /= 2;
    }
    binary_vec.push_back(1);
    
    int size = binary_vec.size();
    int pow_two = 1;
    int n = 0;

    while (pow_two <= size)
    {
        pow_two *= 2;
        ++n;
    }

    for(size_t i = 0; i < pow_two - size; ++i)
    {
        binary_vec.push_back(0);
    }

    size = binary_vec.size();
    for(size_t i = 0; i < size; ++i)
    {
        binary_vec.push_back(0);
    }

    std::reverse(binary_vec.begin(), binary_vec.end());

    return binary_vec;
}

int shonhage_shtrassen(int u, int v)
{
    std::vector<double> u_vec = convert_to_binary(u);
    std::vector<double> v_vec = convert_to_binary(v);
    // Matrix(u_vec).print();
    int N = u_vec.size();

    int n = 0;
    while (N != 1)
    {
        N /= 2;
        n++;
    }
    int l = n / 2;
    int k = n - l;
    int K = pow(2,k);
    int L = pow(2, l);
    // std::cout << K << L;

    std::vector<double> u_clust = clustering_vec(u_vec, K, L);
    // Matrix(u_clust).print();
    std::vector<double> v_clust = clustering_vec(v_vec, K, L);
    // Matrix(negative_wrapped_convolution(u_clust, v_clust, K)).print();
    std::vector<double> w = negative_wrapped_convolution(u_clust, v_clust, K);
    // Matrix(w).print();
    int psi = pow(2, 2.0 * L / K);
    // std::cout << psi;

    std::vector<double> u_psi;
    std::vector<double> v_psi;
    std::reverse(u_clust.begin(), u_clust.end());
    std::reverse(v_clust.begin(), v_clust.end());
    for(size_t i = 0; i < u_clust.size(); ++i)
    {
        u_psi.push_back(u_clust[i] * pow(psi, i));
    }
    for(size_t i = 0; i < v_clust.size(); ++i)
    {
        v_psi.push_back(v_clust[i] * pow(psi, i));
    }
    // Matrix(v_psi).print();

    int m = pow(2, 2*L) + 1;
    int omega = pow(2, 4.0 * L / K);

    Matrix u_dpf = Matrix(u_psi).dpf(m, omega, K);
    Matrix v_dpf = Matrix(v_psi).dpf(m, omega, K);
    std::vector<double> u_dpf_1 = u_dpf.transposition().get_vector();
    std::vector<double> v_dpf_1 = v_dpf.transposition().get_vector();
    // std::cout<<u_dpf_1.size();
    // Matrix(u_dpf_1).print();
    std::vector<double> c;
    for (size_t i = 0; i < u_dpf_1.size(); ++ i)
    {
        c.push_back(u_dpf_1[i] * v_dpf_1[i]);
    }
    c = vec_in_mod(c, m);
    // Matrix(c).print();
    int inv_omega = -1 * pow(2, 2* L - 4.0 * L / K); 
    int inv_k = -1 * pow(2,2 * L - k);
    Matrix c_matrix = Matrix(c);

    Matrix d = c_matrix.dpf(m, inv_omega, 4) * inv_k;
    d.matrix_mod(m);
    // d.print();
    std::vector<double> d_vector = d.transposition().get_vector();
    // std::cout<< d_vector.size();
    std::vector<double> w_final;
    for(size_t i = 0; i < d_vector.size(); ++i)
    {
        w_final.push_back(d_vector[i] / pow(psi, i));
    }
    // Matrix(w_final).print();
    // std::cout<<d.get_matrix().size();
    // Matrix(w).print();
    // Matrix(w_final).print();
    Matrix w_check =  (Matrix(w) - Matrix(w_final)) ;
    w_check.matrix_mod(K);

    w_check = w_check + w_final;
    // w_check.print();
    std::vector<double> w_check_vec = w_check.transposition().get_vector();
    // std::cout << w_vec.size();
    
    std::vector<double> w_return;
    for(size_t i = 0; i < K; ++i)
    {    
        if (w_check_vec[i] < (i+1) * pow(2, 2 * L))
        {
            w_return.push_back(w_check_vec[i]);
        }
        else
        {
            w_return.push_back(w_check_vec[i] - K * (pow(2, 2*L) + 1));
        }
    }

    int y = 0;
    for (size_t i = 0; i < K; ++i)
    {
        y += w_final[i] * pow(2, L * i);
    }

    return y;
}

int main()
{   
    std::cout << shonhage_shtrassen(21, 21);
    // std::cout<< "!"<< vec_in_num({1,0,0,1,1,0,1}) <<"!";
    return 0;
}