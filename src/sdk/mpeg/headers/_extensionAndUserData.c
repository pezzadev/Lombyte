#include "types.h"
#include "rnc/sdk/mpeg/bitstream.h"

typedef void (*ExtFunc)(void *);

typedef struct {
    ExtFunc f[11];
} ExtTable;

extern ExtTable mpeg_extension_dispatch_table __asm__("D_001538B8");

void _extensionAndUserData(void *decoder_state) {
    ExtTable extension_handlers = mpeg_extension_dispatch_table;
    u32      code;
    u32      extension_id;

    _nextStartCode(decoder_state);
    while ((code = _peepBit(decoder_state, 32)) == 0x1B5 || code == 0x1B2) {
        if (code == 0x1B5) {
            _flushBuf(decoder_state, 32);
            extension_id = _nextBit(decoder_state, 4);
            extension_id = extension_id > 10 ? 0 : extension_id;
            extension_handlers.f[extension_id](decoder_state);
            _nextStartCode(decoder_state);
        } else {
            _flushBuf(decoder_state, 32);
            _nextStartCode(decoder_state);
        }
    }
}
