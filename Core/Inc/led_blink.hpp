#ifndef __LED_BLINK_HPP
#define __LED_BLINK_HPP

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f2xx_hal_gpio.h"
#include "cmsis_os.h"

#ifdef __cplusplus
}
#endif

enum color_t{
    green,
    blue,
    red
};
enum state_t{
  disabled,
  on,
  off,
  blink
};

class led{
public:
    explicit led(color_t c);
    ~led();
private:
  color_t clr;
  state_t st;
  uint32_t pin;
  GPIO_TypeDef * port;
};

#endif  // __LED_BLINK_HPP