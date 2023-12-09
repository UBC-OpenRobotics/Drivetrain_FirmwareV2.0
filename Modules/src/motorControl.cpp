#include "motorControl.h"

namespace STM32_motor_control
{   
    stepper_motor_controller* motor_controller_1;

    //Constructor 
    stepper_motor_controller::stepper_motor_controller(GPIO_TypeDef* gpio_port, uint16_t gpio_pin, TIM_HandleTypeDef* htim_handle)
    {
        this -> motorc_port = gpio_port;
        this -> motorc_pin = gpio_pin;
        this -> htim_handle = htim_handle;
    }


    void stepper_motor_controller::set_stepper_rpm(uint32_t motor_rpm)
    {
        this -> calculate_timer_frequency(motor_rpm);
        this -> set_timer_frequency();
    }
    
    void stepper_motor_controller::set_timer_frequency()
    {   

        //find the timer prescalr using HAL
        uint32_t timer_prescalar = (this -> htim_handle -> Instance -> PSC) + 1; 
        uint32_t timer_reload_count = (this -> timer_input_clk_freq/timer_prescalar) / (this -> timer_output_freq);
        //Calcualte the reload value based on the frequency parameter.
        __HAL_TIM_SET_AUTORELOAD(this -> htim_handle, timer_reload_count);
    }


    void stepper_motor_controller::calculate_timer_frequency(uint32_t motor_rpm)
    {  
        //Calculate the timer output frequency based on the motor rpm and 
        //the number of steps per revolution   
        this -> timer_output_freq = motor_rpm * (this -> motor_steps) / (60);
    }

}
