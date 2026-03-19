/*
 * Author: username
 * Date: 2024
 * filename: MockADC.c
 * description: module_purpose
 */

#include "MockADC.h"
#include "CppUTestExt/MockSupport_c.h"

#define FAKESIZE 256

uint16_t    fake_data[FAKESIZE];
int         fake_index = 0;

static bool is_setup   = false;

void        ADC_SetPin(uint8_t pin_num)
{
    return;
}

void ADC_Setup(void)
{
    is_setup = true;
    return;
}

void ADC_Init(uint8_t pin_num)
{
    mock_c()->actualCall("ADC_Init")->withUnsignedIntParameters("pin_num", pin_num);
}

void ADC_Enable(void)
{
    mock_c()->actualCall("ADC_Enable");
}

void ADC_Disable(void)
{
    mock_c()->actualCall("ADC_Disable");
}

uint16_t ADC_ReadValue_Impl(uint8_t pin_num)
{
    mock_c()->actualCall("ADC_ReadValue_Impl")->withUnsignedIntParameters("pin_num", pin_num);

    if (fake_index == 0)
    {
        return 0;
    }
    return fake_data[--fake_index];
}

uint16_t (*ADC_ReadValue)(uint8_t pin_num) = ADC_ReadValue_Impl;

void MockADC_PushValue(uint16_t value)
{
    if (fake_index >= FAKESIZE - 1)
    {
        return;
    }
    fake_data[fake_index++] = value;
}

void MockADC_ZeroIndex(void)
{
    fake_index = 0;
}

int MockADC_GetIndex(void)
{
    return fake_index;
}

bool MockADC_IsSetup(void)
{
    return is_setup;
}
