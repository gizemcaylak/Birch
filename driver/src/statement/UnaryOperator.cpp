/**
 * @file
 */
#include "src/statement/UnaryOperator.hpp"

#include "src/visitor/all.hpp"

birch::UnaryOperator::UnaryOperator(const Annotation annotation, Expression* typeParams,
    Name* name, Expression* single, Type* returnType, Statement* braces,
    Location* loc) :
    Statement(loc),
    Annotated(annotation),
    TypeParameterised(typeParams),
    Named(name),
    Single<Expression>(single),
    ReturnTyped(returnType),
    Braced(braces) {
  //
}

birch::Statement* birch::UnaryOperator::accept(Modifier* visitor) {
  return visitor->modify(this);
}

void birch::UnaryOperator::accept(Visitor* visitor) const {
  visitor->visit(this);
}
