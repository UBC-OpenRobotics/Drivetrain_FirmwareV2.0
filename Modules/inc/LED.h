#ifndef LED_H
#define LED_H

#include "stm32h7xx_hal.h"
#include "cmsis_os.h"

namespace STM32LED
{
    enum class state
    {
        on,
        off,
        blink
    };

    class LED
    {
        public:
            LED(GPIO_TypeDef* gpio_port, uint16_t gpio_pin);
            void set(state s);
            static void toggle(LED* led);
            static void toggle_callback(void* led);
            void timer_init();

            osTimerId_t blink_id;
            osStatus_t status;// Pleease defiene this in the class as a private attributes,            
            state LED_state;

            // osTimerDef(periodic_blink, toggle);   // when the timer expires, the function toggle_power is called

        protected:
            GPIO_TypeDef* gpio_port;
            uint16_t gpio_pin;
    };
    
    extern LED* LED1;
    extern LED* LED2;
    extern LED* LED3;
    //setmode()should be in here 
    void setMode(LED * LED1, LED * LED2, LED* LED3, state s);
}

#endif
