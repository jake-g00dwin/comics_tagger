/**
 * @brief A Mock of the timer module.
 * @details This file is only used for testing.
 * @author Jake G
 * @date 2024-09-02
 * @copyright None
 * @file TimerMock.h
 */

#ifndef TIMER_MOCK_H
#define TIMER_MOCK_H

#include <stdint.h>

/**
 * A function
 * @param a The first argument
 */
void     Timer_Start(void);

void     Timer_Stop(void);

uint16_t Timer_GetOverflowCount(void);

#endif // TIMER_MOCK_H
