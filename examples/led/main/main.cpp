#include <esp_err.h>
#include <esp_log.h>
#include <sdkconfig.h>

#include "esp32_matter_thread.h"

static const char *TAG = "led_example";

extern "C" void app_main(void) {
    ESP_ERROR_CHECK(
        esp32_matter_thread_start_on_off_light(CONFIG_EXAMPLE_LED_GPIO, CONFIG_EXAMPLE_LED_ACTIVE_LOW, true));

    ESP_LOGI(TAG, "Matter LED accessory started (GPIO=%d, active_%s)", CONFIG_EXAMPLE_LED_GPIO,
             CONFIG_EXAMPLE_LED_ACTIVE_LOW ? "low" : "high");
}
