.text
.globl start
start:
	mov $stack_end, %esp
	jmp main

.global page_fault_entry
page_fault_entry:
	pushal
	push %esp
	call page_fault_handler
	addl $4, %esp
	popal
	addl $4, %esp
	iretl

.bss
.balign 4096
	.skip 64*1024
stack_end:
