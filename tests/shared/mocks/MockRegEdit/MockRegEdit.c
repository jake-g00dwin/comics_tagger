/*
 * Author: username
 * Date: 2024
 * filename: MockRegEdit.c
 * description: module_purpose
 */

#include "MockRegEdit.h"
#include "CppUTestExt/MockSupport_c.h"

// For 64-Bit systems and register access.

void RegEdit_u64_SetRegister(void *reg)
{
    mock_c()->actualCall("RegEdit_u64_SetRegister")->withPointerParameters("reg", reg);
}

void RegEdit_u64_ClearRegister(void *reg)
{
    mock_c()->actualCall("RegEdit_u64_ClearRegister")->withPointerParameters("reg", reg);
}

void RegEdit_u64_SetBit(void *reg, uint8_t bit_num)
{
    mock_c()->actualCall("RegEdit_u64_SetBit")->withPointerParameters("reg", reg)->withUnsignedIntParameters("bit_num", bit_num);
}

void RegEdit_u64_ClearBit(void *reg, uint8_t bit_num)
{
    mock_c()->actualCall("RegEdit_u64_ClearBit")->withPointerParameters("reg", reg)->withUnsignedIntParameters("bit_num", bit_num);
}

bool RegEdit_u64_IsBitSet(void *reg, uint8_t bit_num)
{
    return mock_c()->actualCall("RegEdit_u64_IsBitSet")->withPointerParameters("reg", reg)->withUnsignedIntParameters("bit_num", bit_num)->returnBoolValueOrDefault(true);
    // return mock_c()->returnBoolValueOrDefault(true);
}

void RegEdit_u64_OR_Num(void *reg, uint64_t num)
{
    mock_c()->actualCall("RegEdit_u64_OR_Num")->withPointerParameters("reg", reg)->withUnsignedIntParameters("num", num);
}

void RegEdit_u64_AND_Num(void *reg, uint64_t num)
{
    mock_c()->actualCall("RegEdit_u64_AND_Num")->withPointerParameters("reg", reg)->withUnsignedIntParameters("num", num);
}

void RegEdit_u64_SetNum(void *reg, uint64_t num)
{
    mock_c()->actualCall("RegEdit_u64_SetNum")->withPointerParameters("reg", reg)->withUnsignedIntParameters("num", num);
}

uint64_t RegEdit_u64_ReadReg(void *reg)
{
    uint64_t value = *(uint64_t *)reg;

    mock_c()->actualCall("RegEdit_u64_ReadReg")->withPointerParameters("reg", reg)->returnUnsignedIntValueOrDefault(value);

    return value;
}

// For 32-Bit systems and register access.

void RegEdit_u32_SetRegister(void *reg)
{
    mock_c()->actualCall("RegEdit_u32_SetRegister")->withPointerParameters("reg", reg);
}

void RegEdit_u32_ClearRegister(void *reg)
{
    mock_c()->actualCall("RegEdit_u32_ClearRegister")->withPointerParameters("reg", reg);
}

void RegEdit_u32_SetBit(void *reg, uint8_t bit_num)
{
    mock_c()->actualCall("RegEdit_u32_SetBit")->withPointerParameters("reg", reg)->withUnsignedIntParameters("bit_num", bit_num);
}

void RegEdit_u32_ClearBit(void *reg, uint8_t bit_num)
{
    mock_c()->actualCall("RegEdit_u32_ClearBit")->withPointerParameters("reg", reg)->withUnsignedIntParameters("bit_num", bit_num);
}

bool RegEdit_u32_IsBitSet(void *reg, uint8_t bit_num)
{
    return mock_c()->actualCall("RegEdit_u32_IsBitSet")->withPointerParameters("reg", reg)->withUnsignedIntParameters("bit_num", bit_num)->returnBoolValueOrDefault(true);
    // return mock_c()->returnBoolValueOrDefault(true);
}

void RegEdit_u32_OR_Num(void *reg, uint32_t num)
{
    mock_c()->actualCall("RegEdit_u32_OR_Num")->withPointerParameters("reg", reg)->withUnsignedIntParameters("num", num);
}

void RegEdit_u32_AND_Num(void *reg, uint32_t num)
{
    mock_c()->actualCall("RegEdit_u32_AND_Num")->withPointerParameters("reg", reg)->withUnsignedIntParameters("num", num);
}

void RegEdit_u32_SetNum(void *reg, uint32_t num)
{
    mock_c()->actualCall("RegEdit_u32_SetNum")->withPointerParameters("reg", reg)->withUnsignedIntParameters("num", num);
}

uint32_t RegEdit_u32_ReadReg(void *reg)
{
    uint32_t value = *(uint32_t *)reg;

    mock_c()->actualCall("RegEdit_u32_ReadReg")->withPointerParameters("reg", reg)->returnUnsignedIntValueOrDefault(value);

    return value;
}

// For 16-Bit systems and register access.

void RegEdit_u16_SetRegister(void *reg)
{
    mock_c()->actualCall("RegEdit_u16_SetRegister")->withPointerParameters("reg", reg);
}

void RegEdit_u16_ClearRegister(void *reg)
{
    mock_c()->actualCall("RegEdit_u16_ClearRegister")->withPointerParameters("reg", reg);
}

void RegEdit_u16_SetBit(void *reg, uint8_t bit_num)
{
    mock_c()->actualCall("RegEdit_u16_SetBit")->withPointerParameters("reg", reg)->withUnsignedIntParameters("bit_num", bit_num);
}

void RegEdit_u16_ClearBit(void *reg, uint8_t bit_num)
{
    mock_c()->actualCall("RegEdit_u16_ClearBit")->withPointerParameters("reg", reg)->withUnsignedIntParameters("bit_num", bit_num);
}

bool RegEdit_u16_IsBitSet(void *reg, uint8_t bit_num)
{
    return mock_c()->actualCall("RegEdit_u16_IsBitSet")->withPointerParameters("reg", reg)->withUnsignedIntParameters("bit_num", bit_num)->returnBoolValueOrDefault(true);
    // return mock_c()->returnBoolValueOrDefault(true);
}

void RegEdit_u16_OR_Num(void *reg, uint16_t num)
{
    mock_c()->actualCall("RegEdit_u16_OR_Num")->withPointerParameters("reg", reg)->withUnsignedIntParameters("num", num);
}

void RegEdit_u16_AND_Num(void *reg, uint16_t num)
{
    mock_c()->actualCall("RegEdit_u16_AND_Num")->withPointerParameters("reg", reg)->withUnsignedIntParameters("num", num);
}

void RegEdit_u16_SetNum(void *reg, uint16_t num)
{
    mock_c()->actualCall("RegEdit_u16_SetNum")->withPointerParameters("reg", reg)->withUnsignedIntParameters("num", num);
}

uint16_t RegEdit_u16_ReadReg(void *reg)
{
    uint16_t value = *(uint16_t *)reg;

    mock_c()->actualCall("RegEdit_u16_ReadReg")->withPointerParameters("reg", reg)->returnUnsignedIntValueOrDefault(value);

    return value;
}

// For 8-Bit systems and register access.

void RegEdit_u8_SetRegister(void *reg)
{
    mock_c()->actualCall("RegEdit_u8_SetRegister")->withPointerParameters("reg", reg);
}

void RegEdit_u8_ClearRegister(void *reg)
{
    mock_c()->actualCall("RegEdit_u8_ClearRegister")->withPointerParameters("reg", reg);
}

void RegEdit_u8_SetBit(void *reg, uint8_t bit_num)
{
    mock_c()->actualCall("RegEdit_u8_SetBit")->withPointerParameters("reg", reg)->withUnsignedIntParameters("bit_num", bit_num);
}

void RegEdit_u8_ClearBit(void *reg, uint8_t bit_num)
{
    mock_c()->actualCall("RegEdit_u8_ClearBit")->withPointerParameters("reg", reg)->withUnsignedIntParameters("bit_num", bit_num);
}

bool RegEdit_u8_IsBitSet(void *reg, uint8_t bit_num)
{
    return mock_c()->actualCall("RegEdit_u8_IsBitSet")->withPointerParameters("reg", reg)->withUnsignedIntParameters("bit_num", bit_num)->returnBoolValueOrDefault(true);
    // return mock_c()->returnBoolValueOrDefault(true);
}

void RegEdit_u8_OR_Num(void *reg, uint8_t num)
{
    mock_c()->actualCall("RegEdit_u8_OR_Num")->withPointerParameters("reg", reg)->withUnsignedIntParameters("num", num);
}

void RegEdit_u8_AND_Num(void *reg, uint8_t num)
{
    mock_c()->actualCall("RegEdit_u8_AND_Num")->withPointerParameters("reg", reg)->withUnsignedIntParameters("num", num);
}

void RegEdit_u8_SetNum(void *reg, uint8_t num)
{
    mock_c()->actualCall("RegEdit_u8_SetNum")->withPointerParameters("reg", reg)->withUnsignedIntParameters("num", num);
}

uint8_t RegEdit_u8_ReadReg(void *reg)
{
    uint8_t value = *(uint8_t *)reg;

    mock_c()->actualCall("RegEdit_u8_ReadReg")->withPointerParameters("reg", reg)->returnUnsignedIntValueOrDefault(value);

    return value;
}
