/**
 * Particle for use with MoveParticleFilter.
 *
 * - m: Model.
 *
 * The Particle class hierarchy is as follows:
 * <center>
 * <object type="image/svg+xml" data="../../figs/Particle.svg"></object>
 * </center>
 */
class MoveParticle(m:Model) < Particle(m) {
  /**
   * Log-likelihoods. Each element is a lazy expression giving a single
   * step's contribution to the log-likelihood.
   */
  zs:Vector<Expression<Real>>;
  
  /**
   * Log-priors. Each element is a lazy expression giving a single step's
   * contribution to the log-prior.
   */
  ps:Vector<Expression<Real>>;
  
  /**
   * Log-posterior density.
   */
  π:Real <- 0.0;

  /**
   * Number of steps.
   */
  function size() -> Integer {
    return zs.size();
  } 

  /**
   * Add a new step.
   *
   * - t: The step number, beginning at 0.
   * - z: Expression giving the incremental log-likelihood for th new step.
   *
   * Returns: Incremental log-likelihood; zero if the argument is `nil`.
   */
  function augment(t:Integer, z:Expression<Real>?) -> Real {
    /* likelihood */
    auto z' <- z;
    if !z'? {
      z' <- box(0.0);
    }
    auto w <- z'!.pilot(t);
    π <- π + w;
    zs.pushBack(z'!);
    
    /* prior */
    auto p <- z'!.prior();
    if !p? {
      p <- box(0.0);
    }
    π <- π + p!.pilot(t);
    ps.pushBack(p!);

    return w;
  }

  /**
   * Remove the oldest step.
   */
  function truncate() {
    /* calling value() on these expressions has the side effect of making
     * them constant, so that Random objects appearing in them will be
     * ineligible for moves in future; that's what we want */
    if !zs.empty() {
      π <- π - zs.front().get();
      zs.popFront();
    }
    if !ps.empty() {
      π <- π - ps.front().get();
      ps.popFront();
    }
  }
  
  /**
   * Compute gradient.
   */
  function grad(gen:Integer) {
    auto L <- size();    
    for l in 1..L {
      zs.get(l).grad(gen, 1.0);
      ps.get(l).grad(gen, 1.0);
    }
  }

  /**
   * Move.
   *
   * - gen: Generation limit.
   * - κ: Markov kernel.
   */
  function move(gen:Integer, κ:Kernel) {
    auto L <- size();    
    auto π <- 0.0;
    for l in 1..L {
      π <- π + zs.get(l).move(gen, κ);
      π <- π + ps.get(l).move(gen, κ);
    }
    this.π <- π;
  }

  /**
   * Compute log-ratio of proposal after move.
   *
   * - gen: Generation limit.
   * - x: Original state $x$.
   * - κ: Markov kernel.
   *
   * Returns: $\log q(x^\prime \mid x)$.
   */
  function compare(gen:Integer, x:MoveParticle, κ:Kernel) -> Real {
    assert size() == x.size();
    auto L <- size();    
    auto w <- 0.0;
    for l in 1..L {
      w <- w + zs.get(l).compare(gen, x.zs.get(l), κ);
      w <- w + ps.get(l).compare(gen, x.ps.get(l), κ);
    }
    return w;
  }
}

/**
 * Create a MoveParticle.
 */
function MoveParticle(m:Model) -> MoveParticle {
  return construct<MoveParticle>(m);
}