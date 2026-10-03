#include "types.h"
#include "asm.h"

#ifndef NON_MATCHING
INCLUDE_ASM("config/us/expected/asm/assembly/textbin/fun_0022c8d0/FUN_0022c8d0.s", FUN_0022c8d0);
#else
#include "types.h"
#include "qzero.h"
struct VoicePoolInitializationState {
    u8 pad_0[0x40];
    s32 listener_history_position;
    s32 reserved44;
    s32 group_0_volume;
    s32 group_1_volume;
    s32 group_2_volume;
    s32 group_3_volume;
    s32 group_4_volume;
    s32 group_5_volume;
    u8 pad_60[0x10];
    s32 handle;
};

struct VoicePoolInitializationWindow {
    u8 pad_0[0x70];
    s32 handle;
    s32 state;
};

extern struct VoicePoolInitializationState D_0013E550;
extern s32 D_0015EDE8[];
extern s32 D_0015EDEC;
extern s32 D_0015EDF0;
extern s32 func_0012DA28();
extern s32 func_0012E208();
extern s32 func_0012E240();
extern s32 func_0012E280();
extern s32 func_0012E2B8();
extern s32 func_0012EFA8();
extern s32 func_00215390();
void initialize_gameplay_sound_system(void) __asm__("FUN_0022c8d0");

void initialize_gameplay_sound_system(void) {
    u8 *slot_end;
    u8 *header_block;
    struct VoicePoolInitializationWindow *slot_window;
    s32 scaled_volume_80;
    s32 scaled_volume_70;
    s32 header_block_index;

    header_block_index = 3;
    header_block = (u8 *)&D_0013E550;
    do {
        qzero(header_block);
        header_block_index -= 1;
        header_block += 16;
    } while (header_block_index >= 0);
    slot_window = (struct VoicePoolInitializationWindow *)&D_0013E550;
    D_0013E550.listener_history_position = 0;
    D_0013E550.reserved44 = 0;
    slot_end = ((u8 *)&D_0013E550 + 0xD20);
    D_0013E550.handle = 0;
loop_3:
    slot_window->state = 0;
    slot_window = (struct VoicePoolInitializationWindow *)((u8 *)slot_window + 0x70);
    if ((u8 *)slot_window < slot_end) {
        slot_window->handle = 0;
        goto loop_3;
    }
    func_0012DA28(slot_end);
    func_0012E240(D_0015EDE8[0] == 0);
    func_0012E280(0, 1);
    func_0012EFA8(2, 4);
    func_0012E2B8(1, 0x18, 0x2F);
    func_0012E2B8(2, 0x18, 0x2F);
    func_0012E2B8(4, 0x18, 0x2F);
    scaled_volume_80 = (s32) (*(s32 *)0x15EDF0 * 8) / 10;
    D_0013E550.group_1_volume = (s32) *(s32 *)0x15EDEC;
    scaled_volume_70 = (s32) (*(s32 *)0x15EDF0 * 7) / 10;
    D_0013E550.group_0_volume = scaled_volume_80;
    D_0013E550.group_2_volume = scaled_volume_80;
    D_0013E550.group_3_volume = scaled_volume_70;
    D_0013E550.group_4_volume = scaled_volume_70;
    D_0013E550.group_5_volume = (s32) *(s32 *)0x15EDF0;
    func_00215390(0xA, *(s32 *)0x15EDF0, scaled_volume_80, 0xA);
    func_0012E208(0, D_0013E550.group_0_volume);
    func_0012E208(1, D_0013E550.group_1_volume);
    func_0012E208(2, D_0013E550.group_2_volume);
    func_0012E208(3, D_0013E550.group_3_volume);
    func_0012E208(4, D_0013E550.group_4_volume);
    func_0012E208(5, D_0013E550.group_5_volume);
}
#endif /* NON_MATCHING */
