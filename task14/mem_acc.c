#include <stdint.h>
#include <stdio.h>

static uint64_t registers[] = {
    0xFFFFB3F767D0, 0x71018330, 0xFFFFC7A82219, 0x71018945, 0x67A37750};

#define LDR 0x2e5
#define LDRB 0xE5

void mem_bounds(uint32_t instr, uint64_t *lo, uint64_t *hi) {
    unsigned rd = instr & ((1 << 5) - 1);
    instr >>= 5;

    unsigned rs = instr & ((1 << 5) - 1);
    instr >>= 5;

    unsigned off = instr & ((1 << 12) - 1);
    unsigned op = instr >> 12;

    switch (op) {
    case LDRB: {
        uint64_t address = registers[rs] + off;
        *lo = address;
        *hi = address;
        break;
    }
    case LDR: {
        uint64_t address = registers[rs] + off;
        *lo = address;
        *hi = address + 1;
        break;
    }
    default: {
        *lo = -1;
        *hi = -1;
        break;
    }
    }
}

int main() {
    uint32_t i1 = 0x39400002;
    uint32_t i2 = 0xB9419083;

    uint64_t lo1, hi1;
    mem_bounds(i1, &lo1, &hi1);
    uint64_t lo2, hi2;
    mem_bounds(i2, &lo2, &hi2);

    int64_t distance = 0;
    if (hi2 < lo1) {
        distance = lo1 - hi2 - 1;
    } else if (lo2 > hi1) {
        distance = lo2 - hi1 - 1;
    }

    printf("distance: %li\n", distance);

    return 0;
}
