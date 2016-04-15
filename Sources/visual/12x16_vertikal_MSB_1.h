/**
 *  @brief
 *      One character is 12x16 pixel  
 *
 *  @file
 *      12x16_vertikal_MSB.h
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-01-03
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

const uint16_t font_12x16[256][12]={
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x00
{0x0000, 0x0FC0, 0x3030, 0x4008, 0x4C88, 0x8C44, 0x8044, 0x8C44, 0x4C88, 0x4008, 0x3030, 0x0FC0},	// 0x01
{0x0000, 0x0FC0, 0x3FF0, 0x7FF8, 0x7378, 0xF3BC, 0xFFBC, 0xF3BC, 0x7378, 0x7FF8, 0x3FF0, 0x0FC0},	// 0x02
{0x0000, 0x0000, 0x0F00, 0x1F80, 0x1FC0, 0x0FE0, 0x07F0, 0x0FE0, 0x1FC0, 0x1F80, 0x0F00, 0x0000},	// 0x03
{0x0000, 0x0000, 0x0100, 0x0380, 0x07C0, 0x0FE0, 0x1FF0, 0x0FE0, 0x07C0, 0x0380, 0x0100, 0x0000},	// 0x04
{0x0000, 0x01C0, 0x03E0, 0x03E0, 0x1DC8, 0x3FD8, 0x3FF8, 0x3FD8, 0x1DC8, 0x03E0, 0x03E0, 0x01C0},	// 0x05
{0x0000, 0x0000, 0x01C0, 0x03E0, 0x07E8, 0x0FD8, 0x3FF8, 0x0FD8, 0x07E8, 0x03E0, 0x01C0, 0x0000},	// 0x06
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x07
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x08
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x09
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x0A
{0x0000, 0x01C0, 0x03E0, 0x0630, 0x0410, 0x0410, 0x0630, 0x13E0, 0x15C0, 0x1800, 0x1E00, 0x0000},	// 0x0B
{0x0000, 0x0000, 0x0000, 0x0E00, 0x1F10, 0x3190, 0x20FC, 0x20FC, 0x3190, 0x1F10, 0x0E00, 0x0000},	// 0x0C
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x0D
{0x0000, 0x0060, 0x00F0, 0x00F0, 0xFFE0, 0xCC00, 0x660C, 0x331E, 0x199E, 0x0FFC, 0x0000, 0x0000},	// 0x0E
{0x0000, 0x0100, 0x1390, 0x0FE0, 0x0C60, 0x1830, 0x783C, 0x1830, 0x0C60, 0x0FE0, 0x1390, 0x0100},	// 0x0F
{0x0000, 0x0000, 0x0000, 0x3FF8, 0x1FF0, 0x0FE0, 0x07C0, 0x0380, 0x0100, 0x0000, 0x0000, 0x0000},	// 0x10
{0x0000, 0x0000, 0x0000, 0x0100, 0x0380, 0x07C0, 0x0FE0, 0x1FF0, 0x3FF8, 0x0000, 0x0000, 0x0000},	// 0x11
{0x0000, 0x0000, 0x0000, 0x0820, 0x1830, 0x3838, 0x7FFC, 0x3838, 0x1830, 0x0820, 0x0000, 0x0000},	// 0x12
{0x0000, 0x0000, 0x0000, 0x7FEC, 0x7FEC, 0x0000, 0x0000, 0x7FEC, 0x7FEC, 0x0000, 0x0000, 0x0000},	// 0x13
{0x0000, 0x1C00, 0x3E00, 0x6300, 0x4100, 0x7FFC, 0x7FFC, 0x4000, 0x7FFC, 0x7FFC, 0x4000, 0x0000},	// 0x14
{0x0000, 0x0000, 0x3B10, 0x7F98, 0x4488, 0x4488, 0x4488, 0x4488, 0x67F8, 0x2370, 0x0000, 0x0000},	// 0x15
{0x0000, 0x0000, 0x0000, 0x001C, 0x001C, 0x001C, 0x001C, 0x001C, 0x001C, 0x001C, 0x001C, 0x0000},	// 0x16
{0x0000, 0x0000, 0x0000, 0x1022, 0x3032, 0x703A, 0xFFFE, 0x703A, 0x3032, 0x1022, 0x0000, 0x0000},	// 0x17
{0x0000, 0x0000, 0x0000, 0x0800, 0x1800, 0x3800, 0x7FFC, 0x3800, 0x1800, 0x0800, 0x0000, 0x0000},	// 0x18
{0x0000, 0x0000, 0x0000, 0x0020, 0x0030, 0x0038, 0x7FFC, 0x0038, 0x0030, 0x0020, 0x0000, 0x0000},	// 0x19
{0x0000, 0x0000, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0FE0, 0x07C0, 0x0380, 0x0100, 0x0000},	// 0x1A
{0x0000, 0x0000, 0x0100, 0x0380, 0x07C0, 0x0FE0, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0000},	// 0x1B
{0x0000, 0x00FC, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0000},	// 0x1C
{0x0000, 0x0100, 0x0380, 0x07C0, 0x0FE0, 0x0100, 0x0100, 0x0100, 0x0FE0, 0x07C0, 0x0380, 0x0100},	// 0x1D
{0x0000, 0x0020, 0x0060, 0x00E0, 0x01E0, 0x03E0, 0x07E0, 0x03E0, 0x01E0, 0x00E0, 0x0060, 0x0020},	// 0x1E
{0x0000, 0x0400, 0x0600, 0x0700, 0x0780, 0x07C0, 0x07E0, 0x07C0, 0x0780, 0x0700, 0x0600, 0x0400},	// 0x1F
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x20
{0x0000, 0x0000, 0x0000, 0x0000, 0x3E00, 0xFFCC, 0xFFCC, 0x3E00, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x21
{0x0000, 0x0000, 0x0000, 0x3C00, 0x3C00, 0x0000, 0x0000, 0x3C00, 0x3C00, 0x0000, 0x0000, 0x0000},	// 0x22
{0x0000, 0x0040, 0x0878, 0x09F8, 0x0FC0, 0x7E40, 0x7878, 0x09F8, 0x0FC0, 0x7E40, 0x7800, 0x0800},	// 0x23
{0x0000, 0x0000, 0x1E20, 0x3F30, 0x3330, 0xFFFC, 0xFFFC, 0x3330, 0x33F0, 0x11E0, 0x0000, 0x0000},	// 0x24
{0x0000, 0x000C, 0x1C1C, 0x1C38, 0x1C70, 0x00E0, 0x01C0, 0x0380, 0x071C, 0x0E1C, 0x1C1C, 0x3800},	// 0x25
{0x0000, 0x0000, 0x00F8, 0x1DFC, 0x3F8C, 0x6384, 0x47EC, 0x7C78, 0x3838, 0x006C, 0x0044, 0x0000},	// 0x26
{0x0000, 0x0000, 0x0000, 0x0000, 0xE400, 0xFC00, 0xF800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x27
{0x0000, 0x0000, 0x0000, 0x0FC0, 0x3FF0, 0x7FF8, 0xE01C, 0x8004, 0x8004, 0x0000, 0x0000, 0x0000},	// 0x28
{0x0000, 0x0000, 0x0000, 0x8004, 0x8004, 0xE01C, 0x7FF8, 0x3FF0, 0x0FC0, 0x0000, 0x0000, 0x0000},	// 0x29
{0x0000, 0x0000, 0x1930, 0x1D70, 0x07C0, 0x1FF0, 0x1FF0, 0x07C0, 0x1D70, 0x1930, 0x0000, 0x0000},	// 0x2A
{0x0000, 0x0000, 0x0180, 0x0180, 0x0180, 0x0FF0, 0x0FF0, 0x0180, 0x0180, 0x0180, 0x0000, 0x0000},	// 0x2B
{0x0000, 0x0000, 0x0000, 0x0000, 0x001D, 0x001F, 0x001E, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x2C
{0x0000, 0x0000, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0000, 0x0000},	// 0x2D
{0x0000, 0x0000, 0x0000, 0x0000, 0x001C, 0x001C, 0x001C, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x2E
{0x0000, 0x0018, 0x0038, 0x0070, 0x00E0, 0x01C0, 0x0380, 0x0700, 0x0E00, 0x1C00, 0x3800, 0x7000},	// 0x2F
{0x0000, 0x1FE0, 0x7FF8, 0x6078, 0xC0CC, 0xC18C, 0xC30C, 0xC60C, 0xCC0C, 0x7818, 0x7FF8, 0x1FE0},	// 0x30
{0x0000, 0x0000, 0x0000, 0x300C, 0x300C, 0x700C, 0xFFFC, 0xFFFC, 0x000C, 0x000C, 0x000C, 0x0000},	// 0x31
{0x0000, 0x380C, 0x781C, 0xE03C, 0xC07C, 0xC0EC, 0xC1CC, 0xC38C, 0xC70C, 0xEE0C, 0x7C0C, 0x380C},	// 0x32
{0x0000, 0x3030, 0x7038, 0xE01C, 0xC30C, 0xC30C, 0xC30C, 0xC30C, 0xC30C, 0xE79C, 0x7EF8, 0x3C70},	// 0x33
{0x0000, 0x03C0, 0x07C0, 0x0EC0, 0x1CC0, 0x38C0, 0x70C0, 0xE0C0, 0xFFFC, 0xFFFC, 0x00C0, 0x00C0},	// 0x34
{0x0000, 0xFC30, 0xFE38, 0xC61C, 0xC60C, 0xC60C, 0xC60C, 0xC60C, 0xC60C, 0xC71C, 0xC3F8, 0xC1F0},	// 0x35
{0x0000, 0x03F0, 0x0FF8, 0x1F9C, 0x3B0C, 0x730C, 0xE30C, 0xC30C, 0xC30C, 0xC39C, 0x01F8, 0x00F0},	// 0x36
{0x0000, 0xC000, 0xC000, 0xC000, 0xC00C, 0xC03C, 0xC0F0, 0xC3C0, 0xCF00, 0xFC00, 0xF000, 0xC000},	// 0x37
{0x0000, 0x00F0, 0x3DF8, 0x7F9C, 0xE70C, 0xC30C, 0xC30C, 0xC30C, 0xE70C, 0x7F9C, 0x3DF8, 0x00F0},	// 0x38
{0x0000, 0x3C00, 0x7E00, 0xE70C, 0xC30C, 0xC30C, 0xC31C, 0xC338, 0xC370, 0xE7E0, 0x7FC0, 0x3F00},	// 0x39
{0x0000, 0x0000, 0x0000, 0x0000, 0x0E38, 0x0E38, 0x0E38, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x3A
{0x0000, 0x0000, 0x0000, 0x0000, 0x0E39, 0x0E3F, 0x0E3E, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x3B
{0x0000, 0x0000, 0x0300, 0x0780, 0x0FC0, 0x1CE0, 0x3870, 0x7038, 0xE01C, 0xC00C, 0x0000, 0x0000},	// 0x3C
{0x0000, 0x0000, 0x0660, 0x0660, 0x0660, 0x0660, 0x0660, 0x0660, 0x0660, 0x0660, 0x0660, 0x0000},	// 0x3D
{0x0000, 0x0000, 0xC00C, 0xE01C, 0x7038, 0x3870, 0x1CE0, 0x0FC0, 0x0780, 0x0300, 0x0000, 0x0000},	// 0x3E
{0x0000, 0x3800, 0x7800, 0xE000, 0xC000, 0xC1EC, 0xC3EC, 0xC700, 0xEE00, 0x7C00, 0x3800, 0x0000},	// 0x3F
{0x0000, 0x1FF0, 0x7FF8, 0xE018, 0xCFCC, 0xDFEC, 0xD86C, 0xDFEC, 0xDFEC, 0xE06C, 0x7FC0, 0x1F80},	// 0x40
{0x0000, 0x001C, 0x00FC, 0x07E0, 0x3F60, 0xF860, 0xF860, 0x3F60, 0x07E0, 0x00FC, 0x001C, 0x0000},	// 0x41
{0x0000, 0xFFFC, 0xFFFC, 0xC30C, 0xC30C, 0xC30C, 0xC30C, 0xE70C, 0x7F9C, 0x3DF8, 0x00F0, 0x0000},	// 0x42
{0x0000, 0x0FC0, 0x3FF0, 0x7038, 0xE01C, 0xC00C, 0xC00C, 0xC00C, 0xE01C, 0x7038, 0x3030, 0x0000},	// 0x43
{0x0000, 0xFFFC, 0xFFFC, 0xC00C, 0xC00C, 0xC00C, 0xC00C, 0xE01C, 0x7038, 0x3FF0, 0x0FC0, 0x0000},	// 0x44
{0x0000, 0xFFFC, 0xFFFC, 0xC30C, 0xC30C, 0xC30C, 0xC30C, 0xC30C, 0xC30C, 0xC00C, 0xC00C, 0x0000},	// 0x45
{0x0000, 0xFFFC, 0xFFFC, 0xC300, 0xC300, 0xC300, 0xC300, 0xC300, 0xC300, 0xC000, 0xC000, 0x0000},	// 0x46
{0x0000, 0x0FC0, 0x3FF0, 0x7038, 0xE01C, 0xC00C, 0xC30C, 0xC30C, 0xC30C, 0xE3FC, 0x63FC, 0x0000},	// 0x47
{0x0000, 0xFFFC, 0xFFFC, 0x0300, 0x0300, 0x0300, 0x0300, 0x0300, 0x0300, 0xFFFC, 0xFFFC, 0x0000},	// 0x48
{0x0000, 0x0000, 0x0000, 0xC00C, 0xC00C, 0xFFFC, 0xFFFC, 0xC00C, 0xC00C, 0x0000, 0x0000, 0x0000},	// 0x49
{0x0000, 0x0070, 0x0078, 0x001C, 0x000C, 0x000C, 0x000C, 0x000C, 0x001C, 0xFFF8, 0xFFE0, 0x0000},	// 0x4A
{0x0000, 0xFFFC, 0xFFFC, 0x0300, 0x0780, 0x0FC0, 0x1CE0, 0x3870, 0x7038, 0xE01C, 0xC00C, 0x0000},	// 0x4B
{0x0000, 0xFFFC, 0xFFFC, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x0000},	// 0x4C
{0x0000, 0xFFFC, 0xFFFC, 0x7800, 0x1E00, 0x0780, 0x0780, 0x1E00, 0x7800, 0xFFFC, 0xFFFC, 0x0000},	// 0x4D
{0x0000, 0xFFFC, 0xFFFC, 0x7000, 0x1C00, 0x0F00, 0x03C0, 0x00E0, 0x0038, 0xFFFC, 0xFFFC, 0x0000},	// 0x4E
{0x0000, 0x0FC0, 0x3FF0, 0x7038, 0xE01C, 0xC00C, 0xC00C, 0xE01C, 0x7038, 0x3FF0, 0x0FC0, 0x0000},	// 0x4F
{0x0000, 0xFFFC, 0xFFFC, 0xC180, 0xC180, 0xC180, 0xC180, 0xC180, 0xE380, 0x7F00, 0x3E00, 0x0000},	// 0x50
{0x0000, 0x0FC0, 0x3FF0, 0x7038, 0xE01C, 0xC00C, 0xC06C, 0xE07C, 0x7038, 0x3FFC, 0x0FCC, 0x0000},	// 0x51
{0x0000, 0xFFFC, 0xFFFC, 0xC180, 0xC180, 0xC1C0, 0xC1E0, 0xC1F0, 0xE3B8, 0x7F1C, 0x3E0C, 0x0000},	// 0x52
{0x0000, 0x3C30, 0x7E38, 0xE71C, 0xC30C, 0xC30C, 0xC30C, 0xC30C, 0xE39C, 0x71F8, 0x30F0, 0x0000},	// 0x53
{0x0000, 0x0000, 0xC000, 0xC000, 0xC000, 0xFFFC, 0xFFFC, 0xC000, 0xC000, 0xC000, 0x0000, 0x0000},	// 0x54
{0x0000, 0xFFE0, 0xFFF8, 0x001C, 0x000C, 0x000C, 0x000C, 0x000C, 0x001C, 0xFFF8, 0xFFE0, 0x0000},	// 0x55
{0x0000, 0xE000, 0xFC00, 0x1F80, 0x03F0, 0x007C, 0x007C, 0x03F0, 0x1F80, 0xFC00, 0xE000, 0x0000},	// 0x56
{0x0000, 0xFFFC, 0xFFFC, 0x0038, 0x0060, 0x01C0, 0x01C0, 0x0060, 0x0038, 0xFFFC, 0xFFFC, 0x0000},	// 0x57
{0x0000, 0xC00C, 0xF03C, 0x3870, 0x0CC0, 0x0780, 0x0780, 0x0CC0, 0x3870, 0xF03C, 0xC00C, 0x0000},	// 0x58
{0x0000, 0xC000, 0xF000, 0x3C00, 0x0F00, 0x03FC, 0x03FC, 0x0F00, 0x3C00, 0xF000, 0xC000, 0x0000},	// 0x59
{0x0000, 0xC00C, 0xC03C, 0xC07C, 0xC0CC, 0xC38C, 0xC70C, 0xCC0C, 0xF80C, 0xF00C, 0xC00C, 0x0000},	// 0x5A
{0x0000, 0x0000, 0x0000, 0xFFFC, 0xFFFC, 0xC00C, 0xC00C, 0xC00C, 0xC00C, 0x0000, 0x0000, 0x0000},	// 0x5B
{0x0000, 0x7000, 0x3800, 0x1C00, 0x0E00, 0x0700, 0x0380, 0x01C0, 0x00E0, 0x0070, 0x0038, 0x0018},	// 0x5C
{0x0000, 0x0000, 0x0000, 0xC00C, 0xC00C, 0xC00C, 0xC00C, 0xFFFC, 0xFFFC, 0x0000, 0x0000, 0x0000},	// 0x5D
{0x0000, 0x0600, 0x0E00, 0x1C00, 0x3800, 0x7000, 0xE000, 0x7000, 0x3800, 0x1C00, 0x0E00, 0x0600},	// 0x5E
{0x0000, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003},	// 0x5F
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x7C00, 0x7E00, 0x7200, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x60
{0x0000, 0x0038, 0x027C, 0x06CC, 0x06CC, 0x06CC, 0x06CC, 0x06CC, 0x06CC, 0x07FC, 0x03FC, 0x0000},	// 0x61
{0x0000, 0xFFFC, 0xFFFC, 0x030C, 0x060C, 0x060C, 0x060C, 0x060C, 0x071C, 0x03F8, 0x01F0, 0x0000},	// 0x62
{0x0000, 0x01F0, 0x03F8, 0x071C, 0x060C, 0x060C, 0x060C, 0x060C, 0x060C, 0x0318, 0x0110, 0x0000},	// 0x63
{0x0000, 0x01F0, 0x03F8, 0x071C, 0x060C, 0x060C, 0x060C, 0x070C, 0x030C, 0xFFFC, 0xFFFC, 0x0000},	// 0x64
{0x0000, 0x01F0, 0x03F8, 0x07DC, 0x06CC, 0x06CC, 0x06CC, 0x06CC, 0x06CC, 0x03C8, 0x0180, 0x0000},	// 0x65
{0x0000, 0x0300, 0x0300, 0x3FFC, 0x7FFC, 0xE300, 0xC300, 0xC300, 0xC000, 0x0000, 0x0000, 0x0000},	// 0x66
{0x0000, 0x01C0, 0x03E3, 0x0773, 0x0633, 0x0633, 0x0633, 0x0633, 0x0667, 0x07FE, 0x07FC, 0x0000},	// 0x67
{0x0000, 0xFFFC, 0xFFFC, 0x0300, 0x0600, 0x0600, 0x0600, 0x0700, 0x03FC, 0x01FC, 0x0000, 0x0000},	// 0x68
{0x0000, 0x0000, 0x0000, 0x000C, 0x060C, 0x37FC, 0x37FC, 0x000C, 0x000C, 0x0000, 0x0000, 0x0000},	// 0x69
{0x0000, 0x0000, 0x0000, 0x0006, 0x0007, 0x0003, 0x0603, 0x37FF, 0x37FE, 0x0000, 0x0000, 0x0000},	// 0x6A
{0x0000, 0x0000, 0xFFFC, 0xFFFC, 0x00C0, 0x01E0, 0x03F0, 0x0738, 0x061C, 0x000C, 0x0000, 0x0000},	// 0x6B
{0x0000, 0x0000, 0x0000, 0x000C, 0xC00C, 0xFFFC, 0xFFFC, 0x000C, 0x000C, 0x0000, 0x0000, 0x0000},	// 0x6C
{0x0000, 0x07FC, 0x03FC, 0x0700, 0x0700, 0x03FC, 0x03FC, 0x0700, 0x0700, 0x03FC, 0x01FC, 0x0000},	// 0x6D
{0x0000, 0x0000, 0x07FC, 0x07FC, 0x0600, 0x0600, 0x0600, 0x0600, 0x0700, 0x03FC, 0x01FC, 0x0000},	// 0x6E
{0x0000, 0x01F0, 0x03F8, 0x071C, 0x060C, 0x060C, 0x060C, 0x060C, 0x071C, 0x03F8, 0x01F0, 0x0000},	// 0x6F
{0x0000, 0x07FF, 0x07FF, 0x0630, 0x0618, 0x0618, 0x0618, 0x0618, 0x0738, 0x03F0, 0x01E0, 0x0000},	// 0x70
{0x0000, 0x01E0, 0x03F0, 0x0738, 0x0618, 0x0618, 0x0618, 0x0618, 0x0630, 0x07FF, 0x07FF, 0x0000},	// 0x71
{0x0000, 0x0000, 0x07FC, 0x07FC, 0x0300, 0x0600, 0x0600, 0x0600, 0x0600, 0x0700, 0x0300, 0x0000},	// 0x72
{0x0000, 0x0388, 0x07CC, 0x06CC, 0x06CC, 0x06CC, 0x06CC, 0x06FC, 0x0278, 0x0000, 0x0000, 0x0000},	// 0x73
{0x0000, 0x0600, 0x0600, 0x7FF8, 0x7FFC, 0x060C, 0x060C, 0x060C, 0x000C, 0x0000, 0x0000, 0x0000},	// 0x74
{0x0000, 0x07F0, 0x07F8, 0x001C, 0x000C, 0x000C, 0x000C, 0x000C, 0x0018, 0x07FC, 0x07FC, 0x0000},	// 0x75
{0x0000, 0x0600, 0x0780, 0x01E0, 0x0078, 0x001C, 0x001C, 0x0078, 0x01E0, 0x0780, 0x0600, 0x0000},	// 0x76
{0x0000, 0x07E0, 0x07F8, 0x001C, 0x0038, 0x07F0, 0x07F0, 0x0038, 0x001C, 0x07F8, 0x07E0, 0x0000},	// 0x77
{0x0000, 0x060C, 0x071C, 0x03B8, 0x01F0, 0x00E0, 0x01F0, 0x03B8, 0x071C, 0x060C, 0x0000, 0x0000},	// 0x78
{0x0000, 0x0000, 0x0600, 0x0781, 0x01E7, 0x007E, 0x0078, 0x01E0, 0x0780, 0x0600, 0x0000, 0x0000},	// 0x79
{0x0000, 0x060C, 0x061C, 0x063C, 0x066C, 0x06CC, 0x078C, 0x070C, 0x060C, 0x040C, 0x0000, 0x0000},	// 0x7A
{0x0000, 0x0000, 0x0100, 0x0380, 0x3FF8, 0x7EFC, 0xE00E, 0xC006, 0xC006, 0xC006, 0x0000, 0x0000},	// 0x7B
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFDFC, 0xFDFC, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0x7C
{0x0000, 0x0000, 0xC006, 0xC006, 0xC006, 0xE00E, 0x7EFC, 0x3FF8, 0x0380, 0x0100, 0x0000, 0x0000},	// 0x7D
{0x0000, 0x0800, 0x1800, 0x3000, 0x2000, 0x3000, 0x1800, 0x0800, 0x1800, 0x3000, 0x2000, 0x0000},	// 0x7E
{0x0000, 0x00F0, 0x01F0, 0x0330, 0x0630, 0x0C30, 0x0C30, 0x0630, 0x0330, 0x01F0, 0x00F0, 0x0000},	// 0x7F
{0x0000, 0x0F80, 0x3FE0, 0x7073, 0xE03B, 0xC01F, 0xC01F, 0xC018, 0xE038, 0x7870, 0x3860, 0x0000},	// 0x80
{0x0000, 0x07F0, 0x07F8, 0x301C, 0x300C, 0x000C, 0x000C, 0x300C, 0x3018, 0x07FC, 0x07FC, 0x0000},	// 0x81
{0x0000, 0x01F0, 0x03F8, 0x07DC, 0x06CC, 0x16CC, 0x36CC, 0x66CC, 0x46CC, 0x03C8, 0x01C0, 0x0000},	// 0x82
{0x0000, 0x0038, 0x027C, 0x16CC, 0x36CC, 0x66CC, 0x66CC, 0x36CC, 0x16CC, 0x07FC, 0x03FC, 0x0000},	// 0x83
{0x0000, 0x0038, 0x027C, 0x36CC, 0x36CC, 0x06CC, 0x06CC, 0x36CC, 0x36CC, 0x07FC, 0x03FC, 0x0000},	// 0x84
{0x0000, 0x0038, 0x027C, 0x06CC, 0x46CC, 0x66CC, 0x36CC, 0x16CC, 0x06CC, 0x07FC, 0x03FC, 0x0000},	// 0x85
{0x0000, 0x0038, 0x027C, 0x06CC, 0x26CC, 0x56CC, 0x56CC, 0x26CC, 0x06CC, 0x07FC, 0x03FC, 0x0000},	// 0x86
{0x0000, 0x01F0, 0x03F8, 0x071D, 0x060D, 0x060F, 0x060F, 0x060C, 0x071C, 0x0318, 0x0110, 0x0000},	// 0x87
{0x0000, 0x01F0, 0x03F8, 0x17CC, 0x36CC, 0x66CC, 0x66CC, 0x36CC, 0x16CC, 0x03C8, 0x01C0, 0x0000},	// 0x88
{0x0000, 0x01F0, 0x03F8, 0x37CC, 0x36CC, 0x06CC, 0x06CC, 0x36CC, 0x36CC, 0x03C8, 0x01C0, 0x0000},	// 0x89
{0x0000, 0x01F0, 0x03F8, 0x07CC, 0x46CC, 0x66CC, 0x36CC, 0x16CC, 0x06CC, 0x03C8, 0x01C0, 0x0000},	// 0x8A
{0x0000, 0x0000, 0x0000, 0x300C, 0x360C, 0x07FC, 0x37FC, 0x300C, 0x000C, 0x0000, 0x0000, 0x0000},	// 0x8B
{0x0000, 0x0000, 0x0000, 0x100C, 0x360C, 0x67FC, 0x67FC, 0x300C, 0x100C, 0x0000, 0x0000, 0x0000},	// 0x8C
{0x0000, 0x0000, 0x0000, 0x000C, 0x460C, 0x67FC, 0x37FC, 0x100C, 0x000C, 0x0000, 0x0000, 0x0000},	// 0x8D
{0x0000, 0x001C, 0x007C, 0xC1F0, 0xC7B0, 0x1E30, 0x1E30, 0xC7B0, 0xC1F0, 0x007C, 0x001C, 0x0000},	// 0x8E
{0x0000, 0x001C, 0x007C, 0x01F0, 0x47B0, 0xAE30, 0xAE30, 0x47B0, 0x01F0, 0x007C, 0x001C, 0x0000},	// 0x8F
{0x0000, 0x1FFC, 0x1FFC, 0x198C, 0x198C, 0x398C, 0x798C, 0xD98C, 0x998C, 0x180C, 0x180C, 0x0000},	// 0x90
{0x0000, 0x0138, 0x037C, 0x0244, 0x0244, 0x03F8, 0x01FC, 0x0244, 0x0244, 0x03CC, 0x0188, 0x0000},	// 0x91
{0x0000, 0x003C, 0x01FC, 0x0FE0, 0x3E60, 0xF860, 0xFFFC, 0xFFFC, 0xC30C, 0xC30C, 0xC00C, 0x0000},	// 0x92
{0x0000, 0x01F0, 0x03F8, 0x171C, 0x360C, 0x660C, 0x660C, 0x360C, 0x171C, 0x03F8, 0x01F0, 0x0000},	// 0x93
{0x0000, 0x01F0, 0x03F8, 0x371C, 0x360C, 0x060C, 0x060C, 0x360C, 0x371C, 0x03F8, 0x01F0, 0x0000},	// 0x94
{0x0000, 0x01F0, 0x03F8, 0x071C, 0x460C, 0x660C, 0x360C, 0x160C, 0x071C, 0x03F8, 0x01F0, 0x0000},	// 0x95
{0x0000, 0x07F0, 0x07F8, 0x101C, 0x300C, 0x600C, 0x600C, 0x300C, 0x1018, 0x07FC, 0x07FC, 0x0000},	// 0x96
{0x0000, 0x07F0, 0x07F8, 0x001C, 0x400C, 0x600C, 0x300C, 0x100C, 0x0018, 0x07FC, 0x07FC, 0x0000},	// 0x97
{0x0000, 0x0000, 0x0600, 0x3781, 0x31E7, 0x007E, 0x0078, 0x31E0, 0x3780, 0x0600, 0x0000, 0x0000},	// 0x98
{0x0000, 0x07F0, 0x0FF8, 0xDC1C, 0xD80C, 0x180C, 0x180C, 0xD80C, 0xDC1C, 0x0FF8, 0x07F0, 0x0000},	// 0x99
{0x0000, 0x07F0, 0x07F8, 0x301C, 0x300C, 0x000C, 0x000C, 0x300C, 0x3018, 0x07FC, 0x07FC, 0x0000},	// 0x9A
{0x0000, 0x01F4, 0x03FC, 0x0718, 0x063C, 0x066C, 0x06CC, 0x078C, 0x031C, 0x07F8, 0x05F0, 0x0000},	// 0x9B
{0x0000, 0x0000, 0x0018, 0x0138, 0x1FF8, 0x3FD0, 0x3118, 0x3118, 0x3818, 0x1818, 0x0010, 0x0000},	// 0x9C
{0x0000, 0x0FF4, 0x1FFC, 0x3818, 0x307C, 0x31EC, 0x378C, 0x3E0C, 0x181C, 0x3FF8, 0x2FF0, 0x0000},	// 0x9D
{0x0000, 0x0000, 0x0820, 0x0C60, 0x06C0, 0x0380, 0x0380, 0x06C0, 0x0C60, 0x0820, 0x0000, 0x0000},	// 0x9E
{0x0000, 0x0000, 0x000C, 0x010E, 0x0106, 0x7FFE, 0xFFFC, 0xC100, 0xE100, 0x6000, 0x0000, 0x0000},	// 0x9F
{0x0000, 0x0038, 0x027C, 0x06CC, 0x16CC, 0x36CC, 0x66CC, 0x46CC, 0x06CC, 0x07FC, 0x03FC, 0x0000},	// 0xA0
{0x0000, 0x0000, 0x0000, 0x000C, 0x160C, 0x37FC, 0x67FC, 0x400C, 0x000C, 0x0000, 0x0000, 0x0000},	// 0xA1
{0x0000, 0x01F0, 0x03F8, 0x071C, 0x160C, 0x360C, 0x660C, 0x460C, 0x071C, 0x03F8, 0x01F0, 0x0000},	// 0xA2
{0x0000, 0x07F0, 0x07F8, 0x001C, 0x100C, 0x300C, 0x600C, 0x400C, 0x0018, 0x07FC, 0x07FC, 0x0000},	// 0xA3
{0x0000, 0x0000, 0x07FC, 0x17FC, 0x3600, 0x2600, 0x3600, 0x1600, 0x3700, 0x23FC, 0x01FC, 0x0000},	// 0xA4
{0x0000, 0x1FFC, 0x1FFC, 0x4E00, 0xC700, 0x8380, 0xC1C0, 0x40E0, 0xC070, 0x9FFC, 0x1FFC, 0x0000},	// 0xA5
{0x0000, 0x0E00, 0x5F60, 0xDB60, 0xDB60, 0xDB60, 0xDB60, 0xDB60, 0xDB60, 0xFF60, 0x7F00, 0x0000},	// 0xA6
{0x0000, 0x3C00, 0x7E60, 0xE760, 0xC360, 0xC360, 0xC360, 0xC360, 0xE760, 0x7E60, 0x3C00, 0x0000},	// 0xA7
{0x0000, 0x0070, 0x00F8, 0x01DC, 0x038C, 0xDF0C, 0xDE0C, 0x000C, 0x001C, 0x0078, 0x0070, 0x0000},	// 0xA8
{0x0000, 0x0FE0, 0x1FF0, 0x3838, 0x37D8, 0x37D8, 0x3518, 0x37D8, 0x32D8, 0x3838, 0x1FF0, 0x0FE0},	// 0xA9
{0x1800, 0x1800, 0x1800, 0x1800, 0x1800, 0x1800, 0x1800, 0x1800, 0x1800, 0x1FC0, 0x1FC0, 0x0000},	// 0xAA
{0x0000, 0x1200, 0x3E20, 0x3E60, 0x02C0, 0x0180, 0x0300, 0x0698, 0x0CB8, 0x08E8, 0x0048, 0x0000},	// 0xAB
{0x0000, 0x1200, 0x3E20, 0x3E60, 0x02C0, 0x0180, 0x0360, 0x06E0, 0x0C20, 0x08F8, 0x00F8, 0x0000},	// 0xAC
{0x0000, 0x0000, 0x0000, 0x0000, 0x01F0, 0xCFFC, 0xCFFC, 0x01F0, 0x0000, 0x0000, 0x0000, 0x0000},	// 0xAD
{0x0000, 0x0100, 0x0380, 0x06C0, 0x0440, 0x0000, 0x0100, 0x0380, 0x06C0, 0x0440, 0x0000, 0x0000},	// 0xAE
{0x0000, 0x0440, 0x06C0, 0x0380, 0x0100, 0x0000, 0x0440, 0x06C0, 0x0380, 0x0100, 0x0000, 0x0000},	// 0xAF
{0xAAAA, 0x0000, 0x5555, 0x0000, 0xAAAA, 0x0000, 0x5555, 0x0000, 0xAAAA, 0x0000, 0x5555, 0x0000},	// 0xB0
{0x5555, 0xAAAA, 0x5555, 0xAAAA, 0x5555, 0xAAAA, 0x5555, 0xAAAA, 0x5555, 0xAAAA, 0x5555, 0xAAAA},	// 0xB1
{0x5555, 0xFFFF, 0xAAAA, 0xFFFF, 0x5555, 0xFFFF, 0xAAAA, 0xFFFF, 0x5555, 0xFFFF, 0xAAAA, 0xFFFF},	// 0xB2
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0xB3
{0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0xB4
{0x0000, 0x001C, 0x007C, 0x01F0, 0x27B0, 0x7E30, 0xDE30, 0x87B0, 0x01F0, 0x007C, 0x001C, 0x0000},	// 0xB5
{0x0000, 0x001C, 0x007C, 0x21F0, 0x67B0, 0xDE30, 0xDE30, 0x67B0, 0x21F0, 0x007C, 0x001C, 0x0000},	// 0xB6
{0x0000, 0x001C, 0x007C, 0x01F0, 0x87B0, 0xDE30, 0x7E30, 0x27B0, 0x01F0, 0x007C, 0x001C, 0x0000},	// 0xB7
{0x0000, 0x0FE0, 0x1FF0, 0x3838, 0x3398, 0x37D8, 0x3458, 0x36D8, 0x3298, 0x3838, 0x1FF0, 0x0FE0},	// 0xB8
{0x0360, 0x0360, 0xFF7F, 0xFF7F, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0xB9
{0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0xBA
{0x0360, 0x0360, 0x037F, 0x037F, 0x0300, 0x03FF, 0x03FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0xBB
{0x0360, 0x0360, 0xFF60, 0xFF60, 0x0060, 0xFFE0, 0xFFE0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0xBC
{0x0000, 0x0000, 0x07C0, 0x0FE0, 0x1C70, 0x7FFC, 0x7FFC, 0x1830, 0x1C70, 0x0C60, 0x0000, 0x0000},	// 0xBD
{0x0000, 0xC000, 0xF050, 0x3C50, 0x0F50, 0x03FC, 0x03FC, 0x0F50, 0x3C50, 0xF050, 0xC000, 0x0000},	// 0xBE
{0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x01FF, 0x01FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0xBF
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFF80, 0xFF80, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180},	// 0xC0
{0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0xFF80, 0xFF80, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180},	// 0xC1
{0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x01FF, 0x01FF, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180},	// 0xC2
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180},	// 0xC3
{0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180},	// 0xC4
{0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0xFFFF, 0xFFFF, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180},	// 0xC5
{0x0000, 0x0038, 0x027C, 0x16CC, 0x36CC, 0x26CC, 0x36CC, 0x16CC, 0x36CC, 0x27FC, 0x03FC, 0x0000},	// 0xC6
{0x0000, 0x001C, 0x007C, 0x41F0, 0xC7B0, 0x9E30, 0xDE30, 0x47B0, 0xC1F0, 0x807C, 0x001C, 0x0000},	// 0xC7
{0x0000, 0x0000, 0xFFE0, 0xFFE0, 0x0060, 0xFF60, 0xFF60, 0x0360, 0x0360, 0x0360, 0x0360, 0x0360},	// 0xC8
{0x0000, 0x0000, 0x03FF, 0x03FF, 0x0300, 0x037F, 0x037F, 0x0360, 0x0360, 0x0360, 0x0360, 0x0360},	// 0xC9
{0x0360, 0x0360, 0xFF60, 0xFF60, 0x0060, 0xFF60, 0xFF60, 0x0360, 0x0360, 0x0360, 0x0360, 0x0360},	// 0xCA
{0x0360, 0x0360, 0x037F, 0x037F, 0x0300, 0x037F, 0x037F, 0x0360, 0x0360, 0x0360, 0x0360, 0x0360},	// 0xCB
{0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0xFF7F, 0xFF7F, 0x0360, 0x0360, 0x0360, 0x0360, 0x0360},	// 0xCC
{0x0360, 0x0360, 0x0360, 0x0360, 0x0360, 0x0360, 0x0360, 0x0360, 0x0360, 0x0360, 0x0360, 0x0360},	// 0xCD
{0x0360, 0x0360, 0xFF7F, 0xFF7F, 0x0000, 0xFF7F, 0xFF7F, 0x0360, 0x0360, 0x0360, 0x0360, 0x0360},	// 0xCE
{0x0000, 0x6FD8, 0x7FF8, 0x1860, 0x3030, 0x3030, 0x3030, 0x3030, 0x1860, 0x7FF8, 0x6FD8, 0x0000},	// 0xCF
{0x0000, 0x0000, 0x0000, 0x1E38, 0x3F7C, 0x33CC, 0x31CC, 0x30FC, 0x1878, 0x0000, 0x0000, 0x0000},	// 0xD0
{0x0000, 0x0300, 0xFFFC, 0xFFFC, 0xC30C, 0xC00C, 0xC00C, 0xE01C, 0x7038, 0x3FF0, 0x0FC0, 0x0000},	// 0xD1
{0x0000, 0x1FFC, 0x1FFC, 0x398C, 0x798C, 0xD98C, 0xD98C, 0x798C, 0x398C, 0x180C, 0x180C, 0x0000},	// 0xD2
{0x0000, 0x1FFC, 0x1FFC, 0xD98C, 0xD98C, 0x198C, 0x198C, 0xD98C, 0xD98C, 0x180C, 0x180C, 0x0000},	// 0xD3
{0x0000, 0x1FFC, 0x1FFC, 0x998C, 0xD98C, 0x798C, 0x398C, 0x198C, 0x198C, 0x180C, 0x180C, 0x0000},	// 0xD4
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x7E00, 0x7E00, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0xD5
{0x0000, 0x0000, 0x0000, 0x180C, 0x180C, 0x3FFC, 0x7FFC, 0xD80C, 0x980C, 0x0000, 0x0000, 0x0000},	// 0xD6
{0x0000, 0x0000, 0x0000, 0x380C, 0x780C, 0xDFFC, 0xDFFC, 0x780C, 0x380C, 0x0000, 0x0000, 0x0000},	// 0xD7
{0x0000, 0x0000, 0x0000, 0xD80C, 0xD80C, 0x1FFC, 0x1FFC, 0xD80C, 0xD80C, 0x0000, 0x0000, 0x0000},	// 0xD8
{0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0xFF80, 0xFF80, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0xD9
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x01FF, 0x01FF, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180},	// 0xDA
{0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},	// 0xDB
{0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF},	// 0xDC
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFDFC, 0xFDFC, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0xDD
{0x0000, 0x0000, 0x0000, 0x980C, 0xD80C, 0x7FFC, 0x3FFC, 0x180C, 0x180C, 0x0000, 0x0000, 0x0000},	// 0xDE
{0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00},	// 0xDF
{0x0000, 0x07F0, 0x0FF8, 0x1C1C, 0x180C, 0x380C, 0x780C, 0xD80C, 0x9C1C, 0x0FF8, 0x07F0, 0x0000},	// 0xE0
{0x0000, 0x0000, 0x03FF, 0x07FF, 0x0C84, 0x0884, 0x0884, 0x0CCC, 0x07FC, 0x0378, 0x0000, 0x0000},	// 0xE1
{0x0000, 0x07F0, 0x0FF8, 0x3C1C, 0x780C, 0xD80C, 0xD80C, 0x780C, 0x3C1C, 0x0FF8, 0x07F0, 0x0000},	// 0xE2
{0x0000, 0x07F0, 0x0FF8, 0x9C1C, 0xD80C, 0x780C, 0x380C, 0x180C, 0x1C1C, 0x0FF8, 0x07F0, 0x0000},	// 0xE3
{0x0000, 0x01F0, 0x13F8, 0x371C, 0x260C, 0x360C, 0x160C, 0x360C, 0x271C, 0x03F8, 0x01F0, 0x0000},	// 0xE4
{0x0000, 0x07F0, 0x0FF8, 0x5C1C, 0xD80C, 0x980C, 0xD80C, 0x580C, 0xDC1C, 0x8FF8, 0x07F0, 0x0000},	// 0xE5
{0x0000, 0x0FFF, 0x0FFF, 0x0070, 0x0030, 0x0030, 0x0030, 0x0060, 0x0FF0, 0x0FF0, 0x0000, 0x0000},	// 0xE6
{0x0000, 0x0000, 0x300C, 0x3FFC, 0x3FFC, 0x366C, 0x0660, 0x0660, 0x07E0, 0x03C0, 0x0000, 0x0000},	// 0xE7
{0x0000, 0x0000, 0xC00C, 0xFFFC, 0xFFFC, 0xD86C, 0x1860, 0x1860, 0x1FE0, 0x0FC0, 0x0000, 0x0000},	// 0xE8
{0x0000, 0x1FE0, 0x1FF8, 0x001C, 0x000C, 0x200C, 0x600C, 0xC00C, 0x801C, 0x1FF8, 0x1FE0, 0x0000},	// 0xE9
{0x0000, 0x1FE0, 0x1FF8, 0x201C, 0x600C, 0xC00C, 0xC00C, 0x600C, 0x201C, 0x1FF8, 0x1FE0, 0x0000},	// 0xEA
{0x0000, 0x1FE0, 0x1FF8, 0x801C, 0xC00C, 0x600C, 0x200C, 0x000C, 0x001C, 0x1FF8, 0x1FE0, 0x0000},	// 0xEB
{0x0000, 0x0000, 0x0600, 0x0781, 0x01E7, 0x087E, 0x1878, 0x31E0, 0x2780, 0x0600, 0x0000, 0x0000},	// 0xEC
{0x0000, 0x1000, 0x1800, 0x0C00, 0x0600, 0x23FC, 0x63FC, 0xC600, 0x8C00, 0x1800, 0x1000, 0x0000},	// 0xED
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3000, 0x3000, 0x3000, 0x3000, 0x0000, 0x0000, 0x0000},	// 0xEE
{0x0000, 0x0000, 0x0000, 0x0000, 0x2000, 0x6000, 0xC000, 0x8000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0xEF
{0x0000, 0x0000, 0x0000, 0x0300, 0x0300, 0x0300, 0x0300, 0x0300, 0x0300, 0x0000, 0x0000, 0x0000},	// 0xF0
{0x0000, 0x0000, 0x0000, 0x0318, 0x0318, 0x0FD8, 0x0FD8, 0x0318, 0x0318, 0x0000, 0x0000, 0x0000},	// 0xF1
{0x0000, 0x0000, 0x0000, 0x0360, 0x0360, 0x0360, 0x0360, 0x0360, 0x0360, 0x0000, 0x0000, 0x0000},	// 0xF2
{0x0000, 0x2200, 0x2A20, 0x3E60, 0x14C0, 0x0180, 0x0360, 0x06E0, 0x0C20, 0x08F8, 0x00F8, 0x0000},	// 0xF3
{0x0000, 0x1C00, 0x3E00, 0x6300, 0x4100, 0x7FFC, 0x7FFC, 0x4000, 0x7FFC, 0x7FFC, 0x4000, 0x0000},	// 0xF4
{0x0000, 0x0000, 0x3B10, 0x7F98, 0x4488, 0x4488, 0x4488, 0x4488, 0x67F8, 0x2370, 0x0000, 0x0000},	// 0xF5
{0x0000, 0x0000, 0x0180, 0x0180, 0x0180, 0x0DB0, 0x0DB0, 0x0180, 0x0180, 0x0180, 0x0000, 0x0000},	// 0xF6
{0x0000, 0x0000, 0x0000, 0x0200, 0x0100, 0x0100, 0x0300, 0x0300, 0x0000, 0x0000, 0x0000, 0x0000},	// 0xF7
{0x0000, 0x0000, 0x0000, 0x7800, 0xFC00, 0xCC00, 0xCC00, 0xFC00, 0x7800, 0x0000, 0x0000, 0x0000},	// 0xF8
{0x0000, 0x0000, 0x0180, 0x03C0, 0x0180, 0x0000, 0x0000, 0x0180, 0x03C0, 0x0180, 0x0000, 0x0000},	// 0xF9
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0180, 0x03C0, 0x0180, 0x0000, 0x0000, 0x0000, 0x0000},	// 0xFA
{0x0000, 0x0000, 0x4000, 0xF800, 0xF800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0xFB
{0x0000, 0x0000, 0x8800, 0xA800, 0xA800, 0xF800, 0x5000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0xFC
{0x0000, 0x0000, 0x9800, 0xB800, 0xA800, 0xE800, 0x4800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// 0xFD
{0x0000, 0x0000, 0x0000, 0x0000, 0x0FC0, 0x0FC0, 0x0FC0, 0x0FC0, 0x0000, 0x0000, 0x0000, 0x0000},	// 0xFE
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000} 	// 0xFF
};
