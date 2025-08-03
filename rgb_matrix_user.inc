RGB_MATRIX_EFFECT(outrun_sunset)
RGB_MATRIX_EFFECT(orange_phosphor)


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

static bool orange_phosphor(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  // Blank out the colors on initialization.
  if (params->init) {
    rgb_matrix_set_color_all(0, 0, 0);
  }

  // Orange phosphor CRT colors - orange gradient for border
  HSV border_start_hsv = { 25, 255, 200 };  // Deep orange
  HSV border_end_hsv = { 25, 255, 255 };    // Bright orange/amber

  for (uint8_t i = led_min; i < led_max; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();

    HSV hsv = rgb_matrix_config.hsv;
    
    // Create vertical gradient from top (brightest) to bottom (25% brightness)
    // Get the Y position of the current LED (0 = top, 64 = bottom)
    uint8_t led_y = g_led_config.point[i].y;
    
    // Calculate brightness based on Y position
    // Top (y=0) = 100% brightness, Bottom (y=64) = 25% brightness
    float brightness_factor = 1.0f - (0.75f * (led_y / 64.0f));
    
    // Set orange phosphor color for all keys
    hsv.h = 25;                             // Orange/amber hue
    hsv.s = 0.95f * hsv.s;                  // High saturation
    hsv.v = brightness_factor * hsv.v;       // Gradient brightness

    RGB rgb;

    if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
      // Orange border gradient for underglow (darkened by 30%)
      border_start_hsv.v = 0.56f * rgb_matrix_config.hsv.v;  // 0.80 * 0.70 = 0.56
      border_end_hsv.v = 0.70f * rgb_matrix_config.hsv.v;    // 1.0 * 0.70 = 0.70
      RGB border_start_color = hsv_to_rgb(border_start_hsv);
      RGB border_end_color = hsv_to_rgb(border_end_hsv);

      // Calculate border gradient color based on position
      uint8_t frac = 255.0f * (g_led_config.point[i].y / 64.0f);
      rgb.r = blend8(border_start_color.r, border_end_color.r, frac);
      rgb.g = blend8(border_start_color.g, border_end_color.g, frac);
      rgb.b = blend8(border_start_color.b, border_end_color.b, frac);
    } else {
      // Convert HSV to RGB for keys
      rgb = hsv_to_rgb(hsv);
    }

    // Set the LED color
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }

  return rgb_matrix_check_finished_leds(led_max);
}


#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS