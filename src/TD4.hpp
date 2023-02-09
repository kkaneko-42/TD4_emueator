#pragma once

#include <cstddef>
#include <map>
#include <iostream>
#include <bitset>

#define ROM_SIZE 16

namespace td4 {
    enum OpeCode {
        ADD_REG_A     = 0b0000,
        ADD_REG_B     = 0b0101,
        MOV_REG_A_IMM = 0b0011,
        MOV_REG_B_IMM = 0b0111,
        MOV_REG_A_B   = 0b0001,
        MOV_REG_B_A   = 0b0100,
        JMP           = 0b1111,
        JNC           = 0b1110,
        IN_A          = 0b0010,
        IN_B          = 0b0110,
        OUT_B         = 0b1001,
        OUT_IMM       = 0b1011,
    };

    struct Operand {
        unsigned char imm; // 4bit
    };

    struct Registers {
        unsigned char reg_a; // 4bit
        unsigned char reg_b; // 4bit
        unsigned char carry_flag; // 1bit
        unsigned char pc; // 4bit

        void print() {
            std::cout << "==== Registers info ====" << std::endl;
            std::cout << "Reg A     : " << std::bitset<4>(reg_a) << std::endl;
            std::cout << "Reg B     : " << std::bitset<4>(reg_b) << std::endl;
            std::cout << "Carry flag: " << std::bitset<4>(carry_flag) << std::endl;
            std::cout << "PC        : " << std::bitset<4>(pc) << std::endl;
        }
    };

    struct Ports {
        unsigned char in; // 4bit
        unsigned char out; // 4bit
    };

    class TD4_test;

    class TD4 {
        public:
            #ifdef TEST
            friend TD4_test;
            #endif
            TD4( void );
            void run( void );
            void consumeClock( void );
            void setInPort( unsigned char value ) {
                // 下位4bitをマスクして代入
                _ports.in = value & 0b1111;
            }
            unsigned char getOutPort( void ) { return _ports.out; }
            void setROM( unsigned char* rom ) { _rom = rom; }

        private:
            typedef void (TD4::*Operation)( void );
            std::map<OpeCode, Operation> _operationMap;

            unsigned char fetch( void );
            unsigned char fetch_debug( void );
            bool decode( unsigned char op );
            void execute( void );
            void addRegA( void );
            void addRegB( void );
            void movRegAImm( void );
            void movRegBImm( void );
            void movRegAB( void );
            void movRegBA( void );
            void jmp( void );
            void jnc( void );
            void inA( void );
            void inB( void );
            void outB( void );
            void outImm( void );

            Registers _registers;
            Ports _ports;

            OpeCode _opecode;
            Operand _operand;

            unsigned char* _rom;
    };
}