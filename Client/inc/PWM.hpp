#ifndef PWM_H
#define PWM_H

#include <stdio.h>
#include <stdlib.h>

class PWM
{
private:
    int pwm_num;
    int header;
    int pin;
    char * command;

public:
    PWM(int n, int h, int p);
    void Start();
};





#endif /*PWM_H*/