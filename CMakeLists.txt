#
# Copyright (c) 2020 Patrick Moffitt <patrick@moffitt.com>
#
# SPDX-License-Identifier: Apache-2.0
#

cmake_minimum_required(VERSION 3.13.1)
set(BOARD adafruit_feather_nrf52840)
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(zephyr)

FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})

add_definitions(-Wfatal-errors)