#include "TD4.hpp"
#include <cstring>

using namespace td4;

TD4::TD4( void ) {
    _registers.reg_a = 0;
    _registers.reg_b = 0;
    _registers.carry_flag = 0;
    _registers.pc = 0;

    _ports.in = 0;
    _ports.out = 0;

    _operationMap[ADD_REG_A]        = &TD4::addRegA;
    _operationMap[ADD_REG_B]        = &TD4::addRegB;
    _operationMap[MOV_REG_A_IMM]    = &TD4::movRegAImm;
    _operationMap[MOV_REG_B_IMM]    = &TD4::movRegBImm;
    _operationMap[MOV_REG_A_B]      = &TD4::movRegAB;
    _operationMap[MOV_REG_B_A]      = &TD4::movRegBA;
    _operationMap[JMP]              = &TD4::jmp;
    _operationMap[JNC]              = &TD4::jnc;
    _operationMap[IN_A]             = &TD4::inA;
    _operationMap[IN_B]             = &TD4::inB;
    _operationMap[OUT_B]            = &TD4::outB;
    _operationMap[OUT_IMM]          = &TD4::outImm;
}

void TD4::run( void ) {
    unsigned char opcode = 0, imm = 0;

    while (true) {
        _registers.print();
        unsigned char op = fetch();
        
        if (!decode(op)) {
            fprintf(stderr, "invalid operation");
            break;
        }

        execute();
    }
}

unsigned char TD4::fetch( void ) {
    // ROMからfetchして、pcをインクリメント
    // 実験用に標準入力から受け取る
    char buf[1024];

    while (true) {
        std::cin >> buf;
        if (std::strlen(buf) != 8) {
            fprintf(stderr, "invalid operation length");
            continue;
        }

        break;
    }

    return static_cast<unsigned char>(std::stoi(buf, nullptr, 2));
}

bool TD4::decode( unsigned char op ) {
    _opecode = static_cast<OpeCode>(op >> 4);
    _operand.imm = (op & 0b1111);

    return true;
}

void TD4::execute( void ) {
    (this->*(_operationMap[_opecode]))();
}

void TD4::addRegA( void ) {
    _registers.reg_a += _operand.imm;
    // 5bit目をマスクして、1bit目に移動
    _registers.carry_flag = (_registers.reg_a & 0b10000) >> 4;
    // 下位4bitのみ反映
    _registers.reg_a &= 0b1111;
}

void TD4::addRegB( void ) {
    _registers.reg_b += _operand.imm;
    // 5bit目をとってくる
    _registers.carry_flag = (_registers.reg_b & 0b10000) >> 4;
    // 下位4bitのみ反映
    _registers.reg_b &= 0b1111;
}

void TD4::movRegAImm( void ) {
    _registers.reg_a = _operand.imm;
}

void TD4::movRegBImm( void ) {
    _registers.reg_b = _operand.imm;
}

void TD4::movRegAB( void ) {
    _registers.reg_a = _registers.reg_b;
}

void TD4::movRegBA( void ) {
    _registers.reg_b = _registers.reg_a;
}

void TD4::jmp( void ) {
    _registers.pc = _operand.imm;
}

void TD4::jnc( void ) {
    if (_registers.carry_flag == 0) {
        jmp();
    }
}

void TD4::inA( void ) {
    _registers.reg_a = _ports.in;
}

void TD4::inB( void ) {
    _registers.reg_b = _ports.in;
}

void TD4::outB( void ) {
    _ports.out = _registers.reg_b;
}

void TD4::outImm( void ) {
    _ports.out = _operand.imm;
}
