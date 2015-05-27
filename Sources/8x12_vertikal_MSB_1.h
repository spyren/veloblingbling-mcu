/**
 *  @brief
 *      One character is 8x12 pixel  
 *
 *  @file
 *      8x12_vertikal_MSB.h
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-01-03
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 */

const uint16_t font_8x12[256][8]={
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x00
{0x03F8, 0x060C, 0x04A4, 0x0434, 0x0434, 0x04A4, 0x060C, 0x03F8},	// 0x01
{0x03F8, 0x07FC, 0x075C, 0x07CC, 0x07CC, 0x075C, 0x07FC, 0x03F8},	// 0x02
{0x01E0, 0x03F0, 0x01F8, 0x00FC, 0x01F8, 0x03F0, 0x01E0, 0x0000},	// 0x03
{0x00C0, 0x01E0, 0x03F0, 0x07F8, 0x03F0, 0x01E0, 0x00C0, 0x0000},	// 0x04
{0x00E0, 0x00E4, 0x03E4, 0x079C, 0x079C, 0x03E4, 0x00E4, 0x00E0},	// 0x05
{0x00C0, 0x01E4, 0x03E4, 0x07FC, 0x07FC, 0x03E4, 0x01E4, 0x00C0},	// 0x06
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x07
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x08
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x09
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x0A
{0x0078, 0x00FC, 0x05C4, 0x05C4, 0x077C, 0x0638, 0x0780, 0x0000},	// 0x0B
{0x0000, 0x0390, 0x07D0, 0x047C, 0x047C, 0x07D0, 0x0390, 0x0000},	// 0x0C
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x0D
{0x000E, 0x07FE, 0x07FC, 0x0500, 0x0500, 0x051C, 0x07FC, 0x07F8},	// 0x0E
{0x0168, 0x01F8, 0x00F0, 0x039C, 0x039C, 0x00F0, 0x01F8, 0x0168},	// 0x0F
{0x07FC, 0x03F8, 0x01F0, 0x00E0, 0x00E0, 0x0040, 0x0040, 0x0000},	// 0x10
{0x0040, 0x0040, 0x00E0, 0x00E0, 0x01F0, 0x03F8, 0x07FC, 0x0000},	// 0x11
{0x0000, 0x0110, 0x0318, 0x07FC, 0x07FC, 0x0318, 0x0110, 0x0000},	// 0x12
{0x0000, 0x07CC, 0x07CC, 0x0000, 0x0000, 0x07CC, 0x07CC, 0x0000},	// 0x13
{0x0380, 0x07C0, 0x0440, 0x07FC, 0x07FC, 0x0400, 0x07FC, 0x07FC},	// 0x14
{0x0004, 0x0666, 0x07F2, 0x0592, 0x049A, 0x04FE, 0x0666, 0x0200},	// 0x15
{0x001C, 0x001C, 0x001C, 0x001C, 0x001C, 0x001C, 0x001C, 0x0000},	// 0x16
{0x0000, 0x0112, 0x031A, 0x07FE, 0x07FE, 0x031A, 0x0112, 0x0000},	// 0x17
{0x0000, 0x0100, 0x0300, 0x07FC, 0x07FC, 0x0300, 0x0100, 0x0000},	// 0x18
{0x0000, 0x0010, 0x0018, 0x07FC, 0x07FC, 0x0018, 0x0010, 0x0000},	// 0x19
{0x0040, 0x0040, 0x0040, 0x0150, 0x01F0, 0x00E0, 0x0040, 0x0000},	// 0x1A
{0x0040, 0x00E0, 0x01F0, 0x0150, 0x0040, 0x0040, 0x0040, 0x0000},	// 0x1B
{0x00F0, 0x00F0, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0000},	// 0x1C
{0x0040, 0x00E0, 0x01F0, 0x0040, 0x0040, 0x01F0, 0x00E0, 0x0040},	// 0x1D
{0x000C, 0x003C, 0x00FC, 0x03FC, 0x00FC, 0x003C, 0x000C, 0x0000},	// 0x1E
{0x0300, 0x03C0, 0x03F0, 0x03FC, 0x03F0, 0x03C0, 0x0300, 0x0000},	// 0x1F
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x20
{0x0000, 0x0380, 0x07EC, 0x07EC, 0x0380, 0x0000, 0x0000, 0x0000},	// 0x21
{0x0000, 0x0700, 0x0780, 0x0000, 0x0000, 0x0780, 0x0700, 0x0000},	// 0x22
{0x0110, 0x07FC, 0x07FC, 0x0110, 0x07FC, 0x07FC, 0x0110, 0x0000},	// 0x23
{0x0188, 0x03C8, 0x0E4E, 0x0E4E, 0x0278, 0x0230, 0x0000, 0x0000},	// 0x24
{0x018C, 0x0198, 0x0030, 0x0060, 0x00CC, 0x018C, 0x0000, 0x0000},	// 0x25
{0x0378, 0x07FC, 0x04C4, 0x07EC, 0x0378, 0x003C, 0x0064, 0x0000},	// 0x26
{0x0000, 0x0080, 0x0780, 0x0700, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x27
{0x0000, 0x00E0, 0x01F0, 0x0318, 0x060C, 0x0404, 0x0000, 0x0000},	// 0x28
{0x0000, 0x0404, 0x060C, 0x0318, 0x01F0, 0x00E0, 0x0000, 0x0000},	// 0x29
{0x0040, 0x0150, 0x01F0, 0x00E0, 0x00E0, 0x01F0, 0x0150, 0x0040},	// 0x2A
{0x0000, 0x0040, 0x0040, 0x01F0, 0x01F0, 0x0040, 0x0040, 0x0000},	// 0x2B
{0x0000, 0x0002, 0x000E, 0x000C, 0x000C, 0x0000, 0x0000, 0x0000},	// 0x2C
{0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0000},	// 0x2D
{0x0000, 0x0000, 0x000C, 0x000C, 0x000C, 0x0000, 0x0000, 0x0000},	// 0x2E
{0x000C, 0x0018, 0x0030, 0x0060, 0x00C0, 0x0180, 0x0300, 0x0000},	// 0x2F
{0x03F8, 0x07FC, 0x0434, 0x04E4, 0x0584, 0x07FC, 0x03F8, 0x0000},	// 0x30
{0x0104, 0x0104, 0x03FC, 0x07FC, 0x0004, 0x0004, 0x0000, 0x0000},	// 0x31
{0x030C, 0x071C, 0x0434, 0x0464, 0x07CC, 0x038C, 0x0000, 0x0000},	// 0x32
{0x0208, 0x060C, 0x0444, 0x0444, 0x07FC, 0x03B8, 0x0000, 0x0000},	// 0x33
{0x0060, 0x00E0, 0x01A0, 0x0324, 0x07FC, 0x07FC, 0x0024, 0x0000},	// 0x34
{0x07C8, 0x07CC, 0x0444, 0x0444, 0x047C, 0x0438, 0x0000, 0x0000},	// 0x35
{0x01F8, 0x03FC, 0x0644, 0x0444, 0x047C, 0x0038, 0x0000, 0x0000},	// 0x36
{0x0700, 0x0700, 0x041C, 0x043C, 0x0460, 0x07C0, 0x0780, 0x0000},	// 0x37
{0x03B8, 0x07FC, 0x0444, 0x0444, 0x07FC, 0x03B8, 0x0000, 0x0000},	// 0x38
{0x0380, 0x07C4, 0x044C, 0x047C, 0x07F0, 0x03C0, 0x0000, 0x0000},	// 0x39
{0x0000, 0x0000, 0x0198, 0x0198, 0x0198, 0x0000, 0x0000, 0x0000},	// 0x3A
{0x0000, 0x0000, 0x019A, 0x019E, 0x019C, 0x0000, 0x0000, 0x0000},	// 0x3B
{0x0040, 0x00E0, 0x01B0, 0x0318, 0x060C, 0x0404, 0x0000, 0x0000},	// 0x3C
{0x0000, 0x00A0, 0x00A0, 0x00A0, 0x00A0, 0x00A0, 0x00A0, 0x0000},	// 0x3D
{0x0000, 0x0404, 0x060C, 0x0318, 0x01B0, 0x00E0, 0x0040, 0x0000},	// 0x3E
{0x0200, 0x0600, 0x046C, 0x04EC, 0x0780, 0x0300, 0x0000, 0x0000},	// 0x3F
{0x03F8, 0x07FC, 0x0404, 0x04E4, 0x04E4, 0x07E4, 0x03E0, 0x0000},	// 0x40
{0x01FC, 0x03FC, 0x0620, 0x0620, 0x03FC, 0x01FC, 0x0000, 0x0000},	// 0x41
{0x0404, 0x07FC, 0x07FC, 0x0444, 0x0444, 0x07FC, 0x03B8, 0x0000},	// 0x42
{0x01F0, 0x03F8, 0x060C, 0x0404, 0x0404, 0x071C, 0x0318, 0x0000},	// 0x43
{0x0404, 0x07FC, 0x07FC, 0x0404, 0x060C, 0x03F8, 0x01F0, 0x0000},	// 0x44
{0x0404, 0x07FC, 0x07FC, 0x0444, 0x0444, 0x04E4, 0x060C, 0x0000},	// 0x45
{0x0404, 0x07FC, 0x07FC, 0x0444, 0x0440, 0x06E0, 0x0700, 0x0000},	// 0x46
{0x01F0, 0x03F8, 0x060C, 0x0404, 0x0424, 0x073C, 0x033C, 0x0000},	// 0x47
{0x07FC, 0x07FC, 0x0040, 0x0040, 0x07FC, 0x07FC, 0x0000, 0x0000},	// 0x48
{0x0000, 0x0404, 0x07FC, 0x07FC, 0x0404, 0x0000, 0x0000, 0x0000},	// 0x49
{0x0038, 0x003C, 0x0004, 0x0404, 0x07FC, 0x07F8, 0x0400, 0x0000},	// 0x4A
{0x0404, 0x07FC, 0x07FC, 0x0040, 0x01F0, 0x07BC, 0x060C, 0x0000},	// 0x4B
{0x0404, 0x07FC, 0x07FC, 0x0404, 0x0004, 0x001C, 0x003C, 0x0000},	// 0x4C
{0x07FC, 0x07FC, 0x0380, 0x01C0, 0x0380, 0x07FC, 0x07FC, 0x0000},	// 0x4D
{0x07FC, 0x07FC, 0x01C0, 0x00E0, 0x0070, 0x07FC, 0x07FC, 0x0000},	// 0x4E
{0x01F0, 0x03F8, 0x060C, 0x0404, 0x060C, 0x03F8, 0x01F0, 0x0000},	// 0x4F
{0x0404, 0x07FC, 0x07FC, 0x0444, 0x0440, 0x07C0, 0x0380, 0x0000},	// 0x50
{0x01F0, 0x03F8, 0x0608, 0x041A, 0x063E, 0x03FE, 0x01F2, 0x0000},	// 0x51
{0x0404, 0x07FC, 0x07FC, 0x0440, 0x0460, 0x07FC, 0x039C, 0x0000},	// 0x52
{0x0398, 0x07DC, 0x0444, 0x0464, 0x073C, 0x0318, 0x0000, 0x0000},	// 0x53
{0x0600, 0x0404, 0x07FC, 0x07FC, 0x0404, 0x0600, 0x0000, 0x0000},	// 0x54
{0x07F8, 0x07FC, 0x0004, 0x0004, 0x07FC, 0x07F8, 0x0000, 0x0000},	// 0x55
{0x07F0, 0x07F8, 0x000C, 0x000C, 0x07F8, 0x07F0, 0x0000, 0x0000},	// 0x56
{0x07E0, 0x07FC, 0x001C, 0x0060, 0x001C, 0x07FC, 0x07E0, 0x0000},	// 0x57
{0x071C, 0x07BC, 0x00E0, 0x00E0, 0x07BC, 0x071C, 0x0000, 0x0000},	// 0x58
{0x0780, 0x07C4, 0x007C, 0x007C, 0x07C4, 0x0780, 0x0000, 0x0000},	// 0x59
{0x070C, 0x063C, 0x0474, 0x05C4, 0x0784, 0x060C, 0x061C, 0x0000},	// 0x5A
{0x0000, 0x0000, 0x07FC, 0x07FC, 0x0404, 0x0404, 0x0000, 0x0000},	// 0x5B
{0x0300, 0x0180, 0x00C0, 0x0060, 0x0030, 0x0018, 0x000C, 0x0000},	// 0x5C
{0x0000, 0x0000, 0x0404, 0x0404, 0x07FC, 0x07FC, 0x0000, 0x0000},	// 0x5D
{0x0100, 0x0300, 0x0600, 0x0C00, 0x0600, 0x0300, 0x0100, 0x0000},	// 0x5E
{0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002},	// 0x5F
{0x0000, 0x0000, 0x0C00, 0x0E00, 0x0200, 0x0000, 0x0000, 0x0000},	// 0x60
{0x0018, 0x00BC, 0x00A4, 0x00A4, 0x00F8, 0x007C, 0x0004, 0x0000},	// 0x61
{0x0404, 0x07FC, 0x07F8, 0x0084, 0x0084, 0x00FC, 0x0078, 0x0000},	// 0x62
{0x0078, 0x00FC, 0x0084, 0x0084, 0x00CC, 0x0048, 0x0000, 0x0000},	// 0x63
{0x0078, 0x00FC, 0x0084, 0x0484, 0x07F8, 0x07FC, 0x0004, 0x0000},	// 0x64
{0x0078, 0x00FC, 0x00A4, 0x00A4, 0x00EC, 0x0068, 0x0000, 0x0000},	// 0x65
{0x0044, 0x03FC, 0x07FC, 0x0444, 0x0640, 0x0200, 0x0000, 0x0000},	// 0x66
{0x0072, 0x00FB, 0x0089, 0x0089, 0x007F, 0x00FE, 0x0080, 0x0000},	// 0x67
{0x0404, 0x07FC, 0x07FC, 0x0040, 0x0080, 0x00FC, 0x007C, 0x0000},	// 0x68
{0x0000, 0x0084, 0x0084, 0x06FC, 0x06FC, 0x0004, 0x0004, 0x0000},	// 0x69
{0x0006, 0x0007, 0x0081, 0x0081, 0x06FF, 0x06FE, 0x0000, 0x0000},	// 0x6A
{0x0404, 0x07FC, 0x07FC, 0x0020, 0x0070, 0x00DC, 0x008C, 0x0000},	// 0x6B
{0x0000, 0x0404, 0x0404, 0x07FC, 0x07FC, 0x0004, 0x0004, 0x0000},	// 0x6C
{0x00FC, 0x00FC, 0x0080, 0x00F8, 0x0080, 0x00FC, 0x007C, 0x0000},	// 0x6D
{0x00FC, 0x00FC, 0x0080, 0x0080, 0x00FC, 0x007C, 0x0000, 0x0000},	// 0x6E
{0x0078, 0x00FC, 0x0084, 0x0084, 0x00FC, 0x0078, 0x0000, 0x0000},	// 0x6F
{0x0081, 0x00FF, 0x007F, 0x0085, 0x0084, 0x00FC, 0x0078, 0x0000},	// 0x70
{0x0078, 0x00FC, 0x0084, 0x0085, 0x007F, 0x00FF, 0x0081, 0x0000},	// 0x71
{0x0084, 0x00FC, 0x00FC, 0x0024, 0x00C0, 0x00E0, 0x0060, 0x0000},	// 0x72
{0x0048, 0x00EC, 0x00A4, 0x0094, 0x00DC, 0x0048, 0x0000, 0x0000},	// 0x73
{0x0080, 0x01F8, 0x03FC, 0x0084, 0x008C, 0x0088, 0x0000, 0x0000},	// 0x74
{0x00F8, 0x00FC, 0x0004, 0x0004, 0x00F8, 0x00FC, 0x0004, 0x0000},	// 0x75
{0x00F0, 0x00F8, 0x000C, 0x000C, 0x00F8, 0x00F0, 0x0000, 0x0000},	// 0x76
{0x00F0, 0x00FC, 0x000C, 0x0030, 0x000C, 0x00FC, 0x00F0, 0x0000},	// 0x77
{0x0084, 0x00CC, 0x0078, 0x0030, 0x0078, 0x00CC, 0x0084, 0x0000},	// 0x78
{0x0001, 0x00F1, 0x00F9, 0x000B, 0x000E, 0x00FC, 0x00F0, 0x0000},	// 0x79
{0x00CC, 0x009C, 0x0094, 0x00A4, 0x00E4, 0x00CC, 0x0000, 0x0000},	// 0x7A
{0x0040, 0x00E0, 0x03B8, 0x071C, 0x0404, 0x0404, 0x0000, 0x0000},	// 0x7B
{0x0000, 0x0000, 0x0000, 0x07BC, 0x07BC, 0x0000, 0x0000, 0x0000},	// 0x7C
{0x0404, 0x0404, 0x071C, 0x03B8, 0x00E0, 0x0040, 0x0000, 0x0000},	// 0x7D
{0x0300, 0x0700, 0x0400, 0x0600, 0x0300, 0x0100, 0x0700, 0x0400},	// 0x7E
{0x0038, 0x0078, 0x00C8, 0x0188, 0x00C8, 0x0078, 0x0038, 0x0000},	// 0x7F
{0x03F8, 0x07FD, 0x0407, 0x0406, 0x071C, 0x0318, 0x0000, 0x0000},	// 0x80
{0x06F8, 0x06FC, 0x0004, 0x0004, 0x06F8, 0x06FC, 0x0004, 0x0000},	// 0x81
{0x0078, 0x00FC, 0x02A4, 0x06A4, 0x0CEC, 0x0868, 0x0000, 0x0000},	// 0x82
{0x0218, 0x06BC, 0x0CA4, 0x0CA4, 0x06F8, 0x027C, 0x0004, 0x0000},	// 0x83
{0x0618, 0x06BC, 0x00A4, 0x00A4, 0x06F8, 0x067C, 0x0004, 0x0000},	// 0x84
{0x0818, 0x0CBC, 0x06A4, 0x02A4, 0x00F8, 0x007C, 0x0004, 0x0000},	// 0x85
{0x0098, 0x06BC, 0x0FA4, 0x09A4, 0x0FF8, 0x067C, 0x0004, 0x0000},	// 0x86
{0x0078, 0x00FD, 0x0087, 0x0086, 0x00CC, 0x0048, 0x0000, 0x0000},	// 0x87
{0x0278, 0x06FC, 0x0CA4, 0x0CA4, 0x06E4, 0x0264, 0x0000, 0x0000},	// 0x88
{0x0678, 0x06FC, 0x00A4, 0x00A4, 0x06E4, 0x0664, 0x0000, 0x0000},	// 0x89
{0x0878, 0x0CFC, 0x06A4, 0x02A4, 0x00E4, 0x0064, 0x0000, 0x0000},	// 0x8A
{0x0000, 0x0684, 0x0684, 0x00FC, 0x06FC, 0x0604, 0x0004, 0x0000},	// 0x8B
{0x0000, 0x0284, 0x0684, 0x0CFC, 0x06FC, 0x0204, 0x0004, 0x0000},	// 0x8C
{0x0000, 0x0884, 0x0C84, 0x06FC, 0x02FC, 0x0004, 0x0004, 0x0000},	// 0x8D
{0x047C, 0x04FC, 0x0190, 0x0190, 0x04FC, 0x047C, 0x0000, 0x0000},	// 0x8E
{0x067C, 0x0FFC, 0x0990, 0x0990, 0x0FFC, 0x067C, 0x0000, 0x0000},	// 0x8F
{0x01FC, 0x01FC, 0x0124, 0x0524, 0x0D24, 0x098C, 0x0000, 0x0000},	// 0x90
{0x009C, 0x00BC, 0x00A4, 0x00F8, 0x00FC, 0x00A4, 0x00E4, 0x0064},	// 0x91
{0x01FC, 0x03FC, 0x0640, 0x07FC, 0x07FC, 0x0444, 0x0444, 0x0000},	// 0x92
{0x0278, 0x06FC, 0x0C84, 0x0C84, 0x06FC, 0x0278, 0x0000, 0x0000},	// 0x93
{0x0678, 0x06FC, 0x0084, 0x0084, 0x06FC, 0x0678, 0x0000, 0x0000},	// 0x94
{0x0878, 0x0CFC, 0x0684, 0x0284, 0x00FC, 0x0078, 0x0000, 0x0000},	// 0x95
{0x02F8, 0x06FC, 0x0C04, 0x0C04, 0x06F8, 0x02FC, 0x0004, 0x0000},	// 0x96
{0x08F8, 0x0CFC, 0x0604, 0x0204, 0x00F8, 0x00FC, 0x0004, 0x0000},	// 0x97
{0x0001, 0x06F1, 0x06F9, 0x000B, 0x000E, 0x06FC, 0x06F0, 0x0000},	// 0x98
{0x04F8, 0x05FC, 0x0104, 0x0104, 0x05FC, 0x04F8, 0x0000, 0x0000},	// 0x99
{0x0BF8, 0x0BFC, 0x0004, 0x0004, 0x0BFC, 0x0BF8, 0x0000, 0x0000},	// 0x9A
{0x0078, 0x00FC, 0x0094, 0x00A4, 0x00FC, 0x0078, 0x0000, 0x0000},	// 0x9B
{0x004C, 0x07FC, 0x0FF4, 0x0844, 0x0844, 0x0C44, 0x0404, 0x0000},	// 0x9C
{0x01F4, 0x03F8, 0x061C, 0x04E4, 0x070C, 0x03F8, 0x05F0, 0x0000},	// 0x9D
{0x0044, 0x006C, 0x0038, 0x0010, 0x0038, 0x006C, 0x0044, 0x0000},	// 0x9E
{0x0008, 0x008C, 0x0084, 0x07FC, 0x0FF8, 0x0880, 0x0C80, 0x0400},	// 0x9F
{0x0018, 0x00BC, 0x02A4, 0x06A4, 0x0CF8, 0x087C, 0x0004, 0x0000},	// 0xA0
{0x0000, 0x0084, 0x0284, 0x06FC, 0x0CFC, 0x0804, 0x0004, 0x0000},	// 0xA1
{0x0078, 0x00FC, 0x0284, 0x0684, 0x0CFC, 0x0878, 0x0000, 0x0000},	// 0xA2
{0x00F8, 0x00FC, 0x0204, 0x0604, 0x0CF8, 0x08FC, 0x0004, 0x0000},	// 0xA3
{0x02FC, 0x06FC, 0x0480, 0x0680, 0x02FC, 0x067C, 0x0400, 0x0000},	// 0xA4
{0x05FC, 0x0DFC, 0x08C0, 0x0C60, 0x0430, 0x0DFC, 0x09FC, 0x0000},	// 0xA5
{0x0320, 0x07A0, 0x04A0, 0x04A0, 0x07A0, 0x03A0, 0x00A0, 0x0000},	// 0xA6
{0x0320, 0x07A0, 0x04A0, 0x04A0, 0x07A0, 0x0320, 0x0020, 0x0000},	// 0xA7
{0x0038, 0x007C, 0x06C4, 0x0684, 0x000C, 0x0008, 0x0000, 0x0000},	// 0xA8
{0x01F0, 0x0208, 0x05F4, 0x0564, 0x05D4, 0x0208, 0x01F0, 0x0000},	// 0xA9
{0x0040, 0x0040, 0x0040, 0x0040, 0x0078, 0x0078, 0x0000, 0x0000},	// 0xAA
{0x0218, 0x07B0, 0x07E0, 0x00C2, 0x01A6, 0x032E, 0x063A, 0x0012},	// 0xAB
{0x0218, 0x07B0, 0x07EC, 0x00DC, 0x01B4, 0x0364, 0x067E, 0x047E},	// 0xAC
{0x0000, 0x0038, 0x06FC, 0x06FC, 0x0038, 0x0000, 0x0000, 0x0000},	// 0xAD
{0x0030, 0x0078, 0x00CC, 0x0084, 0x0030, 0x0078, 0x00CC, 0x0084},	// 0xAE
{0x0084, 0x00CC, 0x0078, 0x0030, 0x0084, 0x00CC, 0x0078, 0x0030},	// 0xAF
{0x0492, 0x0249, 0x0924, 0x0492, 0x0249, 0x0924, 0x0492, 0x0249},	// 0xB0
{0x0555, 0x0AAA, 0x0555, 0x0AAA, 0x0555, 0x0AAA, 0x0555, 0x0AAA},	// 0xB1
{0x06DB, 0x0DB6, 0x0B6D, 0x06DB, 0x0DB6, 0x0B6D, 0x06DB, 0x0DB6},	// 0xB2
{0x0000, 0x0000, 0x0000, 0x0FFF, 0x0FFF, 0x0000, 0x0000, 0x0000},	// 0xB3
{0x0040, 0x0040, 0x0040, 0x0FFF, 0x0FFF, 0x0000, 0x0000, 0x0000},	// 0xB4
{0x007C, 0x00FC, 0x0190, 0x0590, 0x0CFC, 0x087C, 0x0000, 0x0000},	// 0xB5
{0x047C, 0x0CFC, 0x0990, 0x0990, 0x0CFC, 0x047C, 0x0000, 0x0000},	// 0xB6
{0x007C, 0x08FC, 0x0D90, 0x0590, 0x00FC, 0x007C, 0x0000, 0x0000},	// 0xB7
{0x01F0, 0x0208, 0x05F4, 0x0514, 0x0514, 0x0208, 0x01F0, 0x0000},	// 0xB8
{0x0090, 0x0F9F, 0x0F9F, 0x0000, 0x0000, 0x0FFF, 0x0FFF, 0x0000},	// 0xB9
{0x0000, 0x0FFF, 0x0FFF, 0x0000, 0x0000, 0x0FFF, 0x0FFF, 0x0000},	// 0xBA
{0x0090, 0x009F, 0x009F, 0x0080, 0x0080, 0x00FF, 0x00FF, 0x0000},	// 0xBB
{0x0090, 0x0F90, 0x0F90, 0x0010, 0x0010, 0x0FF0, 0x0FF0, 0x0000},	// 0xBC
{0x00F0, 0x01F8, 0x070E, 0x070E, 0x0198, 0x0090, 0x0000, 0x0000},	// 0xBD
{0x0F50, 0x0FD0, 0x00FC, 0x00FC, 0x0FD0, 0x0F50, 0x0000, 0x0000},	// 0xBE
{0x0040, 0x0040, 0x0040, 0x007F, 0x007F, 0x0000, 0x0000, 0x0000},	// 0xBF
{0x0000, 0x0000, 0x0000, 0x0FC0, 0x0FC0, 0x0040, 0x0040, 0x0040},	// 0xC0
{0x0040, 0x0040, 0x0040, 0x0FC0, 0x0FC0, 0x0040, 0x0040, 0x0040},	// 0xC1
{0x0040, 0x0040, 0x0040, 0x007F, 0x007F, 0x0040, 0x0040, 0x0040},	// 0xC2
{0x0000, 0x0000, 0x0000, 0x0FFF, 0x0FFF, 0x0040, 0x0040, 0x0040},	// 0xC3
{0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040},	// 0xC4
{0x0040, 0x0040, 0x0040, 0x0FFF, 0x0FFF, 0x0040, 0x0040, 0x0040},	// 0xC5
{0x0218, 0x06BC, 0x04A4, 0x06A4, 0x02F8, 0x067C, 0x0404, 0x0000},	// 0xC6
{0x047C, 0x0CFC, 0x0990, 0x0D90, 0x04FC, 0x0C7C, 0x0800, 0x0000},	// 0xC7
{0x0000, 0x0FF0, 0x0FF0, 0x0010, 0x0010, 0x0F90, 0x0F90, 0x0090},	// 0xC8
{0x0000, 0x00FF, 0x00FF, 0x0080, 0x0080, 0x009F, 0x009F, 0x0090},	// 0xC9
{0x0090, 0x0F90, 0x0F90, 0x0010, 0x0010, 0x0F90, 0x0F90, 0x0090},	// 0xCA
{0x0090, 0x009F, 0x009F, 0x0080, 0x0080, 0x009F, 0x009F, 0x0090},	// 0xCB
{0x0000, 0x0FFF, 0x0FFF, 0x0000, 0x0000, 0x0F9F, 0x0F9F, 0x0090},	// 0xCC
{0x0090, 0x0090, 0x0090, 0x0090, 0x0090, 0x0090, 0x0090, 0x0090},	// 0xCD
{0x0090, 0x0F9F, 0x0F9F, 0x0000, 0x0000, 0x0F9F, 0x0F9F, 0x0090},	// 0xCE
{0x0044, 0x007C, 0x0038, 0x0028, 0x0038, 0x007C, 0x0044, 0x0000},	// 0xCF
{0x0A38, 0x0A7C, 0x0444, 0x0644, 0x0B44, 0x09FC, 0x00F8, 0x0000},	// 0xD0
{0x0444, 0x07FC, 0x07FC, 0x0444, 0x060C, 0x03F8, 0x01F0, 0x0000},	// 0xD1
{0x05FC, 0x0DFC, 0x0924, 0x0924, 0x0D24, 0x058C, 0x0000, 0x0000},	// 0xD2
{0x05FC, 0x05FC, 0x0124, 0x0124, 0x0524, 0x058C, 0x0000, 0x0000},	// 0xD3
{0x01FC, 0x09FC, 0x0D24, 0x0524, 0x0124, 0x018C, 0x0000, 0x0000},	// 0xD4
{0x0440, 0x0440, 0x07C0, 0x07C0, 0x0040, 0x0040, 0x0000, 0x0000},	// 0xD5
{0x0000, 0x0104, 0x05FC, 0x0DFC, 0x0904, 0x0000, 0x0000, 0x0000},	// 0xD6
{0x0400, 0x0D04, 0x09FC, 0x09FC, 0x0D04, 0x0400, 0x0000, 0x0000},	// 0xD7
{0x0400, 0x0504, 0x01FC, 0x01FC, 0x0504, 0x0400, 0x0000, 0x0000},	// 0xD8
{0x0040, 0x0040, 0x0040, 0x0FC0, 0x0FC0, 0x0000, 0x0000, 0x0000},	// 0xD9
{0x0000, 0x0000, 0x0000, 0x007F, 0x007F, 0x0040, 0x0040, 0x0040},	// 0xDA
{0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF},	// 0xDB
{0x003F, 0x003F, 0x003F, 0x003F, 0x003F, 0x003F, 0x003F, 0x003F},	// 0xDC
{0x0000, 0x0000, 0x0000, 0x07BC, 0x07BC, 0x0000, 0x0000, 0x0000},	// 0xDD
{0x0000, 0x0904, 0x0DFC, 0x05FC, 0x0104, 0x0000, 0x0000, 0x0000},	// 0xDE
{0x0FC0, 0x0FC0, 0x0FC0, 0x0FC0, 0x0FC0, 0x0FC0, 0x0FC0, 0x0FC0},	// 0xDF
{0x00F8, 0x01FC, 0x0504, 0x0D04, 0x09FC, 0x00F8, 0x0000, 0x0000},	// 0xE0
{0x03FC, 0x07FE, 0x040A, 0x0488, 0x07F8, 0x0370, 0x0000, 0x0000},	// 0xE1
{0x04F8, 0x0DFC, 0x0904, 0x0904, 0x0DFC, 0x04F8, 0x0000, 0x0000},	// 0xE2
{0x00F8, 0x09FC, 0x0D04, 0x0504, 0x01FC, 0x00F8, 0x0000, 0x0000},	// 0xE3
{0x0278, 0x06FC, 0x0484, 0x0684, 0x02FC, 0x0678, 0x0400, 0x0000},	// 0xE4
{0x04F8, 0x0DFC, 0x0904, 0x0D04, 0x05FC, 0x0CF8, 0x0800, 0x0000},	// 0xE5
{0x0001, 0x00FF, 0x00FE, 0x0004, 0x0004, 0x00F8, 0x00FC, 0x0004},	// 0xE6
{0x0204, 0x03FC, 0x03FC, 0x0094, 0x0090, 0x00F0, 0x0060, 0x0000},	// 0xE7
{0x0404, 0x07FC, 0x07FC, 0x0514, 0x0110, 0x01F0, 0x00E0, 0x0000},	// 0xE8
{0x01F8, 0x01FC, 0x0404, 0x0C04, 0x09FC, 0x01F8, 0x0000, 0x0000},	// 0xE9
{0x05F8, 0x0DFC, 0x0804, 0x0804, 0x0DFC, 0x05F8, 0x0000, 0x0000},	// 0xEA
{0x01F8, 0x09FC, 0x0C04, 0x0404, 0x01FC, 0x01F8, 0x0000, 0x0000},	// 0xEB
{0x0001, 0x00F1, 0x00F9, 0x020B, 0x060E, 0x0CFC, 0x08F0, 0x0000},	// 0xEC
{0x01C0, 0x01E4, 0x043C, 0x0C3C, 0x09E4, 0x01C0, 0x0000, 0x0000},	// 0xED
{0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0000, 0x0000},	// 0xEE
{0x0000, 0x0000, 0x0200, 0x0600, 0x0C00, 0x0800, 0x0000, 0x0000},	// 0xEF
{0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0000, 0x0000},	// 0xF0
{0x0088, 0x0088, 0x03E8, 0x03E8, 0x0088, 0x0088, 0x0000, 0x0000},	// 0xF1
{0x0048, 0x0048, 0x0048, 0x0048, 0x0048, 0x0000, 0x0000, 0x0000},	// 0xF2
{0x0898, 0x0AB0, 0x0FEC, 0x05DC, 0x01B4, 0x0364, 0x067E, 0x047E},	// 0xF3
{0x0380, 0x07C0, 0x0440, 0x07FC, 0x07FC, 0x0400, 0x07FC, 0x07FC},	// 0xF4
{0x0004, 0x0666, 0x07F2, 0x0592, 0x049A, 0x04FE, 0x0666, 0x0200},	// 0xF5
{0x0040, 0x0040, 0x0358, 0x0358, 0x0040, 0x0040, 0x0000, 0x0000},	// 0xF6
{0x0000, 0x0001, 0x0003, 0x0003, 0x0000, 0x0000, 0x0000, 0x0000},	// 0xF7
{0x0000, 0x0380, 0x07C0, 0x0440, 0x0440, 0x07C0, 0x0380, 0x0000},	// 0xF8
{0x0400, 0x0400, 0x0000, 0x0000, 0x0400, 0x0400, 0x0000, 0x0000},	// 0xF9
{0x0000, 0x0000, 0x0000, 0x0040, 0x0040, 0x0000, 0x0000, 0x0000},	// 0xFA
{0x0000, 0x0240, 0x07C0, 0x07C0, 0x0040, 0x0000, 0x0000, 0x0000},	// 0xFB
{0x0000, 0x0440, 0x0540, 0x0540, 0x07C0, 0x0280, 0x0000, 0x0000},	// 0xFC
{0x0000, 0x0440, 0x04C0, 0x05C0, 0x0740, 0x0240, 0x0000, 0x0000},	// 0xFD
{0x01F8, 0x01F8, 0x01F8, 0x01F8, 0x01F8, 0x01F8, 0x0000, 0x0000},	// 0xFE
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000} 	// 0xFF
};
