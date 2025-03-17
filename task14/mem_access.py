instructions = [0x39400002, 0xB9419083]

regs = [0xFFFFB3F767D0, 0x71018330, 0xFFFFC7A82219, 0x71018945, 0x67A37750]

dispatch = {}


def ld_w(off, rs, rd):
    addr = regs[rs] + off
    print(f"ld word {addr=}, {rd=}")
    return (addr, addr + 1)


dispatch[0x2E5] = ld_w


def ld_b(off, rs, rd):
    addr = regs[rs] + off
    print(f"ld byte {addr=}, {rd=}")
    return (addr, addr)


dispatch[0xE5] = ld_b


def decode(instr: int):
    print(f"{instr:0>32b}")
    rd = instr & ((1 << 5) - 1)
    instr >>= 5

    rs = instr & ((1 << 5) - 1)
    instr >>= 5

    off = instr & ((1 << 12) - 1)
    instr >>= 12

    op = instr

    print(f"{op:0>10b}{off:0>12b}{rs:0>5b}{rd:0>5b}")
    print(f"0x{op:x}:{off}:{rs}:{rd}")

    return op, off, rs, rd


op, off, rs, rd = decode(instructions[0])
lo1, hi1 = dispatch[op](off, rs, rd)

op, off, rs, rd = decode(instructions[1])
lo2, hi2 = dispatch[op](off, rs, rd)

print(lo1, hi1)
print(lo2, hi2)


def dist(lo1, hi1, lo2, hi2):
    if hi2 < lo1:
        return lo1 - hi2 - 1
    elif lo2 > hi1:
        return lo2 - hi1 - 1
    return 0


print(dist(lo1, hi1, lo2, hi2))
print(dist(-2, -1, 0, 0))
print(dist(-2, -2, 0, 0))
print(dist(-3, 3, 0, 0))
