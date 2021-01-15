/*
 * Copyright (c) 2020, Patrick Moffitt <patrick@moffitt.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * BLE GATT configuration for bt_notify of BME680 and VBATT
 */

#ifndef FEATHER_NRF52840_BT_GATT_CONFIG_H
#define FEATHER_NRF52840_BT_GATT_CONFIG_H

#include <bluetooth/bluetooth.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>
#include <sys/byteorder.h>
#include <settings/settings.h>
#include <logging/log.h>

#include "bme680.h"
#include "vbatt.h"

/* Custom Notify Acknowledge Characteristics */
static const struct bt_uuid_128 A_uuid = BT_UUID_INIT_128(
        0xee, 0xcd, 0xab, 0x56, 0x34, 0x12, 0x90, 0x78,
        0x56, 0x34, 0x12, 0x90, 0x78, 0x56, 0x34, 0x12);

static const char notify_acknowledge_label[] = "Notify Acknowledge";

#define BT_UUID_UNITLESS 0x2700
/* Custom Notify Acknowledge Presentation Format */
static const struct bt_gatt_cpf notify_ack_cpf = {
        .unit = BT_UUID_UNITLESS,
        .format = BT_CPF_UNIT_INT32
};


static const char gas_resistance_label[] = "Gas Resistance Ohms";

/* Custom Gas Resistance Presentation Format */
static const struct bt_gatt_cpf gas_res_cpf = {
        .unit = BT_UUID_RESISTANCE_OHMS,
        .format = BT_CPF_UNIT_INT32
};

/* Custom Gas Resistance Characteristics */
static const struct bt_uuid_128 G_uuid = BT_UUID_INIT_128(
        0xef, 0xcd, 0xab, 0x56, 0x34, 0x12, 0x90, 0x78,
        0x56, 0x34, 0x12, 0x90, 0x78, 0x56, 0x34, 0x12);

/* Custom Battery Volts Presentation Format */
static const struct bt_gatt_cpf batt_volts_cpf = {
        .unit = BT_UUID_ELECTRIC_POTENTIAL_DIFFERENCE_VOLTS,
        .format = BT_CPF_UNIT_INT32
};

static unsigned char mfg_data[] = {0x22, 0x08}; // Adafruit Industries

static const struct bt_data ad[] = {
        BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
        BT_DATA(BT_DATA_MANUFACTURER_DATA, mfg_data, sizeof(mfg_data)),

        BT_DATA_BYTES(BT_DATA_UUID128_ALL,
                      0xf0, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12,
                      0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12),
};

extern void bt_ready(int err);

extern struct bt_conn_cb conn_callbacks;

extern int bt_gatt_notify_readings();

#endif //FEATHER_NRF52840_BT_GATT_CONFIG_H