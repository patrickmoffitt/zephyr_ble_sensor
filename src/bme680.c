/*
 * Copyright (c) 2020, Patrick Moffitt <patrick@moffitt.com>
 * Copyright (c) 2018 Bosch Sensortec GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * i2c interface for the Feather nRF52840 Express and the
 * Adafruit BME680
 */

#include "bme680.h"
LOG_MODULE_REGISTER(dev_bme680);

// Sensor BME680
const struct device *dev_bme680;

const struct sensor_value temp_calib = {-1, -0.4};

/*
 * @brief Turn the BME680 sensor on.
 *
 * @return 0 on success or negative error value.
 */
int bme680_power_on() {
    // GPIO Controller 0
    const struct device *gpio_0;
    const char *dev_gpio0_label =
            DT_LABEL(DT_INST(0, nordic_nrf_gpio));
    gpio_0 = device_get_binding(dev_gpio0_label);
    if (gpio_0 == NULL) {
        LOG_ERR("Failed to bind %s device.\n", dev_gpio0_label);
        return -EINVAL;
    }
    LOG_INF("Bound device %s.\n", dev_gpio0_label);
    gpio_pin_t a0 = 4;
    uint32_t flags = GPIO_OUTPUT_HIGH;
    int return_code = gpio_pin_configure(gpio_0, a0, flags);
    if (return_code < 0) {
        LOG_ERR("Failed to configure pins for %s device.\n", dev_gpio0_label);
        return return_code;
    }
    LOG_INF("Set pin %d on device %s.\n", a0, dev_gpio0_label);
    return 0;
}

/*
 * @brief Save power by turning the BME680 sensor off.
 *
 * @return 0 on success or negative error value.
 */
int bme680_power_off(){
    const struct device *gpio_0;
    const char *dev_gpio0_label =
            DT_LABEL(DT_INST(0, nordic_nrf_gpio));
    gpio_0 = device_get_binding(dev_gpio0_label);
    if (gpio_0 == NULL) {
        LOG_ERR("Failed to bind %s device.\n", dev_gpio0_label);
        return -EINVAL;
    }
    LOG_INF("Bound device %s.\n", dev_gpio0_label);
    gpio_pin_t a0 = 4;
    uint32_t flags = GPIO_INPUT | GPIO_PULL_DOWN;
    int return_code = gpio_pin_configure(gpio_0, a0, flags);
    if (return_code < 0) {
        LOG_ERR("Failed to configure pins for %s device.\n", dev_gpio0_label);
        return return_code;
    }
    LOG_INF("Set pin %d on device %s.\n", a0, dev_gpio0_label);
    return 0;
}

SYS_INIT(bme680_power_on, PRE_KERNEL_2, BME680_PWR_INIT_PRIORITY);

/*
 * @brief Bind BME680 sensor to device struct
 *
 * @return -EINVAL if label is not found or can't be used or 0 on success.
 */
int bind_dev_bme680(){
    const char *dev_bme680_label =
            DT_LABEL(DT_INST(0, bosch_bme680));
    dev_bme680 = device_get_binding(dev_bme680_label);
    if (dev_bme680 == NULL) {
        LOG_ERR("Failed to bind %s device.\n", dev_bme680_label);
        return -EINVAL;
    }
    LOG_INF("Bound device %s\n", dev_bme680->name);
    return 0;
}

