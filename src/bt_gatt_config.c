/*
 * Copyright (c) 2020, Patrick Moffitt <patrick@moffitt.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * BLE GATT configuration for bt_notify of BME680 and VBATT
 */

#include "bt_gatt_config.h"
LOG_MODULE_REGISTER(bt_gatt_config);

/* Characteristic Configuration Change (CCC)
 * Notify Callback Temperature Changed */
static unsigned char bTNotify;

/* Notify Temperature Changed Callback Function */
static void T_ccc_cfg_changed(const struct bt_gatt_attr *attr,
                              unsigned short value)
{
    bTNotify = (value == BT_GATT_CCC_NOTIFY) ? 1 : 0;
}

/* Characteristic Configuration Change (CCC)
 * Notify Callback Humidity Changed */
static unsigned char bHNotify;

/* Notify Humidity Changed Callback Function */
static void H_ccc_cfg_changed(const struct bt_gatt_attr *attr,
                              unsigned short value)
{
    bHNotify = (value == BT_GATT_CCC_NOTIFY) ? 1 : 0;
}

/* Characteristic Configuration Change (CCC)
 * Notify Callback Pressure Changed */
static unsigned char bPNotify;

/* Notify Pressure Changed Callback Function */
static void P_ccc_cfg_changed(const struct bt_gatt_attr *attr,
                              unsigned short value)
{
    bPNotify = (value == BT_GATT_CCC_NOTIFY) ? 1 : 0;
}

/* Characteristic Configuration Change (CCC)
 * Notify Callback Gas Ohms Changed */
static unsigned char bGNotify;

/* Notify Gas Ohms Callback Function */
static void G_ccc_cfg_changed(const struct bt_gatt_attr *attr,
                              unsigned short value)
{
    bGNotify = (value == BT_GATT_CCC_NOTIFY) ? 1 : 0;
}

/* Characteristic Configuration Change (CCC)
 * Notify Callback Battery V Changed */
static unsigned char bBNotify;

/* Notify Battery V Changed Callback Function */
static void B_ccc_cfg_changed(const struct bt_gatt_attr *attr,
                              unsigned short value)
{
    bBNotify = (value == BT_GATT_CCC_NOTIFY) ? 1 : 0;
}

/* Characteristic Configuration Change (CCC)
 * Notify Callback Notify Acknowledged Changed */
static unsigned char bANotify;

/* Notify Notify Acknowledged Changed Callback Function */
static void A_ccc_cfg_changed(const struct bt_gatt_attr *attr,
                              unsigned short value)
{
    bANotify = (value == BT_GATT_CCC_NOTIFY) ? 1 : 0;
}


static signed int T_val[1] = {0};

// Read Temperature
static ssize_t read_T(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                      void *buf, unsigned short len, unsigned short offset)
{
    const char *value = attr->user_data;
    return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
                             sizeof(T_val));
}

static signed int H_val[1] = {0};

// Read humidity
static ssize_t read_H(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                      void *buf, unsigned short len, unsigned short offset)
{
    const char *value = attr->user_data;
    return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
                             sizeof(H_val));
}

static signed int P_val[1] = {0};

// Read Pressure
static ssize_t read_P(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                      void *buf, unsigned short len, unsigned short offset)
{
    const char *value = attr->user_data;
    return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
                             sizeof(P_val));
}

static signed int G_val[1] = {0};

// Read Gas
static ssize_t read_G(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                      void *buf, unsigned short len, unsigned short offset)
{
    const char *value = attr->user_data;
    return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
                             sizeof(G_val));
}

static signed int B_val[1] = {0};

// Read Battery
static ssize_t read_B(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                      void *buf, unsigned short len, unsigned short offset)
{
    const char *value = attr->user_data;
    return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
                             sizeof(B_val));
}

static signed int A_val[1] = {0};

// Read Notify Acknowledge
static ssize_t read_A(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                      void *buf, unsigned short len, unsigned short offset)
{
    const char *value = attr->user_data;
    return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
                             sizeof(A_val));
}

// Write Notify Acknowledged
static ssize_t write_A(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                          const void *buf, uint16_t len, uint16_t offset,
                          uint8_t flags)
{
    uint16_t value;

    if (offset) {
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
    }

    if (!len || len > sizeof(uint16_t)) {
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_ATTRIBUTE_LEN);
    }

    if (len < sizeof(uint16_t)) {
        value = *(uint8_t *)buf;
    } else {
        value = sys_get_le16(buf);
    }
    LOG_INF("Notify Acknowledged: %hu\n", value);
    extern void sleep_now();
    sleep_now();
    return 0;
}

/* Primary Service Declaration */
static struct bt_gatt_attr primary_attrs[] = {
    /* Environmental Sensor Service */
    BT_GATT_PRIMARY_SERVICE(BT_UUID_ESS),

    // Temperature
    BT_GATT_CHARACTERISTIC(BT_UUID_TEMPERATURE,
                           BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
                           BT_GATT_PERM_READ,
                           read_T, NULL, T_val),
    BT_GATT_CCC(T_ccc_cfg_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),

    // Humidity
    BT_GATT_CHARACTERISTIC(BT_UUID_HUMIDITY,
                           BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
                           BT_GATT_PERM_READ,
                           read_H, NULL, H_val),
    BT_GATT_CCC(H_ccc_cfg_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),

    // Pressure
    BT_GATT_CHARACTERISTIC(BT_UUID_PRESSURE,
                           BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
                           BT_GATT_PERM_READ,
                           read_P, NULL, P_val),
    BT_GATT_CCC(P_ccc_cfg_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),

    // Gas Resistance
    BT_GATT_CHARACTERISTIC(&G_uuid.uuid,
                           BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
                           BT_GATT_PERM_READ,
                           read_G, NULL, G_val),
    BT_GATT_CUD(gas_resistance_label, BT_GATT_PERM_READ),
    BT_GATT_CPF(&gas_res_cpf),
    BT_GATT_CCC(G_ccc_cfg_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),

    // Battery Level
    BT_GATT_CHARACTERISTIC(BT_UUID_BAS_BATTERY_LEVEL,
                           BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
                           BT_GATT_PERM_READ,
                           read_B, NULL, B_val),
    BT_GATT_CPF(&batt_volts_cpf),
    BT_GATT_CCC(B_ccc_cfg_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),

    // Notify Acknowledge
    BT_GATT_CHARACTERISTIC(&A_uuid.uuid,
                           BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY
                           | BT_GATT_CHRC_WRITE_WITHOUT_RESP,
                           BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
                           read_A, write_A, A_val),
    BT_GATT_CUD(notify_acknowledge_label, BT_GATT_PERM_READ),
    BT_GATT_CPF(&notify_ack_cpf),
    BT_GATT_CCC(A_ccc_cfg_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE)
};

static struct bt_gatt_service primary_svc = BT_GATT_SERVICE(primary_attrs);

// Connected event handler (callback function).
static void connected(struct bt_conn *conn, unsigned char err)
{
    if (err) {
        LOG_ERR("Connection failed (err %u)\n", err);
    } else {
        LOG_INF("Connected\n");
    }
}

// Disconnected event handler (callback function).
static void disconnected(struct bt_conn *conn, unsigned char reason)
{
    LOG_INF("Disconnected (reason %u)\n", reason);
}

// Register connected and disconnected (event) callback functions.
struct bt_conn_cb conn_callbacks = {
        .connected = connected,
        .disconnected = disconnected,
};

/**
 * @brief Format two integers as data for bt_gatt_notify
 *
 * @param lhs The integer for the left-hand side of the decimal point.
 * @param rhs The integer for the right-hand side of the decimal point.
 * @param places The number of decimal places required.
 */
static int sensor_val_arr_to_int(int lhs, int rhs, int places)
{
    int pow10[] = {1, 10, 100, 1000, 10000, 100000, 1000000};
    lhs *= pow10[places];
    char rhs_char[7];
    snprintf(rhs_char, sizeof(rhs_char), "%06d", rhs);
    int p = places - 1;
    for (int i=0; i<places; i++)
    {
        lhs += (rhs_char[i] - 48) * pow10[p]; // ascii[48] = '0'
        p--;
    }
    return lhs;
}

static int update_sensor_data() {
    struct adc_results battery;
    battery = read_battery();

    struct sensor_value temp, press, humidity, gas_ohms;
    int return_code;
    // Get sensor data.
    return_code = sensor_sample_fetch(dev_bme680);
    if (return_code < 0) {
        LOG_ERR("Failed to fetch samples from BME680 (error %d).\n",
                return_code);
        return return_code;
    }
    /* Adjust reading to correct by calibrated error. */
    temp.val1 += temp_calib.val1;
    temp.val2 += temp_calib.val2;

    return_code = sensor_channel_get(dev_bme680, SENSOR_CHAN_AMBIENT_TEMP,
                                     &temp);
    if (return_code < 0) {
        LOG_ERR("Failed to get temperature from channel (error %d).\n",
                return_code);
        return return_code;
    }

    return_code = sensor_channel_get(dev_bme680, SENSOR_CHAN_HUMIDITY,
                                     &humidity);
    if (return_code < 0) {
        LOG_ERR("Failed to get humidity from channel (error %d).\n",
                return_code);
        return return_code;
    }

    return_code = sensor_channel_get(dev_bme680, SENSOR_CHAN_PRESS,
                                     &press);
    if (return_code < 0) {
        LOG_ERR("Failed to get pressure from channel (error %d).\n",
                return_code);
        return return_code;
    }

    return_code = sensor_channel_get(dev_bme680, SENSOR_CHAN_GAS_RES,
                                     &gas_ohms);
    if (return_code < 0) {
        LOG_ERR("Failed to get gas ohms from channel (error %d).\n",
                return_code);
        return return_code;
    }

    T_val[0] = sensor_val_arr_to_int(temp.val1, temp.val2, 2);
    H_val[0] = sensor_val_arr_to_int(humidity.val1, humidity.val2, 2);
    P_val[0] = sensor_val_arr_to_int(press.val1, press.val2, 4);
    G_val[0] = gas_ohms.val1;
    B_val[0] = battery.millivolts;

    LOG_INF("T: %d.%06d; H: %d.%06d; P: %d.%06d; G: %d; B: %d\n",
            temp.val1, temp.val2, humidity.val1, humidity.val2,
            press.val1, press.val2, gas_ohms.val1, battery.millivolts);
    return return_code;
}

// BT Enable event callback function.
void bt_ready(int err)
{
    if (err) {
        LOG_ERR("Bluetooth init failed (err %d)\n", err);
        return;
    }

    LOG_INF("Bluetooth initialized.\n");

    int return_code;
    return_code = bt_gatt_service_register(&primary_svc);
    if (return_code != 0)
        LOG_ERR("Failed to register primary service.");

    if (IS_ENABLED(CONFIG_SETTINGS)) {
        return_code = settings_load();
        if (return_code != 0)
            LOG_ERR("BT settings load failed.");
    }

    return_code = bt_le_adv_start(BT_LE_ADV_CONN_NAME, ad,
                                  ARRAY_SIZE(ad), NULL, 0);
    if (return_code) {
        LOG_ERR("Advertising failed to start (err %d)\n", return_code);
        return;
    }

    LOG_INF("Advertising successfully started.\n");
}

int bt_gatt_notify_readings() {
    int return_code = 0;
    // Test is true for uninitialized BME680 sensor.
    while(T_val[0] == 0U && H_val[0] == 0U && P_val[0] == 0U && G_val[0] == 0U) {
        return_code = update_sensor_data();
        k_sleep(K_MSEC(25));
    }

    if (return_code < 0) {
        LOG_ERR("Update sensor data failed (error: %d).\n", return_code);
        return return_code;
    }

    bt_gatt_notify(NULL, &primary_attrs[2], T_val, sizeof(T_val));
    bt_gatt_notify(NULL, &primary_attrs[5], H_val, sizeof(H_val));
    bt_gatt_notify(NULL, &primary_attrs[8], P_val, sizeof(P_val));
    bt_gatt_notify(NULL, &primary_attrs[11], G_val, sizeof(G_val));
    bt_gatt_notify(NULL, &primary_attrs[16], B_val, sizeof(B_val));
    bt_gatt_notify(NULL, &primary_attrs[20], A_val, sizeof(A_val));

    return return_code;
}