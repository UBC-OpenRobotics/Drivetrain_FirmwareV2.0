#include "motorControl.h"

namespace STM32_motorcontrol
{   
    motorcontrol* motorc1;

    //Constructor 
    motorcontrol::motorcontrol(GPIO_TypeDef* gpio_port, uint16_t gpio_pin, TIM_HandleTypeDef* htim_handle)
    {
        this -> motorc_port = gpio_port;
        this -> motorc_pin = gpio_pin;
        this -> htim_handle = htim_handle;
    }


    void motorcontrol::timer_start()
    {
        HAL_TIM_Base_Start(this -> htim_handle);
    }

    void motorcontrol::timer_stop()
    {
        HAL_TIM_Base_Stop(this -> htim_handle);
    }

    
    void motorcontrol::adjust_timer_frequency()
    {
        uint32_t timer_reload_count = this -> clk_freq / this -> timer_freq;
        //Calcualte the reload value based on the frequency parameter.
        __HAL_TIM_SET_AUTORELOAD(this -> htim_handle, timer_reload_count);
    }


    void motorcontrol::calculate_timer_frequency(uint16_t motor_rpm)
    {
        this -> timer_freq = motor_rpm*(this -> motorSteps) / (60);
    }

}
