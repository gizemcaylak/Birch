/**
 * Linear transformation of a multivariate normal-inverse-gamma random
 * variate.
 */
class TransformMultivariateLinearNormalInverseGamma(A:Real[_,_],
    x:DelayMultivariateNormalInverseGamma, c:Real[_]) <
    TransformMultivariateLinear<Real>(A, c) {
  /**
   * Random variate.
   */
  x:DelayMultivariateNormalInverseGamma <- x;
}

function TransformMultivariateLinearNormalInverseGamma(A:Real[_,_],
    x:DelayMultivariateNormalInverseGamma, c:Real[_]) ->
    TransformMultivariateLinearNormalInverseGamma {
  m:TransformMultivariateLinearNormalInverseGamma(A, x, c);
  return m;    
}

function TransformMultivariateLinearNormalInverseGamma(A:Real[_,_],
    x:DelayMultivariateNormalInverseGamma) ->
    TransformMultivariateLinearNormalInverseGamma {
  return TransformMultivariateLinearNormalInverseGamma(A, x,
      vector(0.0, rows(A)));
}
