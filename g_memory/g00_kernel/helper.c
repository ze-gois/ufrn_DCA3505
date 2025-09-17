#include <stdint.h>
#include <stddef.h>

#include "helper.h"

__attribute__((section (".multiboot_header"))) struct {
	uint32_t magic;
	uint32_t flags;
	uint32_t xsum;
} multiboot_header = { 0x1BADB002, 0, -0x1BADB002 };

void invlpg(void *addr)
{
	asm volatile("invlpg (%0)" :: "r" (addr) : "memory");
}

void set_cr4(uint32_t value)
{
	asm volatile("movl %0, %%cr4" :: "r" (value) : "memory");
}

uint32_t get_cr4(void)
{
	uint32_t value;
	asm volatile("movl %%cr4, %0" : "=r"(value));
	return value;
}

void set_cr3(uint32_t value)
{
	asm volatile("movl %0, %%cr3" :: "r" (value) : "memory");
}

uint32_t get_cr3(void)
{
	uint32_t value;
	asm volatile("movl %%cr3, %0" : "=r"(value));
	return value;
}

uint32_t get_cr2(void)
{
	uint32_t value;
	asm volatile("movl %%cr2, %0" : "=r"(value));
	return value;
}

void set_cr0(uint32_t value)
{
	asm volatile("movl %0, %%cr0" :: "r" (value) : "memory");
}

uint32_t get_cr0(void)
{
	uint32_t value;
	asm volatile("movl %%cr0, %0" : "=r"(value));
	return value;
}

void outb(uint8_t value, uint16_t port)
{
	asm volatile("outb %b0, %w1" :: "a"(value), "Nd"(port));
}

uint8_t inb(uint16_t port)
{
	uint8_t value;
	asm volatile("inb %w1, %b0" : "=a"(value):  "Nd"(port));
	return value;
}

#define PORT 0x3f8
void putc(char c)
{
	while ((inb(PORT + 5) & 0x20) == 0) {}
	outb(c, PORT);
}

void puts(const char *s)
{
	while (*s) {
		putc(*s);
		s++;
	}
}

void put_hex(uint32_t v)
{
	char buf[10];
	char *ptr = buf + 8;

	buf[9] = 0;

	while (v) {
		*ptr = "0123456789abcdef"[v & 0xf];
		v >>= 4;
		ptr--;
	}

	puts("0x");
	if (ptr != buf + 8) {
		puts(ptr + 1);
	} else {
		puts("0");
	}
}

 __attribute__((weak))
void page_fault_handler(struct state *s)
{
	puts("\nPage fault\n");
	for(;;);
}

struct idt_entry {
	uint16_t offset_lo;
	uint16_t segment;
	uint16_t attrs;
	uint16_t offset_hi;
} __attribute__ ((__packed__));

struct idt_desc {
	uint16_t limit;
	uint32_t addr;
} __attribute__ ((__packed__));

void init_idt(void)
{
	static struct idt_entry idt[15];
	static struct idt_desc desc = { sizeof(idt) - 1, (size_t)&idt[0] };
	void page_fault_entry(void);

	idt[14].offset_lo = (size_t)&page_fault_entry;
	idt[14].offset_hi = (size_t)&page_fault_entry >> 16;
	idt[14].segment = 8;
	idt[14].attrs = 0x8f00;

	asm volatile("lidtl %0" :: "m"(desc));
}
