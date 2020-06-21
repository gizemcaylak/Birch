/**
 * Unary map.
 *
 * - x: Operand.
 * - f: Operator.
 *
 * Applies `f` to each element of `X`.
 */
function for_each<Type>(x:Type[_], f:\(Type)) {
  for i in 1..length(x) {
    f(x[i]);
  }
}

/**
 * Unary map.
 *
 * - X: Operand.
 * - f: Operator.
 *
 * Applies `f` to each element of `X`.
 */
function for_each<Type>(X:Type[_,_], f:\(Type)) {
  for i in 1..rows(X) {
    for j in 1..columns(X) {
      f(X[i,j]);
    }
  }
}

/**
 * Binary map.
 *
 * - x: First operand.
 * - y: Second operand.
 * - f: Operator.
 */
function for_each<Input1,Input2>(x:Input1[_], y:Input2[_],
    f:\(Input1, Input2)) {
  assert length(x) == length(y);
  for i in 1..length(x) {
    f(x[i], y[i]);
  }
}

/**
 * Binary map.
 *
 * - X: First operand.
 * - Y: Second operand.
 * - f: Operator.
 */
function for_each<Input1,Input2>(X:Input1[_,_], Y:Input2[_,_],
    f:\(Input1, Input2)) {
  assert rows(X) == rows(Y);
  assert columns(X) == columns(Y);
  for i in 1..rows(X) {
    for j in 1..columns(X) {
      f(X[i,j], Y[i,j]);
    }
  }
}

/**
 * Ternary map.
 *
 * - x: First operand.
 * - y: Second operand.
 * - z: Third operand.
 * - f: Operator.
 */
function for_each<Input1,Input2,Input3>(x:Input1[_], y:Input2[_],
    z:Input3[_], f:\(Input1, Input2, Input3)) {
  assert length(x) == length(y);
  assert length(y) == length(z);
  for i in 1..length(x) {
    f(x[i], y[i], z[i]);
  }
}

/**
 * Ternary map.
 *
 * - X: First operand.
 * - Y: Second operand.
 * - Z: Third operand.
 * - f: Operator.
 */
function for_each<Input1,Input2,Input3>(X:Input1[_,_], Y:Input2[_,_],
    Z:Input3[_,_], f:\(Input1, Input2, Input3)) {
  assert rows(X) == rows(Y);
  assert rows(Y) == rows(Z);
  assert columns(X) == columns(Y);
  assert columns(Y) == columns(Z);
  for i in 1..rows(X) {
    for j in 1..columns(X) {
      f(X[i,j], Y[i,j], Z[i,j]);
    }
  }
}

/**
 * Unary transformation.
 *
 * - x: Operand.
 * - f: Operator.
 */
function transform<Input,Output>(x:Input[_], f:\(Input) -> Output) ->
    Output[_] {
  return vector(\(i:Integer) -> Output {
        return f(x[i]);
      }, length(x));
}

/**
 * Unary transformation.
 *
 * - X: Operand.
 * - f: Operator.
 */
function transform<Input,Output>(X:Input[_,_], f:\(Input) -> Output) ->
    Output[_,_] {
  return matrix(\(i:Integer, j:Integer) -> Output {
        return f(X[i,j]);
      }, rows(X), columns(X));
}

/**
 * Binary transformation.
 *
 * - x: First operand.
 * - y: Second operand.
 * - f: Operator.
 */
function transform<Input1,Input2,Output>(x:Input1[_], y:Input2[_],
    f:\(Input1, Input1) -> Output) -> Output[_] {
  assert length(x) == length(y);
  return vector(\(i:Integer) -> Output {
        return f(x[i], y[i]);
      }, length(x));
}

/**
 * Binary transformation.
 *
 * - X: First operand.
 * - Y: Second operand.
 * - f: Operator.
 */
function transform<Input1,Input2,Output>(X:Input1[_,_], Y:Input2[_,_],
    f:\(Input1, Input2) -> Output) -> Output[_,_] {
  assert rows(X) == rows(Y);
  assert columns(X) == columns(Y);
  return matrix(\(i:Integer, j:Integer) -> Output {
        return f(X[i,j], Y[i,j]);
      }, rows(X), columns(X));
}

/**
 * Ternary transformation.
 *
 * - x: First operand.
 * - y: Second operand.
 * - z: Third operand.
 * - f: Operator.
 */
function transform<Input1,Input2,Input3,Output>(x:Input1[_], y:Input2[_],
    z:Input3[_], f:\(Input1, Input2, Input3) -> Output) -> Output[_] {
  assert length(x) == length(y);
  assert length(x) == length(z);
  return vector(\(i:Integer) -> Output {
        return f(x[i], y[i], z[i]);
      }, length(x));
}

/**
 * Ternary transformation.
 *
 * - X: First operand.
 * - Y: Second operand.
 * - Z: Third operand.
 * - f: Operator.
 */
function transform<Input1,Input2,Input3,Output>(X:Input1[_,_], Y:Input2[_,_],
    Z:Input3[_,_], f:\(Input1, Input2, Input3) -> Output) -> Output[_,_] {
  assert rows(X) == rows(Y);
  assert rows(X) == rows(Z);
  assert columns(X) == columns(Y);
  assert columns(Y) == columns(Z);
  return matrix(\(i:Integer, j:Integer) -> Output {
        return f(X[i,j], Y[i,j], Z[i,j]);
      }, rows(X), columns(X));
}

/**
 * Reduction.
 *
 * - x: Vector.
 * - init: Initial value.
 * - op: Operator.
 */
function reduce<Type>(x:Type[_], init:Type, op:\(Type, Type) -> Type) ->
    Type {
  result:Type;
  cpp{{
  x.pin();
  // result = return std::reduce(x.begin(), x.end(), init, op);
  // ^ C++17
  result = std::accumulate(x.begin(), x.end(), init, op);
  x.unpin();
  return result;
  }}
}

/**
 * Unary transformation and reduction.
 *
 * - x: First operand.
 * - init: Initial value.
 * - op1: Reduction operator.
 * - op2: Transformation operator.
 */
function transform_reduce<Type>(x:Type[_], init:Type,
    op1:\(Type, Type) -> Type, op2:\(Type) -> Type) -> Type {
  auto y <- init;
  for n in 1..length(x) {
    y <- op1(y, op2(x[n]));
  }
  return y;
}

/**
 * Binary transformation and reduction.
 *
 * - x: First operand.
 * - y: Second operand.
 * - init: Initial value.
 * - op1: Reduction operator.
 * - op2: Transformation operator.
 */
function transform_reduce<Type>(x:Type[_], y:Type[_], init:Type,
    op1:\(Type, Type) -> Type, op2:\(Type, Type) -> Type) -> Type {
  assert length(x) == length(y);
  auto z <- init;
  for n in 1..length(x) {
    z <- op1(z, op2(x[n], y[n]));
  }
  return z;
}

/**
 * Ternary transformation and reduction.
 *
 * - x: First operand.
 * - y: Second operand.
 * - z: Third operand.
 * - init: Initial value.
 * - op1: Reduction operator.
 * - op2: Transformation operator.
 */
function transform_reduce<Type>(x:Type[_], y:Type[_], z:Type[_],
    init:Type, op1:\(Type, Type) -> Type,
    op2:\(Type, Type, Type) -> Type) -> Type {
  assert length(x) == length(y);
  assert length(y) == length(z);
  auto a <- init;
  for n in 1..length(x) {
    a <- op1(a, op2(x[n], y[n], z[n]));
  }
  return a;
}

/**
 * Inclusive scan.
 *
 * - x: Vector.
 * - op: Operator.
 */
function inclusive_scan<Type>(x:Type[_], op:\(Type, Type) -> Type) -> Type[_] {
  y:Type[length(x)];
  cpp{{
  x.pin();
  // std::inclusive_scan(x.begin(), x.end(), y.begin(), op);
  // ^ C++17
  std::partial_sum(x.begin(), x.end(), y.begin(), op);
  x.unpin();
  }}
  return y;
}

/**
 * Exclusive scan.
 *
 * - x: Vector.
 * - init: Initial value.
 * - op: Operator.
 */
function exclusive_scan<Type>(x:Type[_], init:Type,
    op:\(Type, Type) -> Type) -> Type[_] {
  assert length(x) > 0;
  y:Type[length(x)];
  //cpp{{
  // std::exclusive_scan(x.begin(), x.end(), y.begin(), init, op);
  // ^ C++17
  //}}
  y[1] <- init;
  for i in 2..length(x) {
    y[i] <- y[i - 1] + x[i - 1];
  }
  return y;
}

/**
 * Adjacent difference.
 *
 * - x: Vector.
 * - op: Operator.
 */
function adjacent_difference<Type>(x:Type[_],
    op:\(Type, Type) -> Type) -> Type[_] {
  y:Type[length(x)];
  cpp{{
  x.pin();
  std::adjacent_difference(x.begin(), x.end(), y.begin(), op);
  x.unpin();
  }}
  return y;
}

/**
 * Sort a vector.
 *
 * - x: Vector.
 *
 * Returns: A vector giving the elements of `x` in ascending order.
 */
function sort<Type>(x:Type[_]) -> Type[_] {
  auto y <- x;
  cpp{{
  y.pinWrite();
  std::sort(y.begin(), y.end());
  y.unpin();
  }}
  return y;
}

/**
 * Sort a vector.
 *
 * - x: Vector.
 *
 * Returns: A vector giving the indices of elements in `x` in ascending
 * order.
 */
function sort_index<Type>(x:Type[_]) -> Integer[_] {
  auto a <- iota(1, length(x));
  cpp{{
  x.pin();
  std::sort(a.begin(), a.end(), [=](bi::type::Integer i, bi::type::Integer j) {
      return x(libbirch::make_slice(i - 1)) < x(libbirch::make_slice(j - 1));
    });
  x.unpin();
  }}
  return a;
}

/**
 * Gather.
 *
 * - a: Indices.
 * - x: Source vector.
 *
 * Returns: a vector `y` where `y[n] == x[a[n]]`.
 */
function gather<Type>(a:Integer[_], x:Type[_]) -> Type[_] {
  return vector(\(i:Integer) -> Type { return x[a[i]]; }, length(a));
}

/**
 * Scatter.
 *
 * - a: Indices.
 * - x: Source vector.
 *
 * Returns: a vector `y` where `y[a[n]] == x[n]`.
 *
 * If the same index appears more than once in `a`, the result is undefined.
 */
function scatter<Type>(a:Integer[_], x:Type[_]) -> Type[_] {
  auto N <- length(a);
  y:Type[N];
  for n in 1..N {
    y[a[n]] <- x[n];
  }
  return y;
}
