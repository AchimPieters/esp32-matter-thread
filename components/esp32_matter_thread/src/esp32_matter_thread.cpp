#include "esp32_matter_thread.h"

#include <app/server/OnboardingCodesUtil.h>
#include <app-common/zap-generated/attributes/Accessors.h>
#include <driver/gpio.h>
#include <esp_check.h>
#include <esp_log.h>
#include <esp_matter.h>
#include <nvs_flash.h>

static const char *TAG = "esp32_matter_thread";
static int s_led_gpio = -1;
static bool s_active_low = false;
static bool s_led_on = false;
static bool s_started = false;

static int physical_level(bool on) { return s_active_low ? (on ? 0 : 1) : (on ? 1 : 0); }

static esp_err_t matter_attribute_update_cb(esp_matter::callback_type_t type, uint16_t endpoint_id, uint32_t cluster_id,
                                            uint32_t attribute_id, esp_matter_attr_val_t *val, void *priv_data) {
    (void)endpoint_id;
    (void)priv_data;
    if (type != esp_matter::PRE_UPDATE || cluster_id != esp_matter::cluster::OnOff::Id ||
        attribute_id != esp_matter::cluster::OnOff::Attributes::OnOff::Id || val == nullptr) {
        return ESP_OK;
    }
    return esp32_matter_thread_led_set(val->val.b);
}

esp_err_t esp32_matter_thread_led_driver_init(const esp32_matter_thread_led_config_t *config) {
    if (config == nullptr || !GPIO_IS_VALID_OUTPUT_GPIO(config->led_gpio)) {
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

esp_err_t esp32_matter_thread_init_nvs(void) {
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_RETURN_ON_ERROR(nvs_flash_erase(), TAG, "Failed to erase NVS after init error");
        err = nvs_flash_init();
    }
    return err;
}

void esp32_matter_thread_print_onboarding_codes_thread(void) {
    chip::RendezvousInformationFlags rendezvous_flags(chip::RendezvousInformationFlag::kThread);
    chip::PrintOnboardingCodes(rendezvous_flags);
}

esp32_matter_thread_config_t esp32_matter_thread_default_config(void) {
    esp32_matter_thread_config_t config = {};
    config.accessory_type = ESP32_MATTER_THREAD_ACCESSORY_ON_OFF_LIGHT;
    config.primary_gpio = 8;
    config.primary_gpio_active_low = false;
    config.print_onboarding_codes = true;
    return config;
}

esp_err_t esp32_matter_thread_start(const esp32_matter_thread_config_t *config) {
    if (config == nullptr) {
        return ESP_ERR_INVALID_ARG;
    }
    if (s_started) {
        return ESP_ERR_INVALID_STATE;
    }

    ESP_RETURN_ON_ERROR(esp32_matter_thread_init_nvs(), TAG, "NVS init failed");

    if (config->accessory_type != ESP32_MATTER_THREAD_ACCESSORY_ON_OFF_LIGHT) {
        return ESP_ERR_NOT_SUPPORTED;
    }

    const esp32_matter_thread_led_config_t led_config = {
        .led_gpio = config->primary_gpio,
        .active_low = config->primary_gpio_active_low,
    };
    ESP_RETURN_ON_ERROR(esp32_matter_thread_led_driver_init(&led_config), TAG, "LED driver init failed");

    esp_matter::node::config_t node_config = {};
    esp_matter::node_t *node = esp_matter::node::create(&node_config, matter_attribute_update_cb, nullptr);
    if (node == nullptr) {
        return ESP_FAIL;
    }

    esp_matter::endpoint::on_off_light::config_t light_config = {};
    esp_matter::endpoint_t *light_endpoint =
        esp_matter::endpoint::on_off_light::create(node, &light_config, ENDPOINT_FLAG_NONE, nullptr);
    if (light_endpoint == nullptr) {
        return ESP_FAIL;
    }

    ESP_RETURN_ON_ERROR(esp_matter::start(nullptr), TAG, "esp_matter start failed");
    s_started = true;

    if (config->print_onboarding_codes) {
        esp32_matter_thread_print_onboarding_codes_thread();
    }

    ESP_LOGI(TAG, "Matter accessory started type=%d gpio=%d active_%s", config->accessory_type, config->primary_gpio,
             config->primary_gpio_active_low ? "low" : "high");
    return ESP_OK;
}

esp_err_t esp32_matter_thread_start_on_off_light(int gpio, bool active_low, bool print_onboarding_codes) {
    esp32_matter_thread_config_t config = esp32_matter_thread_default_config();
    config.accessory_type = ESP32_MATTER_THREAD_ACCESSORY_ON_OFF_LIGHT;
    config.primary_gpio = gpio;
    config.primary_gpio_active_low = active_low;
    config.print_onboarding_codes = print_onboarding_codes;
    return esp32_matter_thread_start(&config);
}
