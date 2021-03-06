/**
 * @file
 */
#pragma once

#include "src/expression/Expression.hpp"
#include "src/common/Single.hpp"
#include "src/expression/EmptyExpression.hpp"

namespace birch {
/**
 * Expression in parentheses.
 *
 * @ingroup expression
 */
class Parentheses: public Expression, public Single<Expression> {
public:
  /**
   * Constructor.
   *
   * @param single Expression in parentheses.
   * @param loc Location.
   */
  Parentheses(Expression* single, Location* loc = nullptr);

  /**
   * Destructor.
   */
  virtual ~Parentheses();

  virtual const Expression* strip() const;
  virtual bool isAssignable() const;
  virtual bool isSlice() const;
  virtual bool isTuple() const;
  virtual bool isMembership() const;
  virtual bool isGlobal() const;
  virtual bool isMember() const;
  virtual bool isLocal() const;
  virtual bool isParameter() const;

  virtual Expression* accept(Cloner* visitor) const;
  virtual Expression* accept(Modifier* visitor);
  virtual void accept(Visitor* visitor) const;
};
}
