/**
 * @brief PUT_TEXT_HERE
 * @details This file is...
 * @author username
 * @date todays_date
 * @copyright None
 * @file MOCKADC.h
 */

#ifndef MOCKADC_H
#define MOCKADC_H

#include <stdbool.h>
#include <stdint.h>

void ADC_Setup(void);
void ADC_SetPin(uint8_t pin_num);
void ADC_Init(uint8_t pin_num);
void ADC_Enable(void);
void ADC_Disable(void);

extern uint16_t (*ADC_ReadValue)(uint8_t pin_num);

void MockADC_PushValue(uint16_t value);
void MockADC_ZeroIndex(void);
int  MockADC_GetIndex(void);
bool MockADC_IsSetup(void);

#endif // MOCKADC_H
