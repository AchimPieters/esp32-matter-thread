#include <app-common/zap-generated/attributes/Accessors.h>
#include <esp_err.h>
#include <esp_log.h>
#include <esp_matter.h>
#include <nvs_flash.h>

#include "esp32_matter_thread.h"

using namespace esp_matter;
using namespace esp_matter::cluster;
using namespace esp_matter::endpoint;

static const char *TAG = "led_example";
static constexpr int kDefaultLedGpio = 8;

static esp_err_t app_attribute_update_cb(callback_type_t type, uint16_t endpoint_id, uint32_t cluster_id,
                                         uint32_t attribute_id, esp_matter_attr_val_t *val, void *priv_data)
{
    if (type != PRE_UPDATE || cluster_id != OnOff::Id || attribute_id != OnOff::Attributes::OnOff::Id || val == nullptr) {
        return ESP_OK;
    }

    const bool on = val->val.b;
    ESP_LOGI(TAG, "OnOff update: endpoint=%u value=%s", endpoint_id, on ? "ON" : "OFF");
    return esp32_matter_thread_led_set(on);
}

extern "C" void app_main(void)
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    esp32_matter_thread_led_config_t led_cfg = {
        .led_gpio = kDefaultLedGpio,
    };
    ESP_ERROR_CHECK(esp32_matter_thread_led_driver_init(&led_cfg));

    node::config_t node_config = {};
    node_t *node = node::create(&node_config, app_attribute_update_cb, nullptr);
    ESP_ERROR_CHECK(node != nullptr ? ESP_OK : ESP_FAIL);

    on_off_light::config_t light_config = {};
    endpoint_t *light_endpoint = on_off_light::create(node, &light_config, ENDPOINT_FLAG_NONE, nullptr);
    ESP_ERROR_CHECK(light_endpoint != nullptr ? ESP_OK : ESP_FAIL);

    ESP_ERROR_CHECK(esp_matter::start(nullptr));

    ESP_LOGI(TAG, "Matter LED accessory started (GPIO=%d)", kDefaultLedGpio);
}
