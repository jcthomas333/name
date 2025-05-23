#include <iostream>
#include <vector>
#include <bitset>
#include <string>

const int NUM_REGISTERS = 32;
const int MEMORY_SIZE = 1024;

std::vector<int32_t> registers(NUM_REGISTERS, 0);  // Registers initialized to 0
std::vector<int32_t> memory(MEMORY_SIZE, 0);       // Memory initialized to 0

enum Instructions { ADD = 32, SUB = 34, AND = 36, OR = 37, SLT = 42, LW = 35, SW = 43, BEQ = 4, J = 2 };

struct Instruction {
    Instructions type;
    int rs = 0, rt = 0, rd = 0;     // Register fields
    int immediate = 0;               // Immediate value (I format)
    int shamt = 0;                   // Shift amount (R format)
    int funct = 0;                   // Function code (R format)
    int address = 0;                 // Address (J format)
};

// Convert hex string to 32-bit binary
std::bitset<32> hexToBinary(const std::string &hex) {
    uint32_t instruction = std::stoul(hex, nullptr, 16);
    return std::bitset<32>(instruction);
}

// Decode a binary instruction
Instruction decodeInstruction(const std::bitset<32> &binaryInstruction) {
    Instruction instr;
    uint32_t opcode = binaryInstruction.to_ulong() >> 26;

    if (opcode == 0) {  // R-format
        instr.rs = (binaryInstruction >> 21 & 0x1F).to_ulong();
        instr.rt = (binaryInstruction >> 16 & 0x1F).to_ulong();
        instr.rd = (binaryInstruction >> 11 & 0x1F).to_ulong();
        instr.shamt = (binaryInstruction >> 6 & 0x1F).to_ulong();
        instr.funct = (binaryInstruction & 0x3F).to_ulong();
        instr.type = static_cast<Instructions>(instr.funct);
    } else if __
    } else {  // I-format
        instr.type = static_cast<Instructions>(opcode);
        instr.rs = (binaryInstruction >> 21 & 0x1F).to_ulong();
        instr.rt = (binaryInstruction >> 16 & 0x1F).to_ulong();
        instr.immediate = (binaryInstruction & 0xFFFF).to_ulong();
    }

    return instr;
}

// Execute R-format instructions
void executeAdd(int rs, int rt, int rd) { registers[rd] = registers[rs] + registers[rt]; }
void executeSub(int rs, int rt, int rd) { registers[rd] = registers[rs] - registers[rt]; }
void executeAnd(int rs, int rt, int rd) { registers[rd] = registers[rs] & registers[rt]; }
void executeOr(int rs, int rt, int rd) { registers[rd] = registers[rs] | registers[rt]; }
void executeSlt(int rs, int rt, int rd) { registers[rd] = (registers[rs] < registers[rt]) ? 1 : 0; }

// Execute I-format instructions
void executeLw(int base, int rt, int offset) {
    int address = registers[base] + offset;
    if (address >= 0 && address < MEMORY_SIZE) registers[rt] = memory[address];
}
void executeSw(int base, int rt, int offset) {
    int address = registers[base] + offset;
    if (address >= 0 && address < MEMORY_SIZE) memory[address] = registers[rt];
}
void executeBeq(int rs, int rt, int offset, int &pc) {
    if (registers[rs] == registers[rt]) pc += offset;
}

// Execute J-format instruction
void executeJ(int address, int &pc) { pc = address; }

// Execute an instruction
void executeInstruction(Instruction instr, int &pc) {
    switch (instr.type) {
        case ADD: executeAdd(instr.rs, instr.rt, instr.rd); break;
        case SUB: executeSub(instr.rs, instr.rt, instr.rd); break;
        case AND: executeAnd(instr.rs, instr.rt, instr.rd); break;
        case OR: executeOr(instr.rs, instr.rt, instr.rd); break;
        case SLT: executeSlt(instr.rs, instr.rt, instr.rd); break;
        case LW: executeLw(instr.rs, instr.rt, instr.immediate); break;
        case SW: executeSw(instr.rs, instr.rt, instr.immediate); break;
        case BEQ: executeBeq(instr.rs, instr.rt, instr.immediate, pc); break;
        case J: executeJ(instr.address, pc); break;
        default: std::cerr << "Unknown instruction!" << std::endl; break;
    }
}

// Display register contents
void displayRegisters() {
    std::cout << "Register contents:\n";
    for (int i = 0; i < NUM_REGISTERS; i++) {
        std::cout << "$" << i << ": " << registers[i] << "\t";
        if ((i + 1) % 4 == 0) std::cout << "\n";
    }
    std::cout << "\n";
}

// Main function
int main() {
    int pc = 0;
    std::string hexInstruction;
    std::vector<Instruction> program;

    std::cout << "Enter hexadecimal MIPS instructions (type 'done' to finish):\n";
    while (std::cin >> hexInstruction && hexInstruction != "done") {
        std::bitset<32> binaryInstruction = hexToBinary(hexInstruction);
        Instruction instr = decodeInstruction(binaryInstruction);
        program.push_back(instr);
    }

    while (pc < program.size()) {
        Instruction instr = program[pc];
        executeInstruction(instr, pc);
        displayRegisters();  // Display registers after each instruction execution
        pc++;
    }

    return 0;
}

Hexadecimal to Binary Conversion: Converts hex instructions to binary.
Instruction Struct: Represents R, I, or J format MIPS instructions. Do pint the j form at 
Instruction Decoding: Parses binary instructions.
Execution Functions: Executes different MIPS instructions.
Display Registers: Shows register contents after each instruction execution.
