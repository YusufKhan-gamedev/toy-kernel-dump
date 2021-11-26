 #pragma once

#include <stdint.h>

struct KeyboardBar {
    uint64_t addr;
    uint64_t size;

    bool mmio;
    bool prefetchable;
};

struct KeyboardHeader {
    uint32_t bus;
    uint32_t device;
    uint32_t function;
    uint32_t address;

    KeyboardHeader(uint32_t bus, uint32_t device, uint32_t function) : bus(bus), device(device), function(function) {
        address = (bus << 16) | (device << 11) | (function << 8);
    }

    uint16_t get_vendor_id();
    uint16_t get_device_id();

    uint8_t get_class_code();
    uint8_t get_subclass();
    uint8_t get_prog_if();
    uint8_t get_revision();
    uint8_t get_header_type();

    uint8_t read_byte(uint32_t offset);
    uint16_t read_word(uint32_t offset);
    uint32_t read_dword(uint32_t offset);

    void write_byte(uint32_t offset, uint8_t value);
    void write_word(uint32_t offset, uint16_t value);
    void write_dword(uint32_t offset, uint32_t value);

    KeyboardBar get_bar(uint32_t index);

    void enable_mmio();
    void become_master();
};

namespace keyboard {

void scan();

}
