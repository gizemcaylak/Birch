/**
 * @file
 */
#pragma once

#include "libbirch/external.hpp"

namespace libbirch {
/**
 * Constant to indicate a mutable value in Length, Offset, Stride, etc. Zero
 * is convenient as it allows values to be multiplied to arrive a non-zero
 * non-mutable value overall, or zero mutable value overall.
 *
 * @ingroup libbirch
 */
static constexpr int64_t mutable_value = 0;
}
