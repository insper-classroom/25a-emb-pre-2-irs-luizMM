#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int PIN_R_OUT = 4;
volatile int btn_pressed = 0;
int btn_state = 0;

void btn_callback(uint gpio, uint32_t events){
  if (events == 0x4){
    btn_pressed = 1;
  }
}


int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_init(PIN_R_OUT);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_set_dir(PIN_R_OUT, GPIO_OUT);
  gpio_pull_up(BTN_PIN_R);

  gpio_set_irq_enabled_with_callback(
    BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true, &btn_callback);


  while (true) {
    if (btn_pressed){
      btn_state = !btn_state;
      gpio_put(PIN_R_OUT, btn_state);
      btn_pressed = 0;
    }
  }
}
