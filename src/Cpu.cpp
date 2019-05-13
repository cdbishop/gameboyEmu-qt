#include "Cpu.hpp"

#include "Instructions/Placeholder.hpp"
#include "Instructions/Jump.hpp"
#include "Instructions/NoOp.hpp"
#include "Instructions/LogicalOp.hpp"
#include "Instructions/Load.hpp"

#include <map>

const std::map<unsigned char, Instruction> s_lookup = {
  { 0x00, Instruction("noop", 1, 0, &Instructions::NoOp) },
  { 0x01, Instruction("ld bc", 3, 3, std::bind(Instructions::LoadImmediate16, std::placeholders::_1, Register16::BC)) },
  { 0x02, Instruction("ld (bc) a", 1, 2, &Instructions::Placeholder) },
  { 0x03, Instruction("inc bc", 1, 2, &Instructions::Placeholder) },
  { 0x04, Instruction("inc b", 1, 1, &Instructions::Placeholder) },
  { 0x05, Instruction("dec b", 1, 1, &Instructions::Placeholder) },
  { 0x06, Instruction("ld b {lower}", 2, 2, std::bind(Instructions::LoadImmediate8, std::placeholders::_1, Register8::B)) },
  { 0x07, Instruction("RLC A", 1, 1, &Instructions::Placeholder) },
  { 0x08, Instruction("ld (nn) sp", 3, 5, &Instructions::Placeholder) },
  { 0x09, Instruction("add hl bc", 1, 2, &Instructions::Placeholder) },
  { 0x0a, Instruction("ld a (bc)", 1, 2, &Instructions::Placeholder) },
  { 0x0b, Instruction("dec bc", 1, 2, &Instructions::Placeholder) },
  { 0x0c, Instruction("inc c", 1, 1, &Instructions::Placeholder) },
  { 0x0d, Instruction("dec c", 1, 2, &Instructions::Placeholder) },
  { 0x0e, Instruction("ld c {lower}", 2, 2, std::bind(Instructions::LoadImmediate8, std::placeholders::_1, Register8::C)) },
  { 0x0f, Instruction("rrc A", 1, 1, &Instructions::Placeholder) },
  { 0x10, Instruction("STOP", 2, 1, &Instructions::Placeholder) },
  { 0x11, Instruction("ld DE {upper|lower}", 3, 3, &Instructions::Placeholder) },
  { 0x12, Instruction("ld (DE) A", 1, 2, &Instructions::Placeholder) },
  { 0x13, Instruction("inc DE", 1, 2, &Instructions::Placeholder) },
  { 0x14, Instruction("inc D", 1, 1, &Instructions::Placeholder) },
  { 0x15, Instruction("dec D", 1, 1, &Instructions::Placeholder) },
  { 0x16, Instruction("LD D {lower}", 2, 2, std::bind(Instructions::LoadImmediate8, std::placeholders::_1, Register8::D)) },
  { 0x17, Instruction("RL A", 1, 1, &Instructions::Placeholder) },
  { 0x18, Instruction("JR n", 2, 2, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0x19, Instruction("ADD HE DE", 1, 2, &Instructions::Placeholder) },
  { 0x1a, Instruction("LD A (DE)", 1, 2, &Instructions::Placeholder) }, 
  { 0x1b, Instruction("DEC DE", 1, 2, &Instructions::Placeholder) },
  { 0x1c, Instruction("INC E", 1, 1, &Instructions::Placeholder) },
  { 0x1d, Instruction("DEC E", 1, 1, &Instructions::Placeholder) },
  { 0x1e, Instruction("LD E {lower}", 2, 2, std::bind(Instructions::LoadImmediate8, std::placeholders::_1, Register8::E)) },
  { 0x1f, Instruction("RR A", 1, 1, &Instructions::Placeholder) },
  { 0x20, Instruction("JR NZ {lower}", 2, 2, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0x21, Instruction("LD HL {upper|lower}", 3, 3, std::bind(Instructions::LoadImmediate16, std::placeholders::_1, Register16::HL)) },
  { 0x22, Instruction("LDI (HL) A", 1, 2, &Instructions::Placeholder) },
  { 0x23, Instruction("INC HL", 1, 2, &Instructions::Placeholder) },
  { 0x24, Instruction("INC H", 1, 1, &Instructions::Placeholder) },
  { 0x25, Instruction("DEC H", 1, 1, &Instructions::Placeholder) },
  { 0x26, Instruction("LD H (n)", 2, 2, &Instructions::Placeholder) },
  { 0x27, Instruction("DAA", 1, 1, &Instructions::Placeholder) },
  { 0x28, Instruction("jr z {lower", 2, 2, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0x29, Instruction("ADD HL HL", 1, 2, &Instructions::Placeholder) },
  { 0x2a, Instruction("LDI A (HL)", 1, 2, &Instructions::Placeholder) },
  { 0x2b, Instruction("DEC HL", 1, 2, &Instructions::Placeholder) },
  { 0x2c, Instruction("INC L", 1, 1, &Instructions::Placeholder) },
  { 0x2d, Instruction("DEC L", 1, 1, &Instructions::Placeholder) },
  { 0x2e, Instruction("LD L n", 2, 2, std::bind(Instructions::LoadImmediate8, std::placeholders::_1, Register8::L)) },
  { 0x2f, Instruction("CPL", 1, 1, &Instructions::Placeholder) },
  { 0x30, Instruction("jr nc {lower}", 2, 2, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0x31, Instruction("LD SP nn", 3, 3, &Instructions::Placeholder) },
  { 0x32, Instruction("ldd hl", 1, 2, &Instructions::Placeholder) },
  { 0x33, Instruction("INC SP", 2, 2, &Instructions::Placeholder) },
  { 0x34, Instruction("INC (HL)", 2, 2, &Instructions::Placeholder) },
  { 0x35, Instruction("DEC (HL)", 2, 2, &Instructions::Placeholder) },
  { 0x36, Instruction("LD (HL), n", 2, 4, &Instructions::Placeholder) },
  { 0x37, Instruction("SCF", 1, 1, &Instructions::Placeholder) },
  { 0x38, Instruction("JR C {lower}", 2, 2, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0x39, Instruction("ADD HL SP", 1, 2, &Instructions::Placeholder) },
  { 0x3a, Instruction("LDD A (HL)", 1, 2, &Instructions::Placeholder) },
  { 0x3b, Instruction("DEC SP", 1, 2, &Instructions::Placeholder) },
  { 0x3c, Instruction("INC A", 1, 1, &Instructions::Placeholder) },
  { 0x3d, Instruction("DEC A", 1, 1, &Instructions::Placeholder) },
  { 0x3e, Instruction("LD A {lower}", 2, 2, std::bind(Instructions::LoadImmediate8, std::placeholders::_1, Register8::A)) },
  { 0x3f, Instruction("CCF", 1, 1, &Instructions::Placeholder) },
  { 0x40, Instruction("LD B B", 1, 1, &Instructions::Placeholder) },
  { 0x41, Instruction("LD B C", 1, 1, &Instructions::Placeholder) },
  { 0x42, Instruction("LD B D", 1, 1, &Instructions::Placeholder) },
  { 0x43, Instruction("LD B E", 1, 1, &Instructions::Placeholder) },
  { 0x44, Instruction("LD B H", 1, 1, &Instructions::Placeholder) },
  { 0x45, Instruction("LD B L", 1, 1, &Instructions::Placeholder) },
  { 0x46, Instruction("LD B (HL)", 1, 2, &Instructions::Placeholder) },
  { 0x47, Instruction("LD B A", 1, 1, &Instructions::Placeholder) },
  { 0x48, Instruction("LD B C", 1, 1, &Instructions::Placeholder) },
  { 0x49, Instruction("LD C C", 1, 1, &Instructions::Placeholder) },
  { 0x4a, Instruction("LD C D", 1, 1, &Instructions::Placeholder) },
  { 0x4b, Instruction("LD C E", 1, 1, &Instructions::Placeholder) },
  { 0x4c, Instruction("LD C H", 1, 1, &Instructions::Placeholder) },
  { 0x4d, Instruction("LD C L", 1, 1, &Instructions::Placeholder) },
  { 0x4e, Instruction("LD C (HL)", 1, 2, &Instructions::Placeholder) },
  { 0x4f, Instruction("LD C A", 1, 1, &Instructions::Placeholder) },
  { 0x50, Instruction("LD D B", 1, 1, &Instructions::Placeholder) },
  { 0x51, Instruction("LD D C", 1, 1, &Instructions::Placeholder) },
  { 0x52, Instruction("LD D D", 1, 1, &Instructions::Placeholder) },
  { 0x53, Instruction("LD D E", 1, 1, &Instructions::Placeholder) },
  { 0x54, Instruction("LD D H", 1, 1, &Instructions::Placeholder) },
  { 0x55, Instruction("LD D L", 1, 1, &Instructions::Placeholder) },
  { 0x56, Instruction("LD D (HL)", 1, 2, &Instructions::Placeholder) },
  { 0x57, Instruction("LD D A", 1, 1, &Instructions::Placeholder) },
  { 0x58, Instruction("LD E B", 1, 1, &Instructions::Placeholder) },
  { 0x59, Instruction("LD E C", 1, 1, &Instructions::Placeholder) },
  { 0x5a, Instruction("LD E D", 1, 1, &Instructions::Placeholder) },
  { 0x5b, Instruction("LD E E", 1, 1, &Instructions::Placeholder) },
  { 0x5c, Instruction("LD E H", 1, 1, &Instructions::Placeholder) },
  { 0x5d, Instruction("LD E L", 1, 1, &Instructions::Placeholder) },
  { 0x5e, Instruction("LD E (HL)", 1, 2, &Instructions::Placeholder) },
  { 0x5f, Instruction("LD E A", 1, 1, &Instructions::Placeholder) },
  { 0x60, Instruction("LD H B", 1, 1, &Instructions::Placeholder) },
  { 0x61, Instruction("LD H C", 1, 1, &Instructions::Placeholder) },
  { 0x62, Instruction("LD H D", 1, 1, &Instructions::Placeholder) },
  { 0x63, Instruction("LD H E", 1, 1, &Instructions::Placeholder) },
  { 0x64, Instruction("LD H H", 1, 1, &Instructions::Placeholder) },
  { 0x65, Instruction("LD H L", 1, 1, &Instructions::Placeholder) },
  { 0x66, Instruction("LD H (HL)", 1, 2, &Instructions::Placeholder) },
  { 0x67, Instruction("LD H A", 1, 1, &Instructions::Placeholder) },
  { 0x68, Instruction("LD L B", 1, 1, &Instructions::Placeholder) },
  { 0x69, Instruction("LD L C", 1, 1, &Instructions::Placeholder) },
  { 0x6a, Instruction("LD L D", 1, 1, &Instructions::Placeholder) },
  { 0x6b, Instruction("LD L E", 1, 1, &Instructions::Placeholder) },
  { 0x6c, Instruction("LD L H", 1, 1, &Instructions::Placeholder) },
  { 0x6d, Instruction("LD L L", 1, 1, &Instructions::Placeholder) },
  { 0x6e, Instruction("LD L (HL)", 2, 3, &Instructions::Placeholder) },
  { 0x6f, Instruction("LD L A", 1, 1, &Instructions::Placeholder) },
  { 0x70, Instruction("LD (HL) B", 1, 2, &Instructions::Placeholder) },
  { 0x71, Instruction("LD (HL) C", 1, 2, &Instructions::Placeholder) },
  { 0x72, Instruction("LD (HL) D", 1, 2, &Instructions::Placeholder) },
  { 0x73, Instruction("LD (HL) E", 1, 2, &Instructions::Placeholder) },
  { 0x74, Instruction("LD (HL) H", 1, 2, &Instructions::Placeholder) },
  { 0x75, Instruction("LD (HL) L", 1, 2, &Instructions::Placeholder) },
  { 0x76, Instruction("HALT", 1, 1, &Instructions::Placeholder) },
  { 0x77, Instruction("LD (HL) A", 2, 2, &Instructions::Placeholder) },
  { 0x78, Instruction("LD A B", 1, 1, &Instructions::Placeholder) },
  { 0x79, Instruction("LD A C", 1, 1, &Instructions::Placeholder) },
  { 0x7a, Instruction("LD A D", 1, 1, &Instructions::Placeholder) },
  { 0x7b, Instruction("LD A E", 1, 1, &Instructions::Placeholder) },
  { 0x7c, Instruction("LD A H", 1, 1, &Instructions::Placeholder) },
  { 0x7d, Instruction("LD A L", 1, 1, &Instructions::Placeholder) },
  { 0x7e, Instruction("LD A (HL)", 1, 2, &Instructions::Placeholder) },
  { 0x7f, Instruction("LD A A", 1, 1, &Instructions::Placeholder) },
  { 0x80, Instruction("ADD A B", 1, 1, &Instructions::Placeholder) },
  { 0x81, Instruction("ADD A C", 1, 1, &Instructions::Placeholder) },
  { 0x82, Instruction("ADD A D", 1, 1, &Instructions::Placeholder) },
  { 0x83, Instruction("ADD A E", 1, 1, &Instructions::Placeholder) },
  { 0x84, Instruction("ADD A H", 1, 0, &Instructions::Placeholder) },
  { 0x85, Instruction("ADD A L", 1, 1, &Instructions::Placeholder) },
  { 0x86, Instruction("ADD A (HL)", 1, 2, &Instructions::Placeholder) },
  { 0x87, Instruction("ADC A A", 1, 1, &Instructions::Placeholder) },
  { 0x88, Instruction("ADC A B", 1, 1, &Instructions::Placeholder) },
  { 0x89, Instruction("ADC A C", 1, 1, &Instructions::Placeholder) },
  { 0x8a, Instruction("ADC A D", 1, 1, &Instructions::Placeholder) },
  { 0x8b, Instruction("ADC A E", 1, 1, &Instructions::Placeholder) },
  { 0x8c, Instruction("ADC A H", 1, 1, &Instructions::Placeholder) },
  { 0x8d, Instruction("ADC A L", 1, 1, &Instructions::Placeholder) },
  { 0x8e, Instruction("ADC A (HL)", 1, 2, &Instructions::Placeholder) },
  { 0x8f, Instruction("ADC A A", 1, 1, &Instructions::Placeholder) },
  { 0x90, Instruction("SUB A B", 1, 1, &Instructions::Placeholder) },
  { 0x91, Instruction("SUB A C", 1, 1, &Instructions::Placeholder) },
  { 0x92, Instruction("SUB A D", 1, 1, &Instructions::Placeholder) },
  { 0x93, Instruction("SUB A E", 1, 1, &Instructions::Placeholder) },
  { 0x94, Instruction("SUB A H", 1, 1, &Instructions::Placeholder) },
  { 0x95, Instruction("SUB A L", 1, 1, &Instructions::Placeholder) },
  { 0x96, Instruction("SUB A (HL)", 1, 2, &Instructions::Placeholder) },
  { 0x97, Instruction("SUB A A", 1, 1, &Instructions::Placeholder) },
  { 0x98, Instruction("SBC A B", 1, 1, &Instructions::Placeholder) },
  { 0x99, Instruction("SBC A C", 1, 1, &Instructions::Placeholder) },
  { 0x9a, Instruction("SBC A D", 1, 1, &Instructions::Placeholder) },
  { 0x9b, Instruction("SBC A E", 1, 1, &Instructions::Placeholder) },
  { 0x9c, Instruction("SBC A H", 1, 1, &Instructions::Placeholder) },
  { 0x9d, Instruction("SBC A L", 1, 1, &Instructions::Placeholder) },
  { 0x9e, Instruction("SBC A (HL)", 1, 2, &Instructions::Placeholder) },
  { 0x9f, Instruction("SBC A A", 1, 1, &Instructions::Placeholder) },
  { 0xa0, Instruction("AND B", 1, 1, &Instructions::Placeholder) },
  { 0xa1, Instruction("AND C", 1, 1, &Instructions::Placeholder) },
  { 0xa2, Instruction("AND D", 1, 1, &Instructions::Placeholder) },
  { 0xa3, Instruction("AND E", 1, 1, &Instructions::Placeholder) },
  { 0xa4, Instruction("AND H", 1, 1, &Instructions::Placeholder) },
  { 0xa5, Instruction("AND L", 1, 1, &Instructions::Placeholder) },
  { 0xa6, Instruction("AND (HL)", 1, 2, &Instructions::Placeholder) },
  { 0xa7, Instruction("AND A", 1, 1, &Instructions::Placeholder) },
  { 0xa8, Instruction("XOR B", 1, 1, std::bind(Instructions::LogicalOp, std::placeholders::_1, Register8::B, Register8::A, Op::Xor)) },
  { 0xa9, Instruction("XOR C", 1, 1, std::bind(Instructions::LogicalOp, std::placeholders::_1, Register8::C, Register8::A, Op::Xor)) },
  { 0xaa, Instruction("XOR D", 1, 1, std::bind(Instructions::LogicalOp, std::placeholders::_1, Register8::D, Register8::A, Op::Xor)) },
  { 0xab, Instruction("XOR E", 1, 1, std::bind(Instructions::LogicalOp, std::placeholders::_1, Register8::E, Register8::A, Op::Xor)) },
  { 0xac, Instruction("XOR H", 1, 1, std::bind(Instructions::LogicalOp, std::placeholders::_1, Register8::H, Register8::A, Op::Xor)) },
  { 0xad, Instruction("XOR L", 1, 1, std::bind(Instructions::LogicalOp, std::placeholders::_1, Register8::L, Register8::A, Op::Xor)) },
  { 0xae, Instruction("XOR (HL)", 1, 2, &Instructions::Placeholder) },
  { 0xaf, Instruction("XOR A", 1, 1, std::bind(Instructions::LogicalOp, std::placeholders::_1, Register8::A, Register8::A, Op::Xor)) },
  { 0xb0, Instruction("OR B", 1, 1, &Instructions::Placeholder) },
  { 0xb1, Instruction("OR C", 1, 1, &Instructions::Placeholder) },
  { 0xb2, Instruction("OR D", 1, 1, &Instructions::Placeholder) },
  { 0xb3, Instruction("OR E", 1, 1, &Instructions::Placeholder) },
  { 0xb4, Instruction("OR H", 1, 1, &Instructions::Placeholder) },
  { 0xb5, Instruction("OR L", 1, 1, &Instructions::Placeholder) },
  { 0xb6, Instruction("OR (HL)", 1, 2, &Instructions::Placeholder) },
  { 0xb7, Instruction("OR A", 1, 1, &Instructions::Placeholder) },
  { 0xb8, Instruction("CP B", 1, 1, &Instructions::Placeholder) },
  { 0xb9, Instruction("CP C", 1, 1, &Instructions::Placeholder) },
  { 0xba, Instruction("CP D", 1, 1, &Instructions::Placeholder) },
  { 0xbb, Instruction("CP E", 1, 1, &Instructions::Placeholder) },
  { 0xbc, Instruction("CP H", 1, 1, &Instructions::Placeholder) },
  { 0xbd, Instruction("CP L", 1, 1, &Instructions::Placeholder) },
  { 0xbe, Instruction("CP (HL)", 1, 2, &Instructions::Placeholder) },
  { 0xbf, Instruction("CP A", 1, 1, &Instructions::Placeholder) },
  { 0xc0, Instruction("RET NZ", 1, 2, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xc1, Instruction("POP BC", 1, 3, &Instructions::Placeholder) },
  { 0xc2, Instruction("JP NZ nn", 3, 3, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xc3, Instruction("JP nn", 3, 3,  &Instructions::Jmp_immediate, Instruction::OpOrder::Pre) },
  { 0xc4, Instruction("CALL NZ nn", 2, 2, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xc5, Instruction("PUSH BC", 2, 2, &Instructions::Placeholder) },
  { 0xc6, Instruction("ADD A n", 2, 2, &Instructions::Placeholder) },
  { 0xc7, Instruction("RST 0", 1, 4, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xc8, Instruction("RET Z", 1, 2, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xc9, Instruction("RET", 1, 1, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xca, Instruction("JP Z nn", 3, 3, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xcb, Instruction("extended", 1, 0, &Instructions::Placeholder) },
  { 0xcc, Instruction("CALL Z nn", 3, 3, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xcd, Instruction("CALL nn", 3, 3, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xce, Instruction("ADC A n", 2, 2, &Instructions::Placeholder) },
  { 0xcf, Instruction("RST 8", 2, 4, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xd0, Instruction("RET NC", 1, 2, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xd1, Instruction("POP DE", 1, 3, &Instructions::Placeholder) },
  { 0xd2, Instruction("JP NC nn", 3, 3, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xd3, Instruction("XX - not implemented", 0, 0, &Instructions::Placeholder) },
  { 0xd4, Instruction("CALL NC nn", 3, 3, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xd5, Instruction("PUSH DE", 1, 4, &Instructions::Placeholder) },
  { 0xd6, Instruction("SUB A n", 2, 2, &Instructions::Placeholder) },
  { 0xd7, Instruction("RST 10", 1, 4, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xd8, Instruction("RET C", 1, 2, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xd9, Instruction("RETI", 2, 2, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xda, Instruction("JP C nn", 2, 2, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xdb, Instruction("XX - not implemented", 1, 0, &Instructions::Placeholder) },
  { 0xdc, Instruction("CALL C nn", 3, 3, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xdd, Instruction("XX - not implemented", 1, 0, &Instructions::Placeholder) },
  { 0xde, Instruction("SBC A n", 2, 2, &Instructions::Placeholder) },
  { 0xdf, Instruction("RST 18", 1, 4, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xe0, Instruction("LDH n A", 2, 3, &Instructions::Placeholder) },
  { 0xe1, Instruction("POP HL", 1, 3, &Instructions::Placeholder) },
  { 0xe2, Instruction("LDH C A", 1, 2, &Instructions::Placeholder) },
  { 0xe3, Instruction("XX - not implemented", 1, 0, &Instructions::Placeholder) },
  { 0xe4, Instruction("XX - not implemented", 1, 0, &Instructions::Placeholder) },
  { 0xe5, Instruction("PUSH HL", 1, 4, &Instructions::Placeholder) },
  { 0xe6, Instruction("AND n", 2, 2, &Instructions::Placeholder) },
  { 0xe7, Instruction("RST 20", 1, 4, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xe8, Instruction("ADD SP n", 2, 4, &Instructions::Placeholder) },
  { 0xe9, Instruction("JP HL", 1, 1, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xea, Instruction("LD A nn", 3, 4, &Instructions::Placeholder) },
  { 0xeb, Instruction("XX - not implemented", 1, 0, &Instructions::Placeholder) },
  { 0xec, Instruction("XX - not implemented", 1, 0, &Instructions::Placeholder) },
  { 0xed, Instruction("XX - not implemented", 1, 0, &Instructions::Placeholder) },
  { 0xee, Instruction("XOR n", 2, 2, &Instructions::Placeholder) },
  { 0xef, Instruction("RST 28", 1, 4, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xf0, Instruction("LDH n A", 2, 3, &Instructions::Placeholder) },
  { 0xf1, Instruction("POP AF", 1, 3, &Instructions::Placeholder) },
  { 0xf2, Instruction("XX - not implemented", 1, 0, &Instructions::Placeholder) },
  { 0xf3, Instruction("DI", 1, 1, &Instructions::Placeholder) },
  { 0xf4, Instruction("XX - not implemented", 1, 0, &Instructions::Placeholder) },
  { 0xf5, Instruction("PUSH AF", 1, 4, &Instructions::Placeholder) },
  { 0xf6, Instruction("OR n", 2, 2, &Instructions::Placeholder) },
  { 0xf7, Instruction("RST 30", 1, 4, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xf8, Instruction("LDHL SP d", 2, 3, &Instructions::Placeholder) },
  { 0xf9, Instruction("LD SP HL", 1, 2, &Instructions::Placeholder) },
  { 0xfa, Instruction("LD A (nn)", 3, 4, &Instructions::Placeholder) },
  { 0xfb, Instruction("EI", 1, 1, &Instructions::Placeholder) },
  { 0xfc, Instruction("XX - not implemented", 1, 0, &Instructions::Placeholder) },
  { 0xfd, Instruction("XX - not implemented", 1, 0, &Instructions::Placeholder) },
  { 0xfe, Instruction("CP A N", 2, 2, &Instructions::Placeholder) },
  { 0xff, Instruction("RST 38", 1, 4, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
};

Cpu::Cpu(const std::shared_ptr<Cart> cart)
  :_cart(cart),
   _a(0x01),
   _b(0x00),
   _c(0x13),
   _d(0x00),
   _e(0xd8),
   _flag(0xb0),
   _h(0x01),
   _l(0x4d),
   _pc(0x100),
   _sp(0xfffe),
   _numCycles(0),
   _clock_m(0), 
   _clock_t(0) {

}

void Cpu::Step()
{
  unsigned char code = _cart->ReadByte(_pc);
  const auto& instruction = s_lookup.at(code); 

  if (instruction.GetOpOrder() == Instruction::OpOrder::Pre) {
    AdvanceState(instruction);
  }

  instruction.Execute(this);
  
  if (instruction.GetOpOrder() == Instruction::OpOrder::Post) {
    AdvanceState(instruction);
  }
}

unsigned char Cpu::ReadByteOffset(unsigned int offset)
{
  return _cart->ReadByte(offset);
}

void Cpu::SetPC(unsigned int address)
{
  _pc = address;
}

unsigned char Cpu::GetRegister(Register8 reg)
{
  switch(reg) {
    case Register8::A:
      return _a;

    case Register8::B:
      return _b;

    case Register8::C:
      return _c;

    case Register8::D:
      return _d;

    case Register8::E:
      return _e;

    case Register8::H:
      return _h;

    case Register8::L:
      return _l;

    default:
      throw std::runtime_error("unknown register");
  }
}

void Cpu::SetRegister(Register8 reg, unsigned char value)
{
  switch (reg) {
  case Register8::A:
    _a = value;
    break;

  case Register8::B:
    _b = value;
    break;

  case Register8::C:
    _c = value;
    break;

  case Register8::D:
    _d = value;
    break;

  case Register8::E:
    _e = value;
    break;

  case Register8::H:
    _h = value;
    break;

  case Register8::L:
    _l = value;
    break;

  default:
    throw std::runtime_error("unknown register");
  }
}

unsigned short Cpu::GetRegister(Register16 reg)
{
  switch (reg) {
    case Register16::BC:
      return _b << 8 | _c;
      break;

    case Register16::DE:
      return _d << 8 | _e;
      break;

    case Register16::HL:
      return _h << 8 | _l;
      break;

    case Register16::SP:
      return _sp;
      break;

    default:
      throw std::runtime_error("Unknown register");
  }
}

void Cpu::SetRegister(Register16 reg, unsigned short value)
{
  unsigned char hi = (value & 0xFF00) >> 8;
  unsigned char lo = (value & 0xFF);

  switch (reg) {
  case Register16::BC:    
    _b = hi;
    _c = lo;
    break;

  case Register16::DE:
    _d = hi;
    _e = lo;
    break;

  case Register16::HL:
    _h = hi;
    _l = lo;
    break;

  case Register16::SP:
    _sp = value;
    break;

  default:
    throw std::runtime_error("Unknown register");
  }
}

void Cpu::AdvanceState(const Instruction& instruction)
{
  _pc += instruction.GetPCAdvance();
  _numCycles += instruction.GetCycles() * 4;
  _clock_m += instruction.GetCycles();
}
