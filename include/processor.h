#pragma once

#include <cstdint>
#include <string>
#include <vector>

class Bus;

class Processor {
private:
	uint8_t accumulator		 = 0x00;
	uint8_t idx_reg_x		 = 0x00;
	uint8_t idx_reg_y		 = 0x00;
	uint16_t program_counter = 0x00;
	uint8_t stack_pointer	 = 0x00;
	bool stack_pointer_carry = 0x00;
	uint8_t status			 = 0x00;
	
	Bus * bus = NULL;

public:
	enum class Flags6502 {
		C = (1 << 0), // Carry bit
		Z = (1 << 1), // Zero
		I = (1 << 2), // Disable Interrupts
		D = (1 << 3), // Decimal mode
		B = (1 << 4), // Break
		U = (1 << 5), // Unused
		V = (1 << 6), // Overflow
		N = (1 << 7), // Negative
	};

public:
	Processor();
	~Processor(){};
	
	uint8_t A(){ return accumulator; }
	uint8_t X(){ return idx_reg_x; }
	uint8_t Y(){ return idx_reg_y; }
	uint16_t PC(){ return program_counter; }
	uint8_t PCL(){ return program_counter & 0x00FF; }
	uint8_t PCH(){ return program_counter & 0xFF00; }
	uint8_t SP(){ return stack_pointer; }
	bool SPC(){ return stack_pointer_carry; }
	uint8_t Status(){ return status; }

	void ConnectBus(Bus * in_bus);
	uint8_t Read(uint16_t addr);
	void Write(uint16_t addr, uint8_t data);

	bool GetFlag(Flags6502 f);
	void SetFlag(Flags6502 f, bool v);

	void Clock();
	void Reset();
	void IRQ(); // Interrupt Request (can be ignored)
	void NMI(); // Non-maskable Interrupt (can never be disabled)

	uint8_t fetch();
	uint8_t m_fetched = 0x00;

	uint16_t m_addr_abs = 0x0000;
	uint16_t m_addr_rel = 0x0000;
	uint8_t m_opcode = 0x00;
	uint8_t m_cycles = 0;

	uint8_t m_additional_cycles_addr = 0;
	uint8_t m_additional_cycles_instruction = 0;
   
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
	void _Accum();
	void _Imm();
	void _Absolute();
	void _ZeroPage();
	void _ZeroPageX();
	void _ZeroPageY();
	void _AbsoluteX();
	void _AbsoluteY();
	void _Implied();
	void _Relative();
	void _IndirectX();
	void _IndirectY();
	void _AbsoluteIndirect();

	void _AddrXXX();

	struct Instruction {
		uint8_t msd;
		uint8_t lsd;
		std::string mnemonic;
		void (Processor::*instruction)(void) = NULL;
		void (Processor::*address_mode)(void) = NULL;
		int instruction_bytes = 0;
		int machine_cycles = 0;
	};

	std::vector<Instruction> instructions;
	
};
