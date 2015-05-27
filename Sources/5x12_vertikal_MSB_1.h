/**
 *  @brief
 *      One character is 5x12 pixel  
 *
 *  @file
 *      5x12_vertikal_MSB.h
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-01-03
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 */

const uint16_t font_5x12[256][5]={
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x00
{0x07F8, 0x0924, 0x0814, 0x0924, 0x07F8},	// 0x01
{0x07F8, 0x0EDC, 0x0FEC, 0x0EDC, 0x07F8},	// 0x02
{0x03E0, 0x07F8, 0x01FE, 0x07F8, 0x03E0},	// 0x03
{0x00E0, 0x03F8, 0x0FFE, 0x03F8, 0x00E0},	// 0x04
{0x0060, 0x0774, 0x0FFC, 0x0774, 0x0060},	// 0x05
{0x00E0, 0x03F4, 0x0FFC, 0x03F4, 0x00E0},	// 0x06
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x07
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x08
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x09
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x0A
{0x0038, 0x0044, 0x02C4, 0x0338, 0x0380},	// 0x0B
{0x0388, 0x047C, 0x0448, 0x0380, 0x0000},	// 0x0C
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x0D
{0x000C, 0x07FC, 0x0A30, 0x0FF0, 0x0000},	// 0x0E
{0x00A8, 0x0050, 0x00D8, 0x0050, 0x00A8},	// 0x0F
{0x03F8, 0x01F0, 0x00E0, 0x0040, 0x0000},	// 0x10
{0x0040, 0x00E0, 0x01F0, 0x03F8, 0x0000},	// 0x11
{0x0110, 0x0208, 0x07FC, 0x0208, 0x0110},	// 0x12
{0x0000, 0x03EC, 0x0000, 0x03EC, 0x0000},	// 0x13
{0x03C0, 0x07FC, 0x0400, 0x07FC, 0x0000},	// 0x14
{0x0348, 0x04A4, 0x04A4, 0x0258, 0x0000},	// 0x15
{0x000C, 0x000C, 0x000C, 0x000C, 0x0000},	// 0x16
{0x0112, 0x020A, 0x07FE, 0x020A, 0x0112},	// 0x17
{0x0100, 0x0200, 0x07FC, 0x0200, 0x0100},	// 0x18
{0x0010, 0x0008, 0x03FC, 0x0008, 0x0010},	// 0x19
{0x0040, 0x0150, 0x00E0, 0x0040, 0x0000},	// 0x1A
{0x0040, 0x00E0, 0x0150, 0x0040, 0x0000},	// 0x1B
{0x0070, 0x0010, 0x0010, 0x0010, 0x0000},	// 0x1C
{0x0040, 0x01F0, 0x0040, 0x01F0, 0x0040},	// 0x1D
{0x0010, 0x0070, 0x01F0, 0x0070, 0x0010},	// 0x1E
{0x0100, 0x01C0, 0x01F0, 0x01C0, 0x0100},	// 0x1F
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x20 " "
{0x0000, 0x0000, 0x07EC, 0x0000, 0x0000},	// 0x21
{0x0000, 0x0F00, 0x0000, 0x0F00, 0x0000},	// 0x22
{0x0120, 0x07F8, 0x0120, 0x07F8, 0x0120},	// 0x23
{0x0188, 0x0644, 0x0226, 0x0118, 0x0000},	// 0x24
{0x060C, 0x0670, 0x018C, 0x060C, 0x0000},	// 0x25
{0x03B8, 0x0444, 0x03A4, 0x0018, 0x0024},	// 0x26
{0x0000, 0x0000, 0x0D00, 0x0E00, 0x0000},	// 0x27
{0x0000, 0x03F8, 0x0404, 0x0000, 0x0000},	// 0x28
{0x0000, 0x0404, 0x03F8, 0x0000, 0x0000},	// 0x29
{0x0120, 0x00C0, 0x03F0, 0x00C0, 0x0120},	// 0x2A
{0x0040, 0x0040, 0x01F0, 0x0040, 0x0040},	// 0x2B
{0x0000, 0x000D, 0x000E, 0x0000, 0x0000},	// 0x2C
{0x0040, 0x0040, 0x0040, 0x0040, 0x0000},	// 0x2D
{0x0000, 0x000C, 0x000C, 0x0000, 0x0000},	// 0x2E
{0x000C, 0x0070, 0x0180, 0x0600, 0x0000},	// 0x2F
{0x03FC, 0x0404, 0x0404, 0x07F8, 0x0000},	// 0x30 "0"
{0x0104, 0x0204, 0x07FC, 0x0004, 0x0000},	// 0x31 "1"
{0x031C, 0x0424, 0x0444, 0x0384, 0x0000},	// 0x32 "2"
{0x0208, 0x0444, 0x0444, 0x03B8, 0x0000},	// 0x33 "3"
{0x0060, 0x01A0, 0x0220, 0x07FC, 0x0000},	// 0x34 "4"
{0x07C8, 0x0444, 0x0444, 0x0438, 0x0000},	// 0x35 "5"
{0x01F8, 0x0284, 0x0484, 0x0478, 0x0000},	// 0x36 "6"
{0x0400, 0x041C, 0x0460, 0x0780, 0x0000},	// 0x37 "7"
{0x03B8, 0x0444, 0x0444, 0x03B8, 0x0000},	// 0x38 "8"
{0x03C4, 0x0424, 0x0428, 0x03F0, 0x0000},	// 0x39 "9"
{0x0000, 0x00CC, 0x00CC, 0x0000, 0x0000},	// 0x3A
{0x0000, 0x00CD, 0x00CE, 0x0000, 0x0000},	// 0x3B
{0x0060, 0x0090, 0x0108, 0x0204, 0x0000},	// 0x3C
{0x0050, 0x0050, 0x0050, 0x0050, 0x0000},	// 0x3D
{0x0204, 0x0108, 0x0090, 0x0060, 0x0000},	// 0x3E
{0x0300, 0x0400, 0x046C, 0x0380, 0x0000},	// 0x3F
{0x03F8, 0x0404, 0x0464, 0x03E4, 0x0000},	// 0x40 "@"
{0x03FC, 0x0440, 0x0440, 0x03FC, 0x0000},	// 0x41 "A"
{0x07FC, 0x0444, 0x0444, 0x03B8, 0x0000},	// 0x42
{0x03F8, 0x0404, 0x0404, 0x0308, 0x0000},	// 0x43
{0x07FC, 0x0404, 0x0404, 0x03F8, 0x0000},	// 0x44
{0x07FC, 0x0444, 0x0444, 0x0444, 0x0000},	// 0x45
{0x07FC, 0x0440, 0x0440, 0x0440, 0x0000},	// 0x46
{0x03F8, 0x0404, 0x0424, 0x0338, 0x0000},	// 0x47
{0x07FC, 0x0040, 0x0040, 0x07FC, 0x0000},	// 0x48
{0x0000, 0x0404, 0x07FC, 0x0404, 0x0000},	// 0x49
{0x0018, 0x0404, 0x07F8, 0x0400, 0x0000},	// 0x4A
{0x07FC, 0x0040, 0x01B0, 0x060C, 0x0000},	// 0x4B
{0x07FC, 0x0004, 0x0004, 0x0004, 0x0000},	// 0x4C
{0x07FC, 0x0180, 0x0180, 0x07FC, 0x0000},	// 0x4D
{0x07FC, 0x0180, 0x0060, 0x07FC, 0x0000},	// 0x4E
{0x03F8, 0x0404, 0x0404, 0x03F8, 0x0000},	// 0x4F
{0x07FC, 0x0440, 0x0440, 0x0380, 0x0000},	// 0x50
{0x03F8, 0x0404, 0x0406, 0x03F9, 0x0000},	// 0x51
{0x07FC, 0x0460, 0x0450, 0x038C, 0x0000},	// 0x52
{0x0398, 0x0444, 0x0444, 0x0338, 0x0000},	// 0x53
{0x0400, 0x0400, 0x07FC, 0x0400, 0x0400},	// 0x54
{0x07F8, 0x0004, 0x0004, 0x07F8, 0x0000},	// 0x55
{0x07C0, 0x0030, 0x000C, 0x07F0, 0x0000},	// 0x56
{0x07FC, 0x0010, 0x0010, 0x07FC, 0x0000},	// 0x57
{0x071C, 0x00E0, 0x00E0, 0x071C, 0x0000},	// 0x58
{0x0700, 0x00C0, 0x003C, 0x00C0, 0x0700},	// 0x59
{0x041C, 0x0464, 0x0584, 0x0604, 0x0000},	// 0x5A
{0x0000, 0x07FC, 0x0404, 0x0000, 0x0000},	// 0x5B
{0x0600, 0x0180, 0x0070, 0x000C, 0x0000},	// 0x5C
{0x0000, 0x0404, 0x07FC, 0x0000, 0x0000},	// 0x5D
{0x0000, 0x0200, 0x0400, 0x0200, 0x0000},	// 0x5E
{0x0001, 0x0001, 0x0001, 0x0001, 0x0001},	// 0x5F
{0x0000, 0x0E00, 0x0D00, 0x0000, 0x0000},	// 0x60
{0x0018, 0x00A4, 0x00A4, 0x007C, 0x0000},	// 0x61 "a"
{0x07FC, 0x0084, 0x0084, 0x0078, 0x0000},	// 0x62
{0x0078, 0x0084, 0x0084, 0x0084, 0x0000},	// 0x63
{0x0078, 0x0084, 0x0084, 0x07FC, 0x0000},	// 0x64
{0x0078, 0x0094, 0x0094, 0x0074, 0x0000},	// 0x65
{0x0080, 0x03FC, 0x0480, 0x0000, 0x0000},	// 0x66
{0x0078, 0x0085, 0x0085, 0x00FE, 0x0000},	// 0x67
{0x07FC, 0x0080, 0x0080, 0x007C, 0x0000},	// 0x68
{0x0000, 0x0004, 0x02FC, 0x0004, 0x0000},	// 0x69
{0x0002, 0x0001, 0x02FE, 0x0000, 0x0000},	// 0x6A
{0x07FC, 0x0030, 0x0048, 0x0084, 0x0000},	// 0x6B
{0x0000, 0x0404, 0x07FC, 0x0004, 0x0000},	// 0x6C
{0x00FC, 0x0040, 0x0040, 0x00FC, 0x0000},	// 0x6D
{0x00FC, 0x0040, 0x0080, 0x007C, 0x0000},	// 0x6E
{0x0078, 0x0084, 0x0084, 0x0078, 0x0000},	// 0x6F
{0x00FF, 0x0084, 0x0084, 0x0078, 0x0000},	// 0x70
{0x0078, 0x0084, 0x0084, 0x00FF, 0x0000},	// 0x71
{0x0080, 0x007C, 0x0080, 0x00C0, 0x0000},	// 0x72
{0x0048, 0x00A4, 0x0094, 0x0048, 0x0000},	// 0x73
{0x0080, 0x03FC, 0x0084, 0x0000, 0x0000},	// 0x74
{0x00F8, 0x0004, 0x0004, 0x00FC, 0x0000},	// 0x75
{0x00C0, 0x0030, 0x000C, 0x00F0, 0x0000},	// 0x76
{0x00FC, 0x0008, 0x0008, 0x00FC, 0x0000},	// 0x77
{0x00CC, 0x0030, 0x0030, 0x00CC, 0x0000},	// 0x78
{0x00F9, 0x0005, 0x0005, 0x00FE, 0x0000},	// 0x79
{0x008C, 0x0094, 0x00A4, 0x00C4, 0x0000},	// 0x7A
{0x0040, 0x03B8, 0x0404, 0x0000, 0x0000},	// 0x7B
{0x0000, 0x0000, 0x0F7C, 0x0000, 0x0000},	// 0x7C
{0x0000, 0x0404, 0x03B8, 0x0040, 0x0000},	// 0x7D
{0x0200, 0x0400, 0x0200, 0x0400, 0x0000},	// 0x7E
{0x007C, 0x0184, 0x0604, 0x0184, 0x007C},	// 0x7F
{0x03F8, 0x0405, 0x0406, 0x0308, 0x0000},	// 0x80
{0x00F8, 0x0604, 0x0004, 0x06FC, 0x0000},	// 0x81
{0x0078, 0x0294, 0x0494, 0x0474, 0x0000},	// 0x82
{0x0248, 0x0494, 0x0494, 0x027C, 0x0000},	// 0x83
{0x0048, 0x0694, 0x0094, 0x067C, 0x0000},	// 0x84
{0x0448, 0x0494, 0x0294, 0x007C, 0x0000},	// 0x85
{0x0048, 0x0294, 0x0594, 0x027C, 0x0000},	// 0x86
{0x0079, 0x0085, 0x0086, 0x0084, 0x0000},	// 0x87
{0x0278, 0x0494, 0x0494, 0x0274, 0x0000},	// 0x88
{0x0078, 0x0694, 0x0094, 0x0674, 0x0000},	// 0x89
{0x0478, 0x0494, 0x0294, 0x0074, 0x0000},	// 0x8A
{0x0000, 0x0684, 0x00FC, 0x0604, 0x0000},	// 0x8B
{0x0200, 0x0484, 0x04FC, 0x0204, 0x0000},	// 0x8C
{0x0000, 0x0484, 0x04FC, 0x0204, 0x0000},	// 0x8D
{0x01FC, 0x0A20, 0x0220, 0x09FC, 0x0000},	// 0x8E
{0x00FC, 0x0520, 0x0B20, 0x04FC, 0x0000},	// 0x8F
{0x01FC, 0x0524, 0x0924, 0x0924, 0x0000},	// 0x90
{0x0008, 0x0094, 0x00F8, 0x0094, 0x0060},	// 0x91
{0x01FC, 0x0320, 0x03FC, 0x0224, 0x0000},	// 0x92
{0x0278, 0x0484, 0x0484, 0x0278, 0x0000},	// 0x93
{0x0078, 0x0684, 0x0084, 0x0678, 0x0000},	// 0x94
{0x0078, 0x0484, 0x0484, 0x0278, 0x0000},	// 0x95
{0x02F8, 0x0404, 0x0404, 0x02FC, 0x0000},	// 0x96
{0x04F8, 0x0404, 0x0204, 0x00FC, 0x0000},	// 0x97
{0x00F9, 0x0605, 0x0005, 0x06FE, 0x0000},	// 0x98
{0x01F8, 0x0A04, 0x0204, 0x09F8, 0x0000},	// 0x99
{0x03F8, 0x0804, 0x0004, 0x0BFC, 0x0000},	// 0x9A
{0x007C, 0x0098, 0x00E8, 0x01F0, 0x0000},	// 0x9B
{0x004C, 0x03FC, 0x0444, 0x020C, 0x0000},	// 0x9C
{0x07FC, 0x087C, 0x0B84, 0x0FF8, 0x0000},	// 0x9D
{0x0110, 0x00A0, 0x0040, 0x00A0, 0x0110},	// 0x9E
{0x0002, 0x0041, 0x07FE, 0x0840, 0x0000},	// 0x9F
{0x0048, 0x0294, 0x0494, 0x047C, 0x0000},	// 0xA0
{0x0000, 0x0284, 0x04FC, 0x0404, 0x0000},	// 0xA1
{0x0078, 0x0284, 0x0484, 0x0478, 0x0000},	// 0xA2
{0x00F8, 0x0204, 0x0404, 0x04FC, 0x0000},	// 0xA3
{0x02FC, 0x0440, 0x0280, 0x047C, 0x0000},	// 0xA4
{0x05FC, 0x08C0, 0x0460, 0x09FC, 0x0000},	// 0xA5
{0x0090, 0x0550, 0x0550, 0x03D0, 0x0000},	// 0xA6
{0x0390, 0x0450, 0x0450, 0x0390, 0x0000},	// 0xA7
{0x0038, 0x06C4, 0x0004, 0x0008, 0x0000},	// 0xA8
{0x01F8, 0x02F4, 0x02A4, 0x0254, 0x01F8},	// 0xA9
{0x0020, 0x0020, 0x0020, 0x0038, 0x0000},	// 0xAA
{0x0018, 0x0760, 0x00AC, 0x0334, 0x0000},	// 0xAB
{0x0018, 0x0760, 0x0098, 0x033C, 0x0000},	// 0xAC
{0x0000, 0x0000, 0x02FC, 0x0000, 0x0000},	// 0xAD
{0x0060, 0x0198, 0x0060, 0x0198, 0x0000},	// 0xAE
{0x0198, 0x0060, 0x0198, 0x0060, 0x0000},	// 0xAF
{0x0208, 0x0041, 0x0208, 0x0041, 0x0208},	// 0xB0
{0x0111, 0x0444, 0x0111, 0x0444, 0x0111},	// 0xB1
{0x0555, 0x0AAA, 0x0555, 0x0AAA, 0x0555},	// 0xB2
{0x0000, 0x0000, 0x0FFF, 0x0000, 0x0000},	// 0xB3
{0x0040, 0x0040, 0x0FFF, 0x0000, 0x0000},	// 0xB4
{0x00FC, 0x0520, 0x0920, 0x08FC, 0x0000},	// 0xB5
{0x00FC, 0x0520, 0x0920, 0x04FC, 0x0000},	// 0xB6
{0x08FC, 0x0920, 0x0520, 0x00FC, 0x0000},	// 0xB7
{0x01F8, 0x0264, 0x0294, 0x0204, 0x01F8},	// 0xB8
{0x00A0, 0x0FBF, 0x0000, 0x0FFF, 0x0000},	// 0xB9
{0x0000, 0x0FFF, 0x0000, 0x0FFF, 0x0000},	// 0xBA
{0x00A0, 0x00BF, 0x0080, 0x00FF, 0x0000},	// 0xBB
{0x00A0, 0x0FA0, 0x0020, 0x0FE0, 0x0000},	// 0xBC
{0x0070, 0x0088, 0x018C, 0x0088, 0x0050},	// 0xBD
{0x04A0, 0x03A0, 0x00FC, 0x03A0, 0x04A0},	// 0xBE
{0x0040, 0x0040, 0x007F, 0x0000, 0x0000},	// 0xBF
{0x0000, 0x0000, 0x0FC0, 0x0040, 0x0040},	// 0xC0
{0x0040, 0x0040, 0x0FC0, 0x0040, 0x0040},	// 0xC1
{0x0040, 0x0040, 0x007F, 0x0040, 0x0040},	// 0xC2
{0x0000, 0x0000, 0x0FFF, 0x0040, 0x0040},	// 0xC3
{0x0040, 0x0040, 0x0040, 0x0040, 0x0040},	// 0xC4
{0x0040, 0x0040, 0x0FFF, 0x0040, 0x0040},	// 0xC5
{0x0248, 0x0494, 0x0294, 0x047C, 0x0000},	// 0xC6
{0x04FC, 0x0920, 0x0520, 0x08FC, 0x0000},	// 0xC7
{0x0000, 0x0FE0, 0x0020, 0x0FA0, 0x00A0},	// 0xC8
{0x0000, 0x00FF, 0x0080, 0x00BF, 0x00A0},	// 0xC9
{0x00A0, 0x0FA0, 0x0020, 0x0FA0, 0x00A0},	// 0xCA
{0x00A0, 0x00BF, 0x0080, 0x00BF, 0x00A0},	// 0xCB
{0x0000, 0x0FFF, 0x0000, 0x0FBF, 0x00A0},	// 0xCC
{0x00A0, 0x00A0, 0x00A0, 0x00A0, 0x00A0},	// 0xCD
{0x00A0, 0x0FBF, 0x0000, 0x0FBF, 0x00A0},	// 0xCE
{0x05F4, 0x0208, 0x0208, 0x05F4, 0x0000},	// 0xCF
{0x0018, 0x01A4, 0x0264, 0x0238, 0x0000},	// 0xD0
{0x0040, 0x07FC, 0x0444, 0x03F8, 0x0000},	// 0xD1
{0x01FC, 0x0524, 0x0924, 0x0524, 0x0000},	// 0xD2
{0x01FC, 0x0524, 0x0124, 0x0524, 0x0000},	// 0xD3
{0x01FC, 0x0924, 0x0924, 0x0524, 0x0000},	// 0xD4
{0x0000, 0x0000, 0x0780, 0x0000, 0x0000},	// 0xD5
{0x0000, 0x0504, 0x09FC, 0x0904, 0x0000},	// 0xD6
{0x0000, 0x0504, 0x09FC, 0x0504, 0x0000},	// 0xD7
{0x0000, 0x0504, 0x01FC, 0x0504, 0x0000},	// 0xD8
{0x0040, 0x0040, 0x0FC0, 0x0000, 0x0000},	// 0xD9
{0x0000, 0x0000, 0x007F, 0x0040, 0x0040},	// 0xDA
{0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF},	// 0xDB
{0x003F, 0x003F, 0x003F, 0x003F, 0x003F},	// 0xDC
{0x0000, 0x0000, 0x0F7C, 0x0000, 0x0000},	// 0xDD
{0x0000, 0x0904, 0x09FC, 0x0504, 0x0000},	// 0xDE
{0x0FC0, 0x0FC0, 0x0FC0, 0x0FC0, 0x0FC0},	// 0xDF
{0x00F8, 0x0504, 0x0904, 0x08F8, 0x0000},	// 0xE0
{0x03FF, 0x0444, 0x04C4, 0x0338, 0x0000},	// 0xE1
{0x00F8, 0x0504, 0x0904, 0x04F8, 0x0000},	// 0xE2
{0x00F8, 0x0904, 0x0904, 0x04F8, 0x0000},	// 0xE3
{0x0278, 0x0484, 0x0284, 0x0478, 0x0000},	// 0xE4
{0x04F8, 0x0904, 0x0504, 0x08F8, 0x0000},	// 0xE5
{0x00FF, 0x0004, 0x0004, 0x00F8, 0x0000},	// 0xE6
{0x01FC, 0x0154, 0x0050, 0x0020, 0x0000},	// 0xE7
{0x07FC, 0x0514, 0x0110, 0x00E0, 0x0000},	// 0xE8
{0x01F8, 0x0404, 0x0804, 0x09F8, 0x0000},	// 0xE9
{0x01F8, 0x0404, 0x0804, 0x05F8, 0x0000},	// 0xEA
{0x01F8, 0x0804, 0x0804, 0x05F8, 0x0000},	// 0xEB
{0x00F9, 0x0205, 0x0405, 0x04FE, 0x0000},	// 0xEC
{0x0180, 0x0460, 0x081C, 0x0860, 0x0180},	// 0xED
{0x0000, 0x0200, 0x0200, 0x0200, 0x0000},	// 0xEE
{0x0000, 0x0D00, 0x0E00, 0x0000, 0x0000},	// 0xEF
{0x0040, 0x0040, 0x0040, 0x0040, 0x0000},	// 0xF0
{0x0044, 0x0044, 0x01F4, 0x0044, 0x0044},	// 0xF1
{0x0050, 0x0050, 0x0050, 0x0050, 0x0000},	// 0xF2
{0x0918, 0x0D60, 0x0A98, 0x033C, 0x0000},	// 0xF3
{0x03C0, 0x07FC, 0x0400, 0x07FC, 0x0000},	// 0xF4
{0x0348, 0x04A4, 0x04A4, 0x0258, 0x0000},	// 0xF5
{0x0040, 0x0040, 0x0150, 0x0040, 0x0040},	// 0xF6
{0x0040, 0x0020, 0x0060, 0x0060, 0x0000},	// 0xF7
{0x0600, 0x0900, 0x0900, 0x0600, 0x0000},	// 0xF8
{0x0000, 0x0060, 0x0000, 0x0060, 0x0000},	// 0xF9
{0x0000, 0x0000, 0x0060, 0x0000, 0x0000},	// 0xFA
{0x0000, 0x0400, 0x0FC0, 0x0000, 0x0000},	// 0xFB
{0x0880, 0x0A40, 0x0A40, 0x0D80, 0x0000},	// 0xFC
{0x04C0, 0x0940, 0x0940, 0x0640, 0x0000},	// 0xFD
{0x0000, 0x01F0, 0x01F0, 0x01F0, 0x0000},	// 0xFE
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000} 	// 0xFF
};
