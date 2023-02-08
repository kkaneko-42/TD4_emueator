#pragma once

#include <cstddef>
#include <map>
#include <iostream>
#include <bitset>

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

    class TD4 {
        public:
            TD4( void );
            void run( void );

        private:
            typedef void (TD4::*Operation)( void );
            std::map<OpeCode, Operation> _operationMap;

            unsigned char fetch( void );
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

            Registers _registers;

            OpeCode _opecode;
            Operand _operand;
    };
}