/**
 *  @brief
 *      One character is 6x8 pixel
 *      Something is wrong
 *
 *  @file
 *      6x8_vertikal_MSB_1.h
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2015-02-02
 *  @remark
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 *  @copyright
 *      Peter Schmid, Switzerland
 *
 *      This file is part of "Velo Bling-Bling" main MCU firmware.
 *
 *		"Velo Bling-Bling" firmware is free software: you can redistribute it
 *		and/or modify it under the terms of the GNU General Public License as
 *		published by the Free Software Foundation, either version 3 of the
 *		License, or (at your option) any later version.
 *
 *		"Velo Bling-Bling" is distributed in the hope that it will be useful,
 *		but WITHOUT ANY WARRANTY; without even the implied warranty of
 *		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *		GNU General Public License for more details.
 *
 *		You should have received a copy of the GNU General Public License along
 *		with "Velo Bling-Bling". If not, see <http://www.gnu.org/licenses/>.
 */

const uint16_t font_6x8[256][6]={
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// 0x00
{0x7C, 0xA2, 0x7C, 0xA2, 0x8A, 0x00},	// 0x01
{0x7C, 0xD6, 0xF6, 0xD6, 0x7C, 0x00},	// 0x02
{0x38, 0x7C, 0x3E, 0x7C, 0x38, 0x00},	// 0x03
{0x18, 0x3C, 0x7E, 0x3C, 0x18, 0x00},	// 0x04
{0x0C, 0x6C, 0xFE, 0x6C, 0x0C, 0x00},	// 0x05
{0x18, 0x3A, 0x7E, 0x3A, 0x18, 0x00},	// 0x06
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// 0x07
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// 0x08
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// 0x09
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// 0x0A
{0x0C, 0x12, 0x52, 0x6C, 0x70, 0x00},	// 0x0B
{0x60, 0x94, 0x9E, 0x94, 0x60, 0x00},	// 0x0C
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// 0x0D
{0x06, 0x7E, 0x50, 0xAC, 0xFC, 0x00},	// 0x0E
{0x54, 0x38, 0x6C, 0x38, 0x54, 0x00},	// 0x0F
{0x00, 0xFE, 0x7C, 0x38, 0x10, 0x00},	// 0x10
{0x10, 0x38, 0x7C, 0xFE, 0x00, 0x00},	// 0x11
{0x28, 0x6C, 0xFE, 0x6C, 0x28, 0x00},	// 0x12
{0x00, 0xFA, 0x00, 0xFA, 0x00, 0x00},	// 0x13
{0x60, 0x90, 0xFE, 0x80, 0xFE, 0x00},	// 0x14
{0x44, 0xB2, 0xAA, 0x9A, 0x44, 0x00},	// 0x15
{0x06, 0x06, 0x06, 0x06, 0x00, 0x00},	// 0x16
{0x28, 0x6D, 0xFF, 0x6D, 0x28, 0x00},	// 0x17
{0x20, 0x60, 0xFE, 0x60, 0x20, 0x00},	// 0x18
{0x08, 0x0C, 0xFE, 0x0C, 0x08, 0x00},	// 0x19
{0x10, 0x10, 0x7C, 0x38, 0x10, 0x00},	// 0x1A
{0x10, 0x38, 0x7C, 0x10, 0x10, 0x00},	// 0x1B
{0x1E, 0x02, 0x02, 0x02, 0x02, 0x00},	// 0x1C
{0x10, 0x7C, 0x10, 0x7C, 0x10, 0x00},	// 0x1D
{0x0C, 0x3C, 0xFC, 0x3C, 0x0C, 0x00},	// 0x1E
{0xC0, 0xF0, 0xFC, 0xF0, 0xC0, 0x00},	// 0x1F
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// 0x20
{0x00, 0x60, 0xFA, 0x60, 0x00, 0x00},	// 0x21
{0xE0, 0xC0, 0x00, 0xE0, 0xC0, 0x00},	// 0x22
{0x24, 0x7E, 0x24, 0x7E, 0x24, 0x00},	// 0x23
{0x24, 0xD4, 0x56, 0x48, 0x00, 0x00},	// 0x24
{0xC6, 0xC8, 0x10, 0x26, 0xC6, 0x00},	// 0x25
{0x6C, 0x92, 0x6A, 0x04, 0x0A, 0x00},	// 0x26
{0x00, 0xE0, 0xC0, 0x00, 0x00, 0x00},	// 0x27
{0x00, 0x7C, 0x82, 0x00, 0x00, 0x00},	// 0x28
{0x00, 0x82, 0x7C, 0x00, 0x00, 0x00},	// 0x29
{0x10, 0x7C, 0x38, 0x7C, 0x10, 0x00},	// 0x2A
{0x10, 0x10, 0x7C, 0x10, 0x10, 0x00},	// 0x2B
{0x00, 0x07, 0x06, 0x00, 0x00, 0x00},	// 0x2C
{0x10, 0x10, 0x10, 0x10, 0x10, 0x00},	// 0x2D
{0x00, 0x06, 0x06, 0x00, 0x00, 0x00},	// 0x2E
{0x04, 0x08, 0x10, 0x20, 0x40, 0x00},	// 0x2F
{0x7C, 0x8A, 0x92, 0xA2, 0x7C, 0x00},	// 0x30
{0x00, 0x42, 0xFE, 0x02, 0x00, 0x00},	// 0x31
{0x46, 0x8A, 0x92, 0x92, 0x62, 0x00},	// 0x32
{0x44, 0x92, 0x92, 0x92, 0x6C, 0x00},	// 0x33
{0x18, 0x28, 0x48, 0xFE, 0x08, 0x00},	// 0x34
{0xF4, 0x92, 0x92, 0x92, 0x8C, 0x00},	// 0x35
{0x3C, 0x52, 0x92, 0x92, 0x0C, 0x00},	// 0x36
{0x80, 0x8E, 0x90, 0xA0, 0xC0, 0x00},	// 0x37
{0x6C, 0x92, 0x92, 0x92, 0x6C, 0x00},	// 0x38
{0x60, 0x92, 0x92, 0x94, 0x78, 0x00},	// 0x39
{0x00, 0x36, 0x36, 0x00, 0x00, 0x00},	// 0x3A
{0x00, 0x37, 0x36, 0x00, 0x00, 0x00},	// 0x3B
{0x10, 0x28, 0x44, 0x82, 0x00, 0x00},	// 0x3C
{0x24, 0x24, 0x24, 0x24, 0x24, 0x00},	// 0x3D
{0x00, 0x82, 0x44, 0x28, 0x10, 0x00},	// 0x3E
{0x40, 0x80, 0x9A, 0x90, 0x60, 0x00},	// 0x3F
{0x7C, 0x82, 0xBA, 0xAA, 0x78, 0x00},	// 0x40
{0x7E, 0x88, 0x88, 0x88, 0x7E, 0x00},	// 0x41
{0xFE, 0x92, 0x92, 0x92, 0x6C, 0x00},	// 0x42
{0x7C, 0x82, 0x82, 0x82, 0x44, 0x00},	// 0x43
{0xFE, 0x82, 0x82, 0x82, 0x7C, 0x00},	// 0x44
{0xFE, 0x92, 0x92, 0x92, 0x82, 0x00},	// 0x45
{0xFE, 0x90, 0x90, 0x90, 0x80, 0x00},	// 0x46
{0x7C, 0x82, 0x92, 0x92, 0x5E, 0x00},	// 0x47
{0xFE, 0x10, 0x10, 0x10, 0xFE, 0x00},	// 0x48
{0x00, 0x82, 0xFE, 0x82, 0x00, 0x00},	// 0x49
{0x0C, 0x02, 0x02, 0x02, 0xFC, 0x00},	// 0x4A
{0xFE, 0x10, 0x28, 0x44, 0x82, 0x00},	// 0x4B
{0xFE, 0x02, 0x02, 0x02, 0x02, 0x00},	// 0x4C
{0xFE, 0x40, 0x20, 0x40, 0xFE, 0x00},	// 0x4D
{0xFE, 0x40, 0x20, 0x10, 0xFE, 0x00},	// 0x4E
{0x7C, 0x82, 0x82, 0x82, 0x7C, 0x00},	// 0x4F
{0xFE, 0x90, 0x90, 0x90, 0x60, 0x00},	// 0x50
{0x7C, 0x82, 0x8A, 0x84, 0x7A, 0x00},	// 0x51
{0xFE, 0x90, 0x90, 0x98, 0x66, 0x00},	// 0x52
{0x64, 0x92, 0x92, 0x92, 0x4C, 0x00},	// 0x53
{0x80, 0x80, 0xFE, 0x80, 0x80, 0x00},	// 0x54
{0xFC, 0x02, 0x02, 0x02, 0xFC, 0x00},	// 0x55
{0xF8, 0x04, 0x02, 0x04, 0xF8, 0x00},	// 0x56
{0xFC, 0x02, 0x3C, 0x02, 0xFC, 0x00},	// 0x57
{0xC6, 0x28, 0x10, 0x28, 0xC6, 0x00},	// 0x58
{0xE0, 0x10, 0x0E, 0x10, 0xE0, 0x00},	// 0x59
{0x8E, 0x92, 0xA2, 0xC2, 0x00, 0x00},	// 0x5A
{0x00, 0xFE, 0x82, 0x82, 0x00, 0x00},	// 0x5B
{0x40, 0x20, 0x10, 0x08, 0x04, 0x00},	// 0x5C
{0x00, 0x82, 0x82, 0xFE, 0x00, 0x00},	// 0x5D
{0x20, 0x40, 0x80, 0x40, 0x20, 0x00},	// 0x5E
{0x01, 0x01, 0x01, 0x01, 0x01, 0x01},	// 0x5F
{0x00, 0xC0, 0xE0, 0x00, 0x00, 0x00},	// 0x60
{0x04, 0x2A, 0x2A, 0x2A, 0x1E, 0x00},	// 0x61
{0xFE, 0x22, 0x22, 0x22, 0x1C, 0x00},	// 0x62
{0x1C, 0x22, 0x22, 0x22, 0x14, 0x00},	// 0x63
{0x1C, 0x22, 0x22, 0x22, 0xFE, 0x00},	// 0x64
{0x1C, 0x2A, 0x2A, 0x2A, 0x10, 0x00},	// 0x65
{0x10, 0x7E, 0x90, 0x90, 0x00, 0x00},	// 0x66
{0x18, 0x25, 0x25, 0x25, 0x3E, 0x00},	// 0x67
{0xFE, 0x20, 0x20, 0x1E, 0x00, 0x00},	// 0x68
{0x00, 0x00, 0xBE, 0x02, 0x00, 0x00},	// 0x69
{0x02, 0x01, 0x21, 0xBE, 0x00, 0x00},	// 0x6A
{0xFE, 0x08, 0x14, 0x22, 0x00, 0x00},	// 0x6B
{0x00, 0x00, 0xFE, 0x02, 0x00, 0x00},	// 0x6C
{0x3E, 0x20, 0x18, 0x20, 0x1E, 0x00},	// 0x6D
{0x3E, 0x20, 0x20, 0x1E, 0x00, 0x00},	// 0x6E
{0x1C, 0x22, 0x22, 0x22, 0x1C, 0x00},	// 0x6F
{0x3F, 0x22, 0x22, 0x22, 0x1C, 0x00},	// 0x70
{0x1C, 0x22, 0x22, 0x22, 0x3F, 0x00},	// 0x71
{0x22, 0x1E, 0x22, 0x20, 0x10, 0x00},	// 0x72
{0x10, 0x2A, 0x2A, 0x2A, 0x04, 0x00},	// 0x73
{0x20, 0x7C, 0x22, 0x24, 0x00, 0x00},	// 0x74
{0x3C, 0x02, 0x04, 0x3E, 0x00, 0x00},	// 0x75
{0x38, 0x04, 0x02, 0x04, 0x38, 0x00},	// 0x76
{0x3C, 0x06, 0x0C, 0x06, 0x3C, 0x00},	// 0x77
{0x36, 0x08, 0x08, 0x36, 0x00, 0x00},	// 0x78
{0x39, 0x05, 0x06, 0x3C, 0x00, 0x00},	// 0x79
{0x26, 0x2A, 0x2A, 0x32, 0x00, 0x00},	// 0x7A
{0x10, 0x7C, 0x82, 0x82, 0x00, 0x00},	// 0x7B
{0x00, 0x00, 0xEE, 0x00, 0x00, 0x00},	// 0x7C
{0x00, 0x82, 0x82, 0x7C, 0x10, 0x00},	// 0x7D
{0x40, 0x80, 0x40, 0x80, 0x00, 0x00},	// 0x7E
{0x3C, 0x64, 0xC4, 0x64, 0x3C, 0x00},	// 0x7F
{0x78, 0x85, 0x87, 0x84, 0x48, 0x00},	// 0x80
{0xBC, 0x02, 0x04, 0xBE, 0x00, 0x00},	// 0x81
{0x1C, 0x2A, 0x2A, 0xAA, 0x90, 0x00},	// 0x82
{0x04, 0xAA, 0xAA, 0xAA, 0x1E, 0x00},	// 0x83
{0x04, 0xAA, 0x2A, 0xAA, 0x1E, 0x00},	// 0x84
{0x04, 0xAA, 0xAA, 0x2A, 0x1E, 0x00},	// 0x85
{0x04, 0xEA, 0xAA, 0xEA, 0x1E, 0x00},	// 0x86
{0x38, 0x45, 0x47, 0x44, 0x28, 0x00},	// 0x87
{0x1C, 0xAA, 0xAA, 0xAA, 0x10, 0x00},	// 0x88
{0x1C, 0xAA, 0x2A, 0xAA, 0x10, 0x00},	// 0x89
{0x1C, 0xAA, 0xAA, 0x2A, 0x10, 0x00},	// 0x8A
{0x00, 0x80, 0x3E, 0x82, 0x00, 0x00},	// 0x8B
{0x00, 0x80, 0xBE, 0x82, 0x00, 0x00},	// 0x8C
{0x00, 0x80, 0x3E, 0x02, 0x00, 0x00},	// 0x8D
{0x0E, 0x94, 0x24, 0x94, 0x0E, 0x00},	// 0x8E
{0x1E, 0xF4, 0xA4, 0xF4, 0x1E, 0x00},	// 0x8F
{0x3E, 0x2A, 0x2A, 0xAA, 0xA2, 0x00},	// 0x90
{0x2C, 0x2A, 0x3E, 0x2A, 0x1A, 0x00},	// 0x91
{0x7E, 0x90, 0xFE, 0x92, 0x92, 0x00},	// 0x92
{0x1C, 0xA2, 0xA2, 0x9C, 0x00, 0x00},	// 0x93
{0x1C, 0xA2, 0x22, 0x9C, 0x00, 0x00},	// 0x94
{0x9C, 0xA2, 0x22, 0x1C, 0x00, 0x00},	// 0x95
{0x3C, 0x82, 0x84, 0xBE, 0x00, 0x00},	// 0x96
{0xBC, 0x82, 0x04, 0x3E, 0x00, 0x00},	// 0x97
{0x39, 0x85, 0x06, 0xBC, 0x00, 0x00},	// 0x98
{0xBC, 0x42, 0x42, 0xBC, 0x00, 0x00},	// 0x99
{0x3C, 0x82, 0x02, 0xBC, 0x00, 0x00},	// 0x9A
{0x0E, 0x16, 0x1A, 0x1C, 0x20, 0x01},	// 0x9B
{0x12, 0x7C, 0x92, 0x92, 0x46, 0x00},	// 0x9C
{0x7E, 0x86, 0xBA, 0xC2, 0xFC, 0x00},	// 0x9D
{0x44, 0x28, 0x10, 0x28, 0x44, 0x00},	// 0x9E
{0x02, 0x11, 0x7E, 0x90, 0x40, 0x00},	// 0x9F
{0x04, 0x2A, 0xAA, 0xAA, 0x1E, 0x00},	// 0xA0
{0x00, 0x00, 0xBE, 0x82, 0x00, 0x00},	// 0xA1
{0x1C, 0x22, 0xA2, 0x9C, 0x00, 0x00},	// 0xA2
{0x3C, 0x02, 0x84, 0xBE, 0x00, 0x00},	// 0xA3
{0x5E, 0x90, 0x50, 0x8E, 0x00, 0x00},	// 0xA4
{0x5E, 0x88, 0x44, 0x9E, 0x00, 0x00},	// 0xA5
{0x10, 0xAA, 0xAA, 0xAA, 0x7A, 0x00},	// 0xA6
{0x72, 0x8A, 0x8A, 0x72, 0x00, 0x00},	// 0xA7
{0x0C, 0x12, 0xB2, 0x02, 0x04, 0x00},	// 0xA8
{0x82, 0xBA, 0xD2, 0xAA, 0x7C, 0x7C},	// 0xA9
{0x20, 0x20, 0x20, 0x20, 0x38, 0x20},	// 0xAA
{0xE8, 0x10, 0x32, 0x56, 0x0A, 0x00},	// 0xAB
{0xE8, 0x10, 0x2C, 0x54, 0x1E, 0x00},	// 0xAC
{0x00, 0x0C, 0xBE, 0x0C, 0x00, 0x00},	// 0xAD
{0x10, 0x28, 0x00, 0x10, 0x28, 0x00},	// 0xAE
{0x28, 0x10, 0x00, 0x28, 0x10, 0x00},	// 0xAF
{0x88, 0x22, 0x88, 0x22, 0x88, 0x22},	// 0xB0
{0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55},	// 0xB1
{0x77, 0xDD, 0x77, 0xDD, 0x77, 0xDD},	// 0xB2
{0x00, 0x00, 0xFF, 0x00, 0x00, 0x00},	// 0xB3
{0x10, 0x10, 0xFF, 0x00, 0x00, 0x10},	// 0xB4
{0x0E, 0x14, 0xA4, 0x94, 0x0E, 0x00},	// 0xB5
{0x0E, 0x94, 0xA4, 0x94, 0x0E, 0x00},	// 0xB6
{0x0E, 0x94, 0xA4, 0x14, 0x0E, 0x00},	// 0xB7
{0x82, 0xBA, 0xAA, 0x82, 0x7C, 0x7C},	// 0xB8
{0xDF, 0x00, 0xFF, 0x00, 0x00, 0x50},	// 0xB9
{0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00},	// 0xBA
{0x5F, 0x40, 0x7F, 0x00, 0x00, 0x50},	// 0xBB
{0xD0, 0x10, 0xF0, 0x00, 0x00, 0x50},	// 0xBC
{0x18, 0x24, 0x66, 0x24, 0x00, 0x00},	// 0xBD
{0x94, 0x54, 0x3E, 0x54, 0x94, 0x00},	// 0xBE
{0x10, 0x10, 0x1F, 0x00, 0x00, 0x10},	// 0xBF
{0x00, 0x00, 0xF0, 0x10, 0x10, 0x00},	// 0xC0
{0x10, 0x10, 0xF0, 0x10, 0x10, 0x10},	// 0xC1
{0x10, 0x10, 0x1F, 0x10, 0x10, 0x10},	// 0xC2
{0x00, 0x00, 0xFF, 0x10, 0x10, 0x00},	// 0xC3
{0x10, 0x10, 0x10, 0x10, 0x10, 0x10},	// 0xC4
{0x10, 0x10, 0xFF, 0x10, 0x10, 0x10},	// 0xC5
{0x04, 0x6A, 0xAA, 0x6A, 0x9E, 0x00},	// 0xC6
{0x0E, 0x54, 0xA4, 0x54, 0x8E, 0x00},	// 0xC7
{0xF0, 0x10, 0xD0, 0x50, 0x50, 0x00},	// 0xC8
{0x7F, 0x40, 0x5F, 0x50, 0x50, 0x00},	// 0xC9
{0xD0, 0x10, 0xD0, 0x50, 0x50, 0x50},	// 0xCA
{0x5F, 0x40, 0x5F, 0x50, 0x50, 0x50},	// 0xCB
{0xFF, 0x00, 0xDF, 0x50, 0x50, 0x00},	// 0xCC
{0x50, 0x50, 0x50, 0x50, 0x50, 0x50},	// 0xCD
{0xDF, 0x00, 0xDF, 0x50, 0x50, 0x50},	// 0xCE
{0xBA, 0x44, 0x44, 0x44, 0xBA, 0x00},	// 0xCF
{0x44, 0xAA, 0x9A, 0x0C, 0x00, 0x00},	// 0xD0
{0x10, 0xFE, 0x92, 0x82, 0x7C, 0x00},	// 0xD1
{0x3E, 0xAA, 0xAA, 0xAA, 0x22, 0x00},	// 0xD2
{0x3E, 0xAA, 0x2A, 0xAA, 0x22, 0x00},	// 0xD3
{0x3E, 0xAA, 0xAA, 0x2A, 0x22, 0x00},	// 0xD4
{0x00, 0x00, 0xE0, 0x00, 0x00, 0x00},	// 0xD5
{0x00, 0x22, 0xBE, 0xA2, 0x00, 0x00},	// 0xD6
{0x00, 0xA2, 0xBE, 0xA2, 0x00, 0x00},	// 0xD7
{0x00, 0xA2, 0x3E, 0xA2, 0x00, 0x00},	// 0xD8
{0x10, 0x10, 0xF0, 0x00, 0x00, 0x10},	// 0xD9
{0x00, 0x00, 0x1F, 0x10, 0x10, 0x00},	// 0xDA
{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},	// 0xDB
{0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F},	// 0xDC
{0x00, 0x00, 0xEE, 0x00, 0x00, 0x00},	// 0xDD
{0x00, 0xA2, 0xBE, 0x22, 0x00, 0x00},	// 0xDE
{0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0},	// 0xDF
{0x3C, 0x42, 0xC2, 0xBC, 0x00, 0x00},	// 0xE0
{0x7F, 0x52, 0x52, 0x2C, 0x00, 0x00},	// 0xE1
{0x3C, 0xC2, 0xC2, 0xBC, 0x00, 0x00},	// 0xE2
{0xBC, 0xC2, 0x42, 0x3C, 0x00, 0x00},	// 0xE3
{0x4C, 0x92, 0x52, 0x8C, 0x00, 0x00},	// 0xE4
{0x5C, 0xA2, 0x62, 0x9C, 0x00, 0x00},	// 0xE5
{0x3F, 0x04, 0x04, 0x38, 0x00, 0x00},	// 0xE6
{0x7F, 0x55, 0x14, 0x08, 0x00, 0x00},	// 0xE7
{0xFF, 0xA5, 0x24, 0x18, 0x00, 0x00},	// 0xE8
{0x3C, 0x02, 0x82, 0xBC, 0x00, 0x00},	// 0xE9
{0x3C, 0x82, 0x82, 0xBC, 0x00, 0x00},	// 0xEA
{0xBC, 0x82, 0x02, 0x3C, 0x00, 0x00},	// 0xEB
{0x39, 0x05, 0x86, 0xBC, 0x00, 0x00},	// 0xEC
{0x20, 0x10, 0x8E, 0x90, 0x20, 0x00},	// 0xED
{0x00, 0x40, 0x40, 0x40, 0x00, 0x00},	// 0xEE
{0x00, 0xE0, 0xC0, 0x00, 0x00, 0x00},	// 0xEF
{0x00, 0x10, 0x10, 0x10, 0x00, 0x00},	// 0xF0
{0x00, 0x24, 0x74, 0x24, 0x00, 0x00},	// 0xF1
{0x24, 0x24, 0x24, 0x24, 0x24, 0x00},	// 0xF2
{0xE8, 0x50, 0x2C, 0x54, 0x1E, 0xA0},	// 0xF3
{0x60, 0x90, 0xFE, 0x80, 0xFE, 0x00},	// 0xF4
{0x44, 0xB2, 0xAA, 0x9A, 0x44, 0x00},	// 0xF5
{0x10, 0x10, 0x54, 0x10, 0x10, 0x00},	// 0xF6
{0x00, 0x10, 0x18, 0x18, 0x00, 0x00},	// 0xF7
{0x60, 0x90, 0x90, 0x60, 0x00, 0x00},	// 0xF8
{0x00, 0x10, 0x00, 0x10, 0x00, 0x00},	// 0xF9
{0x00, 0x10, 0x00, 0x00, 0x00, 0x00},	// 0xFA
{0x40, 0xF0, 0x00, 0x00, 0x00, 0x00},	// 0xFB
{0x90, 0xF0, 0xA0, 0x00, 0x00, 0x00},	// 0xFC
{0x90, 0xB0, 0x50, 0x00, 0x00, 0x00},	// 0xFD
{0x3C, 0x3C, 0x3C, 0x3C, 0x00, 0x00},	// 0xFE
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} 	// 0xFF
};
