/**
 * @file
 */
#include "numbirch/numeric.hpp"

#ifdef BACKEND_CUDA
#include "numbirch/cuda/transform.hpp"
#endif
#ifdef BACKEND_EIGEN
#include "numbirch/eigen/transform.hpp"
#endif
#include "numbirch/common/unary.hpp"

/**
 * @internal
 * 
 * @def UNARY_ARITHMETIC
 * 
 * Explicitly instantiate a unary transformation `f` where the return type is
 * any arithmetic type.
 */
#define UNARY_ARITHMETIC(f) \
    UNARY_FIRST(f, double) \
    UNARY_FIRST(f, float) \
    UNARY_FIRST(f, int) \
    UNARY_FIRST(f, bool)
#define UNARY_RETURN(f) \
    UNARY_FIRST(f, double) \
    UNARY_FIRST(f, float)
#define UNARY_FIRST(f, R) \
    UNARY_DIM(f, R, double) \
    UNARY_DIM(f, R, float) \
    UNARY_DIM(f, R, int) \
    UNARY_DIM(f, R, bool)
#define UNARY_DIM(f, R, T) \
    UNARY_SIG(f, R, ARRAY(T, 2)) \
    UNARY_SIG(f, R, ARRAY(T, 1)) \
    UNARY_SIG(f, R, ARRAY(T, 0)) \
    UNARY_SIG(f, R, T)
#define UNARY_SIG(f, R, T) \
    template explicit_t<R,T> f<R,T,int>(const T&);

/**
 * @internal
 * 
 * @def UNARY_ARITHMETIC_OPERATOR
 * 
 * Explicitly instantiate a unary transformation `f` where the return type is
 * any arithmetic type. This version is used for operators, where the overload
 * for basic types is omitted, as this is not allowed in C++ (e.g.
 * `operator-(double)`).
 */
#define UNARY_OPERATOR(f) \
    UNARY_OPERATOR_FIRST(f, double) \
    UNARY_OPERATOR_FIRST(f, float) \
    UNARY_OPERATOR_FIRST(f, int) \
    UNARY_OPERATOR_FIRST(f, bool)
#define UNARY_OPERATOR_RETURN(f) \
    UNARY_OPERATOR_FIRST(f, double) \
    UNARY_OPERATOR_FIRST(f, float)
#define UNARY_OPERATOR_FIRST(f, R) \
    UNARY_OPERATOR_DIM(f, R, double) \
    UNARY_OPERATOR_DIM(f, R, float) \
    UNARY_OPERATOR_DIM(f, R, int) \
    UNARY_OPERATOR_DIM(f, R, bool)
#define UNARY_OPERATOR_DIM(f, R, T) \
    UNARY_OPERATOR_SIG(f, R, ARRAY(T, 2)) \
    UNARY_OPERATOR_SIG(f, R, ARRAY(T, 1)) \
    UNARY_OPERATOR_SIG(f, R, ARRAY(T, 0))
#define UNARY_OPERATOR_SIG(f, R, T) \
    template explicit_t<R,T> f<R,T,int>(const T&);

/**
 * @internal
 * 
 * @def UNARY_FLOATING_POINT
 * 
 * Explicitly instantiate a unary transformation `f` where the return type is
 * any floating point type.
 */
#define UNARY_FLOATING_POINT(f) \
    UNARY_FIRST(f, double) \
    UNARY_FIRST(f, float)

/**
 * @internal
 * 
 * @def UNARY_GRAD
 * 
 * Explicitly instantiate the gradient of a unary transformation `f`.
 */
#define UNARY_GRAD(f) \
    UNARY_GRAD_FIRST(f, double) \
    UNARY_GRAD_FIRST(f, float)
#define UNARY_GRAD_FIRST(f, G) \
    UNARY_GRAD_DIM(f, G, double) \
    UNARY_GRAD_DIM(f, G, float) \
    UNARY_GRAD_DIM(f, G, int) \
    UNARY_GRAD_DIM(f, G, bool)
#define UNARY_GRAD_DIM(f, G, T) \
    UNARY_GRAD_SIG(f, ARRAY(G, 2), ARRAY(T, 2)) \
    UNARY_GRAD_SIG(f, ARRAY(G, 1), ARRAY(T, 1)) \
    UNARY_GRAD_SIG(f, ARRAY(G, 0), ARRAY(T, 0)) \
    UNARY_GRAD_SIG(f, ARRAY(G, 0), T) \
    UNARY_GRAD_SIG(f, G, ARRAY(T, 0)) \
    UNARY_GRAD_SIG(f, G, T)
#define UNARY_GRAD_SIG(f, G, T) \
    template implicit_t<G,T> f<G,T,int>(const G&, const T&);

namespace numbirch {
UNARY_OPERATOR(operator+)
UNARY_OPERATOR(operator-)
UNARY_OPERATOR(operator!)
UNARY_ARITHMETIC(abs)
UNARY_FLOATING_POINT(acos)
UNARY_FLOATING_POINT(asin)
UNARY_FLOATING_POINT(atan)
UNARY_ARITHMETIC(ceil)
UNARY_FLOATING_POINT(cos)
UNARY_FLOATING_POINT(cosh)
UNARY_FLOATING_POINT(digamma)
UNARY_FLOATING_POINT(exp)
UNARY_FLOATING_POINT(expm1)
UNARY_ARITHMETIC(floor)
UNARY_FLOATING_POINT(lfact)
UNARY_GRAD(lfact_grad)
UNARY_FLOATING_POINT(lgamma)
UNARY_FLOATING_POINT(log)
UNARY_FLOATING_POINT(log1p)
UNARY_FLOATING_POINT(rcp)
UNARY_ARITHMETIC(rectify)
UNARY_GRAD(rectify_grad)
UNARY_ARITHMETIC(round)
UNARY_FLOATING_POINT(sin)
UNARY_FLOATING_POINT(sinh)
UNARY_FLOATING_POINT(sqrt)
UNARY_FLOATING_POINT(tan)
UNARY_FLOATING_POINT(tanh)

}
