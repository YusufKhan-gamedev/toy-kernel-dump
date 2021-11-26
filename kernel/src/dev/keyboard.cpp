#include "keyboard.h"
#include "../arch/asm.h"
#include "../lib/log.h"

constexpr static uint64_t KEYBOARD_CONFIG_ADDRESS_PORT = 0x060;
constexpr static uint64_t KEYBOARD_CONFIG_DATA_PORT = 0x063;

static void set_keyboard_address(uint32_t address, uint32_t offset) {
    arch::io_outd(KEYBOARD_CONFIG_ADDRESS_PORT, address | (offset & 0xfc) | 0x80000000);
}

uint16_t KeyboardHeader::get_vendor_id() {
    return read_word(0x00);
}

uint16_t KeyboardHeader::get_device_id() {
    return read_word(0x02);
}

uint8_t KeyboardHeader::get_class_code() {
    return read_byte(0x0b);
}

uint8_t KeyboardHeader::get_subclass() {
    return read_byte(0x0a);
}

uint8_t KeyboardHeader::get_prog_if() {
    return read_byte(0x09);
}

uint8_t KeyboardHeader::get_revision() {
    return read_byte(0x08);
}

uint8_t KeyboardHeader::get_header_type() {
    return read_byte(0x0e);
}

KeyboardBar KeyboardHeader::get_bar(uint32_t index) {
    // TODO: Implement

    return {};
}

uint8_t KeyboardHeader::read_byte(uint32_t offset) {
    set_keyboard_address(address, offset);

    return arch::io_inb(KEYBOARD_CONFIG_DATA_PORT + (offset & 3));
}

uint16_t KeyboardHeader::read_word(uint32_t offset) {
    assert_msg((offset & 1) == 0, "PCI word read from unaligned offset");

    set_keyboard_address(address, offset);

    return arch::io_inw(KEYBOARD_CONFIG_DATA_PORT + (offset & 3));
}

uint32_t KeyboardHeader::read_dword(uint32_t offset) {
    assert_msg((offset & 3) == 0, "PCI dword read from unaligned offset");

    set_keyboard_address(address, offset);

    return arch::io_ind(KEYBOARD_CONFIG_DATA_PORT + (offset & 3));
}

void KeyboardHeader::enable_mmio() {
    // TODO: Implement
}

void KeyboardHeader::become_master() {
    // TODO: Implement
}

static void handle_keyboard_device(uint64_t bus, uint64_t device, uint64_t function) {
    auto header = KeyboardHeader(bus, device, function);

    if (header.get_vendor_id() == 0xffff)
        return;

    log_debug("Found device {#04x}:{#04x} in slot {}.{} on bus {}, class={}, subclass={}", header.get_vendor_id(), header.get_device_id(),
              device, function, bus, header.get_class_code(), header.get_subclass());
    //log_debug("{}", (const char *) header.get_prog_if());
    

    if (function == 0 && header.get_header_type() & 0x80) {
        for (auto function = 1; function < 8; function++) {
            handle_keyboard_device(bus, device, function);
        }
    }
}

void keyboard::scan() {
    handle_keyboard_device(1, 1, 0);
    // (auto bus = 0; bus < 256; bus++) {
    //    for (auto device = 0; device < 32; device++) {
    //        handle_keyboard_device(bus, device, 0);
    //    }
    //}
}