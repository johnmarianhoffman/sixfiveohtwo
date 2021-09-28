#pragma once

#include <cstdint>
#include <string>
#include <opcodes.h>
#include <vector>

class Processor {
private:
	uint8_t accumulator;
	uint8_t idx_reg_x;
	uint8_t idx_reg_y;
	uint16_t program_counter;
	uint8_t stack_pointer;
	bool stack_pointer_carry;
	uint8_t process_status_register;

public:
	Processor();
	~Processor();
	
	uint8_t A(){ return accumulator; }
	uint8_t X(){ return idx_reg_x; }
	uint8_t Y(){ return idx_reg_y; }
	uint16_t PC(){ return program_counter; }
	uint8_t PCL(){ return program_counter & 0x00FF; }
	uint8_t PCH(){ return program_counter & 0xFF00; }
	uint8_t SP(){ return stack_pointer; }
	bool SPC(){ return stack_pointer_carry; }
	uint8_t Status(){ return process_status_register; }


private:

	// Instructions
    void _ADC(){};
	void _AND(){};
	void _ASL(){};
	void _BCC(){};
	void _BCS(){};
	void _BEQ(){};
	void _BIT(){};
	void _BMI(){};
	void _BNE(){};
	void _BPL(){};
	void _BRK(){};
	void _BVC(){};
	void _BVS(){};
	void _CLC(){};
	void _CLD(){};
	void _CLI(){};
	void _CLV(){};
	void _CMP(){};
	void _CPX(){};
	void _CPY(){};
	void _DEC(){};
	void _DEX(){};
	void _DEY(){};
	void _EOR(){};
	void _INC(){};
	void _INX(){};
	void _INY(){};
	void _JMP(){};
	void _JSR(){};
	void _LDA(){};
	void _LDX(){};
	void _LDY(){};
	void _LSR(){};
	void _NOP(){};
	void _ORA(){};
	void _PHA(){};
	void _PHP(){};
	void _PLA(){};
	void _PLP(){};
	void _ROL(){};
	void _ROR(){};
	void _RTI(){};
	void _RTS(){};
	void _SBC(){};
	void _SEC(){};
	void _SED(){};
	void _SEI(){};
	void _STA(){};
	void _STX(){};
	void _STY(){};
	void _TAX(){};
	void _TAY(){};
	void _TSX(){};
	void _TXA(){};
	void _TXS(){};
	void _TYA(){};

	void _XXX(){}; // Unrecognized
	
	// Addressing Modes
	void _Accum(){};
	void _Imm(){};
	void _Absolute(){};
	void _ZeroPage(){};
	void _ZeroPageX(){};
	void _ZeroPageY(){};
	void _AbsoluteX(){};
	void _AbsoluteY(){};
	void _Implied(){};
	void _Relative(){};
	void _IndirectX(){};
	void _IndirectY(){};
	void _AbsoluteIndirect(){};

	void _AddrXXX(){};

	struct Instruction {
		uint8_t msd;
		uint8_t lsd;
		std::string mnemonic;
		void (Processor::*instruction)(void) = NULL;
		void (Processor::*address_mode)(void) = NULL;
		int instruction_bytes = 0;
		int machine_cycles = 0;
	};

	uint8_t fetch();
	uint8_t fetched = 0x00;

	uint16_t addr_abs = 0x0000;
	uint16_t addr_rel = 0x0000;
	uint8_t opcode = 0x00;
	uint8_t cycles = 0;
   
	std::vector<Instruction> instructions = {
		// ==================================================
		// MSD == 0x0
		// ==================================================
		{0x0, 0x0, "BRK", &Processor::_BRK, &Processor::_Implied , 1, 7},
		{0x0, 0x1, "ORA", &Processor::_ORA, &Processor::_IndirectX , 2, 6},
		{0x0, 0x2, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x0, 0x3, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x0, 0x4, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x0, 0x5, "ORA", &Processor::_ORA, &Processor::_ZeroPage, 2, 3},
		{0x0, 0x6, "ASL", &Processor::_ASL, &Processor::_ZeroPage, 2, 5},
		{0x0, 0x7, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x0, 0x8, "PHP", &Processor::_PHP, &Processor::_Implied, 1 , 3},
		{0x0, 0x9, "ORA", &Processor::_ORA, &Processor::_Imm, 2 , 2},
		{0x0, 0xA, "ASL", &Processor::_ASL, &Processor::_Accum, 1, 2},
		{0x0, 0xB, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x0, 0xC, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x0, 0xD, "ORA", &Processor::_ORA, &Processor::_Absolute, 3, 4},
		{0x0, 0xE, "ASL", &Processor::_ASL, &Processor::_Absolute, 3, 6},
		{0x0, 0xF, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},

		// ==================================================
		// MSD == 0x1
		// ==================================================
		{0x1, 0x0, "BPL", &Processor::_BPL, &Processor::_Relative, 2, 2}, // ** Add 1 to cycle count if branch occurs to same page
		{0x1, 0x1, "ORA", &Processor::_ORA, &Processor::_IndirectY, 2, 5}, // * Add 1 to cycle count if page boundary is crossed
		{0x1, 0x2, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x1, 0x3, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x1, 0x4, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x1, 0x5, "ORA", &Processor::_ORA, &Processor::_ZeroPageX, 2, 4}, 
		{0x1, 0x6, "ASL", &Processor::_ASL, &Processor::_ZeroPageX, 2, 6},
		{0x1, 0x7, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x1, 0x8, "CLC", &Processor::_CLC, &Processor::_Implied, 1, 2},
		{0x1, 0x9, "ORA", &Processor::_ORA, &Processor::_AbsoluteY, 3, 4}, // * Add 1 to cycle count if page boundary is crossed 
		{0x1, 0xA, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x1, 0xB, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x1, 0xC, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x1, 0xD, "ORA", &Processor::_ORA, &Processor::_AbsoluteX, 3, 4}, // * Add 1 to cycle count if page boundary is crossed 
		{0x1, 0xE, "ASL", &Processor::_ASL, &Processor::_AbsoluteX, 3, 7},
		{0x1, 0xF, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},

		// ==================================================
		// MSD == 0x2
		// ==================================================
		{0x2, 0x0, "JSR", &Processor::_JSR, &Processor::_Absolute, 3, 6},
		{0x2, 0x1, "AND", &Processor::_AND, &Processor::_IndirectX, 2, 6}, 
		{0x2, 0x2, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x2, 0x3, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x2, 0x4, "BIT", &Processor::_BIT, &Processor::_ZeroPage, 2, 3},
		{0x2, 0x5, "AND", &Processor::_AND, &Processor::_ZeroPage, 2, 3},
		{0x2, 0x6, "ROL", &Processor::_ROL, &Processor::_ZeroPage, 2, 5},
		{0x2, 0x7, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x2, 0x8, "PLP", &Processor::_PLP, &Processor::_Implied, 1, 4},
		{0x2, 0x9, "AND", &Processor::_AND, &Processor::_Imm, 2, 2},
		{0x2, 0xA, "ROL", &Processor::_ROL, &Processor::_Accum, 1, 2},
		{0x2, 0xB, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x2, 0xC, "BIT", &Processor::_BIT, &Processor::_Absolute, 3, 4},
		{0x2, 0xD, "AND", &Processor::_AND, &Processor::_Absolute, 3, 4},
		{0x2, 0xE, "ROL", &Processor::_ROL, &Processor::_Absolute, 3, 6},
		{0x2, 0xF, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},

		// ==================================================
		// MSD == 0x3
		// ==================================================
		{0x3, 0x0, "BMI", &Processor::_BMI, &Processor::_Relative, 2, 2}, // ** Add 1 to cycle count if branch occurs to same page; Add 2 if branch to different page
		{0x3, 0x1, "AND", &Processor::_AND, &Processor::_IndirectY, 2, 5}, // * Add 1 to cycle count if page boundary is crossed
		{0x3, 0x2, "XXX", &Processor::_XXX , &Processor::_AddrXXX, 0, 0},
		{0x3, 0x3, "XXX", &Processor::_XXX , &Processor::_AddrXXX, 0, 0},
		{0x3, 0x4, "XXX", &Processor::_XXX , &Processor::_AddrXXX, 0, 0},
		{0x3, 0x5, "AND", &Processor::_AND , &Processor::_ZeroPageX, 2, 4},
		{0x3, 0x6, "ROL", &Processor::_ROL , &Processor::_ZeroPageX, 2, 6},
		{0x3, 0x7, "XXX", &Processor::_XXX , &Processor::_AddrXXX, 0, 0},
		{0x3, 0x8, "SEC", &Processor::_SEC , &Processor::_Implied, 1, 2},
		{0x3, 0x9, "AND", &Processor::_AND , &Processor::_AbsoluteY, 3, 4}, // * Add 1 to cycle count if page boundary is crossde
		{0x3, 0xA, "XXX", &Processor::_XXX , &Processor::_AddrXXX, 0, 0},
		{0x3, 0xB, "XXX", &Processor::_XXX , &Processor::_AddrXXX, 0, 0},
		{0x3, 0xC, "XXX", &Processor::_XXX , &Processor::_AddrXXX, 0, 0},
		{0x3, 0xD, "AND" , &Processor::_AND , &Processor::_AbsoluteX, 3, 4}, // * Add 1 to cycle count if page boundary is crossed
		{0x3, 0xE, "ROL", &Processor::_ROL , &Processor::_AbsoluteX, 3, 7},
		{0x3, 0xF, "XXX", &Processor::_XXX , &Processor::_AddrXXX, 0, 0},

		// ==================================================
		// MSD == 0x4
		// ==================================================
		{0x4, 0x0, "RTI", &Processor::_RTI , &Processor::_Implied, 1, 6},
		{0x4, 0x1, "EOR", &Processor::_EOR , &Processor::_IndirectX, 2, 6},
		{0x4, 0x2, "XXX", &Processor::_XXX , &Processor::_AddrXXX, 0, 0},
		{0x4, 0x3, "XXX", &Processor::_XXX , &Processor::_AddrXXX, 0, 0},
		{0x4, 0x4, "XXX", &Processor::_XXX , &Processor::_AddrXXX, 0, 0},
		{0x4, 0x5, "EOR", &Processor::_EOR , &Processor::_ZeroPage, 2, 3},
		{0x4, 0x6, "LSR", &Processor::_LSR , &Processor::_ZeroPage, 2, 5},
		{0x4, 0x7, "XXX", &Processor::_XXX , &Processor::_AddrXXX, 0, 0},
		{0x4, 0x8, "PHA", &Processor::_PHA , &Processor::_Implied, 1, 3},
		{0x4, 0x9, "EOR", &Processor::_EOR , &Processor::_Imm, 2, 2},
		{0x4, 0xA, "LSR", &Processor::_LSR , &Processor::_Accum, 1, 2},
		{0x4, 0xB, "XXX", &Processor::_XXX , &Processor::_AddrXXX, 0, 0},
		{0x4, 0xC, "JMP", &Processor::_JMP , &Processor::_Absolute, 3, 3},
		{0x4, 0xD, "EOR", &Processor::_EOR , &Processor::_Absolute, 3, 4},
		{0x4, 0xE, "LSR", &Processor::_LSR , &Processor::_Absolute, 3, 6},
		{0x4, 0xF, "XXX", &Processor::_XXX , &Processor::_AddrXXX, 0, 0},

		// ==================================================
		// MSD == 0x5
		// ==================================================
		{0x5, 0x0, "BVC", &Processor::_BVC, &Processor::_Relative, 2, 2}, // ** 
		{0x5, 0x1, "EOR", &Processor::_EOR, &Processor::_IndirectY, 2, 5}, // *
		{0x5, 0x2, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x5, 0x3, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x5, 0x4, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x5, 0x5, "EOR", &Processor::_EOR, &Processor::_ZeroPageX, 2, 4},
		{0x5, 0x6, "LSR", &Processor::_LSR, &Processor::_ZeroPageX, 2, 6},
		{0x5, 0x7, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x5, 0x8, "CLI", &Processor::_CLI, &Processor::_Implied, 1, 2},
		{0x5, 0x9, "EOR", &Processor::_EOR, &Processor::_AbsoluteY, 3, 4}, // *
		{0x5, 0xA, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x5, 0xB, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x5, 0xC, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x5, 0xD, "EOR", &Processor::_EOR, &Processor::_AbsoluteX, 3, 4}, // *
		{0x5, 0xE, "LSR", &Processor::_LSR, &Processor::_AbsoluteX, 3, 7},
		{0x5, 0xF, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},

		// ==================================================
		// MSD == 0x6
		// ==================================================
		{0x6, 0x0, "RTS", &Processor::_RTS, &Processor::_Implied, 1, 6},
		{0x6, 0x1, "ADC", &Processor::_ADC, &Processor::_IndirectX, 2, 6},
		{0x6, 0x2, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x6, 0x3, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x6, 0x4, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x6, 0x5, "ADC", &Processor::_ADC, &Processor::_ZeroPage, 2, 3},
		{0x6, 0x6, "ROR", &Processor::_ROR, &Processor::_ZeroPage, 2, 5},
		{0x6, 0x7, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x6, 0x8, "PLA", &Processor::_PLA, &Processor::_Implied, 1, 4},
		{0x6, 0x9, "ADC", &Processor::_ADC, &Processor::_Imm, 2, 2},
		{0x6, 0xA, "ROR", &Processor::_ROR, &Processor::_Accum, 1, 2},
		{0x6, 0xB, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x6, 0xC, "JMP", &Processor::_JMP, &Processor::_AbsoluteIndirect, 3, 5},
		{0x6, 0xD, "ADC", &Processor::_ADC, &Processor::_Absolute, 3, 4},
		{0x6, 0xE, "ROR", &Processor::_ROR, &Processor::_Absolute, 3, 6},
		{0x6, 0xF, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},

		// ==================================================
		// MSD == 0x7
		// ==================================================
		{0x7, 0x0, "BVS", &Processor::_BVS, &Processor::_Relative, 2, 2}, // **
		{0x7, 0x1, "ADC", &Processor::_ADC, &Processor::_IndirectY, 2, 5}, // *
		{0x7, 0x2, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x7, 0x3, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x7, 0x4, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x7, 0x5, "ADC", &Processor::_ADC, &Processor::_ZeroPageX, 2, 4},
		{0x7, 0x6, "ROR", &Processor::_ROR, &Processor::_ZeroPageX, 2, 6},
		{0x7, 0x7, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x7, 0x8, "SEI", &Processor::_SEI, &Processor::_Implied, 1, 2},
		{0x7, 0x9, "ADC", &Processor::_ADC, &Processor::_AbsoluteY, 3, 4}, // *
		{0x7, 0xA, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x7, 0xB, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x7, 0xC, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x7, 0xD, "ADC", &Processor::_ADC, &Processor::_AbsoluteX, 3, 4}, // *
		{0x7, 0xE, "ROR", &Processor::_ROR, &Processor::_AbsoluteX, 3, 7},
		{0x7, 0xF, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},

		// ==================================================
		// MSD == 0x8
		// ==================================================
		{0x8, 0x0, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x8, 0x1, "STA", &Processor::_STA, &Processor::_IndirectX, 2, 6},
		{0x8, 0x2, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x8, 0x3, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x8, 0x4, "STY", &Processor::_STY, &Processor::_ZeroPage, 2, 3},
		{0x8, 0x5, "STA", &Processor::_STA, &Processor::_ZeroPage, 2, 3},
		{0x8, 0x6, "STX", &Processor::_STX, &Processor::_ZeroPage, 2, 3},
		{0x8, 0x7, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x8, 0x8, "DEY", &Processor::_DEY, &Processor::_Implied, 1, 2},
		{0x8, 0x9, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x8, 0xA, "TXA", &Processor::_TXA, &Processor::_Implied, 1, 2},
		{0x8, 0xB, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x8, 0xC, "STY", &Processor::_STY, &Processor::_Absolute, 3, 4},
		{0x8, 0xD, "STA", &Processor::_STA, &Processor::_Absolute, 3, 4},
		{0x8, 0xE, "STX", &Processor::_STX, &Processor::_Absolute, 3, 4},
		{0x8, 0xF, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},

		// ==================================================
		// MSD == 0x9
		// ==================================================
		{0x9, 0x0, "BCC", &Processor::_BCC, &Processor::_Relative, 2, 2}, // **
		{0x9, 0x1, "STA", &Processor::_STA, &Processor::_IndirectY, 2, 6},
		{0x9, 0x2, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x9, 0x3, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x9, 0x4, "STY", &Processor::_STY, &Processor::_ZeroPageX, 2, 4},
		{0x9, 0x5, "STA", &Processor::_STA, &Processor::_ZeroPageX, 2, 4},
		{0x9, 0x6, "STX", &Processor::_STX, &Processor::_ZeroPageY, 2, 4},
		{0x9, 0x7, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x9, 0x8, "TYA", &Processor::_TYA, &Processor::_Implied, 1, 2},
		{0x9, 0x9, "STA", &Processor::_STA, &Processor::_AbsoluteY, 3, 5},
		{0x9, 0xA, "TXS", &Processor::_TXS, &Processor::_Implied, 1, 2},
		{0x9, 0xB, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x9, 0xC, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x9, 0xD, "STA", &Processor::_STA, &Processor::_AbsoluteX, 3, 5},
		{0x9, 0xE, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0x9, 0xF, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},

		// ==================================================
		// MSD == 0xA
		// ==================================================
		{0xA, 0x0, "LDY", &Processor::_LDY, &Processor::_Imm, 2, 2},
		{0xA, 0x1, "LDA", &Processor::_LDA, &Processor::_IndirectX, 2, 6},
		{0xA, 0x2, "LDX", &Processor::_LDX, &Processor::_Imm, 2, 2},
		{0xA, 0x3, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xA, 0x4, "LDY", &Processor::_LDY, &Processor::_ZeroPage, 2, 3},
		{0xA, 0x5, "LDA", &Processor::_LDA, &Processor::_ZeroPage, 2, 3},
		{0xA, 0x6, "LDX", &Processor::_LDX, &Processor::_ZeroPage, 2, 3},
		{0xA, 0x7, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xA, 0x8, "TAY", &Processor::_TAY, &Processor::_Implied, 1, 2},
		{0xA, 0x9, "LDA", &Processor::_LDA, &Processor::_Imm, 2, 2},
		{0xA, 0xA, "TAX", &Processor::_TAX, &Processor::_Implied, 1, 2},
		{0xA, 0xB, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xA, 0xC, "LDY", &Processor::_LDY, &Processor::_Absolute, 3, 4},
		{0xA, 0xD, "LDA", &Processor::_LDA, &Processor::_Absolute, 3, 4},
		{0xA, 0xE, "LDX", &Processor::_LDX, &Processor::_Absolute, 3, 4},
		{0xA, 0xF, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},

		// =================================================
		// MSD == 0xB
		// =================================================
		{0xB, 0x0, "BCS", &Processor::_BCS, &Processor::_Relative, 2, 2}, // **
		{0xB, 0x1, "LDA", &Processor::_LDA, &Processor::_IndirectY, 2, 5}, // *
		{0xB, 0x2, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xB, 0x3, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xB, 0x4, "LDY", &Processor::_LDY, &Processor::_ZeroPageX, 2, 4},
		{0xB, 0x5, "LDA", &Processor::_LDA, &Processor::_ZeroPageX, 2, 4},
		{0xB, 0x6, "LDX", &Processor::_LDX, &Processor::_ZeroPageY, 2, 4},
		{0xB, 0x7, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xB, 0x8, "CLV", &Processor::_CLV, &Processor::_Implied, 1, 2},
		{0xB, 0x9, "LDA", &Processor::_LDA, &Processor::_AbsoluteY, 3, 4}, // *
		{0xB, 0xA, "TSX", &Processor::_TSX, &Processor::_Implied, 1, 2},
		{0xB, 0xB, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xB, 0xC, "LDY", &Processor::_LDY, &Processor::_AbsoluteX, 3, 4}, // *
		{0xB, 0xD, "LDA", &Processor::_LDA, &Processor::_AbsoluteX, 3, 4}, // *
		{0xB, 0xE, "LDX", &Processor::_LDX, &Processor::_AbsoluteY, 3, 4}, // *
		{0xB, 0xF, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},

		// =================================================
		// MSD == 0xC
		// =================================================
		{0xC, 0x0, "CPY", &Processor::_CPY, &Processor::_Imm, 2, 2},
		{0xC, 0x1, "CMP", &Processor::_CMP, &Processor::_IndirectX, 2, 6},
		{0xC, 0x2, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xC, 0x3, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xC, 0x4, "CPY", &Processor::_CPY, &Processor::_ZeroPage, 2, 3},
		{0xC, 0x5, "CMP", &Processor::_CMP, &Processor::_ZeroPage, 2, 3},
		{0xC, 0x6, "DEC", &Processor::_DEC, &Processor::_ZeroPage, 2, 5},
		{0xC, 0x7, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xC, 0x8, "INY", &Processor::_INY, &Processor::_Implied, 1, 2},
		{0xC, 0x9, "CMP", &Processor::_CMP, &Processor::_Imm, 2, 2},
		{0xC, 0xA, "DEX", &Processor::_DEX, &Processor::_Implied, 1, 2},
		{0xC, 0xB, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xC, 0xC, "CPY", &Processor::_CPY, &Processor::_Absolute, 3, 4},
		{0xC, 0xD, "CMP", &Processor::_CMP, &Processor::_Absolute, 3, 4},
		{0xC, 0xE, "DEC", &Processor::_DEC, &Processor::_Absolute, 3, 6},
		{0xC, 0xF, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},

		// =================================================
		// MSD == 0xD
		// =================================================
		{0xD, 0x0, "BNE", &Processor::_BNE, &Processor::_Relative, 2, 2}, // **
		{0xD, 0x1, "CMP", &Processor::_CMP, &Processor::_IndirectY, 2, 5}, // *
		{0xD, 0x2, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xD, 0x3, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xD, 0x4, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xD, 0x5, "CMP", &Processor::_CMP, &Processor::_ZeroPageX, 2, 4},
		{0xD, 0x6, "DEC", &Processor::_DEC, &Processor::_ZeroPageX, 2, 6},
		{0xD, 0x7, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xD, 0x8, "CLD", &Processor::_CLD, &Processor::_Implied, 1, 2},
		{0xD, 0x9, "CMP", &Processor::_CMP, &Processor::_AbsoluteY, 3, 4}, // *
		{0xD, 0xA, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xD, 0xB, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xD, 0xC, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xD, 0xD, "CMP", &Processor::_CMP, &Processor::_AbsoluteX, 3, 4}, // *
		{0xD, 0xE, "DEC", &Processor::_DEC, &Processor::_AbsoluteX, 3, 7},
		{0xD, 0xF, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},

		// =================================================
		// MSD == 0xE
		// =================================================
		{0xE, 0x0, "CPX", &Processor::_CPX, &Processor::_Imm, 2, 2},
		{0xE, 0x1, "SBC", &Processor::_SBC, &Processor::_IndirectX, 2, 6},
		{0xE, 0x2, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xE, 0x3, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xE, 0x4, "CPX", &Processor::_CPX, &Processor::_ZeroPage, 2, 3},
		{0xE, 0x5, "SBC", &Processor::_SBC, &Processor::_ZeroPage, 2, 3},
		{0xE, 0x6, "INC", &Processor::_INC, &Processor::_ZeroPage, 2, 5},
		{0xE, 0x7, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xE, 0x8, "INX", &Processor::_INX, &Processor::_Implied, 1, 2},
		{0xE, 0x9, "SBC", &Processor::_SBC, &Processor::_Imm, 2, 2},
		{0xE, 0xA, "NOP", &Processor::_NOP, &Processor::_Implied, 1, 2},
		{0xE, 0xB, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xE, 0xC, "CPX", &Processor::_CPX, &Processor::_Absolute, 3, 4},
		{0xE, 0xD, "SBC", &Processor::_SBC, &Processor::_Absolute, 3, 4},
		{0xE, 0xE, "INC", &Processor::_INC, &Processor::_Absolute, 3, 6},
		{0xE, 0xF, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},

		// =================================================
		// MSD == 0xF
		// =================================================
		{0xF, 0x0, "BEQ", &Processor::_BEQ, &Processor::_Relative, 2, 2}, // **
		{0xF, 0x1, "SBC", &Processor::_SBC, &Processor::_IndirectY, 2, 5}, // *
		{0xF, 0x2, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xF, 0x3, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xF, 0x4, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xF, 0x5, "SBC", &Processor::_SBC, &Processor::_ZeroPageX, 2, 4},
		{0xF, 0x6, "INC", &Processor::_INC, &Processor::_ZeroPageX, 2, 6},
		{0xF, 0x7, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xF, 0x8, "SED", &Processor::_SED, &Processor::_Implied, 1, 2},
		{0xF, 0x9, "SBC", &Processor::_SBC, &Processor::_AbsoluteY, 3, 4}, // *
		{0xF, 0xA, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xF, 0xB, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xF, 0xC, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
		{0xF, 0xD, "SBC", &Processor::_SBC, &Processor::_AbsoluteX, 3, 4}, // *
		{0xF, 0xE, "INC", &Processor::_INC, &Processor::_AbsoluteX, 3, 7},
		{0xF, 0xF, "XXX", &Processor::_XXX, &Processor::_AddrXXX, 0, 0},
	};		
};

Processor::Processor(){}