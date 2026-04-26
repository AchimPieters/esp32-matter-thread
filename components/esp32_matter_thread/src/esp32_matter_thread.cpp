#include "esp32_matter_thread.h"

#include <driver/gpio.h>
#include <esp_check.h>
#include <esp_log.h>

static const char *TAG = "esp32_matter_thread";
static int s_led_gpio = -1;
static bool s_active_low = false;
static bool s_led_on = false;

static int physical_level(bool on) { return s_active_low ? (on ? 0 : 1) : (on ? 1 : 0); }

esp_err_t esp32_matter_thread_led_driver_init(const esp32_matter_thread_led_config_t *config) {
    if (config == nullptr || config->led_gpio < 0) {
        return ESP_ERR_INVALID_ARG;
    }

    s_led_gpio = config->led_gpio;
    s_active_low = config->active_low;
    s_led_on = false;

    gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = (1ULL << s_led_gpio);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;

    ESP_RETURN_ON_ERROR(gpio_config(&io_conf), TAG, "Failed to configure LED GPIO");
    ESP_RETURN_ON_ERROR(gpio_set_level((gpio_num_t)s_led_gpio, physical_level(false)), TAG,
                        "Failed to set initial LED state");

    ESP_LOGI(TAG, "LED GPIO initialized on pin %d (active_%s)", s_led_gpio, s_active_low ? "low" : "high");
    return ESP_OK;
}

esp_err_t esp32_matter_thread_led_set(bool on) {
    if (s_led_gpio < 0) {
        return ESP_ERR_INVALID_STATE;
    }

    s_led_on = on;
    return gpio_set_level((gpio_num_t)s_led_gpio, physical_level(on));
}

bool esp32_matter_thread_led_get(void) { return s_led_on; }
