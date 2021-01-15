/*
 * Copyright (c) 2020 Patrick Moffitt <patrick@moffitt.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>
#include <stddef.h>
#include <stdio.h>
#include <power/reboot.h>

#include "bme680.h"
#include "bt_gatt_config.h"
#include <logging/log.h>
LOG_MODULE_REGISTER(main);

int loop_counter = 0;
int loop_counter_limit = 2880;
void sleep_now(){
    LOG_INF("Going to sleep.");
    loop_counter = loop_counter_limit;
}

void main(void)
{
    uint32_t now = k_uptime_get_32();

    int return_code;
    return_code = bind_dev_bme680();
    if (return_code != 0) {
        LOG_ERR("Failed to bind BME680 (error %d).", return_code);
        return;
    }

    bt_gatt_notify_readings(); // Loads sensor reading into BT structs.

    // Setup BLE
    return_code = bt_enable(bt_ready);
    if (return_code) {
        LOG_ERR("Bluetooth enable failed (return code %d)\n", return_code);
        return;
    }

    bt_conn_cb_register(&conn_callbacks);

    while (loop_counter < loop_counter_limit) {
        k_sleep(K_MSEC(12));
        k_yield();
        bt_gatt_notify_readings();
        loop_counter++;
    }

    return_code = bme680_power_off();
    if (return_code == 0){
        LOG_INF("BME680 power off.\n");
    }
    return_code = bt_le_adv_stop();
    if (return_code == 0){
        LOG_INF("BLE advertising stopped.\n");
    }

    LOG_INF("Elapsed time %d ms.", (k_uptime_get_32() - now));

    k_sleep(K_MINUTES(15));
    sys_reboot(SYS_REBOOT_COLD);
}
