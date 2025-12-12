#include "led_blink.hpp"

led::led(color_t c) :
    clr(c)
    ,st(disabled)
    ,timers(1)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    switch(clr){
        case green: 
            pin = LD1_Pin;
            port = GPIOB;
        break;
        case blue:
            pin = LD2_Pin;
            port = GPIOB;            
        break;
        case red:
            pin = LD3_Pin;
            port = GPIOB;
        break;
    }
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(port, &GPIO_InitStruct);
    st = off_s;
}

led::~led() {
    HAL_GPIO_DeInit(port, pin);
    st = disabled;
    for(auto t : timers){
        osTimerDelete(t);
    }       
}
int led::on() {
    if(st == blink_s){
        for(auto t : timers)
            osTimerDelete(t);
        timers.clear();     
    }
    HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
    st = on_s;
    return 0;
}       
int led::off(){
    if(st == blink_s){
        for(auto t : timers)
            osTimerDelete(t);
        timers.clear();     
    }
    HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
    st = off_s;
    return 0;   
}
int led::blink(uint32_t period_ms) {
    if(st == blink_s){
        for(auto t : timers)
            osTimerDelete(t);
        timers.clear();     
    }   
    // Create timer
    osTimerId_t t = osTimerNew(
        [](void *argument){
            led * l = static_cast<led*>(argument);
            HAL_GPIO_TogglePin(l->port, l->pin);
        },
        osTimerPeriodic,
        this,
        nullptr
    );
    if(t == nullptr){
        return -1; // Error creating timer
    }
    timers.push_back(t);
    osTimerStart(t, period_ms);
    st = blink_s;
    return 0;
}   

