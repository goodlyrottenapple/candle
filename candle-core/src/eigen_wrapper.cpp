#include <Eigen/Dense>
#include <cstdint>
extern "C" {

void matmul_i64(
    int32_t A_cs, // A column stride
    int32_t A_rs, // A row stride
    const int64_t* A, // K x M
    int32_t B_cs, // B column stride
    int32_t B_rs, // B row stride
    const int64_t* B, // N x K
    int32_t C_cs, // output column stride
    int32_t C_rs, // output row stride
    int64_t* C,       // N x M (output)
    int32_t K, int32_t M, int32_t N
) {
    using ConstI64Map = Eigen::Map<const Eigen::Matrix<int64_t, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>, 0, Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>>;
    using I64Map = Eigen::Map<Eigen::Matrix<int64_t, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>, 0, Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>>;

    ConstI64Map matA(A, K, M, Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>(A_cs, A_rs));
    ConstI64Map matB(B, N, K, Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>(B_cs, B_rs));
    I64Map matC(C, N, M, Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>(C_cs, C_rs));

    matC.noalias() = matB * matA;
}

}
