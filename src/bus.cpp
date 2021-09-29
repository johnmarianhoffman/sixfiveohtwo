#include <processor.h>
#include <bus.h>

Bus::Bus(){
	// Clear out the RAM
	for (auto &i: ram)
		i = 0x00;

	// Connect Processor to bus
	processor.ConnectBus(this);
}


uint8_t Bus::Read(uint16_t addr, bool readOnly){
	if (addr >= 0x0000 && addr <= 0xFFFF)
		return ram[addr];

	return 0x00;
}

void Bus::Write(uint16_t addr, uint8_t data){
	if (addr >= 0x0000 && addr <= 0xFFFF)
		ram[addr] = data;
}