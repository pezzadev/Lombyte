#include "types.h"
#include "asm.h"

#ifndef NON_MATCHING
INCLUDE_ASM("config/us/expected/asm/assembly/textbin/fun_001fa2b8/FUN_001fa2b8.s", FUN_001fa2b8);
#else
#include "rnc/fun_001fa2b8_types.h"

void copy_matrix_basis_columns(volatile struct RncMatrixBasis *destination,
                               const volatile struct RncMatrixBasis *source)
    __asm__("FUN_001fa2b8");

/* Copy the first three 16-byte columns; leave the fourth column untouched. */
void copy_matrix_basis_columns(volatile struct RncMatrixBasis *destination,
                               const volatile struct RncMatrixBasis *source) {
    /* The historical compiler needs these bindings to match retail registers. */
    register u128 first __asm__("$1");
    register u128 second __asm__("$2");
    register u128 third __asm__("$3");

    /* Snapshot all source columns before writing any destination column. */
    first = source->first_column;
    second = source->second_column;
    third = source->third_column;

    destination->first_column = first;
    destination->second_column = second;
    destination->third_column = third;
}

extern __typeof__(copy_matrix_basis_columns) func_001FA2B8
    __attribute__((alias("FUN_001fa2b8")));
#endif /* NON_MATCHING */
