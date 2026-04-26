#include "esp32_matter_thread.h"

#include <app-common/zap-generated/attributes/Accessors.h>
#include <driver/gpio.h>
#include <esp_log.h>

static const char *TAG = "esp32_matter_thread";
static int s_led_gpio = -1;

esp_err_t esp32_matter_thread_led_driver_init(const esp32_matter_thread_led_config_t *config)
{
    if (config == nullptr || config->led_gpio < 0) {
        return ESP_ERR_INVALID_ARG;
    }

    s_led_gpio = config->led_gpio;

    gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = (1ULL << s_led_gpio);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;

    ESP_RETURN_ON_ERROR(gpio_config(&io_conf), TAG, "Failed to configure LED GPIO");
    ESP_RETURN_ON_ERROR(gpio_set_level((gpio_num_t)s_led_gpio, 0), TAG, "Failed to set initial LED state");

    ESP_LOGI(TAG, "LED GPIO initialized on pin %d", s_led_gpio);
    return ESP_OK;
}

esp_err_t esp32_matter_thread_led_set(bool on)
{
    if (s_led_gpio < 0) {
        return ESP_ERR_INVALID_STATE;
    }

    return gpio_set_level((gpio_num_t)s_led_gpio, on ? 1 : 0);
}
