#pragma once

#include <esp_err.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int led_gpio;
} esp32_matter_thread_led_config_t;

/**
 * @brief Initialize board GPIO state used by the LED Matter endpoint.
 */
esp_err_t esp32_matter_thread_led_driver_init(const esp32_matter_thread_led_config_t *config);

/**
 * @brief Set the physical LED state.
 */
esp_err_t esp32_matter_thread_led_set(bool on);

#ifdef __cplusplus
}
#endif
