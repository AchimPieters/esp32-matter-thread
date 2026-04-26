#pragma once

#include <esp_err.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int led_gpio;
    bool active_low;
} esp32_matter_thread_led_config_t;

/**
 * @brief Initialize board GPIO state used by the LED Matter endpoint.
 */
esp_err_t esp32_matter_thread_led_driver_init(const esp32_matter_thread_led_config_t *config);

/**
 * @brief Set the physical LED state.
 */
esp_err_t esp32_matter_thread_led_set(bool on);

/**
 * @brief Return last requested logical LED state.
 */
bool esp32_matter_thread_led_get(void);

/**
 * @brief Initialize default NVS partition with recovery for common version/page errors.
 */
esp_err_t esp32_matter_thread_init_nvs(void);

/**
 * @brief Print Matter onboarding payloads for Thread rendezvous (QR + manual code).
 */
void esp32_matter_thread_print_onboarding_codes_thread(void);

#ifdef __cplusplus
}
#endif
