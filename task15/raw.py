class Instruction:
    def __init__(self, number, read, write):
        self.number = number
        self.read = read
        self.write = write
        self.issue_time = 0

    def __repr__(self):
        return f"({self.number}) at {self.issue_time}: {self.write} = {self.read}"


def base_algorithm(instructions: list[Instruction]):
    clock_cycle = 0
    instruction_count = 0
    instruction_window: list[Instruction] = []
    availability_time = {}
    # data = {}
    # c = 0

    for instr in instructions:
        instr.issue_time = max(
            availability_time.get(instr.read, 0),
            availability_time.get(instr.write, 0),
            clock_cycle,
        )

        availability_time[instr.read] = instr.issue_time + 1
        availability_time[instr.write] = instr.issue_time + 1

        instruction_window.append(instr)

        if len(instruction_window) == 4:
            clock_cycle += 1
            for instr in instruction_window:
                if instr.issue_time < clock_cycle:
                    print(instr)

                    # if instr.read.startswith('0x'):
                    #     data[instr.read] = c
                    #     print(f'[{instr.read}] == {c}')
                    #     c += 1
                    # data[instr.write] = data[instr.read]
            instruction_window = [
                instr for instr in instruction_window if instr.issue_time >= clock_cycle
            ]

        instruction_count += 1

    print()
    while instruction_window:
        clock_cycle += 1
        instruction_window = [
            instr for instr in instruction_window if instr.issue_time >= clock_cycle
        ]
    # for addr, v in data.items():
    #     print(addr, v)

    return clock_cycle, instruction_count


instructions = [
    Instruction(1, "0xffffb396be70", "r3"),
    Instruction(2, "r3", "r3"),
    Instruction(3, "r3", "0xffffb396be70"),
    Instruction(4, "0xfffff23b2fd0", "r2"),
    Instruction(5, "r2", "0xfffff23b2fd0"),  # write None
    Instruction(6, "0xffffb396be80", "r3"),
    Instruction(7, "r3", "r3"),
    Instruction(8, "r3", "0xffffb396be80"),
    Instruction(9, "0xfffff23b2fd8", "r2"),
    Instruction(10, "r2", "0xfffff23b2fd8"),  # write None
    Instruction(11, "0xffffb396bef0", "r3"),
    Instruction(12, "r3", "r3"),
    Instruction(13, "r3", "0xffffb396bef0"),
    Instruction(14, "0xfffff23b3058", "r2"),
    Instruction(15, "r2", "0xfffff23b3058"),  # write None
    Instruction(16, "0xffffb396bee0", "r3"),
    Instruction(17, "r3", "r3"),
    Instruction(18, "r3", "0xffffb396bee0"),
    Instruction(19, "0xfffff23b3160", "r2"),
    Instruction(20, "r2", "0xfffff23b3160"),  # write None
]

clock_cycle, instruction_count = base_algorithm(instructions)
print(f"{clock_cycle=}")
print(f"{instruction_count=}")
