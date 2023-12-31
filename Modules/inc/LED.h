#ifndef LED_H
#define LED_H

#include "stm32h7xx_hal.h"

namespace STM32LED
{
    enum class state
    {
        on,
        off
    };

    class LED
    {
        public:
            LED(GPIO_TypeDef* gpio_port, uint16_t gpio_pin);
            void set(state s);
            void toggle();
            state LED_state;

        protected:
            GPIO_TypeDef* gpio_port;
            uint16_t gpio_pin;
    };
    
    extern LED* LED1;
    extern LED* LED2;
    extern LED* LED3;
}

#endif
