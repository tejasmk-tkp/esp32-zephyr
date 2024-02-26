cmake_minimum_required(VERSION 3.22)

find_package(Zephyr)
project(led_trigger)

target_sources(app PRIVATE src/main.c)
