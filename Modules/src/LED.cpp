#include "LED.h"
#include "cmsis_os.h"

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

    void LED::toggle_callback() //toggle LED each time timer expired
    {   
         STM32LED::toggle();
    }
    //Call this function in main, and this function should also be inside the class.

    void LED::timer_init()
    {   //Do I need the LED:: thing here?
        lED::blink_id = osTimerCreate (osTimer(periodic_blink), osTimerPeriodic, NULL);
        if (LED::status != osOK)  {
                // timer could not be started
            }
    }

    void LED::set(state s) //set the state of the LEDs
    {
        int timer_delay = 1000;

        this->LED_state = s;
        if(s == state::on)
        {
            HAL_GPIO_WritePin(this->gpio_port, this->gpio_pin, GPIO_PIN_SET);
            LED::status = osTimerStop (LED::blink_id);                               // stop timer
            if (LED::status != osOK)  {
                // Timer could not be stopped
            }
        }
        else if(s == state::off)
        {
            HAL_GPIO_WritePin(this->gpio_port, this->gpio_pin, GPIO_PIN_RESET);
            LED::status = osTimerStop (LED::blink_id);                               // stop timer
            if (LED::status != osOK)  {
                // Timer could not be stopped
            }
        }
        else if(s == state::blink)
        {
            //set timer to execute callback function when it expires
            LED::status = osTimerStart (LED::blink_id, timer_delay); 
            
            if (LED::status != osOK)  {
                // timer could not be started
            }

            // keep LED off for now
            HAL_GPIO_WritePin(this->gpio_port, this->gpio_pin, GPIO_PIN_RESET);
        }
    }
    
    void LED::toggle()
    {
        // this->LED_state = (this->LED_state == state::on) ? state::off : state::on;
        if(this -> LED_state == state::on)    this->LED_state = state::off;
        if(this -> LED_state == state::off)    this->LED_state = state::on;
        HAL_GPIO_TogglePin(this->gpio_port, this->gpio_pin);
    }

    //manipulates the states for all three LEDs at the same time
    //this function cannot be inside the class, it should only be inside the namespace 
    void setMode(LED * LED1, LED * LED2, LED* LED3, state s)
    {
        LED1->set(s);
        LED2->set(s);
        LED3->set(s);
    }

}

