#ifndef LOMBYTE_RNC_OVERLAY_SHARED_MATH_VU0_VECTOR_OPS_H
#define LOMBYTE_RNC_OVERLAY_SHARED_MATH_VU0_VECTOR_OPS_H

#include "types.h"

s32  fast_subtract_rotations_cf(void *) __asm__("FUN_L00_001fefc8");
void add_vectors(void *, void *, void *) __asm__("FUN_L00_001ff290");
void reflect_vector(void *, void *, void *) __asm__("FUN_L00_001ff660");
/* Build an XYZW quaternion: axis_index 0=X, 1=Y, 2=Z; angle is in radians. */
void build_axis_rotation_quaternion(void *output_quaternion,
                                    s32   axis_index,
                                    f32   angle_radians) __asm__("FUN_L00_001fff28");

#endif /* LOMBYTE_RNC_OVERLAY_SHARED_MATH_VU0_VECTOR_OPS_H */
