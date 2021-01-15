/*
 * Copyright (c) 2020, Patrick Moffitt <patrick@moffitt.com>
 * Copyright (c) 2018 Bosch Sensortec GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * i2c interface for the Feather nRF52840 Express and the
 * Adafruit BME680
 */

#ifndef FEATHER_NRF52840_I2C_BME680_H
#define FEATHER_NRF52840_I2C_BME680_H

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <drivers/sensor.h>
#include <init.h>
#include <logging/log.h>

#define BME680_PWR_INIT_PRIORITY 0U
#define BME680_TEMP_CALIBRATION -1.4f
#define BT_UUID_RESISTANCE_OHMS 0x272A
#ifndef BT_CPF_UNIT_INT32
#define BT_CPF_UNIT_INT32 0x08 // BLE_GATT_CPF_FORMAT_UINT32
#endif

/* Temperature calibration values. */
extern const struct sensor_value temp_calib;

/* Exported for bt_gatt_config::update_sensor_data() */
extern const struct device *dev_bme680;

extern int bme680_power_on();
extern int bme680_power_off();
extern int bind_dev_bme680();

#endif //FEATHER_NRF52840_I2C_BME680_H