#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define SERIAL_PORT_COM1 0x3F8
#define SERIAL_PORT_COM2 0x2F8
#define SERIAL_PORT_COM3 0x3E8
#define SERIAL_PORT_COM4 0x2E8

void init_serial(uint16_t port);
bool serial_received(uint16_t port);
char read_serial(uint16_t port);
bool serial_transmit_empty(uint16_t port);
void write_serial(uint16_t port, char c);
