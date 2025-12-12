#ifndef __LED_BLINK_HPP
#define __LED_BLINK_HPP

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
//#include "stm32f2xx_hal_gpio.h"
#include "cmsis_os.h"

#ifdef __cplusplus
}
#endif

#include <vector>

enum color_t{
    green,
    blue,
    red
};
enum state_t{
  disabled,
  on_s,
  off_s,
  blink_s
};

class led{
public:
    explicit led(color_t c);
    ~led();
    int on();
    int off();
    int blink(uint32_t period_ms);
    state_t status() const { return st; } 
private:
  color_t clr;
  state_t st;
  uint32_t pin;
  GPIO_TypeDef * port;
  std::vector<osTimerId_t> timers;
};

#endif  // __LED_BLINK_HPP