#include "LED.h"
#include "stm32h7xx_hal.h"

namespace STM32LED
{
    LED* LED2;
    LED* LED3;

    LED::LED(GPIO_TypeDef* gpio_port, uint16_t gpio_pin)
    {
        this->gpio_port = gpio_port;
        this->gpio_pin = gpio_pin;
        this->LED_state = state::off;   //default state is off
    }

    //checks current state - if 
    void LED::set(state s)
    {
        if (s == state::on)
        {
            LED_state = state::on;
            HAL_GPIO_WritePin(gpio_port, gpio_pin, GPIO_PIN_SET);    //turn on the LED
        }
        else if (s == state::off)
        {
            LED_state = state::off;
            HAL_GPIO_WritePin(gpio_port, gpio_pin, GPIO_PIN_RESET);  //turn off the LED
        }
        return;
    }

    //toggles LED based on whether button was pressed or not
    //Checks for button press - then sets appropriate state
    void LED::toggle()  
    {
        if (LED_state == state::on)
        {
            set(state::off);
            //HAL_Delay(500);
        }
        else
        {
            set(state::on);
            //HAL_Delay(500);
        }
       return;
    }

}