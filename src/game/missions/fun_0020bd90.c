/* Ported from rac1-decomp (src/game/missionfunc.c, func_0020CBE0). */
#include "sda.h"
#include "rnc/game/level_object_states.h"

int FUN_0020bd90(void) {
    char *level_object_state_bytes = (char *)level_object_states;
    if (*(int *)(level_object_state_bytes + 0x40C) != 0 && *(int *)(level_object_state_bytes + 0x3FC) != 0)
        return 1;
    return 0;
}

extern __typeof__(FUN_0020bd90) func_0020BD90 __attribute__((alias("FUN_0020bd90")));
