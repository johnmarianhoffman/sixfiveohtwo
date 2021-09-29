#include <processor.h>
#include <bus.h>

Processor::Processor(){
	instructions = {
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
}

void Processor::ConnectBus(Bus * in_bus){
	bus = in_bus;
}

uint8_t Processor::Read(uint16_t addr){
	return bus->Read(addr);
}

void Processor::Write(uint16_t addr, uint8_t data){
	bus->Write(addr, data);
}

bool Processor::GetFlag(Processor::Flags6502 f){
	return (bool)status & (uint8_t)f;
}

void Processor::SetFlag(Processor::Flags6502 f, bool v){
	uint8_t bit_f = (uint8_t)f;
	
	if (v)
		status = status | bit_f; // Set the flag w/ bitwise or
	else
		status = status & (~bit_f); // Unset the flag 	
}

void Processor::Clock(){
	if (m_cycles == 0 ){
		m_opcode = Read(program_counter);
		program_counter++;

		Instruction curr_instruction = instructions[m_opcode];
		m_cycles = curr_instruction.machine_cycles;

		// This pointer dereferencing feels a little too clever.
		// Not 100% sure I like it.
		(this->*curr_instruction.address_mode)();
		(this->*curr_instruction.instruction)();

		m_cycles += (m_additional_cycles_instruction + m_additional_cycles_addr);
		//cycles += (m_additional_cycles_instruction & m_additional_cycles_addr); javidx9 does this, but it's not clear to me why he uses & instead of +

		m_additional_cycles_addr = 0;
		m_additional_cycles_instruction = 0;
		
	}

	m_cycles--;
}

// Addressing Modes

void Processor::_Accum(){
	m_fetched = accumulator;
};

void Processor::_Imm(){
	m_addr_abs = program_counter++;
};

void Processor::_Absolute(){
	uint16_t lsd = Read(program_counter);
	program_counter++;
	uint16_t msd = Read(program_counter);
	program_counter++;

	m_addr_abs = (msd << 8) | lsd;
};

void Processor::_ZeroPage(){
	m_addr_abs = Read(program_counter);
	program_counter++;
	// David Barr has this. I guess just for extra protection? I think
	// it's unecessary...
	m_addr_abs &= 0x00FF; 
};

void Processor::_ZeroPageX(){
	m_addr_abs = Read(program_counter) + idx_reg_x;
	program_counter++;
	
	// This makes more sense here.  From the 6502 data sheet: "No carry is added
	// to the higher order eight bits of memory, and crossing of page boundaries does
	// not occur."
	m_addr_abs &= 0x00FF; 
	
};

void Processor::_ZeroPageY(){
	m_addr_abs = Read(program_counter) + idx_reg_y;
	program_counter++;
	m_addr_abs &= 0x00FF;
};

void Processor::_AbsoluteX(){


};

void Processor::_AbsoluteY(){};
void Processor::_Implied(){};
void Processor::_Relative(){};
void Processor::_IndirectX(){};
void Processor::_IndirectY(){};
void Processor::_AbsoluteIndirect(){};
void Processor::_AddrXXX(){};