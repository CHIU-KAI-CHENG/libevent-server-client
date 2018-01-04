#include "PWM.hpp"

PWM::PWM(int n, int h, int p)
{
    pwm_num = n;
    header = h;
    pin = p;
}

void PWM::Start()
{
    char buf[58];
    sprintf(buf, "echo BB-PWM%d > /sys/devices/bone_capemgr.9/slots", pwm_num);
    printf("%s", buf);
    //system(command);

    sprintf(buf, "echo %d > /sys/class/pwm/export", pwm_num);
    //system(command);

    sprintf(buf, "echo bone_pwm_P%d_%d > /sys/devices/bone_capemgr.9/slots", header, pin);
    //system(command);
}