#include <cstdint>

#include <Processor.h>

class Bus {
public:

	Bus(){
		// Clear out the RAM
		for (auto &i: ram)
			i = 0x00;

		// Connect Processor to bus
		processor.ConnectBus(this);
		
	};
	~Bus(){};

	
public: // Devices on the Bus

	Processor processor;
	std::array<uint8_t, 64 * 1024> ram;
	
	uint8_t Read(uint16_t addr, bool readOnly = false){
		if (addr >= 0x0000 && addr <= 0xFFFF)
			return ram[addr];

		return 0x00;
	}

	void Write(uint16_t addr, uint8_t data){
		if (addr >= 0x0000 && addr <= 0xFFFF)
			ram[addr] = data
	}
	
}