RGB_MATRIX_EFFECT(outrun_sunset)


#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#ifndef LED_FLAG_KEYS
#define LED_FLAG_KEYS (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER)
#endif

static bool outrun_sunset(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  // Blank out the colors on initialization.
  if (params->init) {
    rgb_matrix_set_color_all(0, 0, 0);
  }

  // Define border gradient colors. Colors are packed in GRB order.
  HSV border_start_hsv = { 253, 250, 252 };
  HSV border_end_hsv = { 177, 250, 255 };
  // RGB border_start_color = { 10, 252, 26 };
  // RGB border_end_color = { 5, 104, 242 };

  for (uint8_t i = led_min; i < led_max; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();

    HSV hsv = rgb_matrix_config.hsv;

    if (i >= 19 && i < 23) {
      hsv.h = 34;
      hsv.s = 0.98f * hsv.s; //166;
      hsv.v = 1.0f * hsv.v;
    } else if (i >= 33 && i < 39) {
      hsv.h = 13;
      hsv.s = 0.9f * hsv.s; //145;
      hsv.v = 0.98f * hsv.v; //245;
    } else if (i >= 46 && i < 53) {
      hsv.h = 247;
      hsv.s = 0.87f * hsv.s; //163;
      hsv.v = 0.95f * hsv.v; //237;
    } else if (i >= 60 && i < 63) {
      hsv.h = 239;
      hsv.s = 0.92f * hsv.s; //199;
      hsv.v = 0.89f * hsv.v; //227;
    } else {
      hsv.h = 187;
      hsv.s = 0.67f * hsv.s; //130;
      hsv.v = 0.27f * hsv.v; //69;
    }

    RGB rgb;

    if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
      border_start_hsv.v = 0.98f * rgb_matrix_config.hsv.v;
      border_end_hsv.v = 1.0f * rgb_matrix_config.hsv.v;
      RGB border_start_color = hsv_to_rgb(border_start_hsv);
      RGB border_end_color = hsv_to_rgb(border_end_hsv);

      // Calculate border gradient color at current height.
      uint8_t frac = 255.0f * (g_led_config.point[i].y / 64.0f);
      rgb.r = blend8(border_start_color.r, border_end_color.r, frac);
      rgb.g = blend8(border_start_color.g, border_end_color.g, frac);
      rgb.b = blend8(border_start_color.b, border_end_color.b, frac);
    } else {
      // Otherwise convert HSV to RGB.
      rgb = hsv_to_rgb(hsv);
    }

    // Finally set the color.
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }

  return rgb_matrix_check_finished_leds(led_max);
}




#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS