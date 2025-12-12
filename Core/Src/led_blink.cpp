#include "led_blink.hpp"

led::led(color_t c) :
    clr(c)
,   st(disabled)
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
    st = off;
}

led::~led() {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = pin;
    HAL_GPIO_deInit(port, &GPIO_InitStruct);
    st = disabled;
}

/*
  Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin 
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
*/