/* I2C Slave
 *
*/

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"

#include "nvs.h"
#include "nvs_flash.h"
#include "i2c_slave.h"

#define SDA_GPIO 32
#define SCL_GPIO 33

void app_main()
{
    /*
     * NVS Initialization
     */
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // OTA app partition table has a smaller NVS partition size than the non-OTA
        // partition table. This size mismatch may cause NVS initialization to fail.
        // If this happens, we erase NVS partition and initialize NVS again.
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );



    //xTaskCreatePinnedToCore(&ota_z, "ota_z", 8192, &ota_conf[0], 3, NULL, 0);
    //vTaskDelay(2000 / portTICK_RATE_MS);
    //xTaskCreatePinnedToCore(&ds3231_test, "ds3231_test", configMINIMAL_STACK_SIZE * 3, NULL, 4, NULL, 1);
    xTaskCreatePinnedToCore(&i2c_slave, "i2c_slave", configMINIMAL_STACK_SIZE * 3, NULL, 4, NULL, 1);
}
