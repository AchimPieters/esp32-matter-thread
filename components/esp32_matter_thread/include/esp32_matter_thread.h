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

typedef enum {
    ESP32_MATTER_THREAD_ACCESSORY_ON_OFF_LIGHT = 0,
} esp32_matter_thread_accessory_type_t;

typedef struct {
    esp32_matter_thread_accessory_type_t accessory_type;
    int primary_gpio;
    bool primary_gpio_active_low;
    bool print_onboarding_codes;
} esp32_matter_thread_config_t;

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

/**
 * @brief Return a safe default config for fast onboarding.
 */
esp32_matter_thread_config_t esp32_matter_thread_default_config(void);

/**
 * @brief Start Matter + Thread stack for a supported accessory type.
 *
 * This function handles:
 * - NVS init (with common recovery flow)
 * - GPIO driver init for supported accessory type(s)
 * - Matter node/endpoint creation
 * - `esp_matter::start()`
 * - Optional onboarding QR/manual code print
 */
esp_err_t esp32_matter_thread_start(const esp32_matter_thread_config_t *config);

/**
 * @brief Convenience wrapper for the most common case: one On/Off light GPIO.
 */
esp_err_t esp32_matter_thread_start_on_off_light(int gpio, bool active_low, bool print_onboarding_codes);

#ifdef __cplusplus
}
#endif
