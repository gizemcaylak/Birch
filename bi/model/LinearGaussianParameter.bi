/**
 * Parameter model for Linear-Gaussian state-space model.
 */
class LinearGaussianParameter < Parameter {
  a:Real <- 0.8;
  σ2_x:Real <- 1.0;
  σ2_y:Real <- 0.1;
}
