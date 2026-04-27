idf_component_register(
    SRCS "src/esp32_matter_thread.cpp"
    INCLUDE_DIRS "include"
    REQUIRES driver espressif__esp_matter nvs_flash
)
