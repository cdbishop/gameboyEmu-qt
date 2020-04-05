#include "Cpu.hpp"

#include "CpuState.hpp"
#include "CpuStateNotifier.hpp"

#include "Instructions/Placeholder.hpp"
#include "Instructions/Jump.hpp"
#include "Instructions/NoOp.hpp"
#include "Instructions/LogicalOp.hpp"
#include "Instructions/Load.hpp"
#include "Instructions/Register.hpp"
#include "Instructions/Interrupts.hpp"
#include "Instructions/Compare.hpp"
#include "Instructions/WriteAddress.hpp"
#include "Instructions/Sub.hpp"

#include "MemoryController.hpp"

#include "spdlog/spdlog.h"

#include <iostream>
#include <map>
#include <crtdbg.h>

const std::map<unsigned char, Instruction> s_lookup = {
  { 0x00, Instruction("noop", 0x00, 1, 0, &Instructions::NoOp) },
  { 0x01, Instruction("ld bc", 0x01, 3, 3, std::bind(Instructions::LoadImmediate16, std::placeholders::_1, Register16::BC)) },
  { 0x02, Instruction("ld (bc) a", 0x02, 1, 2, std::bind(Instructions::WriteAddress, std::placeholders::_1, Register16::BC, Register8::A)) },
  { 0x03, Instruction("inc bc", 0x03, 1, 2, std::bind(Instructions::Inc16, std::placeholders::_1, Register16::BC)) },
  { 0x04, Instruction("inc b", 0x04, 1, 1, std::bind(Instructions::Inc8, std::placeholders::_1, Register8::B)) },
  { 0x05, Instruction("dec b", 0x05, 1, 1, std::bind(Instructions::Dec8, std::placeholders::_1, Register8::B)) },
  { 0x06, Instruction("ld b {lower}", 0x06, 2, 2, std::bind(Instructions::LoadImmediate8, std::placeholders::_1, Register8::B)) },
  { 0x07, Instruction("RLC A", 0x07, 1, 1, &Instructions::Placeholder) },
  { 0x08, Instruction("ld (nn) sp", 0x08, 3, 5, &Instructions::Placeholder) },
  { 0x09, Instruction("add hl bc", 0x09, 1, 2, &Instructions::Placeholder) },
  { 0x0a, Instruction("ld a (bc)", 0x0a, 1, 2, &Instructions::Placeholder) },
  { 0x0b, Instruction("dec bc", 0x0b,1, 2, std::bind(Instructions::Dec16, std::placeholders::_1, Register16::BC)) },
  { 0x0c, Instruction("inc c", 0x0c, 1, 1, std::bind(Instructions::Inc8, std::placeholders::_1, Register8::C)) },
  { 0x0d, Instruction("dec c", 0x0d, 1, 2, std::bind(Instructions::Dec8, std::placeholders::_1, Register8::C)) },
  { 0x0e, Instruction("ld c {lower}", 0x0e, 2, 2, std::bind(Instructions::LoadImmediate8, std::placeholders::_1, Register8::C)) },
  { 0x0f, Instruction("rrc A", 0x0f, 1, 1, &Instructions::Placeholder) },
  { 0x10, Instruction("STOP", 0x10, 2, 1, &Instructions::Placeholder) },
  { 0x11, Instruction("ld DE {upper|lower}", 0x11, 3, 3, &Instructions::Placeholder) },
  { 0x12, Instruction("ld (DE) A", 0x12, 1, 2, &Instructions::Placeholder) },
  { 0x13, Instruction("inc DE", 0x13, 1, 2, &Instructions::Placeholder) },
  { 0x14, Instruction("inc D", 0x14, 1, 1, &Instructions::Placeholder) },
  { 0x15, Instruction("dec D", 0x15, 1, 1, &Instructions::Placeholder) },
  { 0x16, Instruction("LD D {lower}", 0x16, 2, 2, std::bind(Instructions::LoadImmediate8, std::placeholders::_1, Register8::D)) },
  { 0x17, Instruction("RL A", 0x17, 1, 1, &Instructions::Placeholder) },
  { 0x18, Instruction("JR n", 0x18, 2, 2, &Instructions::Placeholder, Instruction::OpOrder::None) },
  { 0x19, Instruction("ADD HE DE", 0x19, 1, 2, &Instructions::Placeholder) },
  { 0x1a, Instruction("LD A (DE)", 0x1a, 1, 2, &Instructions::Placeholder) },
  { 0x1b, Instruction("DEC DE", 0x1b, 1, 2, &Instructions::Placeholder) },
  { 0x1c, Instruction("INC E", 0x1c, 1, 1, &Instructions::Placeholder) },
  { 0x1d, Instruction("DEC E", 0x1d, 1, 1, &Instructions::Placeholder) },
  { 0x1e, Instruction("LD E {lower}", 0x1e, 2, 2, std::bind(Instructions::LoadImmediate8, std::placeholders::_1, Register8::E)) },
  { 0x1f, Instruction("RR A", 0x1f, 1, 1, &Instructions::Placeholder) },
  { 0x20, Instruction("JR NZ {lower}", 0x20, 2, 2, std::bind(Instructions::JmpRelative_NotZero, std::placeholders::_1), Instruction::OpOrder::Post) },
  { 0x21, Instruction("LD HL {upper|lower}", 0x21, 3, 3, std::bind(Instructions::LoadImmediate16, std::placeholders::_1, Register16::HL)) },
  { 0x22, Instruction("LDI (HL) A", 0x22, 1, 2, &Instructions::Placeholder) },
  { 0x23, Instruction("INC HL", 0x23, 1, 2, &Instructions::Placeholder) },
  { 0x24, Instruction("INC H", 0x24, 1, 1, &Instructions::Placeholder) },
  { 0x25, Instruction("DEC H", 0x25, 1, 1, &Instructions::Placeholder) },
  { 0x26, Instruction("LD H (n)", 0x26, 2, 2, &Instructions::Placeholder) },
  { 0x27, Instruction("DAA", 0x27, 1, 1, &Instructions::Placeholder) },
  { 0x28, Instruction("jr z {lower}", 0x28, 2, 2,  std::bind(Instructions::JmpRelative_Zero, std::placeholders::_1), Instruction::OpOrder::Pre) },
  { 0x29, Instruction("ADD HL HL", 0x29, 1, 2, &Instructions::Placeholder) },
  { 0x2a, Instruction("LDI A (HL)", 0x2a, 1, 2, &Instructions::Placeholder) },
  { 0x2b, Instruction("DEC HL", 0x2b, 1, 2, &Instructions::Placeholder) },
  { 0x2c, Instruction("INC L", 0x2c, 1, 1, &Instructions::Placeholder) },
  { 0x2d, Instruction("DEC L", 0x2d, 1, 1, &Instructions::Placeholder) },
  { 0x2e, Instruction("LD L n", 0x2e, 2, 2, std::bind(Instructions::LoadImmediate8, std::placeholders::_1, Register8::L)) },
  { 0x2f, Instruction("CPL", 0x2f, 1, 1, &Instructions::Placeholder) },
  { 0x30, Instruction("jr nc {lower}", 0x30, 2, 2, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0x31, Instruction("LD SP nn", 0x31, 3, 3, std::bind(Instructions::LoadImmediate16, std::placeholders::_1, Register16::SP)) },
  { 0x32, Instruction("ldd hl", 0x32, 1, 2, std::bind(Instructions::WriteToAddressAndDec, std::placeholders::_1, Register8::A, Register16::HL)) },
  { 0x33, Instruction("INC SP", 0x33, 2, 2, &Instructions::Placeholder) },
  { 0x34, Instruction("INC (HL)", 0x34, 2, 2, &Instructions::Placeholder) },
  { 0x35, Instruction("DEC (HL)", 0x35, 2, 2, &Instructions::Placeholder) },
  { 0x36, Instruction("LD (HL), n", 0x36, 2, 4, &Instructions::Placeholder) },
  { 0x37, Instruction("SCF", 0x37, 1, 1, &Instructions::Placeholder) },
  { 0x38, Instruction("JR C {lower}", 0x38, 2, 2, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0x39, Instruction("ADD HL SP", 0x39, 1, 2, &Instructions::Placeholder) },
  { 0x3a, Instruction("LDD A (HL)", 0x3a, 1, 2, &Instructions::Placeholder) },
  { 0x3b, Instruction("DEC SP", 0x3b, 1, 2, &Instructions::Placeholder) },
  { 0x3c, Instruction("INC A", 0x3c, 1, 1, &Instructions::Placeholder) },
  { 0x3d, Instruction("DEC A", 0x3d, 1, 1, &Instructions::Placeholder) },
  { 0x3e, Instruction("LD A {lower}", 0x3e, 2, 2, std::bind(Instructions::LoadImmediate8, std::placeholders::_1, Register8::A)) },
  { 0x3f, Instruction("CCF", 0x3f, 1, 1, &Instructions::Placeholder) },
  { 0x40, Instruction("LD B B", 0x40, 1, 1, &Instructions::Placeholder) },
  { 0x41, Instruction("LD B C", 0x41, 1, 1, &Instructions::Placeholder) },
  { 0x42, Instruction("LD B D", 0x42, 1, 1, &Instructions::Placeholder) },
  { 0x43, Instruction("LD B E", 0x43, 1, 1, &Instructions::Placeholder) },
  { 0x44, Instruction("LD B H", 0x44, 1, 1, &Instructions::Placeholder) },
  { 0x45, Instruction("LD B L", 0x45, 1, 1, &Instructions::Placeholder) },
  { 0x46, Instruction("LD B (HL)", 0x46, 1, 2, &Instructions::Placeholder) },
  { 0x47, Instruction("LD B A", 0x47, 1, 1, &Instructions::Placeholder) },
  { 0x48, Instruction("LD B C", 0x48, 1, 1, &Instructions::Placeholder) },
  { 0x49, Instruction("LD C C", 0x49, 1, 1, &Instructions::Placeholder) },
  { 0x4a, Instruction("LD C D", 0x4a, 1, 1, &Instructions::Placeholder) },
  { 0x4b, Instruction("LD C E", 0x4b, 1, 1, &Instructions::Placeholder) },
  { 0x4c, Instruction("LD C H", 0x4c, 1, 1, &Instructions::Placeholder) },
  { 0x4d, Instruction("LD C L", 0x4d, 1, 1, &Instructions::Placeholder) },
  { 0x4e, Instruction("LD C (HL)", 0x4e, 1, 2, &Instructions::Placeholder) },
  { 0x4f, Instruction("LD C A", 0x4f, 1, 1, &Instructions::Placeholder) },
  { 0x50, Instruction("LD D B", 0x50, 1, 1, &Instructions::Placeholder) },
  { 0x51, Instruction("LD D C", 0x51, 1, 1, &Instructions::Placeholder) },
  { 0x52, Instruction("LD D D", 0x52, 1, 1, &Instructions::Placeholder) },
  { 0x53, Instruction("LD D E", 0x5e, 1, 1, &Instructions::Placeholder) },
  { 0x54, Instruction("LD D H", 0x54, 1, 1, &Instructions::Placeholder) },
  { 0x55, Instruction("LD D L", 0x55, 1, 1, &Instructions::Placeholder) },
  { 0x56, Instruction("LD D (HL)", 0x56, 1, 2, &Instructions::Placeholder) },
  { 0x57, Instruction("LD D A", 0x57, 1, 1, &Instructions::Placeholder) },
  { 0x58, Instruction("LD E B", 0x58, 1, 1, &Instructions::Placeholder) },
  { 0x59, Instruction("LD E C", 0x59, 1, 1, &Instructions::Placeholder) },
  { 0x5a, Instruction("LD E D", 0x5a, 1, 1, &Instructions::Placeholder) },
  { 0x5b, Instruction("LD E E", 0x5b, 1, 1, &Instructions::Placeholder) },
  { 0x5c, Instruction("LD E H", 0x5c, 1, 1, &Instructions::Placeholder) },
  { 0x5d, Instruction("LD E L", 0x5d, 1, 1, &Instructions::Placeholder) },
  { 0x5e, Instruction("LD E (HL)", 0x5e, 1, 2, &Instructions::Placeholder) },
  { 0x5f, Instruction("LD E A", 0x5f, 1, 1, &Instructions::Placeholder) },
  { 0x60, Instruction("LD H B", 0x60, 1, 1, &Instructions::Placeholder) },
  { 0x61, Instruction("LD H C", 0x61, 1, 1, &Instructions::Placeholder) },
  { 0x62, Instruction("LD H D", 0x62, 1, 1, &Instructions::Placeholder) },
  { 0x63, Instruction("LD H E", 0x63, 1, 1, &Instructions::Placeholder) },
  { 0x64, Instruction("LD H H", 0x64, 1, 1, &Instructions::Placeholder) },
  { 0x65, Instruction("LD H L", 0x65, 1, 1, &Instructions::Placeholder) },
  { 0x66, Instruction("LD H (HL)", 0x66, 1, 2, &Instructions::Placeholder) },
  { 0x67, Instruction("LD H A", 0x67, 1, 1, &Instructions::Placeholder) },
  { 0x68, Instruction("LD L B", 0x68, 1, 1, &Instructions::Placeholder) },
  { 0x69, Instruction("LD L C", 0x69, 1, 1, &Instructions::Placeholder) },
  { 0x6a, Instruction("LD L D", 0x6a, 1, 1, &Instructions::Placeholder) },
  { 0x6b, Instruction("LD L E", 0x6b, 1, 1, &Instructions::Placeholder) },
  { 0x6c, Instruction("LD L H", 0x6c, 1, 1, &Instructions::Placeholder) },
  { 0x6d, Instruction("LD L L", 0x6d, 1, 1, &Instructions::Placeholder) },
  { 0x6e, Instruction("LD L (HL)", 0x6e, 2, 3, &Instructions::Placeholder) },
  { 0x6f, Instruction("LD L A", 0x6f, 1, 1, &Instructions::Placeholder) },
  { 0x70, Instruction("LD (HL) B", 0x70, 1, 2, &Instructions::Placeholder) },
  { 0x71, Instruction("LD (HL) C", 0x71, 1, 2, &Instructions::Placeholder) },
  { 0x72, Instruction("LD (HL) D", 0x72, 1, 2, &Instructions::Placeholder) },
  { 0x73, Instruction("LD (HL) E", 0x73, 1, 2, &Instructions::Placeholder) },
  { 0x74, Instruction("LD (HL) H", 0x74, 1, 2, &Instructions::Placeholder) },
  { 0x75, Instruction("LD (HL) L", 0x75, 1, 2, &Instructions::Placeholder) },
  { 0x76, Instruction("HALT", 0x76, 1, 1, &Instructions::Placeholder) },
  { 0x77, Instruction("LD (HL) A", 0x77, 2, 2, &Instructions::Placeholder) },
  { 0x78, Instruction("LD A B", 0x78, 1, 1, &Instructions::Placeholder) },
  { 0x79, Instruction("LD A C", 0x79, 1, 1, &Instructions::Placeholder) },
  { 0x7a, Instruction("LD A D", 0x7a, 1, 1, &Instructions::Placeholder) },
  { 0x7b, Instruction("LD A E", 0x7b, 1, 1, &Instructions::Placeholder) },
  { 0x7c, Instruction("LD A H", 0x7c, 1, 1, &Instructions::Placeholder) },
  { 0x7d, Instruction("LD A L", 0x7d, 1, 1, &Instructions::Placeholder) },
  { 0x7e, Instruction("LD A (HL)", 0x7e, 1, 2, &Instructions::Placeholder) },
  { 0x7f, Instruction("LD A A", 0x7f, 1, 1, &Instructions::Placeholder) },
  { 0x80, Instruction("ADD A B", 0x80, 1, 1, &Instructions::Placeholder) },
  { 0x81, Instruction("ADD A C", 0x81, 1, 1, &Instructions::Placeholder) },
  { 0x82, Instruction("ADD A D", 0x82, 1, 1, &Instructions::Placeholder) },
  { 0x83, Instruction("ADD A E", 0x83, 1, 1, &Instructions::Placeholder) },
  { 0x84, Instruction("ADD A H", 0x84, 1, 0, &Instructions::Placeholder) },
  { 0x85, Instruction("ADD A L", 0x85, 1, 1, &Instructions::Placeholder) },
  { 0x86, Instruction("ADD A (HL)", 0x86, 1, 2, &Instructions::Placeholder) },
  { 0x87, Instruction("ADC A A", 0x87, 1, 1, &Instructions::Placeholder) },
  { 0x88, Instruction("ADC A B", 0x88, 1, 1, &Instructions::Placeholder) },
  { 0x89, Instruction("ADC A C", 0x89, 1, 1, &Instructions::Placeholder) },
  { 0x8a, Instruction("ADC A D", 0x8a, 1, 1, &Instructions::Placeholder) },
  { 0x8b, Instruction("ADC A E", 0x8b, 1, 1, &Instructions::Placeholder) },
  { 0x8c, Instruction("ADC A H", 0x8c, 1, 1, &Instructions::Placeholder) },
  { 0x8d, Instruction("ADC A L", 0x8d, 1, 1, &Instructions::Placeholder) },
  { 0x8e, Instruction("ADC A (HL)", 0x8e, 1, 2, &Instructions::Placeholder) },
  { 0x8f, Instruction("ADC A A", 0x8f, 1, 1, &Instructions::Placeholder) },
  { 0x90, Instruction("SUB A B", 0x90, 1, 1, std::bind(Instructions::Sub, std::placeholders::_1, Register8::A, Register8::B)) },
  { 0x91, Instruction("SUB A C", 0x91, 1, 1, std::bind(Instructions::Sub, std::placeholders::_1, Register8::A, Register8::C)) },
  { 0x92, Instruction("SUB A D", 0x92, 1, 1, std::bind(Instructions::Sub, std::placeholders::_1, Register8::A, Register8::D)) },
  { 0x93, Instruction("SUB A E", 0x93, 1, 1, std::bind(Instructions::Sub, std::placeholders::_1, Register8::A, Register8::E)) },
  { 0x94, Instruction("SUB A H", 0x94, 1, 1, std::bind(Instructions::Sub, std::placeholders::_1, Register8::A, Register8::H)) },
  { 0x95, Instruction("SUB A L", 0x95, 1, 1, std::bind(Instructions::Sub, std::placeholders::_1, Register8::A, Register8::L)) },
  { 0x96, Instruction("SUB A (HL)", 0x96, 1, 2, &Instructions::Placeholder) },
  { 0x97, Instruction("SUB A A", 0x97, 1, 1, std::bind(Instructions::Sub, std::placeholders::_1, Register8::A, Register8::A)) },
  { 0x98, Instruction("SBC A B", 0x98, 1, 1, &Instructions::Placeholder) },
  { 0x99, Instruction("SBC A C", 0x99, 1, 1, &Instructions::Placeholder) },
  { 0x9a, Instruction("SBC A D", 0x9a, 1, 1, &Instructions::Placeholder) },
  { 0x9b, Instruction("SBC A E", 0x9b, 1, 1, &Instructions::Placeholder) },
  { 0x9c, Instruction("SBC A H", 0x9c, 1, 1, &Instructions::Placeholder) },
  { 0x9d, Instruction("SBC A L", 0x9d, 1, 1, &Instructions::Placeholder) },
  { 0x9e, Instruction("SBC A (HL)", 0x9e, 1, 2, &Instructions::Placeholder) },
  { 0x9f, Instruction("SBC A A", 0x9f, 1, 1, &Instructions::Placeholder) },
  { 0xa0, Instruction("AND B", 0xa0, 1, 1, &Instructions::Placeholder) },
  { 0xa1, Instruction("AND C", 0xa1, 1, 1, &Instructions::Placeholder) },
  { 0xa2, Instruction("AND D", 0xa2, 1, 1, &Instructions::Placeholder) },
  { 0xa3, Instruction("AND E", 0xa3, 1, 1, &Instructions::Placeholder) },
  { 0xa4, Instruction("AND H", 0xa4, 1, 1, &Instructions::Placeholder) },
  { 0xa5, Instruction("AND L", 0xa5, 1, 1, &Instructions::Placeholder) },
  { 0xa6, Instruction("AND (HL)", 0xa6, 1, 2, &Instructions::Placeholder) },
  { 0xa7, Instruction("AND A", 0xa7, 1, 1, &Instructions::Placeholder) },
  { 0xa8, Instruction("XOR B", 0xa8, 1, 1, std::bind(Instructions::LogicalOp, std::placeholders::_1, Register8::B, Register8::A, Op::Xor)) },
  { 0xa9, Instruction("XOR C", 0xa9, 1, 1, std::bind(Instructions::LogicalOp, std::placeholders::_1, Register8::C, Register8::A, Op::Xor)) },
  { 0xaa, Instruction("XOR D", 0xaa, 1, 1, std::bind(Instructions::LogicalOp, std::placeholders::_1, Register8::D, Register8::A, Op::Xor)) },
  { 0xab, Instruction("XOR E", 0xab, 1, 1, std::bind(Instructions::LogicalOp, std::placeholders::_1, Register8::E, Register8::A, Op::Xor)) },
  { 0xac, Instruction("XOR H", 0xac, 1, 1, std::bind(Instructions::LogicalOp, std::placeholders::_1, Register8::H, Register8::A, Op::Xor)) },
  { 0xad, Instruction("XOR L", 0xad, 1, 1, std::bind(Instructions::LogicalOp, std::placeholders::_1, Register8::L, Register8::A, Op::Xor)) },
  { 0xae, Instruction("XOR (HL)", 0xae, 1, 2, &Instructions::Placeholder) },
  { 0xaf, Instruction("XOR A", 0xaf, 1, 1, std::bind(Instructions::LogicalOp, std::placeholders::_1, Register8::A, Register8::A, Op::Xor)) },
  { 0xb0, Instruction("OR B", 0xb0, 1, 1, &Instructions::Placeholder) },
  { 0xb1, Instruction("OR C", 0xb1, 1, 1, &Instructions::Placeholder) },
  { 0xb2, Instruction("OR D", 0xb2, 1, 1, &Instructions::Placeholder) },
  { 0xb3, Instruction("OR E", 0xb3, 1, 1, &Instructions::Placeholder) },
  { 0xb4, Instruction("OR H", 0xb4, 1, 1, &Instructions::Placeholder) },
  { 0xb5, Instruction("OR L", 0xb5, 1, 1, &Instructions::Placeholder) },
  { 0xb6, Instruction("OR (HL)", 0xb6, 1, 2, &Instructions::Placeholder) },
  { 0xb7, Instruction("OR A", 0xb7, 1, 1, &Instructions::Placeholder) },
  { 0xb8, Instruction("CP B", 0xb8, 1, 1, &Instructions::Placeholder) },
  { 0xb9, Instruction("CP C", 0xb9, 1, 1, &Instructions::Placeholder) },
  { 0xba, Instruction("CP D", 0xba, 1, 1, &Instructions::Placeholder) },
  { 0xbb, Instruction("CP E", 0xbb, 1, 1, &Instructions::Placeholder) },
  { 0xbc, Instruction("CP H", 0xbc, 1, 1, &Instructions::Placeholder) },
  { 0xbd, Instruction("CP L", 0xbd, 1, 1, &Instructions::Placeholder) },
  { 0xbe, Instruction("CP (HL)", 0xbe, 1, 2, &Instructions::Placeholder) },
  { 0xbf, Instruction("CP A", 0xbf, 1, 1, &Instructions::Placeholder) },
  { 0xc0, Instruction("RET NZ", 0xc0, 1, 2, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xc1, Instruction("POP BC", 0xc1, 1, 3, &Instructions::Placeholder) },
  { 0xc2, Instruction("JP NZ nn", 0xc2, 3, 3, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xc3, Instruction("JP nn", 0xc3, 3, 3,  &Instructions::Jmp_immediate, Instruction::OpOrder::None) },
  { 0xc4, Instruction("CALL NZ nn", 0xc4, 2, 2, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xc5, Instruction("PUSH BC", 0xc5, 2, 2, &Instructions::Placeholder) },
  { 0xc6, Instruction("ADD A n", 0xc6, 2, 2, &Instructions::Placeholder) },
  { 0xc7, Instruction("RST 0", 0xc7, 1, 4, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xc8, Instruction("RET Z", 0xc8, 1, 2, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xc9, Instruction("RET", 0xc9, 1, 1, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xca, Instruction("JP Z nn", 0xca, 3, 3, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xcb, Instruction("extended", 0xcb, 1, 0, &Instructions::Placeholder) },
  { 0xcc, Instruction("CALL Z nn", 0xcc, 3, 3, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xcd, Instruction("CALL nn", 0xcd, 3, 6, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xce, Instruction("ADC A n", 0xce, 2, 2, &Instructions::Placeholder) },
  { 0xcf, Instruction("RST 8", 0xcf, 2, 4, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xd0, Instruction("RET NC", 0xd0, 1, 2, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xd1, Instruction("POP DE", 0xd1, 1, 3, &Instructions::Placeholder) },
  { 0xd2, Instruction("JP NC nn", 0xd2, 3, 3, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xd3, Instruction("XX - not implemented", 0xd3, 1, 0, &Instructions::Placeholder) },
  { 0xd4, Instruction("CALL NC nn", 0xd4, 3, 3, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xd5, Instruction("PUSH DE", 0xd5, 1, 4, &Instructions::Placeholder) },
  { 0xd6, Instruction("SUB A n", 0xd6, 2, 2, &Instructions::Placeholder) },
  { 0xd7, Instruction("RST 10", 0xd7, 1, 4, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xd8, Instruction("RET C", 0xd8, 1, 2, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xd9, Instruction("RETI", 0xd9, 1, 2, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xda, Instruction("JP C nn", 0xda, 2, 2, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xdb, Instruction("XX - not implemented", 0xdb, 1, 0, &Instructions::Placeholder) },
  { 0xdc, Instruction("CALL C nn", 0xdc, 3, 3, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xdd, Instruction("XX - not implemented", 0xdd, 1, 0, &Instructions::Placeholder) },
  { 0xde, Instruction("SBC A n", 0xde, 2, 2, &Instructions::Placeholder) },
  { 0xdf, Instruction("RST 18", 0xdf, 1, 4, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xe0, Instruction("LDH n A", 0xe0, 2, 3, std::bind(Instructions::WriteToAddressOffset, std::placeholders::_1, Register8::A, 0xFF00)) },
  { 0xe1, Instruction("POP HL", 0xe1, 1, 3, &Instructions::Placeholder) },
  { 0xe2, Instruction("LDH C A", 0xe2, 1, 2, &Instructions::Placeholder) },
  { 0xe3, Instruction("XX - not implemented", 0xe3, 1, 0, &Instructions::Placeholder) },
  { 0xe4, Instruction("XX - not implemented", 0xe4, 1, 0, &Instructions::Placeholder) },
  { 0xe5, Instruction("PUSH HL", 0xe5, 1, 4, &Instructions::Placeholder) },
  { 0xe6, Instruction("AND n", 0xe6, 2, 2, &Instructions::Placeholder) },
  { 0xe7, Instruction("RST 20", 0xe7, 1, 4, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xe8, Instruction("ADD SP n", 0xe8, 2, 4, &Instructions::Placeholder) },
  { 0xe9, Instruction("JP HL", 0xe9, 1, 1, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xea, Instruction("LD A nn", 0xea, 3, 4, &Instructions::Placeholder) },
  { 0xeb, Instruction("XX - not implemented", 0xeb, 1, 0, &Instructions::Placeholder) },
  { 0xec, Instruction("XX - not implemented", 0xec, 1, 0, &Instructions::Placeholder) },
  { 0xed, Instruction("XX - not implemented", 0xed, 1, 0, &Instructions::Placeholder) },
  { 0xee, Instruction("XOR n", 0xee, 2, 2, &Instructions::Placeholder) },
  { 0xef, Instruction("RST 28", 0xef, 1, 4, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xf0, Instruction("LDH n A", 0xf0, 2, 3, std::bind(&Instructions::ReadFromAddressOffset, std::placeholders::_1, Register8::A, 0xFF00)) },
  { 0xf1, Instruction("POP AF", 0xf1, 1, 3, &Instructions::Placeholder) },
  { 0xf2, Instruction("XX - not implemented", 0xf2, 1, 0, &Instructions::Placeholder) },
  { 0xf3, Instruction("DI", 0xf3, 1, 1, &Instructions::DisableInterrupts) },
  { 0xf4, Instruction("XX - not implemented", 0xf4, 1, 0, &Instructions::Placeholder) },
  { 0xf5, Instruction("PUSH AF", 0xf5, 1, 4, &Instructions::Placeholder) },
  { 0xf6, Instruction("OR n", 0xf6, 2, 2, &Instructions::Placeholder) },
  { 0xf7, Instruction("RST 30", 0xf7, 1, 4, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
  { 0xf8, Instruction("LDHL SP d", 0xf8, 2, 3, &Instructions::Placeholder) },
  { 0xf9, Instruction("LD SP HL", 0xf9, 1, 2, &Instructions::Placeholder) },
  { 0xfa, Instruction("LD A (nn)", 0xfa, 3, 4, &Instructions::Placeholder) },
  { 0xfb, Instruction("EI", 0xfb, 1, 1, &Instructions::EnableInterrupts) },
  { 0xfc, Instruction("XX - not implemented", 0xfc, 1, 0, &Instructions::Placeholder) },
  { 0xfd, Instruction("XX - not implemented", 0xfd, 1, 0, &Instructions::Placeholder) },
  { 0xfe, Instruction("CP A N", 0xfe, 2, 2, std::bind(&Instructions::CompareRegisterImmediate, std::placeholders::_1, Register8::A)) },
  { 0xff, Instruction("RST 38", 0xff, 1, 4, &Instructions::Placeholder, Instruction::OpOrder::Pre) },
};

Cpu::Cpu(const std::shared_ptr<Cart> cart, std::shared_ptr<CpuStateNotifier> notifier,
  std::shared_ptr<MemoryController> memoryController)
  :_cart(cart),
   _state(std::make_shared<cpu::State>()),
  _stateNotifier(std::move(notifier)),
  _running(true),
  _stepping(true),
  _breakpoint_hit(false),
  _history(std::make_shared<cpu::StateHistory>(50)),
  _memoryController(memoryController) {

  _stateNotifier->NotifyState(*_state, _history);
}

void Cpu::Step()
{
  if (_debug.IsPCTargetReached(_state->_pc)) {
    _stepping = true;
    _breakpoint_hit = true;
  }

  if (_debug.TestRegBreakTargets(*_state)) {
    _stepping = true;
    _breakpoint_hit = true;
  }

  unsigned char code = _cart->ReadByte(_state->_pc);
  const auto& instruction = s_lookup.at(code); 

  if (instruction.GetOpOrder() == Instruction::OpOrder::Pre) {
    AdvanceState(instruction);
  }
 
  instruction.Execute(this);
 
  if (instruction.GetOpOrder() == Instruction::OpOrder::Post) {
    AdvanceState(instruction);
  }

  _state->_history.push_back(instruction);

  _history->push_back(std::make_pair(instruction, *_state));

  // TODO: record history sent + only send new history
  if (_stepping || _breakpoint_hit)
    _stateNotifier->NotifyState(*_state, _history);
}

std::vector<Cpu::RomInstruction> Cpu::DumpRom() {
  spdlog::get("console")->info("parsing rom...");
  std::vector<RomInstruction> instructions;
  for (auto addr = 0; addr < _cart->GetLength();) {
    auto code = _cart->ReadByte(addr);
    const auto& instruction = s_lookup.at(code);
    instructions.push_back(std::make_pair(addr, instruction));

    addr += instruction.GetPCAdvance();
  }

  spdlog::get("console")->info("rom parsed");

  return instructions;
}

unsigned char Cpu::ReadByteOffset(unsigned int offset)
{
  return _cart->ReadByte(_state->_pc + offset);
}

void Cpu::SetPC(unsigned int address)
{
  _state->_pc = address;
}

unsigned int Cpu::GetPC() const
{
  return _state->_pc;
}

unsigned char Cpu::GetRegister(Register8 reg)
{
  return _state->ReadRegister(reg);
}

void Cpu::SetRegister(Register8 reg, unsigned char value)
{
  switch (reg) {
  case Register8::A:
    _state->_a = value;
    break;

  case Register8::B:
    _state->_b = value;
    break;

  case Register8::C:
    _state->_c = value;
    break;

  case Register8::D:
    _state->_d = value;
    break;

  case Register8::E:
    _state->_e = value;
    break;

  case Register8::H:
    _state->_h = value;
    break;

  case Register8::L:
    _state->_l = value;
    break;

  default:
    throw std::runtime_error("unknown register");
  }
}

unsigned short Cpu::GetRegister(Register16 reg)
{
  return _state->ReadRegister(reg);
}

void Cpu::SetRegister(Register16 reg, unsigned short value)
{
  unsigned char hi = (value & 0xFF00) >> 8;
  unsigned char lo = (value & 0xFF);

  switch (reg) {
  case Register16::BC:    
    _state->_b = hi;
    _state->_c = lo;
    break;

  case Register16::DE:
    _state->_d = hi;
    _state->_e = lo;
    break;

  case Register16::HL:
    _state->_h = hi;
    _state->_l = lo;
    break;

  case Register16::SP:
    _state->_sp = value;
    break;

  default:
    throw std::runtime_error("Unknown register");
  }
}

void Cpu::DecRegister(Register8 reg)
{
  unsigned char val = GetRegister(reg);
  short original = (short)val;
  val -= 1;

  ClearFlags();
  if (val == 0) {
    SetFlag(cpu::Flag::Zero);
  }

  SetFlag(cpu::Flag::SubOp);

  if (((original & 0xF) - 1) < 0) {
    SetFlag(cpu::Flag::HalfCarry);
  }

  SetRegister(reg, val);
}

void Cpu::DecRegister(Register16 reg)
{
  auto val = GetRegister(reg);
  val -= 1;
  SetRegister(reg, val);
}

void Cpu::IncRegister(Register8 reg)
{
  SetRegister(reg, GetRegister(reg) + 1);
}

void Cpu::IncRegister(Register16 reg)
{
  SetRegister(reg, GetRegister(reg) + 1);
}

void Cpu::ClearFlags()
{
  _state->_flag = 0;
}

void Cpu::SetFlag(cpu::Flag flag)
{
  switch (flag) {
    case cpu::Flag::Carry:
      _state->_flag |= 0x10;
      break;

    case cpu::Flag::HalfCarry:
      _state->_flag |= 0x20;
      break;

    case cpu::Flag::SubOp:
      _state->_flag |= 0x40;
      break;

    case cpu::Flag::Zero:
      _state->_flag |= 0x80;
      break;

    default:
      throw std::invalid_argument("unknown flag");
  }
}

bool Cpu::TestFlag(cpu::Flag flag)
{
  switch (flag) {
    case cpu::Flag::Carry:
      return (_state->_flag & 0x10) == 0x10;

    case cpu::Flag::HalfCarry:
      return (_state->_flag & 0x20) == 0x20;

    case cpu::Flag::SubOp:
      return (_state->_flag & 0x40) == 0x40;

    case cpu::Flag::Zero:
      return (_state->_flag & 0x80) == 0x80;

    default:
      throw std::invalid_argument("unknown flag");
  }
}

void Cpu::ClearFlag(cpu::Flag flag)
{
  switch (flag) {
    case cpu::Flag::Carry:
      _state->_flag &= ~0x10;
      break;

    case cpu::Flag::HalfCarry:
      _state->_flag &= ~0x20;
      break;

    case cpu::Flag::SubOp:
      _state->_flag &= ~0x40;
      break;

    case cpu::Flag::Zero:
      _state->_flag &= ~0x80;
      break;

    default:
      throw std::invalid_argument("unknown flag");
  }
}

bool Cpu::Running()
{
  //TODO: handle killing of cpu/rom
  return _running;
}

bool Cpu::Stepping()
{
  return _stepping;
}

void Cpu::EnableStepping(bool enable)
{
  _stepping = enable;
  if (!_stepping) {
    _stateNotifier->NotifyState(*_state, _history);
  }
}

void Cpu::SetPCDebug(unsigned short pcTarget)
{
  _debug.SetPCTarget(pcTarget);
}

void Cpu::SetRegisterDebug(Register8 reg, unsigned char targetValue)
{
  _debug.SetRegTarget(reg, targetValue);
}

void Cpu::SetRegisterDebug(Register16 reg, unsigned short targetValue)
{
  _debug.SetRegTarget(reg, targetValue);
}

void Cpu::RemovePCDebug()
{
  _debug.ClearPCTarget();
}

void Cpu::RemoveRegisterDebug(Register8 reg)
{
  _debug.RemoveRegTarget(reg);
}

void Cpu::RemoveRegisterDebug(Register16 reg)
{
  _debug.RemoveRegTarget(reg);
}

void Cpu::EnableInterrupts()
{
  _state->EnabledInterrupts();
}

void Cpu::DisableInterrupts()
{
  _state->DisableInterrupts();
}

bool Cpu::BreakpointHit() const 
{
  return _breakpoint_hit;
}

void Cpu::ResetBreakpointFlag()
{
  _breakpoint_hit = false;
}

std::shared_ptr<cpu::State> Cpu::GetState() {
  return _state;
}

void Cpu::AdvanceState(const Instruction& instruction)
{
  _state->_pc += instruction.GetPCAdvance();  

  _state->_clock._m += instruction.GetCycles();
  _state->_clock._t += instruction.GetCycles() * 4;
}
