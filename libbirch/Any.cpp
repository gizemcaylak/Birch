/**
 * @file
 */
#include "libbirch/Any.hpp"

#include "libbirch/Label.hpp"

void libbirch::Any::holdLabel() {
  auto label = getLabel();
  if (label && label != rootLabel) {
    label->incShared();
  }
}

void libbirch::Any::releaseLabel() {
  auto label = getLabel();
  if (label && label != rootLabel) {
    label->decShared();
  }
}
