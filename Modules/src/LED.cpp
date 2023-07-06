#include "LED.h"

namespace STM32LED
{
    LED* LED1;
    LED* LED2;
    LED* LED3;

    LED::LED(GPIO_TypeDef* gpio_port, uint16_t gpio_pin)
    {
        this->gpio_port = gpio_port;
        this->gpio_pin = gpio_pin;
        this->LED_state = state::off;   //default state is off
    }

    void LED::set(state s)
    {
        this->LED_state = s;
        if(s == state::on)
        {
            HAL_GPIO_WritePin(this->gpio_port, this->gpio_pin, GPIO_PIN_SET);
        }
        else
        {
            HAL_GPIO_WritePin(this->gpio_port, this->gpio_pin, GPIO_PIN_RESET);
        }
    }

    void LED::toggle()
    {
        this->LED_state = (this->LED_state == state::on) ? state::off : state::on;
        HAL_GPIO_TogglePin(this->gpio_port, this->gpio_pin);
    }

}