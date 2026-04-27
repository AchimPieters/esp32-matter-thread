/*
 * ESP-IDF v6 removed the legacy component name "json".
 * Some esp_matter versions still require a component called "json".
 *
 * This shim restores that component name and forwards to built-in `cjson`.
 */
void esp32_matter_thread_json_component_shim(void) {}
