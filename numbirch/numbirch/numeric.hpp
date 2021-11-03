/**
 * @file
 */
#pragma once

#include "numbirch/array/Array.hpp"
#include "numbirch/array/Scalar.hpp"
#include "numbirch/array/Vector.hpp"
#include "numbirch/array/Matrix.hpp"

namespace numbirch {
/**
 * Logical `not`.
 * 
 * @ingroup numeric
 * 
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<int D>
Array<bool,D> operator!(const Array<bool,D>& A) {
  Array<bool,D> B(A.shape().compact());
  logical_not(A.width(), A.height(), A.data(), A.stride(), B.data(),
      B.stride());
  return B;
}

/**
 * Negation.
 * 
 * @ingroup numeric
 * 
 * @tparam T Arithmetic type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_arithmetic<T>::value,int> = 0>
Array<T,D> operator-(const Array<T,D>& A) {
  Array<T,D> B(A.shape().compact());
  neg(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Addition.
 * 
 * @ingroup numeric
 * 
 * @tparam T Arithmetic type.
 * @tparam U Arithmetic type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * @param B %Array.
 * 
 * @return %Array.
 */
template<class T, class U, int D, std::enable_if_t<
    std::is_arithmetic<T>::value && std::is_arithmetic<U>::value,int> = 0>
Array<typename promote<T,U>::type,D> operator+(const Array<T,D>& A,
    const Array<U,D>& B) {
  assert(A.rows() == B.rows());
  assert(B.columns() == B.columns());

  Array<typename promote<T,U>::type,D> C(A.shape().compact());
  add(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride(),
      C.data(), C.stride());
  return C;
}

/**
 * Scalar division.
 * 
 * @ingroup numeric
 * 
 * @tparam T Arithmetic type.
 * @tparam U Arithmetic type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * @param b Scalar.
 * 
 * @return %Array.
 */
template<class T, class U, int D, std::enable_if_t<
    std::is_arithmetic<T>::value && std::is_arithmetic<U>::value,int> = 0>
Array<typename promote<T,U>::type,D> operator/(const Array<T,D>& A,
    const Scalar<U>& b) {
  Array<typename promote<T,U>::type,D> C(A.shape().compact());
  div(A.width(), A.height(), A.data(), A.stride(), b.data(), C.data(),
      C.stride());
  return C;
}

/**
 * Equal to comparison.
 * 
 * @ingroup numeric
 * 
 * @tparam T Arithmetic type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * @param B %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_arithmetic<T>::value,int> = 0>
Array<bool,D> operator==(const Array<T,D>& A, const Array<T,D>& B) {
  assert(A.rows() == B.rows());
  assert(B.columns() == B.columns());

  Array<bool,D> C(A.shape().compact());
  equal(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride(),
      C.data(), C.stride());
  return C;
}

/**
 * Greater than comparison.
 * 
 * @ingroup numeric
 * 
 * @tparam T Arithmetic type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * @param B %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_arithmetic<T>::value,int> = 0>
Array<bool,D> operator>(const Array<T,D>& A, const Array<T,D>& B) {
  assert(A.rows() == B.rows());
  assert(B.columns() == B.columns());

  Array<bool,D> C(A.shape().compact());
  greater(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride(),
      C.data(), C.stride());
  return C;
}

/**
 * Greater than or equal to comparison.
 * 
 * @ingroup numeric
 * 
 * @tparam T Arithmetic type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * @param B %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_arithmetic<T>::value,int> = 0>
Array<bool,D> operator>=(const Array<T,D>& A, const Array<T,D>& B) {
  assert(A.rows() == B.rows());
  assert(B.columns() == B.columns());

  Array<bool,D> C(A.shape().compact());
  greater_or_equal(A.width(), A.height(), A.data(), A.stride(), B.data(),
      B.stride(), C.data(), C.stride());
  return C;
}

/**
 * Less than comparison.
 * 
 * @ingroup numeric
 * 
 * @tparam T Arithmetic type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * @param B %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_arithmetic<T>::value,int> = 0>
Array<bool,D> operator<(const Array<T,D>& A, const Array<T,D>& B) {
  assert(A.rows() == B.rows());
  assert(B.columns() == B.columns());

  Array<bool,D> C(A.shape().compact());
  less(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride(),
      C.data(), C.stride());
  return C;
}

/**
 * Less than or equal to comparison.
 * 
 * @ingroup numeric
 * 
 * @tparam T Arithmetic type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * @param B %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_arithmetic<T>::value,int> = 0>
Array<bool,D> operator<=(const Array<T,D>& A, const Array<T,D>& B) {
  assert(A.rows() == B.rows());
  assert(B.columns() == B.columns());

  Array<bool,D> C(A.shape().compact());
  less_or_equal(A.width(), A.height(), A.data(), A.stride(), B.data(),
      B.stride(), C.data(), C.stride());
  return C;
}

/**
 * Logical `and`.
 * 
 * @ingroup numeric
 * 
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * @param B %Array.
 * 
 * @return %Array.
 */
template<int D>
Array<bool,D> operator&&(const Array<bool,D>& A, const Array<bool,D>& B) {
  assert(A.rows() == B.rows());
  assert(B.columns() == B.columns());

  Array<bool,D> C(A.shape().compact());
  logical_and(A.width(), A.height(), A.data(), A.stride(), B.data(),
      B.stride(), C.data(), C.stride());
  return C;
}

/**
 * Logical `or`.
 * 
 * @ingroup numeric
 * 
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * @param B %Array.
 * 
 * @return %Array.
 */
template<int D>
Array<bool,D> operator||(const Array<bool,D>& A, const Array<bool,D>& B) {
  assert(A.rows() == B.rows());
  assert(B.columns() == B.columns());

  Array<bool,D> C(A.shape().compact());
  logical_or(A.width(), A.height(), A.data(), A.stride(), B.data(),
      B.stride(), C.data(), C.stride());
  return C;
}

/**
 * Scalar multiplication.
 * 
 * @ingroup numeric
 * 
 * @tparam T Arithmetic type.
 * @tparam U Arithmetic type.
 * @tparam D Number of dimensions.
 * 
 * @param a %Scalar.
 * @param B %Array.
 * 
 * @return %Array.
 */
template<class T, class U, int D, std::enable_if_t<
    std::is_arithmetic<T>::value && std::is_arithmetic<U>::value,int> = 0>
Array<typename promote<T,U>::type,D> operator*(const Scalar<T>& a,
    const Array<U,D>& B) {
  Array<typename promote<T,U>::type,D> C(B.shape().compact());
  mul(C.width(), C.height(), a.data(), B.data(), B.stride(), C.data(),
      C.stride());
  return C;
}

/**
 * Matrix-vector multiplication. Computes @f$y = Ax@f$.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * 
 * @param A %Matrix.
 * @param x %Vector.
 * 
 * @return %Vector.
 */
template<class T, std::enable_if_t<std::is_floating_point<T>::value,int> = 0>
Vector<T> operator*(const Matrix<T>& A, const Vector<T>& x) {
  assert(A.columns() == x.length());

  Vector<T> y(make_shape(A.rows()));
  mul(A.rows(), A.columns(), A.data(), A.stride(), x.data(), x.stride(),
      y.data(), y.stride());
  return y;
}

/**
 * Matrix-matrix multiplication. Computes @f$C = AB@f$.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * 
 * @param A %Matrix.
 * @param B %Matrix.
 * 
 * @return %Matrix.
 */
template<class T, std::enable_if_t<std::is_floating_point<T>::value,int> = 0>
Matrix<T> operator*(const Matrix<T>& A, const Matrix<T>& B) {
  assert(A.columns() == B.rows());

  Matrix<T> C(make_shape(A.rows(), B.columns()));
  mul(C.rows(), C.columns(), A.columns(), A.data(), A.stride(), B.data(),
      B.stride(), C.data(), C.stride());
  return C;
}

/**
 * Not equal to comparison.
 * 
 * @ingroup numeric
 * 
 * @tparam T Arithmetic type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * @param B %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_arithmetic<T>::value,int> = 0>
Array<bool,D> operator!=(const Array<T,D>& A, const Array<T,D>& B) {
  assert(A.rows() == B.rows());
  assert(B.columns() == B.columns());

  Array<bool,D> C(A.shape().compact());
  not_equal(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride(),
      C.data(), C.stride());
  return C;
}

/**
 * Subtraction.
 * 
 * @ingroup numeric
 * 
 * @tparam T Arithmetic type.
 * @tparam U Arithmetic type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * @param B %Array.
 * 
 * @return %Array.
 */
template<class T, class U, int D, std::enable_if_t<
    std::is_arithmetic<T>::value && std::is_arithmetic<U>::value,int> = 0>
Array<typename promote<T,U>::type,D> operator-(const Array<T,D>& A,
    const Array<U,D>& B) {
  assert(A.rows() == B.rows());
  assert(B.columns() == B.columns());

  Array<typename promote<T,U>::type,D> C(A.shape().compact());
  sub(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride(),
      C.data(), C.stride());
  return C;
}

/**
 * Absolute value.
 * 
 * @ingroup numeric
 * 
 * @tparam T Arithmetic type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> abs(const Array<T,D>& A) {
  Array<T,D> B(A.shape().compact());
  abs(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Arc cosine.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> acos(const Array<T,D>& A) {
  Array<T,D> B(A.shape().compact());
  acos(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Arc sine.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> asin(const Array<T,D>& A) {
  Array<T,D> B(A.shape().compact());
  asin(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Arc tangent.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> atan(const Array<T,D>& A) {
  Array<T,D> B(A.shape().compact());
  atan(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Round to smallest integer value not less than argument.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> ceil(const Array<T,D>& A) {
  Array<T,D> B(A.shape().compact());
  ceil(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Inverse of a symmetric positive definite square matrix, via the Cholesky
 * factorization.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * 
 * @param S Symmetric positive definite matrix.
 * 
 * @return Matrix.
 */
template<class T, std::enable_if_t<std::is_floating_point<T>::value,int> = 0>
Matrix<T> cholinv(const Matrix<T>& S) {
  Matrix<T> B(make_shape(S.rows(), S.columns()));
  cholinv(S.rows(), S.data(), S.stride(), B.data(), B.stride());
  return B;
}

/**
 * Cosine.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> cos(const Array<T,D>& A) {
  Array<T,D> B(A.shape().compact());
  cos(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Hyperbolic cosine.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> cosh(const Array<T,D>& A) {
  Array<T,D> B(A.shape().compact());
  cosh(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Count of non-zero elements.
 * 
 * @ingroup numeric
 * 
 * @tparam T Arithmetic type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return Count of non-zero elements in the array.
 */
template<class T, int D, std::enable_if_t<
    std::is_arithmetic<T>::value,int> = 0>
Scalar<int> count(const Array<T,D>& A) {
  Scalar<int> b;
  count(A.width(), A.height(), A.data(), A.stride(), b.data());
  return b;
}

/**
 * Construct diagonal matrix. Diagonal elements are assigned to a given scalar
 * value, while all off-diagonal elements are assigned zero.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * 
 * @param x Scalar to assign to diagonal.
 * @param n Number of rows and columns.
 */
template<class T, std::enable_if_t<std::is_floating_point<T>::value,int> = 0>
Matrix<T> diagonal(const Scalar<T>& x, const int n) {
  Matrix<T> B(make_shape(n, n));
  diagonal(x.data(), n, B.data(), B.stride());
  return B;
}

/**
 * Digamma.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> digamma(const Array<T,D>& A) {
  Array<T,D> B(A.shape().compact());
  digamma(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Exponential.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> exp(const Array<T,D>& A) {
  Array<T,D> B(A.shape().compact());
  exp(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Exponential minus one.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> expm1(const Array<T,D>& A) {
  Array<T,D> B(A.shape().compact());
  expm1(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Round to largest integer value not greater than argument.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> floor(const Array<T,D>& A) {
  Array<T,D> B(A.shape().compact());
  floor(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Inverse of a square matrix.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * 
 * @param A Matrix.
 * 
 * @return Matrix.
 */
template<class T, std::enable_if_t<std::is_floating_point<T>::value,int> = 0>
Matrix<T> inv(const Matrix<T>& A) {
  Matrix<T> B(make_shape(A.rows(), A.columns()));
  inv(A.rows(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Logarithm of the determinant of a symmetric positive definite matrix, via
 * the Cholesky factorization. The determinant of a positive definite matrix
 * is always positive.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * 
 * @param S Symmetric positive definite matrix.
 * 
 * @return Logarithm of the determinant of `S`.
 */
template<class T, std::enable_if_t<std::is_floating_point<T>::value,int> = 0>
Scalar<T> lcholdet(const Matrix<T>& S) {
  Scalar<T> b;
  lcholdet(S.rows(), S.data(), S.stride(), b.data());
  return b;
}

/**
 * Logarithm of the absolute value of the determinant of a square matrix.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * 
 * @param A Matrix.
 * 
 * @return Logarithm of the absolute value of the determinant of `A`.
 */
template<class T, std::enable_if_t<std::is_floating_point<T>::value,int> = 0>
Scalar<T> ldet(const Matrix<T>& A) {
  Scalar<T> b;
  ldet(A.rows(), A.data(), A.stride(), b.data());
  return b;
}

/**
 * Logarithm of the factorial function.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 * 
 * @note The return type `T` must be explicitly specified.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> lfact(const Array<int,D>& A) {
  Array<T,D> B(A.shape().compact());
  lfact(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Gradient of lfact().
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 * 
 * @note The return type `T` must be explicitly specified.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> lfact_grad(const Array<T,D>& G, const Array<int,D>& A) {
  Array<T,D> B(A.shape().compact());
  lfact_grad(A.width(), A.height(), G.data(), G.stride(), A.data(),
      A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Logarithm of the gamma function.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> lgamma(const Array<T,D>& A) {
  Array<T,D> B(A.shape().compact());
  lgamma(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Logarithm.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> log(const Array<T,D>& A) {
  Array<T,D> B(A.shape().compact());
  log(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Logarithm of one plus argument.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> log1p(const Array<T,D>& A) {
  Array<T,D> B(A.shape().compact());
  log1p(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Reciprocal. For element @f$(i,j)@f$, computes @f$B_{ij} = 1/A_{ij}@f$. The
 * division is as for the type `T`; this will always return zero for an
 * integer type.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> rcp(const Array<T,D>& A) {
  Array<T,D> B(A.shape().compact());
  rcp(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Rectification. For element @f$(i,j)@f$, computes @f$B_{ij} = \max(A_{ij},
 * 0)@f$.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> rectify(const Array<T,D>& A) {
  Array<T,D> B(A.shape().compact());
  rectify(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Gradient of rectify().
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> rectify_grad(const Array<T,D>& G, const Array<T,D>& A) {
  Array<T,D> B(A.shape().compact());
  rectify_grad(A.width(), A.height(), G.data(), G.stride(), A.data(),
      A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Round to nearest integer value.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> round(const Array<T,D>& A) {
  Array<T,D> B(A.shape().compact());
  round(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Sine.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> sin(const Array<T,D>& A) {
  Array<T,D> B(A.shape().compact());
  sin(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Construct single-entry vector. One of the elements of the vector is one,
 * all others are zero.
 * 
 * @ingroup numeric
 * 
 * @tparam T Arithmetic type.
 * 
 * @param i Index of single entry (1-based).
 * @param n Length of vector.
 */
template<class T, std::enable_if_t<std::is_arithmetic<T>::value,int> = 0>
Vector<T> single(const Scalar<int>& i, const int n) {
  Vector<T> x(make_shape(n));
  single(i.data(), n, x.data(), x.stride());
  return x;
}

/**
 * Hyperbolic sine.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> sinh(const Array<T,D>& A) {
  Array<T,D> B(A.shape().compact());
  sinh(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Square root.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> sqrt(const Array<T,D>& A) {
  Array<T,D> B(A.shape().compact());
  sqrt(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Sum of elements.
 * 
 * @ingroup numeric
 * 
 * @tparam T Arithmetic type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return Sum of elements of the array.
 */
template<class T, int D, std::enable_if_t<
    std::is_arithmetic<T>::value,int> = 0>
Scalar<T> sum(const Array<T,D>& A) {
  Scalar<T> b;
  sum(A.width(), A.height(), A.data(), A.stride(), b.data());
  return b;
}

/**
 * Tangent.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> tan(const Array<T,D>& A) {
  Array<T,D> B(A.shape().compact());
  tan(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Hyperbolic tangent.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> tanh(const Array<T,D>& A) {
  Array<T,D> B(A.shape().compact());
  tanh(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride());
  return B;
}

/**
 * Matrix trace.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * 
 * @param A Matrix.
 * 
 * @return Trace of the matrix.
 */
template<class T, std::enable_if_t<std::is_floating_point<T>::value,int> = 0>
Scalar<T> trace(const Matrix<T>& A) {
  Scalar<T> b;
  trace(A.rows(), A.columns(), A.data(), A.stride(), b.data());
  return b;
}

/**
 * Scalar product and transpose. Computes @f$B = xA^\top@f$.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * 
 * @param A Matrix.
 * 
 * @return Matrix.
 */
template<class T, std::enable_if_t<std::is_floating_point<T>::value,int> = 0>
Matrix<T> transpose(const Matrix<T>& A) {
  Matrix<T> B(make_shape(A.columns(), A.rows()));
  transpose(B.rows(), B.columns(), A.data(), A.stride(), B.data(),
      B.stride());
  return B;
}

/**
 * Lower-triangular Cholesky factor of a matrix multiplied by a vector.
 * Computes @f$y = Lx@f$, where @f$S = LL^\top@f$.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * 
 * @param S Symmetric positive definite matrix.
 * @param x Vector.
 * 
 * @return Vector.
 */
template<class T, std::enable_if_t<std::is_floating_point<T>::value,int> = 0>
Vector<T> cholmul(const Matrix<T>& S, const Vector<T>& x) {
  assert(S.rows() == S.columns());
  assert(S.columns() == x.length());

  Vector<T> y(make_shape(S.rows()));
  cholmul(y.rows(), S.data(), S.stride(), x.data(), x.stride(), y.data(),
      y.stride());
  return y;
}

/**
 * Lower-triangular Cholesky factor of a matrix multiplied by a matrix.
 * Computes @f$C = LB@f$, where @f$S = LL^\top@f$.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * 
 * @param S Symmetric positive definite matrix.
 * @param B Matrix.
 * 
 * @return Matrix.
 */
template<class T, std::enable_if_t<std::is_floating_point<T>::value,int> = 0>
Matrix<T> cholmul(const Matrix<T>& S, const Matrix<T>& B) {
  assert(S.rows() == S.columns());
  assert(S.columns() == S.rows());

  Matrix<T> C(make_shape(S.rows(), B.columns()));
  cholmul(C.rows(), C.columns(), S.data(), S.stride(), B.data(), B.stride(),
      C.data(), C.stride());
  return C;
}

/**
 * Outer product of matrix and lower-triangular Cholesky factor of another
 * matrix. Computes @f$C = AL^\top@f$, where @f$S = LL^\top@f$.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * 
 * @param A Matrix.
 * @param S Symmetric positive definite matrix.
 * 
 * @return Matrix.
 */
template<class T, std::enable_if_t<std::is_floating_point<T>::value,int> = 0>
Matrix<T> cholouter(const Matrix<T>& A, const Matrix<T>& S) {
  assert(A.columns() == S.columns());
  assert(S.rows() == S.columns());

  Matrix<T> C(make_shape(A.rows(), S.rows()));
  cholouter(C.rows(), C.columns(), A.data(), A.stride(), S.data(), S.stride(),
      C.data(), C.stride());
  return C;
}

/**
 * Matrix-vector solve, via the Cholesky factorization. Solves for @f$x@f$ in
 * @f$Sx = y@f$.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * 
 * @param S Symmetric positive definite matrix.
 * @param y Vector.
 * 
 * @return Vector.
 */
template<class T, std::enable_if_t<std::is_floating_point<T>::value,int> = 0>
Vector<T> cholsolve(const Matrix<T>& S, const Vector<T>& y) {
  assert(S.rows() == S.columns());
  assert(S.rows() == y.length());

  Vector<T> x(make_shape(y.length()));
  cholsolve(x.rows(), S.data(), S.stride(), x.data(), x.stride(), y.data(),
      y.stride());
  return x;
}

/**
 * Matrix-matrix solve, via the Cholesky factorization. Solves for @f$A@f$ in
 * @f$SA = B@f$.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * 
 * @param S Symmetric positive definite matrix.
 * @param B Matrix.
 * 
 * @return Matrix.
 */
template<class T, std::enable_if_t<std::is_floating_point<T>::value,int> = 0>
Matrix<T> cholsolve(const Matrix<T>& S, const Matrix<T>& B) {
  assert(S.rows() == S.columns());
  assert(S.rows() == B.rows());

  Matrix<T> A(make_shape(B.rows(), B.columns()));
  cholsolve(A.rows(), A.columns(), S.data(), S.stride(), A.data(), A.stride(),
      B.data(), B.stride());
  return A;
}

/**
 * Copy sign of a number.
 * 
 * @ingroup numeric
 * 
 * @tparam T Arithmetic type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * @param B %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_arithmetic<T>::value,int> = 0>
Array<T,D> copysign(const Array<T,D>& A, const Array<T,D>& B) {
  assert(A.rows() == B.rows());
  assert(A.columns() == B.columns());

  Array<T,D> C(A.shape().compact());
  copysign(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride(),
      C.data(), C.stride());
  return C;
}

/**
 * Multivariate digamma function.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * @param B %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> digamma(const Array<T,D>& A, const Array<int,D>& B) {
  assert(A.rows() == B.rows());
  assert(A.columns() == B.columns());

  Array<T,D> C(A.shape().compact());
  digamma(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride(),
      C.data(), C.stride());
  return C;
}

/**
 * Vector-vector dot product. Computes @f$x^\top y@f$, resulting in a scalar.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * 
 * @param x Vector.
 * @param y Vector.
 * 
 * @return Dot product.
 */
template<class T, std::enable_if_t<std::is_floating_point<T>::value,int> = 0>
Scalar<T> dot(const Vector<T>& x, const Vector<T>& y) {
  assert(x.length() == y.length());
  Scalar<T> z;
  dot(x.length(), x.data(), x.stride(), y.data(), y.stride(), z.data());
  return z;
}

/**
 * Vector-matrix dot product. Equivalent to inner() with the arguments
 * reversed: computes @f$A^\top x@f$, resulting in a vector.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * 
 * @param x Vector.
 * @param A Matrix.
 * 
 * @return Vector giving the dot product of @p x with each column of @p A.
 */
template<class T, std::enable_if_t<std::is_floating_point<T>::value,int> = 0>
Vector<T> dot(const Vector<T>& x, const Matrix<T>& A) {
  return inner(A, x);
}

/**
 * Matrix-matrix Frobenius product. Computes @f$\langle A, B 
 * \rangle_\mathrm{F} = \mathrm{Tr}(A^\top B) = \sum_{ij} A_{ij} B_{ij}@f$,
 * resulting in a scalar.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * 
 * @param A Matrix.
 * @param B Matrix.
 * 
 * @return Frobenius product.
 */
template<class T, std::enable_if_t<std::is_floating_point<T>::value,int> = 0>
Scalar<T> frobenius(const Matrix<T>& A, const Matrix<T>& B) {
  assert(A.rows() == B.rows());
  assert(A.columns() == B.columns());
  Scalar<T> c;
  frobenius(A.rows(), A.columns(), A.data(), A.stride(), B.data(), B.stride(),
      c.data());
  return c;
}

/**
 * Normalized lower incomplete gamma function.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * @param B %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> gamma_p(const Array<T,D>& A, const Array<T,D>& B) {
  assert(A.rows() == B.rows());
  assert(A.columns() == B.columns());

  Array<T,D> C(A.shape().compact());
  gamma_p(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride(),
      C.data(), C.stride());
  return C;
}

/**
 * Normalized upper incomplete gamma function.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * @param B %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> gamma_q(const Array<T,D>& A, const Array<T,D>& B) {
  assert(A.rows() == B.rows());
  assert(A.columns() == B.columns());

  Array<T,D> C(A.shape().compact());
  gamma_q(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride(),
      C.data(), C.stride());
  return C;
}

/**
 * Hadamard (element-wise) matrix multiplication.
 * 
 * @ingroup numeric
 * 
 * @tparam T Arithmetic type.
 * @tparam U Arithmetic type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * @param B %Array.
 * 
 * @return %Array.
 */
template<class T, class U, int D, std::enable_if_t<
    std::is_arithmetic<T>::value && std::is_arithmetic<U>::value,int> = 0>
Array<typename promote<T,U>::type,D> hadamard(const Array<T,D>& A,
    const Array<U,D>& B) {
  assert(A.rows() == B.rows());
  assert(A.columns() == B.columns());

  Array<typename promote<T,U>::type,D> C(A.shape().compact());
  hadamard(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride(),
      C.data(), C.stride());
  return C;
}

/**
 * Matrix-vector inner product. Computes @f$y = A^\top x@f$.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * 
 * @param A Matrix.
 * @param x Vector.
 * 
 * @return Vector.
 */
template<class T, std::enable_if_t<std::is_floating_point<T>::value,int> = 0>
Vector<T> inner(const Matrix<T>& A, const Vector<T>& x) {
  assert(A.rows() == x.length());
  
  Vector<T> y(make_shape(A.columns()));
  inner(y.rows(), A.rows(), A.data(), A.stride(), x.data(), x.stride(),
      y.data(), y.stride());
  return y;
}

/**
 * Matrix-matrix inner product. Computes @f$C = A^\top B@f$.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * 
 * @param A Matrix.
 * @param B Matrix.
 * 
 * @return Matrix.
 */
template<class T, std::enable_if_t<std::is_floating_point<T>::value,int> = 0>
Matrix<T> inner(const Matrix<T>& A, const Matrix<T>& B) {
  assert(A.rows() == B.rows());

  Matrix<T> C(make_shape(A.columns(), B.columns()));
  inner(C.rows(), C.columns(), A.rows(), A.data(), A.stride(), B.data(),
      B.stride(), C.data(), C.stride());
  return C;
}

/**
 * Logarithm of the beta function.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * @param B %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> lbeta(const Array<T,D>& A, const Array<T,D>& B) {
  assert(A.rows() == B.rows());
  assert(A.columns() == B.columns());

  Array<T,D> C(A.shape().compact());
  lbeta(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride(),
      C.data(), C.stride());
  return C;
}

/**
 * Logarithm of the binomial coefficient.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * @param B %Array.
 * 
 * @return %Array.
 * 
 * @note The return type `T` must be explicitly specified.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> lchoose(const Array<int,D>& A, const Array<int,D>& B) {
  assert(A.rows() == B.rows());
  assert(A.columns() == B.columns());

  Array<T,D> C(A.shape().compact());
  lchoose(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride(),
      C.data(), C.stride());
  return C;
}

/**
 * Gradient of lchoose().
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param G %Array.
 * @param A %Array.
 * @param B %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
std::pair<Array<T,D>,Array<T,D>> lchoose_grad(const Array<T,D>& G,
    const Array<int,D>& A, const Array<int,D>& B) {
  assert(G.rows() == A.rows());
  assert(G.columns() == A.columns());
  assert(G.rows() == B.rows());
  assert(G.columns() == B.columns());

  Array<T,D> GA(A.shape().compact());
  Array<T,D> GB(A.shape().compact());
  lchoose_grad(G.width(), G.height(), G.data(), G.stride(), A.data(),
      A.stride(), B.data(), B.stride(), GA.data(), GA.stride(), GB.data(),
      GB.stride());
  return std::make_pair(GA, GB);
}

/**
 * Logarithm of the multivariate gamma function.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * @param B %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> lgamma(const Array<T,D>& A, const Array<int,D>& B) {
  assert(A.rows() == B.rows());
  assert(A.columns() == B.columns());

  Array<T,D> C(A.shape().compact());
  lgamma(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride(),
      C.data(), C.stride());
  return C;
}

/**
 * Vector-vector outer product. Computes @f$A = xy^\top@f$.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * 
 * @param x Vector.
 * @param y Vector.
 * 
 * @return Matrix.
 */
template<class T, std::enable_if_t<std::is_floating_point<T>::value,int> = 0>
Matrix<T> outer(const Vector<T>& x, const Vector<T>& y) {
  Matrix<T> C(make_shape(x.length(), y.length()));
  outer(C.rows(), C.columns(), x.data(), x.stride(), y.data(), y.stride(),
      C.data(), C.stride());
  return C;
}

/**
 * Matrix-matrix outer product. Computes @f$C = AB^\top@f$.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * 
 * @param A Matrix.
 * @param B Matrix.
 * 
 * @return Matrix.
 */
template<class T, std::enable_if_t<std::is_floating_point<T>::value,int> = 0>
Matrix<T> outer(const Matrix<T>& A, const Matrix<T>& B) {
  assert(A.columns() == B.columns());

  Matrix<T> C(make_shape(A.rows(), B.rows()));
  outer(C.rows(), C.columns(), A.columns(), A.data(), A.stride(), B.data(),
      B.stride(), C.data(), C.stride());
  return C;
}

/**
 * Power.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * @param B %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> pow(const Array<T,D>& A, const Array<T,D>& B) {
  assert(A.rows() == B.rows());
  assert(A.columns() == B.columns());

  Array<T,D> C(A.shape().compact());
  pow(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride(),
      C.data(), C.stride());
  return C;
}

/**
 * Construct single-entry matrix. One of the elements of the matrix is one,
 * all others are zero.
 * 
 * @ingroup numeric
 * 
 * @tparam T Arithmetic type.
 * 
 * @param i Row index of single entry (1-based).
 * @param j Column index of single entry (1-based).
 * @param m Number of rows.
 * @param n Number of columns.
 * 
 * @return %Matrix.
 * 
 * @note The return type `T` must be explicitly specified.
 */
template<class T, std::enable_if_t<std::is_arithmetic<T>::value,int> = 0>
Matrix<T> single(const Scalar<int>& i, const Scalar<int>& j, const int m,
    const int n) {
  Matrix<T> A(make_shape(m, n));
  single(i.data(), j.data(), m, n, A.data(), A.stride());
  return A;
}

/**
 * Matrix-vector solve. Solves for @f$x@f$ in @f$Ax = y@f$.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * 
 * @param A Matrix.
 * @param y Vector.
 * 
 * @return Vector.
 */
template<class T, std::enable_if_t<std::is_floating_point<T>::value,int> = 0>
Vector<T> solve(const Matrix<T>& A, const Vector<T>& y) {
  assert(A.rows() == A.columns());
  assert(A.rows() == y.length());

  Vector<T> x(make_shape(y.length()));
  solve(x.rows(), A.data(), A.stride(), x.data(), x.stride(), y.data(),
      y.stride());
  return x;
}

/**
 * Matrix-matrix solve. Solves for @f$B@f$ in @f$AB = C@f$.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * 
 * @param A Matrix.
 * @param C Matrix.
 * 
 * @return Matrix.
 */
template<class T, std::enable_if_t<std::is_floating_point<T>::value,int> = 0>
Matrix<T> solve(const Matrix<T>& A, const Matrix<T>& C) {
  assert(A.rows() == A.columns());
  assert(A.rows() == C.rows());

  Matrix<T> B(make_shape(C.rows(), C.columns()));
  solve(A.rows(), A.columns(), A.data(), A.stride(), B.data(), B.stride(),
      C.data(), C.stride());
  return A;
}

/**
 * Normalized incomplete beta function.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam U Arithmetic type.
 * @tparam D Number of dimensions.
 * 
 * @param A %Array.
 * @param B %Array.
 * @param X %Array.
 * 
 * @return %Array.
 */
template<class T, class U, int D, std::enable_if_t<
    std::is_floating_point<T>::value && std::is_arithmetic<U>::value,int> = 0>
Array<T,D> ibeta(const Array<U,D>& A, const Array<U,D>& B,
    const Array<T,D>& X) {
  assert(A.rows() == B.rows());
  assert(A.columns() == B.columns());
  assert(A.rows() == X.rows());
  assert(A.columns() == X.columns());

  Array<T,D> C(A.shape().compact());
  ibeta(A.width(), A.height(), A.data(), A.stride(), B.data(), B.stride(),
      X.data(), X.stride(), C.data(), C.stride());
  return C;
}

/**
 * Linear combination of matrices.
 * 
 * @ingroup numeric
 * 
 * @tparam T Floating point type.
 * @tparam D Number of dimensions.
 * 
 * @param a Coefficient on `A`.
 * @param A %Array.
 * @param b Coefficient on `B`.
 * @param B %Array.
 * @param c Coefficient on `C`.
 * @param C %Array.
 * @param e Coefficient on `D`.
 * @param E %Array.
 * 
 * @return %Array.
 */
template<class T, int D, std::enable_if_t<
    std::is_floating_point<T>::value,int> = 0>
Array<T,D> combine(const T a, const Array<T,D>& A, const T b,
    const Array<T,D>& B, const T c, const Array<T,D>& C, const T e,
    const Array<T,D>& E) {
  assert(A.rows() == B.rows());
  assert(A.rows() == C.rows());
  assert(A.rows() == E.rows());
  assert(A.columns() == B.columns());
  assert(A.columns() == C.columns());
  assert(A.columns() == E.columns());

  Array<T,D> F(A.shape().compact());
  combine(F.width(), F.height(), a, A.data(), A.stride(), b, B.data(),
      B.stride(), c, C.data(), C.stride(), e, E.data(), E.stride(), F.data(),
      F.stride());
  return F;
}

}
