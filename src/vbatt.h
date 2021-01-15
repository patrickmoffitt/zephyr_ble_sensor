/*
 * Copyright (c) 2020, Patrick Moffitt <patrick@moffitt.com>
 * Copyright (c) 2018-2019 Peter Bigot Consulting, LLC
 * Copyright (c) 2019-2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Voltage divider interface for the Feather nRF52840 Express.
 */

#ifndef FEATHER_NRF52840_DEVICE_CONFIG_H
#define FEATHER_NRF52840_DEVICE_CONFIG_H

#include <zephyr.h>
#include <stdio.h>
#include <device.h>
#include <devicetree.h>
#include <sys/printk.h>
#include <drivers/gpio.h>
#include <drivers/adc.h>
#include "vbatt.h"
#include <logging/log.h>

#define VDIV            DT_ALIAS(vdiv)
#if DT_NODE_HAS_STATUS(VDIV, okay)
#define VDIV_LABEL      DT_LABEL(VDIV)
#define VDIV_ADC_LABEL  DT_IO_CHANNELS_LABEL(VDIV)
#define VDIV_ADC_CHAN   DT_IO_CHANNELS_INPUT(VDIV)
#define VDIV_GPIO_LABEL DT_GPIO_LABEL(VDIV, power_gpios)
#define VDIV_GPIO_PIN   DT_PHA_BY_IDX(VDIV, power_gpios, 0, pin)
#define VDIV_GPIO_FLAGS GPIO_OUTPUT_INACTIVE
#define VDIV_STATUS     DT_PROP(VDIV, status)
#else
#error "No voltage divider found in the device tree."
#endif

/* The Feather's twin 100KΩ VDIV divides by 2. */
#define VDIV_DIVISOR 2

/* https://infocenter.nordicsemi.com/topic/ps_nrf52840/saadc.html?cp=4_0_0_5_22 */
#define NRF52840_ADC_GAIN_RATIO_1_6 6
#define NRF52840_ADC_RESOLUTION     14U
#define NRF52840_ADC_OVERSAMPLING   4U

#define BT_UUID_ELECTRIC_POTENTIAL_DIFFERENCE_VOLTS 0x2728
#ifndef BT_CPF_UNIT_INT32
#define BT_CPF_UNIT_INT32 0x08 // BLE_GATT_CPF_FORMAT_UINT32
#endif

/* Inputs for the ADC */
struct divider_data {
    const struct device *adc;
    const struct device *gpio;
    struct adc_channel_cfg adc_cfg;
    struct adc_sequence adc_seq;
    uint32_t raw;
};

/* Outputs and other calculated values from the ADC. */
struct adc_results {
    /* Reference voltage in millivolts */
    uint16_t adc_ref_mV;
    /* ADC resolution bits expressed as a decimal integer. */
    unsigned long res_bits;
    /* ADC millivolts reading as divided by the voltage divider. */
    int32_t divided_mV;
    /* Un-divided ADC millivolts reading. */
    int32_t millivolts;
    /* ADC reading expressed in Volts. */
    char volts[6];
};

extern struct adc_results read_battery();

#endif //FEATHER_NRF52840_DEVICE_CONFIG_H
