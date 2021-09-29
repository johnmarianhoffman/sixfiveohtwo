#pragma once

#include <cstdint>
#include <array>

class Processor;

class Bus {
public:

	Bus();
	~Bus(){};
	
public: // Devices on the Bus

	Processor processor;
	std::array<uint8_t, (std::size_t)64 * 1024> ram;
	
	uint8_t Read(uint16_t addr, bool readOnly = false);
	void Write(uint16_t addr, uint8_t data);
	
};