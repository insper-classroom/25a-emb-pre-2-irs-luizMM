#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;
const int OUT_PIN_R = 4;
const int OUT_PIN_G = 6;

volatile int btn_pressed = 0;
volatile int r_pressed = 0;
volatile int g_pressed = 0;


void btn_callback(uint gpio, uint32_t events){
  if (events == 0x4){
    r_pressed = 1;
  } else if (events == 0x8){
    g_pressed = 1;
  }
  btn_pressed = 1;
}

int main() {
  int r_state = 0;
  int g_state = 0;
  
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_init(BTN_PIN_G);
  gpio_init(OUT_PIN_R);
  gpio_init(OUT_PIN_G);

  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_set_dir(OUT_PIN_R, GPIO_OUT);
  gpio_set_dir(OUT_PIN_G, GPIO_OUT);

  gpio_pull_up(BTN_PIN_R);
  gpio_pull_up(BTN_PIN_G);

  gpio_set_irq_enabled_with_callback(
    BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  gpio_set_irq_enabled_with_callback(
    BTN_PIN_G, GPIO_IRQ_EDGE_RISE, true, &btn_callback);

  
  while (true) {
    if (btn_pressed){
      if (r_pressed){
        r_state = !r_state;
        gpio_put(OUT_PIN_R, r_state);
        r_pressed = 0;
      }
      if (g_pressed){
        g_state = !g_state;
        gpio_put(OUT_PIN_G, g_state);
        g_pressed = 0;
      }
      btn_pressed = 0;
    }
  }
}
