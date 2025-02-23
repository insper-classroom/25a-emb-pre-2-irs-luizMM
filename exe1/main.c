#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
volatile int btn_pressed;
volatile int fall_edge;
volatile int rise_edge;

void btn_callback(uint gpio, uint32_t events) {
  btn_pressed = 1;
  if (events == 0x4) { // fall edge
    fall_edge = 1;
  } else if (events == 0x8) { // rise edge
    rise_edge = 1;
  }
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_set_irq_enabled_with_callback(
      BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  while (true) {
    if (btn_pressed){
      if (fall_edge){
        printf("fall \n");
        fall_edge = 0;
      }
      if (rise_edge){
        printf("rise \n");
        rise_edge = 0;
      }
      btn_pressed = 0;
    }
  }
}
