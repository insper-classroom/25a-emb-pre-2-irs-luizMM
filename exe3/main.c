#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;
volatile int btn_pressed = 0;
volatile int r_pressed = 0;
volatile int g_pressed = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    btn_pressed = 1;
    if (gpio == BTN_PIN_R)
      r_pressed = 1;
    else if (gpio == BTN_PIN_G)
      g_pressed = 1;
  }
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);

  // callback led r (first)
  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true,
                                     &btn_callback);

  // callback led g (nao usar _with_callback)
  gpio_set_irq_enabled(BTN_PIN_G, GPIO_IRQ_EDGE_FALL, true);

  while (true) {
    if (btn_pressed){
      if (r_pressed){
        printf("fall red\n");
        r_pressed = 0;
      }
      if (g_pressed){
        printf("fall green\n");
        g_pressed = 0;
      }
      btn_pressed = 0;
    }
  }
}
