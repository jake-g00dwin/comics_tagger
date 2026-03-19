/*
 * Author: Jake G
 * Date: 2024-09-02
 * filename: TimerMock.c
 * description: mocks timers
 */

#include "TimerMock.h"
#include "CppUTestExt/MockSupport_c.h"
#include <stdbool.h>

static bool timer_started = false;

void        Timer_Start(void)
{
    mock_c()->actualCall("Timer_Start");
    timer_started = true;
}

void Timer_Stop(void)
{
    mock_c()->actualCall("Timer_Stop");
    timer_started = false;
}

uint16_t Timer_GetOverflowCount(void)
{
    uint16_t time = 0xAAAA;
    return mock_c()->actualCall("Timer_GetOverflowCount")->returnUnsignedIntValueOrDefault(time);
}
