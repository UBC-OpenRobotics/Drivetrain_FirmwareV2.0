/*Don't know what these do, but they were in other files, so I assume they
have some importance*/
#ifndef motorControl_H
#define motorControl_H

/*STM32 library*/
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_tim.h"

/* namespace and class defining for motorControl */
namespace STM32_motorcontrol
{
    class motorcontrol
    {
        public:
            /* Defining attributes/fields
            motorC = motor control */
            GPIO_TypeDef* motorc_port;
            uint16_t motorc_pin;

            /* Contstuctor for port and pin assignment/definition */
            motorcontrol(GPIO_TypeDef* gpio_port, uint16_t gpio_pin, TIM_HandleTypeDef* htim_handle);

            void timer_start();
            void timer_stop();
            void adjust_timer_frequency();
            void calculate_timer_frequency(uint16_t motor_rpm);

        protected:  
            const uint16_t motorsteps = 200; //Number of steps per revolution; defined by the hardware stepper motor driver
            uint32_t timer_freq;
            TIM_HandleTypeDef*   htim_handle; //Hardware timer handle
            const uint32_t clk_freq = 1000000; //set clk frequency

    };

    extern motorControl* motorC1;


}

#endif