/*
 * Compatibility shim component for ESP-IDF v6+ where legacy 'json'
 * component name is no longer available as built-in.
 *
 * This component intentionally provides no runtime logic and only exists
 * to satisfy component dependency resolution for third-party components
 * that still require a component named "json".
 */

void esp32_matter_thread_json_shim_keep_compiler_happy(void) {}
