#include "TD4.hpp"
#include <iostream>

int main() {
    td4::TD4 instance;
    unsigned char* rom = new unsigned char[ROM_SIZE];

    rom[ROM_SIZE - 1] = 0b11111111;
    instance.setROM(rom);
    instance.run();
    return 0;
}
