#pragma once

#include <cstdint>
#include <opcodes.h>

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
	
	uint8_t A(){ return accumulator; }
	uint8_t X(){ return idx_reg_x; }
	uint8_t Y(){ return idx_reg_y; }
	uint16_t PC(){ return program_counter; }
	uint8_t PCL(){ return program_counter & 0x00FF; }
	uint8_t PCH(){ return program_counter & 0xFF00; }
	uint8_t SP(){ return stack_pointer; }
	bool SPC(){ return stack_pointer_carry; }
	uint8_t Status(){ return process_status_register; }
	
};