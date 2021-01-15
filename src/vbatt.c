/*
 * Copyright (c) 2020, Patrick Moffitt <patrick@moffitt.com>
 * Copyright (c) 2018-2019 Peter Bigot Consulting, LLC
 * Copyright (c) 2019-2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Battery voltage monitor for the Adafruit Feather nRF52840 Express.
 */


#include "vbatt.h"
LOG_MODULE_REGISTER(vbatt);

struct adc_results read_battery(){
    struct divider_data dd;
    struct adc_results results = {0, 0, 0,
            0, "0.0"};
    int return_code;

    LOG_INF("%s status: %s\n", VDIV_LABEL, VDIV_STATUS);

    dd.adc = device_get_binding(VDIV_ADC_LABEL);
    if (dd.adc == NULL) {
        LOG_ERR("Unable to bind %s adc device.", VDIV_LABEL);
        return results;
    }

    dd.gpio = device_get_binding(VDIV_GPIO_LABEL);
    if (dd.gpio == NULL) {
        LOG_ERR("Unable to bind %s gpio device.", VDIV_GPIO_LABEL);
        return results;
    }

    return_code = gpio_pin_configure(dd.gpio, VDIV_GPIO_PIN,
                                     VDIV_GPIO_FLAGS);
    if (return_code < 0) {
        LOG_ERR("Unable to configure pin %d on %s.",
                VDIV_GPIO_PIN,
                VDIV_GPIO_LABEL);
        return results;
    }

    dd.adc_cfg = (struct adc_channel_cfg){
            .gain = ADC_GAIN_1_6,
            .reference = ADC_REF_INTERNAL,
            .acquisition_time =
                    ADC_ACQ_TIME(ADC_ACQ_TIME_MICROSECONDS, 40),
            .input_positive =
                    SAADC_CH_PSELP_PSELP_AnalogInput0 + VDIV_ADC_CHAN,
    };
    return_code = adc_channel_setup(dd.adc, &dd.adc_cfg);
    if (return_code < 0) {
        LOG_ERR("Failed to setup of %s channel %d. Error code %d.\n",
                VDIV_ADC_LABEL,
                VDIV_ADC_CHAN,
                return_code);
        return results;
    } else {
        LOG_INF("Setup of %s channel %d succeeded.\n",
                VDIV_ADC_LABEL,
                VDIV_ADC_CHAN);
    }

    return_code = gpio_pin_set(dd.gpio, VDIV_GPIO_PIN, 1);
    if (return_code < 0) {
        LOG_ERR("Failed to enable gpio pin.\n");
        return results;
    }

    dd.raw = 0;
    dd.adc_seq = (struct adc_sequence){
            .channels = BIT(0),
            .buffer = &dd.raw,
            .buffer_size = sizeof(dd.raw),
            .oversampling = NRF52840_ADC_OVERSAMPLING,
            .calibrate = true,
            .resolution = NRF52840_ADC_RESOLUTION,
    };

    return_code = adc_read(dd.adc, &dd.adc_seq);
    if (return_code < 0) {
        LOG_ERR("Failed reading ADC.\n");
        return results;
    }
    dd.adc_seq.calibrate = false;

    results.divided_mV = dd.raw;
    return_code = adc_raw_to_millivolts(adc_ref_internal(dd.adc),
                                        dd.adc_cfg.gain,
                                        dd.adc_seq.resolution,
                                        &results.divided_mV);
    if (return_code == -EINVAL) {
        LOG_ERR("Failed converting ADC raw to millivolts.\n");
        return results;
    }
    results.millivolts = VDIV_DIVISOR * results.divided_mV;
    results.adc_ref_mV = adc_ref_internal(dd.adc);
    results.res_bits = 1UL << dd.adc_seq.resolution;
    snprintf(results.volts, sizeof(results.volts), "%f.3f",
             (results.millivolts / 1000.0)); /* Convert mV to V. */

    LOG_INF("ADC reference voltage: %d mV\n", results.adc_ref_mV);
    LOG_INF("ADC gain ratio 1:%d.\n", NRF52840_ADC_GAIN_RATIO_1_6);
    LOG_INF("ADC resolution bits: %lu\n", results.res_bits);
    LOG_INF("Voltage divider divisor: %d\n", VDIV_DIVISOR);
    LOG_INF("ADC raw: %d\n", dd.raw);
    LOG_INF("The Math:\n");
    LOG_INF("div_div * raw * ((adc_ref_mV * gain) / resolution_bits) = mV\n");
    LOG_INF("%d * %d * ((%d * %d) / %lu) = %d mV.\n",
            VDIV_DIVISOR,
            dd.raw,
            results.adc_ref_mV,
            NRF52840_ADC_GAIN_RATIO_1_6,
            results.res_bits,
            results.millivolts);
    LOG_INF("Battery voltage: %s\n", log_strdup(results.volts));
    return results;
}