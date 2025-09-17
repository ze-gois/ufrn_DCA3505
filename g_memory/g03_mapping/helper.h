#include <stdint.h>

void invlpg(void *addr);

void puts(const char *s);
void put_hex(uint32_t v);

void set_cr4(uint32_t value);
uint32_t get_cr4(void);

void set_cr3(uint32_t value);
uint32_t get_cr3(void);

uint32_t get_cr2(void);

void set_cr0(uint32_t value);
uint32_t get_cr0(void);

void init_idt(void);

struct state {
	uint32_t edi;
	uint32_t esi;
	uint32_t ebp;
	uint32_t reserved;
	uint32_t ebx;
	uint32_t edx;
	uint32_t ecx;
	uint32_t eax;
	uint32_t error;
	uint32_t eip;
	uint32_t cs;
	uint32_t eflags;
};

void page_fault_handler(struct state *s);
