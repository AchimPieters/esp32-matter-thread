idf_component_register(
    SRCS "src/esp32_matter_thread.cpp"
    INCLUDE_DIRS "include"
    REQUIRES esp_driver_gpio espressif__esp_matter
)
