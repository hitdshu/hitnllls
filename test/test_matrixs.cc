#include "catch/catch.hpp"
#include "matrix/matrixs.h"

TEST_CASE( "Test sparse matrix operation", "[matrixs]") {
    ::hitnlls::matrix::Matrixsf ms1(3, 3);
    ms1(0, 0) = 0.05;
    ms1(0, 1) = 0.02;
    ms1(1, 0) = 0.02;
    ms1(1, 1) = 0.01;
    ms1(2, 2) = 1;
    ::hitnlls::matrix::Matrixsf ms2(3, 4);
    ms2(0, 0) = 2;
    ms2(1, 2) = 5;
    ms2(2, 2) = 9;
    ::hitnlls::matrix::Matrixsf ms = ms1 * ms2;
    REQUIRE(ms(0, 0) == Approx(0.2));
    REQUIRE(ms(1, 0) == Approx(0.09));
    REQUIRE(ms(2, 0) == Approx(9));
    ms1.SetLambdalm(2);
    ::hitnlls::matrix::Matrixsf l = ms1.CholeskyLLT();
    REQUIRE(l(0, 0) == Approx(1.43178));
    REQUIRE(l(1, 0) == Approx(0.0139686));
    REQUIRE(l(1, 1) == Approx(1.41768));
    REQUIRE(l(2, 2) == Approx(1.73205));
}

TEST_CASE( "Test sparse matrix operation with dense matrix as elements", "[matrixs]") {
    ::hitnlls::matrix::Matrixsxf sf(2, 2);
    ::hitnlls::matrix::Matrixxf mf1(2, 2);
    mf1(0, 0) = 0.1;
    mf1(0, 1) = 0.02;
    mf1(1, 0) = 0.02;
    mf1(1, 1) = 0.3;
    sf(0, 0) = mf1;
    ::hitnlls::matrix::Matrixxf mf2(2, 2);
    mf2(0, 0) = 0.4;
    mf2(0, 1) = 0.2;
    mf2(1, 0) = 0.2;
    mf2(1, 1) = 0.4;
    sf(1, 1) = mf2;
    ::hitnlls::matrix::Matrixsxf chol = sf.CholeskyLLT();
    REQUIRE((chol(0, 0))(0, 0) == Approx(0.316228));
    REQUIRE((chol(0, 0))(1, 0) == Approx(0.0632455));
    REQUIRE((chol(0, 0))(1, 1) == Approx(0.544059));
    REQUIRE((chol(1, 1))(0, 0) == Approx(0.632456));
    REQUIRE((chol(1, 1))(1, 0) == Approx(0.316228));
    REQUIRE((chol(1, 1))(1, 1) == Approx(0.547723));
}

TEST_CASE( "Test sparse matrix cholesky decomposition with lm lambda", "[matrixs]") {
    ::hitnlls::matrix::Matrixsxf sf(4, 4);
    ::hitnlls::matrix::Matrixxf b00(2, 2);
    b00(0, 0) = 33.4328;
    b00(0, 1) = 11.1395;
    b00(1, 0) = 11.1395;
    b00(1, 1) = 30.0546;
    ::hitnlls::matrix::Matrixxf b10(3, 2);
    b10(0, 0) = -0.8622;
    b10(0, 1) = -1.3941;
    b10(1, 0) = 7.3386;
    b10(1, 1) = 13.4468;
    b10(2, 0) = -0.3757;
    b10(2, 1) = -1.6571;
    ::hitnlls::matrix::Matrixxf b11(3, 3);
    b11(0, 0) = 26.6782;
    b11(0, 1) = -6.3518;
    b11(0, 2) = 2.9747;
    b11(1, 0) = -6.3518;
    b11(1, 1) = 26.1955;
    b11(1, 2) = 5.5299;
    b11(2, 0) = 2.9747;
    b11(2, 1) = 5.5299;
    b11(2, 2) = 17.4060;
    ::hitnlls::matrix::Matrixxf b22(2, 2);
    b22(0, 0) = 23.6090;
    b22(0, 1) = -3.7071;
    b22(1, 0) = -3.7071;
    b22(1, 1) = 14.7363;
    ::hitnlls::matrix::Matrixxf b30(1, 2);
    b30(0, 0) = -0.0810;
    b30(0, 1) = 6.4773;
    ::hitnlls::matrix::Matrixxf b33(1, 1);
    b33(0, 0) = 14.3292;
    sf(0, 0) = b00;
    sf(1, 0) = b10;
    sf(0, 1) = b10.Transpose();
    sf(1, 1) = b11;
    sf(2, 2) = b22;
    sf(3, 0) = b30;
    sf(0, 3) = b30.Transpose();
    sf(3, 3) = b33;
    sf.SetLambdalm(2.0);
    ::hitnlls::matrix::Matrixsxf chol = sf.CholeskyLLT();
    REQUIRE((chol(0, 0))(0, 0) == Approx(5.95255));
    REQUIRE((chol(0, 0))(1, 0) == Approx(1.87138));
    REQUIRE((chol(0, 0))(1, 1) == Approx(5.34346));
    REQUIRE((chol(1, 0))(0, 0) == Approx(-0.144846));
    REQUIRE((chol(1, 0))(0, 1) == Approx(-0.210171));
    REQUIRE((chol(1, 0))(1, 0) == Approx(1.23285));
    REQUIRE((chol(1, 0))(1, 1) == Approx(2.08473));
    REQUIRE((chol(1, 0))(2, 0) == Approx(-0.0631159));
    REQUIRE((chol(1, 0))(2, 1) == Approx(-0.288013));
    REQUIRE((chol(1, 1))(0, 0) == Approx(5.34912));
    REQUIRE((chol(1, 1))(1, 0) == Approx(-1.07215));
    REQUIRE((chol(1, 1))(1, 1) == Approx(4.60217));
    REQUIRE((chol(1, 1))(2, 0) == Approx(0.543085));
    REQUIRE((chol(1, 1))(2, 1) == Approx(1.47548));
    REQUIRE((chol(1, 1))(2, 2) == Approx(4.10452));
    REQUIRE((chol(2, 2))(0, 0) == Approx(5.06053));
    REQUIRE((chol(2, 2))(1, 0) == Approx(-0.732551));
    REQUIRE((chol(2, 2))(1, 1) == Approx(4.02488));
}

TEST_CASE( "Test sparse matrix solve equation", "[matrixs]") {
    ::hitnlls::matrix::Matrixsf ms(3, 3);
    ms(0, 0) = 0.05;
    ms(0, 1) = 0.02;
    ms(1, 0) = 0.02;
    ms(1, 1) = 0.05;
    ms(2, 2) = 1;
    ms.SetLambdalm(2);
    ::hitnlls::matrix::Vecfs b(3);
    b[0] = 1.1;
    b[1] = 2.2;
    b[2] = 3.3;
    ::hitnlls::matrix::Vecfs x = ms.SolveWithlm(b);
    REQUIRE(x(0) == Approx(0.526166));
    REQUIRE(x(1) == Approx(1.06804));
    REQUIRE(x(2) == Approx(1.1));
}

TEST_CASE( "Test sparse matrix solve equation hard case", "[matrixs]") {
    ::hitnlls::matrix::Matrixsxf sf(4, 4);
    ::hitnlls::matrix::Matrixxf b00(2, 2);
    b00(0, 0) = 33.4328;
    b00(0, 1) = 11.1395;
    b00(1, 0) = 11.1395;
    b00(1, 1) = 30.0546;
    ::hitnlls::matrix::Matrixxf b10(3, 2);
    b10(0, 0) = -0.8622;
    b10(0, 1) = -1.3941;
    b10(1, 0) = 7.3386;
    b10(1, 1) = 13.4468;
    b10(2, 0) = -0.3757;
    b10(2, 1) = -1.6571;
    ::hitnlls::matrix::Matrixxf b11(3, 3);
    b11(0, 0) = 26.6782;
    b11(0, 1) = -6.3518;
    b11(0, 2) = 2.9747;
    b11(1, 0) = -6.3518;
    b11(1, 1) = 26.1955;
    b11(1, 2) = 5.5299;
    b11(2, 0) = 2.9747;
    b11(2, 1) = 5.5299;
    b11(2, 2) = 17.4060;
    ::hitnlls::matrix::Matrixxf b22(2, 2);
    b22(0, 0) = 23.6090;
    b22(0, 1) = -3.7071;
    b22(1, 0) = -3.7071;
    b22(1, 1) = 14.7363;
    ::hitnlls::matrix::Matrixxf b30(1, 2);
    b30(0, 0) = -0.0810;
    b30(0, 1) = 6.4773;
    ::hitnlls::matrix::Matrixxf b33(1, 1);
    b33(0, 0) = 14.3292;
    sf(0, 0) = b00;
    sf(1, 0) = b10;
    sf(0, 1) = b10.Transpose();
    sf(1, 1) = b11;
    sf(2, 2) = b22;
    sf(3, 0) = b30;
    sf(0, 3) = b30.Transpose();
    sf(3, 3) = b33;
    sf.SetLambdalm(2.0);
    ::hitnlls::matrix::Vecxsxf vf(4);
    ::hitnlls::matrix::Matrixxf v0(2);
    v0[0] = 1.1;
    v0[1] = 2.2;
    ::hitnlls::matrix::Matrixxf v1(3);
    v1[0] = 3.3;
    v1[1] = 4.4;
    v1[2] = 5.5;
    ::hitnlls::matrix::Matrixxf v2(2);
    v2[0] = 6.6;
    v2[1] = 7.7;
    ::hitnlls::matrix::Matrixxf v3(1);
    v3[0] = 8.8;
    vf[0] = v0;
    vf[1] = v1;
    vf[2] = v2;
    vf[3] = v3;
    ::hitnlls::matrix::Vecxsxf xr = sf.SolveWithlm(vf);
    REQUIRE((xr(0))[0] == Approx(0.0376985));
    REQUIRE((xr(0))[1] == Approx(-0.132674));
    REQUIRE((xr(1))[0] == Approx(0.134182));
    REQUIRE((xr(1))[1] == Approx(0.201534));
    REQUIRE((xr(1))[2] == Approx(0.194821));
    REQUIRE((xr(2))[0] == Approx(0.335065));
    REQUIRE((xr(2))[1] == Approx(0.534295));
    REQUIRE((xr(3))[0] == Approx(0.591727));
}