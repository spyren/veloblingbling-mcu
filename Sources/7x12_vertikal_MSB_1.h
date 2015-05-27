/**
 *  @brief
 *      One character is 7x12 pixel  
 *
 *  @file
 *      7x12_vertikal_MSB.h
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-01-03
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 */

const uint16_t font_7x12[256][7]={
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x00
{0x01E0, 0x0250, 0x0528, 0x0428, 0x0528, 0x0250, 0x01E0},	// 0x01
{0x01E0, 0x03B0, 0x06D8, 0x07D8, 0x06D8, 0x03B0, 0x01E0},	// 0x02
{0x0380, 0x07C0, 0x07E0, 0x03F0, 0x07E0, 0x07C0, 0x0380},	// 0x03
{0x0080, 0x01C0, 0x03E0, 0x07F0, 0x03E0, 0x01C0, 0x0080},	// 0x04
{0x00C0, 0x01E8, 0x0EE8, 0x0FD8, 0x0EE8, 0x01E8, 0x00C0},	// 0x05
{0x01C0, 0x03E8, 0x07E8, 0x0FD8, 0x07E8, 0x03E8, 0x01C0},	// 0x06
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x07
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x08
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x09
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x0A
{0x0070, 0x0088, 0x0088, 0x0588, 0x0670, 0x0700, 0x0000},	// 0x0B
{0x0000, 0x0720, 0x08A0, 0x08F8, 0x08A0, 0x0720, 0x0000},	// 0x0C
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x0D
{0x0018, 0x0018, 0x07F0, 0x0500, 0x0A30, 0x0A30, 0x0FE0},	// 0x0E
{0x0080, 0x05D0, 0x0220, 0x0E38, 0x0220, 0x05D0, 0x0080},	// 0x0F
{0x0000, 0x0000, 0x03F8, 0x01F0, 0x00E0, 0x0040, 0x0000},	// 0x10
{0x0000, 0x0040, 0x00E0, 0x01F0, 0x03F8, 0x0000, 0x0000},	// 0x11
{0x0000, 0x0220, 0x0630, 0x0FF8, 0x0630, 0x0220, 0x0000},	// 0x12
{0x0000, 0x0FD8, 0x0FD8, 0x0000, 0x0FD8, 0x0FD8, 0x0000},	// 0x13
{0x0000, 0x0700, 0x0F80, 0x0880, 0x0FF8, 0x0800, 0x0FF8},	// 0x14
{0x0000, 0x0718, 0x0FD8, 0x0948, 0x0DF8, 0x0C70, 0x0000},	// 0x15
{0x0000, 0x0038, 0x0038, 0x0038, 0x0038, 0x0038, 0x0000},	// 0x16
{0x0000, 0x0248, 0x0668, 0x0FF8, 0x0668, 0x0248, 0x0000},	// 0x17
{0x0000, 0x0200, 0x0600, 0x0FF8, 0x0600, 0x0200, 0x0000},	// 0x18
{0x0000, 0x0020, 0x0030, 0x0FF8, 0x0030, 0x0020, 0x0000},	// 0x19
{0x0040, 0x0040, 0x0040, 0x01F0, 0x00E0, 0x0040, 0x0000},	// 0x1A
{0x0040, 0x00E0, 0x01F0, 0x0040, 0x0040, 0x0040, 0x0000},	// 0x1B
{0x0000, 0x00F8, 0x0008, 0x0008, 0x0008, 0x0008, 0x0000},	// 0x1C
{0x0040, 0x00E0, 0x01F0, 0x0040, 0x01F0, 0x00E0, 0x0040},	// 0x1D
{0x0030, 0x00F0, 0x03F0, 0x0FF0, 0x03F0, 0x00F0, 0x0030},	// 0x1E
{0x0600, 0x0780, 0x07E0, 0x07F8, 0x07E0, 0x0780, 0x0600},	// 0x1F
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x20
{0x0000, 0x0000, 0x0FD8, 0x0FD8, 0x0000, 0x0000, 0x0000},	// 0x21
{0x0000, 0x0E00, 0x0E00, 0x0000, 0x0E00, 0x0E00, 0x0000},	// 0x22
{0x0000, 0x0120, 0x07F8, 0x0120, 0x07F8, 0x0120, 0x0000},	// 0x23
{0x0000, 0x0320, 0x0790, 0x0C9C, 0x04F0, 0x0260, 0x0000},	// 0x24
{0x0000, 0x0638, 0x0978, 0x06C0, 0x01B0, 0x0F48, 0x0E30},	// 0x25
{0x0000, 0x0670, 0x0FF8, 0x0988, 0x0FF0, 0x0678, 0x00C8},	// 0x26
{0x0000, 0x0000, 0x0200, 0x0E00, 0x0C00, 0x0000, 0x0000},	// 0x27
{0x0000, 0x03E0, 0x07F0, 0x0C18, 0x0808, 0x0000, 0x0000},	// 0x28
{0x0000, 0x0808, 0x0C18, 0x07F0, 0x03E0, 0x0000, 0x0000},	// 0x29
{0x0080, 0x02A0, 0x03E0, 0x01C0, 0x03E0, 0x02A0, 0x0080},	// 0x2A
{0x0000, 0x0040, 0x0040, 0x01F0, 0x01F0, 0x0040, 0x0040},	// 0x2B
{0x0000, 0x0000, 0x001A, 0x001E, 0x001C, 0x0000, 0x0000},	// 0x2C
{0x0000, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0000},	// 0x2D
{0x0000, 0x0000, 0x0018, 0x0018, 0x0018, 0x0000, 0x0000},	// 0x2E
{0x0008, 0x0038, 0x00F0, 0x03C0, 0x0F00, 0x0C00, 0x0000},	// 0x2F
{0x0000, 0x07F8, 0x0FF8, 0x0808, 0x0FF8, 0x0FF0, 0x0000},	// 0x30
{0x0000, 0x0200, 0x0600, 0x0FF8, 0x0FF8, 0x0000, 0x0000},	// 0x31
{0x0000, 0x0618, 0x0E38, 0x08E8, 0x0FC8, 0x0708, 0x0000},	// 0x32
{0x0000, 0x0410, 0x0C98, 0x0888, 0x0FF8, 0x0770, 0x0000},	// 0x33
{0x0000, 0x01E0, 0x0FE0, 0x0E20, 0x01F8, 0x01F8, 0x0020},	// 0x34
{0x0000, 0x0F90, 0x0F98, 0x0888, 0x08F8, 0x0870, 0x0000},	// 0x35
{0x0000, 0x01F0, 0x07F8, 0x0E88, 0x08F8, 0x0070, 0x0000},	// 0x36
{0x0000, 0x0800, 0x0838, 0x09F8, 0x0FC0, 0x0E00, 0x0000},	// 0x37
{0x0000, 0x0770, 0x0FF8, 0x0888, 0x0FF8, 0x0770, 0x0000},	// 0x38
{0x0000, 0x0708, 0x0F98, 0x08F0, 0x0FE0, 0x0780, 0x0000},	// 0x39
{0x0000, 0x0000, 0x0318, 0x0318, 0x0318, 0x0000, 0x0000},	// 0x3A
{0x0000, 0x0000, 0x031A, 0x031E, 0x031C, 0x0000, 0x0000},	// 0x3B
{0x0000, 0x0080, 0x01C0, 0x0360, 0x0630, 0x0C18, 0x0000},	// 0x3C
{0x0000, 0x0120, 0x0120, 0x0120, 0x0120, 0x0120, 0x0000},	// 0x3D
{0x0000, 0x0C18, 0x0630, 0x0360, 0x01C0, 0x0080, 0x0000},	// 0x3E
{0x0000, 0x0600, 0x0E58, 0x08D8, 0x0F80, 0x0700, 0x0000},	// 0x3F
{0x0000, 0x03E0, 0x07F0, 0x0C18, 0x09C8, 0x0A28, 0x07C8},	// 0x40
{0x0000, 0x03F8, 0x07F8, 0x0C40, 0x07F8, 0x03F8, 0x0000},	// 0x41
{0x0000, 0x0FF8, 0x0FF8, 0x0888, 0x0FF8, 0x0770, 0x0000},	// 0x42
{0x0000, 0x07F0, 0x0FF8, 0x0808, 0x0E38, 0x0630, 0x0000},	// 0x43
{0x0000, 0x0FF8, 0x0FF8, 0x0808, 0x0FF8, 0x07F0, 0x0000},	// 0x44
{0x0000, 0x0FF8, 0x0FF8, 0x0888, 0x0888, 0x0808, 0x0000},	// 0x45
{0x0000, 0x0FF8, 0x0FF8, 0x0880, 0x0880, 0x0800, 0x0000},	// 0x46
{0x0000, 0x07F0, 0x0FF8, 0x0808, 0x0CF8, 0x04F0, 0x0000},	// 0x47
{0x0000, 0x0FF8, 0x0FF8, 0x0080, 0x0FF8, 0x0FF8, 0x0000},	// 0x48
{0x0000, 0x0000, 0x0808, 0x0FF8, 0x0FF8, 0x0808, 0x0000},	// 0x49
{0x0000, 0x0030, 0x0038, 0x0008, 0x0FF8, 0x0FF0, 0x0000},	// 0x4A
{0x0000, 0x0FF8, 0x0FF8, 0x01C0, 0x0F78, 0x0E38, 0x0000},	// 0x4B
{0x0000, 0x0FF8, 0x0FF8, 0x0008, 0x0008, 0x0008, 0x0000},	// 0x4C
{0x0FF8, 0x0FF8, 0x0380, 0x00E0, 0x0380, 0x0FF8, 0x0FF8},	// 0x4D
{0x0000, 0x0FF8, 0x0FF8, 0x0380, 0x00C0, 0x0FF8, 0x0FF8},	// 0x4E
{0x0000, 0x07F0, 0x0FF8, 0x0808, 0x0FF8, 0x07F0, 0x0000},	// 0x4F
{0x0000, 0x0FF8, 0x0FF8, 0x0880, 0x0F80, 0x0700, 0x0000},	// 0x50
{0x0000, 0x07F0, 0x0FF8, 0x080C, 0x0FFE, 0x07F2, 0x0000},	// 0x51
{0x0000, 0x0FF8, 0x0FF8, 0x0880, 0x0FF8, 0x0778, 0x0000},	// 0x52
{0x0000, 0x0730, 0x0F98, 0x09C8, 0x0CF8, 0x0670, 0x0000},	// 0x53
{0x0000, 0x0800, 0x0800, 0x0FF8, 0x0FF8, 0x0800, 0x0800},	// 0x54
{0x0000, 0x0FF0, 0x0FF8, 0x0008, 0x0FF8, 0x0FF0, 0x0000},	// 0x55
{0x0000, 0x0FE0, 0x0FF0, 0x0018, 0x0FF0, 0x0FE0, 0x0000},	// 0x56
{0x0FC0, 0x0FF8, 0x0038, 0x03C0, 0x0038, 0x0FF8, 0x0FC0},	// 0x57
{0x0000, 0x0E38, 0x0F78, 0x01C0, 0x0F78, 0x0E38, 0x0000},	// 0x58
{0x0000, 0x0F00, 0x0F80, 0x00F8, 0x00F8, 0x0F80, 0x0F00},	// 0x59
{0x0000, 0x0838, 0x08F8, 0x0BC8, 0x0F08, 0x0C08, 0x0000},	// 0x5A
{0x0000, 0x0000, 0x0FFE, 0x0FFE, 0x0802, 0x0802, 0x0000},	// 0x5B
{0x0000, 0x0C00, 0x0F00, 0x03C0, 0x00F0, 0x0038, 0x0008},	// 0x5C
{0x0000, 0x0802, 0x0802, 0x0FFE, 0x0FFE, 0x0000, 0x0000},	// 0x5D
{0x0000, 0x0200, 0x0600, 0x0C00, 0x0600, 0x0200, 0x0000},	// 0x5E
{0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002},	// 0x5F
{0x0000, 0x0000, 0x0C00, 0x0E00, 0x0200, 0x0000, 0x0000},	// 0x60
{0x0000, 0x0030, 0x0178, 0x0148, 0x01F8, 0x00F8, 0x0000},	// 0x61
{0x0000, 0x0FF8, 0x0FF8, 0x0108, 0x01F8, 0x00F0, 0x0000},	// 0x62
{0x0000, 0x00F0, 0x01F8, 0x0108, 0x0198, 0x0090, 0x0000},	// 0x63
{0x0000, 0x00F0, 0x01F8, 0x0108, 0x0FF8, 0x0FF8, 0x0000},	// 0x64
{0x0000, 0x00F0, 0x01F8, 0x0148, 0x01C8, 0x00D0, 0x0000},	// 0x65
{0x0000, 0x0100, 0x07F8, 0x0FF8, 0x0900, 0x0900, 0x0000},	// 0x66
{0x0000, 0x00E4, 0x01F2, 0x0112, 0x01FE, 0x01FC, 0x0000},	// 0x67
{0x0000, 0x0FF8, 0x0FF8, 0x0100, 0x01F8, 0x00F8, 0x0000},	// 0x68
{0x0000, 0x0000, 0x0108, 0x09F8, 0x09F8, 0x0008, 0x0000},	// 0x69
{0x0000, 0x0002, 0x0102, 0x09FE, 0x09FC, 0x0000, 0x0000},	// 0x6A
{0x0000, 0x0FF8, 0x0FF8, 0x00E0, 0x01B8, 0x0118, 0x0000},	// 0x6B
{0x0000, 0x0000, 0x0808, 0x0FF8, 0x0FF8, 0x0008, 0x0000},	// 0x6C
{0x01F8, 0x01F8, 0x0180, 0x00F0, 0x0180, 0x01F8, 0x00F8},	// 0x6D
{0x0000, 0x01F8, 0x01F8, 0x0100, 0x01F8, 0x00F8, 0x0000},	// 0x6E
{0x0000, 0x00F0, 0x01F8, 0x0108, 0x01F8, 0x00F0, 0x0000},	// 0x6F
{0x0000, 0x01FE, 0x01FE, 0x0108, 0x01F8, 0x00F0, 0x0000},	// 0x70
{0x0000, 0x00F0, 0x01F8, 0x0108, 0x01FE, 0x01FE, 0x0000},	// 0x71
{0x0000, 0x01F8, 0x01F8, 0x0080, 0x0180, 0x0180, 0x0000},	// 0x72
{0x0000, 0x00C8, 0x01E8, 0x0168, 0x0178, 0x0130, 0x0000},	// 0x73
{0x0000, 0x0100, 0x07F0, 0x07F8, 0x0108, 0x0008, 0x0000},	// 0x74
{0x0000, 0x01F0, 0x01F8, 0x0008, 0x01F8, 0x01F8, 0x0000},	// 0x75
{0x0000, 0x01E0, 0x01F0, 0x0018, 0x01F0, 0x01E0, 0x0000},	// 0x76
{0x01E0, 0x01F8, 0x0018, 0x00F0, 0x0018, 0x01F8, 0x01E0},	// 0x77
{0x0000, 0x0198, 0x01F8, 0x0060, 0x01F8, 0x0198, 0x0000},	// 0x78
{0x0000, 0x01E2, 0x01F6, 0x001C, 0x01F8, 0x01E0, 0x0000},	// 0x79
{0x0000, 0x0118, 0x0138, 0x0168, 0x01C8, 0x0188, 0x0000},	// 0x7A
{0x0000, 0x0080, 0x07F0, 0x0F78, 0x0808, 0x0808, 0x0000},	// 0x7B
{0x0000, 0x0000, 0x0FBE, 0x0FBE, 0x0000, 0x0000, 0x0000},	// 0x7C
{0x0000, 0x0808, 0x0F78, 0x07F0, 0x0080, 0x0000, 0x0000},	// 0x7D
{0x0000, 0x0600, 0x0C00, 0x0E00, 0x0600, 0x0C00, 0x0000},	// 0x7E
{0x0000, 0x00F8, 0x0198, 0x0318, 0x0198, 0x00F8, 0x0000},	// 0x7F
{0x0000, 0x07F0, 0x0FF9, 0x080D, 0x0E3A, 0x0630, 0x0000},	// 0x80
{0x0000, 0x0DF0, 0x0DF8, 0x0008, 0x0DF8, 0x0DF8, 0x0000},	// 0x81
{0x0000, 0x00F0, 0x05F8, 0x0D48, 0x09C8, 0x08D0, 0x0000},	// 0x82
{0x0000, 0x0430, 0x0D78, 0x0948, 0x0DF8, 0x04F8, 0x0000},	// 0x83
{0x0000, 0x0C30, 0x0D78, 0x0148, 0x0DF8, 0x0CF8, 0x0000},	// 0x84
{0x0000, 0x0830, 0x0978, 0x0D48, 0x05F8, 0x00F8, 0x0000},	// 0x85
{0x0000, 0x0430, 0x0B78, 0x0B48, 0x05F8, 0x00F8, 0x0000},	// 0x86
{0x0000, 0x00F0, 0x01F9, 0x010D, 0x019A, 0x0090, 0x0000},	// 0x87
{0x0000, 0x04F0, 0x0DF8, 0x0948, 0x0DC8, 0x04D0, 0x0000},	// 0x88
{0x0000, 0x0CF0, 0x0DF8, 0x0148, 0x0DC8, 0x0CD0, 0x0000},	// 0x89
{0x0000, 0x08F0, 0x09F8, 0x0D48, 0x05C8, 0x00D0, 0x0000},	// 0x8A
{0x0000, 0x0C00, 0x0D08, 0x01F8, 0x0DF8, 0x0C08, 0x0000},	// 0x8B
{0x0000, 0x0508, 0x0DF8, 0x09F8, 0x0C08, 0x0408, 0x0000},	// 0x8C
{0x0000, 0x0800, 0x0908, 0x0DF8, 0x05F8, 0x0008, 0x0000},	// 0x8D
{0x0000, 0x0CF8, 0x0DF8, 0x0320, 0x0DF8, 0x0CF8, 0x0000},	// 0x8E
{0x0000, 0x00F8, 0x05F8, 0x0B20, 0x05F8, 0x00F8, 0x0000},	// 0x8F
{0x0000, 0x01F8, 0x05F8, 0x0D48, 0x0948, 0x0908, 0x0000},	// 0x90
{0x0000, 0x0130, 0x0148, 0x01F8, 0x01F0, 0x0128, 0x00E8},	// 0x91
{0x0000, 0x07F8, 0x0C40, 0x0FF8, 0x0FF8, 0x0888, 0x0888},	// 0x92
{0x0000, 0x04F0, 0x0DF8, 0x0908, 0x0DF8, 0x04F0, 0x0000},	// 0x93
{0x0000, 0x0CF0, 0x0DF8, 0x0108, 0x0DF8, 0x0CF0, 0x0000},	// 0x94
{0x0000, 0x08F0, 0x09F8, 0x0D08, 0x05F8, 0x00F0, 0x0000},	// 0x95
{0x0000, 0x05F0, 0x0DF8, 0x0808, 0x0DF8, 0x05F8, 0x0000},	// 0x96
{0x0000, 0x09F0, 0x09F8, 0x0C08, 0x05F8, 0x01F8, 0x0000},	// 0x97
{0x0000, 0x0DE2, 0x0DF6, 0x001C, 0x0DF8, 0x0DE0, 0x0000},	// 0x98
{0x0000, 0x09F0, 0x0BF8, 0x0208, 0x0BF8, 0x09F0, 0x0000},	// 0x99
{0x0000, 0x0BF0, 0x0BF8, 0x0008, 0x0BF8, 0x0BF0, 0x0000},	// 0x9A
{0x0000, 0x00FC, 0x01F8, 0x0168, 0x01F8, 0x03F0, 0x0000},	// 0x9B
{0x0098, 0x07F8, 0x0FE8, 0x0888, 0x0C88, 0x0408, 0x0000},	// 0x9C
{0x0000, 0x03FC, 0x07F8, 0x04C8, 0x07F8, 0x0FF0, 0x0000},	// 0x9D
{0x0000, 0x0220, 0x0140, 0x0080, 0x0140, 0x0220, 0x0000},	// 0x9E
{0x0000, 0x0104, 0x07FC, 0x0FF8, 0x0900, 0x0900, 0x0000},	// 0x9F
{0x0000, 0x0030, 0x0578, 0x0D48, 0x09F8, 0x08F8, 0x0000},	// 0xA0
{0x0000, 0x0000, 0x0508, 0x0DF8, 0x09F8, 0x0808, 0x0000},	// 0xA1
{0x0000, 0x00F0, 0x05F8, 0x0D08, 0x09F8, 0x08F0, 0x0000},	// 0xA2
{0x0000, 0x01F0, 0x05F8, 0x0C08, 0x09F8, 0x09F8, 0x0000},	// 0xA3
{0x0000, 0x05F8, 0x09F8, 0x0D00, 0x05F8, 0x08F8, 0x0000},	// 0xA4
{0x0000, 0x05F8, 0x09F8, 0x0CC0, 0x0460, 0x09F8, 0x01F8},	// 0xA5
{0x0000, 0x0190, 0x0BD0, 0x0A50, 0x0FD0, 0x07D0, 0x0000},	// 0xA6
{0x0000, 0x0790, 0x0FD0, 0x0850, 0x0FD0, 0x0790, 0x0000},	// 0xA7
{0x0000, 0x0070, 0x00F8, 0x0D88, 0x0D38, 0x0030, 0x0000},	// 0xA8
{0x03E0, 0x0410, 0x0BE8, 0x0A88, 0x0968, 0x0410, 0x03E0},	// 0xA9
{0x0000, 0x0080, 0x0080, 0x0080, 0x0080, 0x00F8, 0x0000},	// 0xAA
{0x0000, 0x0420, 0x0F40, 0x0080, 0x0198, 0x02B8, 0x0048},	// 0xAB
{0x0000, 0x0420, 0x0F40, 0x0090, 0x0130, 0x0250, 0x00F8},	// 0xAC
{0x0000, 0x0000, 0x0DF8, 0x0DF8, 0x0000, 0x0000, 0x0000},	// 0xAD
{0x00C0, 0x01E0, 0x0330, 0x02D0, 0x01E0, 0x0330, 0x0210},	// 0xAE
{0x0210, 0x0330, 0x01E0, 0x02D0, 0x0330, 0x01E0, 0x00C0},	// 0xAF
{0x0222, 0x0000, 0x0888, 0x0222, 0x0000, 0x0888, 0x0000},	// 0xB0
{0x0555, 0x0000, 0x0AAA, 0x0555, 0x0000, 0x0AAA, 0x0000},	// 0xB1
{0x0555, 0x0AAA, 0x0AAA, 0x0555, 0x0AAA, 0x0555, 0x0AAA},	// 0xB2
{0x0000, 0x0000, 0x0000, 0x0FFF, 0x0000, 0x0000, 0x0000},	// 0xB3
{0x0040, 0x0040, 0x0040, 0x0FFF, 0x0000, 0x0000, 0x0000},	// 0xB4
{0x0000, 0x00F8, 0x05F8, 0x0F20, 0x09F8, 0x08F8, 0x0000},	// 0xB5
{0x0000, 0x04F8, 0x0DF8, 0x0B20, 0x0DF8, 0x04F8, 0x0000},	// 0xB6
{0x0000, 0x08F8, 0x09F8, 0x0F20, 0x05F8, 0x00F8, 0x0000},	// 0xB7
{0x03E0, 0x0410, 0x09C8, 0x0A28, 0x0948, 0x0410, 0x03E0},	// 0xB8
{0x00A0, 0x00A0, 0x0FBF, 0x0000, 0x0FFF, 0x0000, 0x0000},	// 0xB9
{0x0000, 0x0000, 0x0FFF, 0x0000, 0x0FFF, 0x0000, 0x0000},	// 0xBA
{0x00A0, 0x00A0, 0x00BF, 0x0080, 0x00FF, 0x0000, 0x0000},	// 0xBB
{0x00A0, 0x00A0, 0x0FA0, 0x0020, 0x0FE0, 0x0000, 0x0000},	// 0xBC
{0x0000, 0x01C0, 0x03E0, 0x0220, 0x0E38, 0x0220, 0x0000},	// 0xBD
{0x0000, 0x0E50, 0x0F50, 0x01F8, 0x01F8, 0x0F50, 0x0E50},	// 0xBE
{0x0040, 0x0040, 0x0040, 0x007F, 0x0000, 0x0000, 0x0000},	// 0xBF
{0x0000, 0x0000, 0x0000, 0x0FC0, 0x0040, 0x0040, 0x0040},	// 0xC0
{0x0040, 0x0040, 0x0040, 0x0FC0, 0x0040, 0x0040, 0x0040},	// 0xC1
{0x0040, 0x0040, 0x0040, 0x007F, 0x0040, 0x0040, 0x0040},	// 0xC2
{0x0000, 0x0000, 0x0000, 0x0FFF, 0x0040, 0x0040, 0x0040},	// 0xC3
{0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040},	// 0xC4
{0x0040, 0x0040, 0x0040, 0x0FFF, 0x0040, 0x0040, 0x0040},	// 0xC5
{0x0000, 0x0430, 0x0978, 0x0D48, 0x05F8, 0x08F8, 0x0000},	// 0xC6
{0x0000, 0x04F8, 0x09F8, 0x0F20, 0x05F8, 0x08F8, 0x0000},	// 0xC7
{0x0000, 0x0000, 0x0FE0, 0x0020, 0x0FA0, 0x00A0, 0x00A0},	// 0xC8
{0x0000, 0x0000, 0x00FF, 0x0080, 0x00BF, 0x00A0, 0x00A0},	// 0xC9
{0x00A0, 0x00A0, 0x0FA0, 0x0020, 0x0FA0, 0x00A0, 0x00A0},	// 0xCA
{0x00A0, 0x00A0, 0x00BF, 0x0080, 0x00BF, 0x00A0, 0x00A0},	// 0xCB
{0x0000, 0x0000, 0x0FFF, 0x0000, 0x0FBF, 0x00A0, 0x00A0},	// 0xCC
{0x00A0, 0x00A0, 0x00A0, 0x00A0, 0x00A0, 0x00A0, 0x00A0},	// 0xCD
{0x00A0, 0x00A0, 0x0FBF, 0x0000, 0x0FBF, 0x00A0, 0x00A0},	// 0xCE
{0x02E8, 0x0110, 0x0208, 0x0208, 0x0110, 0x02E8, 0x0000},	// 0xCF
{0x0000, 0x04F0, 0x0FF8, 0x0B08, 0x09F8, 0x08F0, 0x0000},	// 0xD0
{0x0080, 0x0FF8, 0x0FF8, 0x0888, 0x0FF8, 0x07F0, 0x0000},	// 0xD1
{0x0000, 0x05F8, 0x0DF8, 0x0948, 0x0D48, 0x0508, 0x0000},	// 0xD2
{0x0000, 0x0DF8, 0x0DF8, 0x0148, 0x0D48, 0x0D08, 0x0000},	// 0xD3
{0x0000, 0x09F8, 0x09F8, 0x0D48, 0x0548, 0x0108, 0x0000},	// 0xD4
{0x0000, 0x0000, 0x0780, 0x0780, 0x0000, 0x0000, 0x0000},	// 0xD5
{0x0000, 0x0108, 0x05F8, 0x0DF8, 0x0908, 0x0800, 0x0000},	// 0xD6
{0x0400, 0x0D08, 0x09F8, 0x0DF8, 0x0508, 0x0000, 0x0000},	// 0xD7
{0x0000, 0x0D08, 0x0DF8, 0x01F8, 0x0D08, 0x0C00, 0x0000},	// 0xD8
{0x0040, 0x0040, 0x0040, 0x0FC0, 0x0000, 0x0000, 0x0000},	// 0xD9
{0x0000, 0x0000, 0x0000, 0x007F, 0x0040, 0x0040, 0x0040},	// 0xDA
{0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF},	// 0xDB
{0x003F, 0x003F, 0x003F, 0x003F, 0x003F, 0x003F, 0x003F},	// 0xDC
{0x0000, 0x0000, 0x0FBE, 0x0FBE, 0x0000, 0x0000, 0x0000},	// 0xDD
{0x0800, 0x0908, 0x0DF8, 0x05F8, 0x0108, 0x0000, 0x0000},	// 0xDE
{0x0FC0, 0x0FC0, 0x0FC0, 0x0FC0, 0x0FC0, 0x0FC0, 0x0FC0},	// 0xDF
{0x0000, 0x05F0, 0x0FF8, 0x0A08, 0x0BF8, 0x01F0, 0x0000},	// 0xE0
{0x0000, 0x07FC, 0x0FFC, 0x0888, 0x0FF8, 0x0770, 0x0000},	// 0xE1
{0x0000, 0x05F0, 0x0FF8, 0x0A08, 0x0FF8, 0x05F0, 0x0000},	// 0xE2
{0x0000, 0x01F0, 0x0BF8, 0x0A08, 0x0FF8, 0x05F0, 0x0000},	// 0xE3
{0x0000, 0x04F0, 0x09F8, 0x0D08, 0x05F8, 0x08F0, 0x0000},	// 0xE4
{0x0000, 0x05F0, 0x0BF8, 0x0E08, 0x07F8, 0x09F0, 0x0000},	// 0xE5
{0x0000, 0x01FE, 0x01FE, 0x0008, 0x01F0, 0x01F8, 0x0008},	// 0xE6
{0x0408, 0x07F8, 0x07F8, 0x0528, 0x01E0, 0x00C0, 0x0000},	// 0xE7
{0x0808, 0x0FF8, 0x0FF8, 0x0A28, 0x03E0, 0x01C0, 0x0000},	// 0xE8
{0x0000, 0x01F0, 0x05F8, 0x0C08, 0x09F8, 0x09F0, 0x0000},	// 0xE9
{0x0000, 0x05F0, 0x0DF8, 0x0808, 0x0DF8, 0x05F0, 0x0000},	// 0xEA
{0x0000, 0x09F0, 0x09F8, 0x0C08, 0x05F8, 0x01F0, 0x0000},	// 0xEB
{0x0000, 0x01E2, 0x05F6, 0x0C1C, 0x09F8, 0x09E0, 0x0000},	// 0xEC
{0x0000, 0x0380, 0x07C0, 0x0C78, 0x0878, 0x0BC0, 0x0380},	// 0xED
{0x0000, 0x0000, 0x0200, 0x0200, 0x0200, 0x0200, 0x0000},	// 0xEE
{0x0000, 0x0000, 0x0400, 0x0C00, 0x0800, 0x0800, 0x0000},	// 0xEF
{0x0000, 0x0000, 0x0040, 0x0040, 0x0040, 0x0040, 0x0000},	// 0xF0
{0x0000, 0x0088, 0x0088, 0x03E8, 0x03E8, 0x0088, 0x0088},	// 0xF1
{0x0000, 0x0120, 0x0120, 0x0120, 0x0120, 0x0120, 0x0000},	// 0xF2
{0x0000, 0x0D20, 0x0F40, 0x0A90, 0x0130, 0x0250, 0x00F8},	// 0xF3
{0x0000, 0x0700, 0x0F80, 0x0880, 0x0FF8, 0x0800, 0x0FF8},	// 0xF4
{0x0000, 0x0718, 0x0FD8, 0x0948, 0x0DF8, 0x0C70, 0x0000},	// 0xF5
{0x0000, 0x0040, 0x0040, 0x0358, 0x0358, 0x0040, 0x0040},	// 0xF6
{0x0000, 0x0000, 0x0040, 0x0020, 0x0060, 0x0060, 0x0000},	// 0xF7
{0x0000, 0x0700, 0x0F80, 0x0880, 0x0F80, 0x0700, 0x0000},	// 0xF8
{0x0000, 0x00C0, 0x00C0, 0x0000, 0x00C0, 0x00C0, 0x0000},	// 0xF9
{0x0000, 0x0000, 0x0000, 0x00C0, 0x00C0, 0x0000, 0x0000},	// 0xFA
{0x0000, 0x0000, 0x0F80, 0x0F80, 0x0000, 0x0000, 0x0000},	// 0xFB
{0x0000, 0x0880, 0x0A80, 0x0F80, 0x0500, 0x0000, 0x0000},	// 0xFC
{0x0000, 0x0980, 0x0B80, 0x0E80, 0x0480, 0x0000, 0x0000},	// 0xFD
{0x0000, 0x0000, 0x01E0, 0x01E0, 0x01E0, 0x01E0, 0x0000},	// 0xFE
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000} 	// 0xFF
};



