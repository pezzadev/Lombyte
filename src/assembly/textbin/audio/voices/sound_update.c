#include "types.h"
#include "asm.h"

#ifndef NON_MATCHING
INCLUDE_ASM("config/us/expected/asm/assembly/textbin/audio/voices/sound_update/FUN_0022ca50.s", FUN_0022ca50);
#else
#include "types.h"
#include "eetypes.h"
#include "qcopy.h"
#include "qzero.h"

typedef union {
    u128 q;
    f32 f[4];
} VoiceVector;

typedef struct {
    u8 pad00[0x18];
    u8 source_state;
    u8 attenuation_flags;
    s16 sound_index;
    s32 bank_handle;
} VoiceDefinition;

typedef struct {
    u8 pad00[0x10];
    VoiceVector position;
    u8 state;
    u8 pad21[0x9F];
    VoiceVector rotation;
} VoiceMoby;

typedef struct {
    u32 handle;      /* 0x00 */
    u8 state;        /* 0x04 */
    u8 flags;        /* 0x05 */
    u8 pad06[2];
    VoiceDefinition *definition;   /* 0x08 */
    s32 pad0C;
    s32 volume;      /* 0x10 */
    s32 pitch_bend;       /* 0x14 */
    VoiceMoby *moby; /* 0x18 */
    s32 owner_context;     /* 0x1C */
    VoiceVector position;        /* 0x20 */
    VoiceVector position_offset;      /* 0x30 */
    u32 occlusion_history_position;    /* 0x40 */
    u8 occlusion_history[36];     /* 0x44 */
    u8 pad68[8];
} VoiceSlot;

typedef struct {
    VoiceVector listener_history[4];   /* 0x000 */
    s32 listener_history_position;        /* 0x040 */
    s32 pad44;
    s32 group_0_volume;          /* 0x048 */
    s32 group_1_volume;
    s32 group_2_volume;
    s32 group_3_volume;
    s32 group_4_volume;
    s32 group_5_volume;
    s32 pad60;
    s32 reverb_depth;          /* 0x064 */
    u8 reverb_type;
    u8 reverb_delay;
    u8 reverb_feedback;
    u8 reverb_commands;
    s32 pending_commands;          /* 0x06C */
    VoiceSlot voices[30];   /* 0x070 */
    s32 padD90[2];
    s32 occlusion_frame;         /* 0xD98 */
    s32 padD9C;
    VoiceVector occlusion_samples[6];     /* 0xDA0 */
} VoiceRuntimeState;

extern VoiceRuntimeState D_0013E550;
extern f32 D_0013F640[];
extern f32 D_0015ED6C;
extern s32 D_0015F5E8;
extern s32 D_0015F604;
extern s32 D_0015F60C;
extern VoiceVector D_00187080;
extern u8 D_00187290[];
extern s32 D_001872D4;

extern s32 ComputeByteStringHash(u8 *, s32);
extern int ComputeSectorIndex(int arg0);
extern void FillTransferWords(void *, s32, s32);
extern void ReadGlobalTableEntry(void);
extern void func_0012DC80() __asm__("FUN_0012dc80");
extern void func_0012E208() __asm__("FUN_0012e208");
extern void func_0012E308() __asm__("FUN_0012e308");
extern void func_0012E368() __asm__("FUN_0012e368");
extern void func_0012E448() __asm__("FUN_0012e448");
extern void func_0012E4C0() __asm__("FUN_0012e4c0");
extern void func_0012EB00() __asm__("FUN_0012eb00");
extern void func_0012EF68() __asm__("FUN_0012ef68");
extern void func_0012EFE0() __asm__("FUN_0012efe0");
extern void func_001F9A10(void *out, void *a, void *b) __asm__("FUN_001f9a10");
extern void func_001F9A28(void *out, void *a, void *b) __asm__("FUN_001f9a28");
extern void func_001F9A68(void *out, void *a, f32 runtime) __asm__("FUN_001f9a68");
extern f32 func_001F9AB0(void *a, void *b) __asm__("FUN_001f9ab0");
extern f32 func_001F9AF0(void *a) __asm__("FUN_001f9af0");
extern void func_001F9BF8(void *out, void *a, f32 len) __asm__("FUN_001f9bf8");
extern void func_001F9CF8(void *out, void *a, void *b) __asm__("FUN_001f9cf8");
extern void func_001FA2D8(void *out, void *a) __asm__("FUN_001fa2d8");
extern f32 ConvertIntegerToFloat(s32) __asm__("func_001FA6C0");
extern s32 truncate_float_to_s32(f32) __asm__("FUN_001fa6d0");
extern void music_update() __asm__("FUN_00216290");
extern void clamp_voice_position_to_collision(void *) __asm__("FUN_0022c5a8");
extern u8 test_voice_occlusion(VoiceSlot *, void *) __asm__("FUN_0022c658");
extern s32 calculate_voice_volume(VoiceSlot *, VoiceVector *) __asm__("FUN_0022c7e8");
extern s32 calculate_voice_pan(VoiceSlot *, VoiceVector *, void *) __asm__("FUN_0022c830");
extern void voice_start_callback() __asm__("FUN_0022dd90");
extern void voice_update_callback() __asm__("FUN_0022ddd8");

s32 sound_update(void) __asm__("FUN_0022ca50");

s32 sound_update(void) {
    VoiceVector listener_occlusion_position;
    VoiceVector listener_velocity;
    VoiceVector relative_velocity;
    s32 flags[30];
    s32 voice_volumes[30];
    f32 radial_velocities[30];
    VoiceVector direction;
    VoiceVector listener_matrix[4];
    s32 i;
    s32 underwater;
    f32 *radial_velocity_values;
    VoiceVector *velocity;
    VoiceVector *matrix;
    s32 *voice_flags;
    s32 *volumes;
    VoiceRuntimeState *runtime;
    VoiceMoby *moby;
    VoiceVector *relative;
    VoiceVector *unit_direction;
    f32 water_height;
    s32 history_index;
    s32 previous_history_index;
    s32 n;
    s32 group_volume;
    s32 j;
    s32 k;
    s32 m;
    s32 owner_removed;
    s32 distance_volume;
    s32 count;
    s32 mode;
    s32 pan;
    s32 pitch;
    s32 pitch_bend;
    s32 handle;
    s32 f;

    water_height = 0.0f;
    underwater = D_001872D4;
    if (underwater != 0) {
        water_height = D_0013F640[0];
    }
    func_0012DC80();

    if (D_0013E550.reverb_commands & 8) {
        func_0012EF68(2, 0, 0, 0, 0);
    } else if (D_0013E550.reverb_commands & 0x13) {
        func_0012EF68(2, D_0013E550.reverb_type, D_0013E550.reverb_depth, D_0013E550.reverb_delay, D_0013E550.reverb_feedback);
    } else if (D_0013E550.reverb_commands & 4) {
        func_0012EFE0(2, D_0013E550.reverb_depth, 0xC, 3);
    }
    D_0013E550.reverb_commands = 0;

    if ((D_0015F604 == 0 || D_0015F604 == 2) && D_0015F5E8 == 0) {
        clamp_voice_position_to_collision(&listener_occlusion_position);
    }

    qzero(&listener_velocity);
    runtime = &D_0013E550;
    history_index = (runtime->listener_history_position + 1) % 4;
    runtime->listener_history_position = history_index;
    qcopy(&runtime->listener_history[history_index], &D_00187080);

    velocity = &listener_velocity;
    voice_flags = flags;
    radial_velocity_values = radial_velocities;
    matrix = listener_matrix;
    volumes = voice_volumes;
    n = 0;
    previous_history_index = (history_index + 3) % 4;
    if (previous_history_index != history_index) {
        do {
            func_001F9A28(&relative_velocity, &runtime->listener_history[history_index], &runtime->listener_history[previous_history_index]);
            if (!(func_001F9AF0(&relative_velocity) < D_0015ED6C * 60.0f)) {
                break;
            }
            n++;
            func_001F9A10(velocity, velocity, &relative_velocity);
            history_index = previous_history_index;
            previous_history_index = (history_index + 3) % 4;
        } while (previous_history_index != runtime->listener_history_position);
    }
    if (n >= 2) {
        func_001F9A68(velocity, velocity, 1.0f / ConvertIntegerToFloat(n));
    }

    if (D_0015F604 == 2) {
        func_0012E208(1, 0);
        func_0012E208(0, D_0013E550.group_0_volume / 2);
        func_0012E208(3, D_0013E550.group_3_volume / 2);
    } else {
        group_volume = D_0013E550.group_1_volume;
        if (underwater) {
            group_volume = group_volume * 3 / 5;
        }
        func_0012E208(1, group_volume);
        func_0012E208(0, D_0013E550.group_0_volume);
        func_0012E208(3, D_0013E550.group_3_volume);
    }
    func_0012E208(2, D_0013E550.group_2_volume);
    func_0012E208(4, D_0013E550.group_4_volume);
    func_0012E208(5, D_0013E550.group_5_volume);

    FillTransferWords(voice_flags, 0, 0x78);
    FillTransferWords(volumes, 0, 0x78);
    FillTransferWords(radial_velocity_values, 0, 0x78);

    for (i = 0; i < 30; i++) {
        if (D_0013E550.voices[i].state != 7) {
            if (D_0013E550.voices[i].handle == 0) {
                continue;
            }
            if (D_0013E550.voices[i].handle == -1) {
                continue;
            }
        }
        moby = D_0013E550.voices[i].moby;
        owner_removed = 0;
        if (moby != NULL && (moby->state == 0xFE || moby->state == 0xFD)) {
            owner_removed = 1;
        }
        if (owner_removed) {
            D_0013E550.voices[i].moby = NULL;
        }
        if (D_0013E550.voices[i].state == 4 || (D_0013E550.voices[i].state != 6 && owner_removed && D_0013E550.voices[i].definition->source_state != 0)) {
            voice_flags[i] = 0x20;
            continue;
        }
        if (D_0015F604 != 0 && D_0015F604 != 2 && D_0015F604 != 6 && D_0013E550.voices[i].state != 7) {
            voice_flags[i] = 0x10;
            continue;
        }

        if (D_0013E550.voices[i].moby != NULL && !(D_0013E550.voices[i].flags & 8)) {
            if (D_0013E550.voices[i].flags & 0x40) {
                func_001F9CF8(&direction, &D_0013E550.voices[i].position_offset, &moby->rotation);
                func_001F9A10(&direction, &direction, &moby->position);
                func_001F9A28(&relative_velocity, &direction, &D_0013E550.voices[i].position);
                qcopy(&D_0013E550.voices[i].position, &direction);
            } else {
                D_0013E550.voices[i].position.f[2] -= 1.0f;
                func_001F9A28(&relative_velocity, &D_0013E550.voices[i].moby->position, &D_0013E550.voices[i].position);
                qcopy(&D_0013E550.voices[i].position, &D_0013E550.voices[i].moby->position);
                D_0013E550.voices[i].position.f[2] += 1.0f;
            }
        } else {
            qzero(&relative_velocity);
        }
        relative = &relative_velocity;
        unit_direction = &direction;
        func_001F9A28(relative, relative, velocity);
        func_001F9A28(unit_direction, &D_00187080, &D_0013E550.voices[i].position);
        func_001F9BF8(unit_direction, unit_direction, 1.0f);
        radial_velocity_values[i] = func_001F9AB0(unit_direction, relative);

        if (!(D_0013E550.voices[i].flags & 0x10)) {
            distance_volume = calculate_voice_volume(&D_0013E550.voices[i], &D_0013E550.voices[i].position);
            volumes[i] = distance_volume * D_0013E550.voices[i].volume / 1024;
            if (!(D_0013E550.voices[i].definition->attenuation_flags & 2)) {
                voice_flags[i] |= 8;
            }
        } else {
            distance_volume = 0x400;
            volumes[i] = D_0013E550.voices[i].volume;
        }
        if (underwater && !(D_0013E550.voices[i].definition->attenuation_flags & 4) && water_height < D_0013E550.voices[i].position.f[2]) {
            volumes[i] /= 2;
        }
        voice_flags[i] |= 1;
        if (distance_volume < 0x20 && volumes[i] < 0x20 && (D_0013E550.voices[i].flags & 4)) {
            voice_flags[i] = 0x20;
            continue;
        }
        if (!(D_0013E550.voices[i].flags & 1)) {
            voice_flags[i] |= 2;
            if (!(D_0013E550.voices[i].flags & 0x20)) {
                voice_flags[i] |= 4;
            }
        }
    }

    for (i = 0; i < 30; i++) {
        if (!(voice_flags[i] & 8)) {
            continue;
        }
        if (D_0013E550.voices[i].state == 7) {
            if ((D_0015F604 != 0 && D_0015F604 != 2) || D_0015F5E8 != 0) {
                continue;
            }
            if (D_0015F60C != D_0013E550.occlusion_frame) {
                for (j = 0; j < 6; j++) {
                    clamp_voice_position_to_collision(&D_0013E550.occlusion_samples[j]);
                }
                D_0013E550.occlusion_frame = D_0015F60C;
            }
            count = 0;
            for (j = 0, k = 0; j < 36; j += 6, k++) {
                D_0013E550.voices[i].occlusion_history[j] = test_voice_occlusion(&D_0013E550.voices[i], &D_0013E550.occlusion_samples[k]);
                for (m = 1; m < 6; m++) {
                    D_0013E550.voices[i].occlusion_history[j + m] = D_0013E550.voices[i].occlusion_history[j];
                }
                if (D_0013E550.voices[i].occlusion_history[j]) {
                    count += 6;
                }
            }
            if (count >= 36) {
                volumes[i] = 0;
            } else if (count >= 19) {
                volumes[i] = (36 - count) * volumes[i] / 18;
            }
        } else {
            if ((D_0015F604 == 0 || D_0015F604 == 2) && D_0015F5E8 == 0) {
                D_0013E550.voices[i].occlusion_history_position = (D_0013E550.voices[i].occlusion_history_position + 1) % 36;
                f = (i ^ D_0015F60C) & 1;
                if (!(D_0013E550.voices[i].flags & 4)) {
                    f = ((D_0015F60C ^ i) & 3) == 0;
                }
                if (f) {
                    D_0013E550.voices[i].occlusion_history[D_0013E550.voices[i].occlusion_history_position] = test_voice_occlusion(&D_0013E550.voices[i], &listener_occlusion_position);
                } else {
                    D_0013E550.voices[i].occlusion_history[D_0013E550.voices[i].occlusion_history_position] = D_0013E550.voices[i].occlusion_history[(D_0013E550.voices[i].occlusion_history_position + 35) % 36];
                }
            }
            count = ComputeByteStringHash(D_0013E550.voices[i].occlusion_history, 36);
            if (count >= 36) {
                volumes[i] = 0;
            } else if (count >= 19) {
                volumes[i] = (36 - count) * volumes[i] / 18;
            }
        }
    }

    func_001FA2D8(matrix, D_00187290);
    for (i = 0; i < 30; i++) {
        f = voice_flags[i];
        if (f == 0) {
            continue;
        }
        handle = D_0013E550.voices[i].handle;
        D_0013E550.voices[i].handle = -1;
        if (f & 0x20) {
            if (D_0013E550.voices[i].state == 7) {
                D_0013E550.voices[i].state = 0;
                D_0013E550.voices[i].moby = NULL;
                D_0013E550.voices[i].owner_context = 0;
            } else {
                func_0012E368(handle);
                D_0013E550.voices[i].state = 6;
                func_0012E448(handle, voice_update_callback, &D_0013E550.voices[i]);
            }
        } else if (f & 0x10) {
            func_0012E448(handle, voice_update_callback, &D_0013E550.voices[i]);
        } else {
            pitch_bend = D_0013E550.voices[i].pitch_bend;
            mode = pitch_bend ? 0x11 : 1;
            pan = 0;
            pitch = 0;
            if (f & 2) {
                pan = calculate_voice_pan(&D_0013E550.voices[i], &D_0013E550.voices[i].position, matrix);
                mode |= 6;
            }
            if (voice_flags[i] & 4) {
                mode |= 8;
                pitch = ComputeSectorIndex(truncate_float_to_s32(radial_velocity_values[i] * 300.0f));
            }
            if (underwater && !(D_0013E550.voices[i].definition->attenuation_flags & 8)) {
                mode |= 8;
                pitch -= 0x5F4;
            }
            if (D_0013E550.voices[i].state != 7) {
                func_0012E4C0(handle, mode, volumes[i], pan, pitch, pitch_bend, voice_update_callback, &D_0013E550.voices[i]);
            } else {
                D_0013E550.voices[i].state = 1;
                func_0012E308(D_0013E550.voices[i].definition->bank_handle, D_0013E550.voices[i].definition->sound_index, volumes[i], pan, pitch, pitch_bend, voice_start_callback, &D_0013E550.voices[i]);
            }
        }
    }

    music_update();
    func_0012EB00();
    func_0012DC80();
    ReadGlobalTableEntry();
    D_0013E550.pending_commands = 0;
    return 0;
}
#endif /* NON_MATCHING */
