#ifndef RNC_FUN_001FA2B8_TYPES_H
#define RNC_FUN_001FA2B8_TYPES_H

#include "eetypes.h"

/* Three aligned matrix columns, at byte offsets 0, 16, and 32. */
struct RncMatrixBasis {
    u128 first_column;
    u128 second_column;
    u128 third_column;
};

#endif /* RNC_FUN_001FA2B8_TYPES_H */
