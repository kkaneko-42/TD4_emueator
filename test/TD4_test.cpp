#include "../src/TD4.hpp"
#include <climits>

namespace td4 {
    class TD4_test {
        public:
            void testAll() {
                testAddRegA();
                testAddRegB();
                testMovRegAImm();
                testMovRegBImm();
                testMovRegAB();
                testMovRegBA();
                testJmp();
                testJnc();
            }

            void testAddRegA() {
                std::cout << " ==== ADD_REG_A test ==== " << std::endl;
                TD4 subject;
                unsigned char rom[ROM_SIZE];
                rom[0] = 0b00000000; // nop
                rom[1] = 0b00000001; // add 1
                rom[2] = 0b00000101; // add 5
                rom[3] = 0b00001111; // add 15, carry expected
                subject.setROM(rom);

                // nop test
                subject.consumeClock();
                assert(rom[0], 0, subject._registers.reg_a);

                // add 1 test
                subject.consumeClock();
                assert(rom[1], 1, subject._registers.reg_a);

                // add 5 test
                subject.consumeClock();
                assert(rom[2], 6, subject._registers.reg_a);

                // add 15, and carry test
                subject.consumeClock();
                assert(rom[3], 5, subject._registers.reg_a);
                assert(rom[3], 1, subject._registers.carry_flag);
            }

            void testAddRegB() {
                std::cout << " ==== ADD_REG_B test ==== " << std::endl;
                TD4 subject;
                unsigned char rom[ROM_SIZE];
                rom[0] = 0b01010000; // nop
                rom[1] = 0b01010001; // add 1
                rom[2] = 0b01010101; // add 5
                rom[3] = 0b01011111; // add 15, carry expected
                subject.setROM(rom);

                // nop test
                subject.consumeClock();
                assert(rom[0], 0, subject._registers.reg_b);

                // add 1 test
                subject.consumeClock();
                assert(rom[1], 1, subject._registers.reg_b);

                // add 5 test
                subject.consumeClock();
                assert(rom[2], 6, subject._registers.reg_b);

                // add 15, and carry test
                subject.consumeClock();
                assert(rom[3], 5, subject._registers.reg_b);
                assert(rom[3], 1, subject._registers.carry_flag);
            }

            void testMovRegAImm() {
                std::cout << " ==== MOV_REG_A_IMM test ==== " << std::endl;
                TD4 subject;
                unsigned char rom[ROM_SIZE];
                rom[0] = 0b00110001; // move 1
                rom[1] = 0b00111000; // move 8
                rom[2] = 0b00110000; // move 0
                subject.setROM(rom);

                subject.consumeClock();
                assert(rom[0], 1, subject._registers.reg_a);

                subject.consumeClock();
                assert(rom[1], 8, subject._registers.reg_a);

                subject.consumeClock();
                assert(rom[2], 0, subject._registers.reg_a);
            }

            void testMovRegBImm() {
                std::cout << " ==== MOV_REG_B_IMM test ==== " << std::endl;
                TD4 subject;
                unsigned char rom[ROM_SIZE];
                rom[0] = 0b01110001; // move 1
                rom[1] = 0b01111000; // move 8
                rom[2] = 0b01110000; // move 0
                subject.setROM(rom);

                subject.consumeClock();
                assert(rom[0], 1, subject._registers.reg_b);

                subject.consumeClock();
                assert(rom[1], 8, subject._registers.reg_b);

                subject.consumeClock();
                assert(rom[2], 0, subject._registers.reg_b);
            }

            void testMovRegAB() {
                std::cout << " ==== MOV_REG_A_B test ==== " << std::endl;
                TD4 subject;
                unsigned char rom[ROM_SIZE];
                unsigned char operation = 0b00010000;
                rom[0] = 0b01110001; // mov b 1
                rom[1] = operation; // mov a b
                rom[2] = 0b01111000; // mov b 8
                rom[3] = operation; // mov a b
                subject.setROM(rom);

                subject.consumeClock();
                subject.consumeClock();
                assert(rom[1], 1, subject._registers.reg_a);

                subject.consumeClock();
                subject.consumeClock();
                assert(rom[1], 8, subject._registers.reg_a);
            }

            void testMovRegBA() {
                std::cout << " ==== MOV_REG_B_A test ==== " << std::endl;
                TD4 subject;
                unsigned char rom[ROM_SIZE];
                unsigned char operation = 0b01000000;
                rom[0] = 0b00110001; // mov a 1
                rom[1] = operation; // mov b a
                rom[2] = 0b00111000; // mov a 8
                rom[3] = operation; // mov b a
                subject.setROM(rom);

                subject.consumeClock();
                subject.consumeClock();
                assert(rom[1], 1, subject._registers.reg_b);

                subject.consumeClock();
                subject.consumeClock();
                assert(rom[1], 8, subject._registers.reg_b);
            }

            void testJmp() {
                std::cout << " ==== JMP test ==== " << std::endl;
                TD4 subject;
                unsigned char rom[ROM_SIZE];
                rom[0] = 0b11110010; // jmp 2
                rom[2] = 0b11111000; // jmp 8
                rom[8] = 0b11110000; // jmp 0
                subject.setROM(rom);

                subject.consumeClock();
                assert(rom[0], 2, subject._registers.pc);
                
                subject.consumeClock();
                assert(rom[2], 8, subject._registers.pc);

                subject.consumeClock();
                assert(rom[8], 0, subject._registers.pc);
            }

            void testJnc() {
                std::cout << " ==== JNC test ==== " << std::endl;
                TD4 subject;
                unsigned char rom[ROM_SIZE];
                rom[0] = 0b00001111; // add a 15
                rom[1] = 0b00000001; // add a 1
                rom[2] = 0b11100000; // jnc 0
                rom[3] = 0b00000001; // add a 1
                rom[4] = 0b11101111; // jnc 15
                subject.setROM(rom);

                subject.consumeClock();
                subject.consumeClock();
                subject.consumeClock();
                assert(rom[2], 3, subject._registers.pc);

                subject.consumeClock();
                subject.consumeClock();
                assert(rom[4], 15, subject._registers.pc);
            }

        private:
            void assert(unsigned char input, unsigned char expected, unsigned char actual) {
                std::cout << std::bitset<CHAR_BIT>(input) << " => " << std::bitset<CHAR_BIT>(actual) << "/" << std::bitset<CHAR_BIT>(expected) << std::endl;
                if (expected != actual) {
                    throw std::logic_error("test fail");
                }
            }
    };
}

int main( void ) {
    td4::TD4_test tester;

    tester.testAll();
    return 0;
}
