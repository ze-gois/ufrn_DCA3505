all: kernel k00_run k01_paging k02_test k03_map k04_read_effect k05_write_effect k06_remove_map k07_invalidate_tlb k08_readonly k09_exception_handler k10_custom_handler k11_fault_details k12_two_level kernel_desafio k13_update_child k14_two_tables
	@echo "Coompiling all."

k00_run: entry.s m00_run.c helper.c helper.h linker.ld
	mkdir -p build
	gcc -O3 -ffreestanding -o ./build/k00_run entry.s m00_run.c helper.c -nostdlib -m32 -g0 -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
	objdump -D ./build/k00_run > ./objdump/d00_run.s

k01_paging: entry.s m01_paging.c helper.c helper.h linker.ld
	mkdir -p build
	gcc -O3 -ffreestanding -o ./build/k01_paging entry.s m01_paging.c helper.c -nostdlib -m32 -g0 -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
	objdump -D ./build/k01_paging > ./objdump/d01_paging.s

k02_test: entry.s m02_test.c helper.c helper.h linker.ld
	mkdir -p build
	gcc -O3 -ffreestanding -o ./build/k02_test entry.s m02_test.c helper.c -nostdlib -m32 -g0 -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
	objdump -D ./build/k02_test > ./objdump/d02_test.s

k03_map: entry.s m03_map.c helper.c helper.h linker.ld
	mkdir -p build
	gcc -O3 -ffreestanding -o ./build/k03_map entry.s m03_map.c helper.c -nostdlib -m32 -g0 -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
	objdump -D ./build/k03_map > ./objdump/d03_map.s

k04_read_effect: entry.s m04_read_effect.c helper.c helper.h linker.ld
	mkdir -p build
	gcc -O3 -ffreestanding -o ./build/k04_read_effect entry.s m04_read_effect.c helper.c -nostdlib -m32 -g0 -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
	objdump -D ./build/k04_read_effect > ./objdump/d04_read_effect.s

k05_write_effect: entry.s m05_write_effect.c helper.c helper.h linker.ld
	mkdir -p build
	gcc -O3 -ffreestanding -o ./build/k05_write_effect entry.s m05_write_effect.c helper.c -nostdlib -m32 -g0 -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
	objdump -D ./build/k05_write_effect > ./objdump/d05_write_effect.s

k06_remove_map: entry.s m06_remove_map.c helper.c helper.h linker.ld
	mkdir -p build
	gcc -O3 -ffreestanding -o ./build/k06_remove_map entry.s m06_remove_map.c helper.c -nostdlib -m32 -g0 -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
	objdump -D ./build/k06_remove_map > ./objdump/d06_remove_map.s

k07_invalidate_tlb: entry.s m07_invalidate_tlb.c helper.c helper.h linker.ld
	mkdir -p build
	gcc -O3 -ffreestanding -o ./build/k07_invalidate_tlb entry.s m07_invalidate_tlb.c helper.c -nostdlib -m32 -g0 -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
	objdump -D ./build/k07_invalidate_tlb > ./objdump/d07_invalidate_tlb.s

k08_readonly: entry.s m08_readonly.c helper.c helper.h linker.ld
	mkdir -p build
	gcc -O3 -ffreestanding -o ./build/k08_readonly entry.s m08_readonly.c helper.c -nostdlib -m32 -g0 -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
	objdump -D ./build/k08_readonly > ./objdump/d08_readonly.s

k09_exception_handler: entry.s m09_exception_handler.c helper.c helper.h linker.ld
	mkdir -p build
	gcc -O3 -ffreestanding -o ./build/k09_exception_handler entry.s m09_exception_handler.c helper.c -nostdlib -m32 -g0 -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
	objdump -D ./build/k09_exception_handler > ./objdump/d09_exception_handler.s

k10_custom_handler: entry.s m10_custom_handler.c helper.c helper.h linker.ld
	mkdir -p build
	gcc -O3 -ffreestanding -o ./build/k10_custom_handler entry.s m10_custom_handler.c helper.c -nostdlib -m32 -g0 -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
	objdump -D ./build/k10_custom_handler > ./objdump/d10_custom_handler.s

kernel_desafio: entry.s m10_desafio.c helper.c helper.h linker.ld
	mkdir -p build
	gcc -O3 -ffreestanding -o ./build/kernel_desafio entry.s m10_desafio.c helper.c -nostdlib -m32 -g0 -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
	objdump -D ./build/kernel_desafio > ./objdump/dernel_desafio.s

k11_fault_details: entry.s m11_fault_details.c helper.c helper.h linker.ld
	mkdir -p build
	gcc -O3 -ffreestanding -o ./build/k11_fault_details entry.s m11_fault_details.c helper.c -nostdlib -m32 -g0 -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
	objdump -D ./build/k11_fault_details > ./objdump/d11_fault_details.s

k12_two_level: entry.s m12_two_level.c helper.c helper.h linker.ld
	mkdir -p build
	gcc -O3 -ffreestanding -o ./build/k12_two_level entry.s m12_two_level.c helper.c -nostdlib -m32 -g0 -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
	objdump -D ./build/k12_two_level > ./objdump/d12_two_level.s

k13_update_child: entry.s m13_update_child.c helper.c helper.h linker.ld
	mkdir -p build
	gcc -O3 -ffreestanding -o ./build/k13_update_child entry.s m13_update_child.c helper.c -nostdlib -m32 -g0 -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
	objdump -D ./build/k13_update_child > ./objdump/d13_update_child.s

k14_two_tables: entry.s m14_two_tables.c helper.c helper.h linker.ld
	mkdir -p build
	gcc -O3 -ffreestanding -o ./build/k14_two_tables entry.s m14_two_tables.c helper.c -nostdlib -m32 -g0 -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
	objdump -D ./build/k14_two_tables > ./objdump/d14_two_tables.s

run_k00: k00_run
	pkill qemu-system-138 || true
	qemu-system-i386 -kernel ./build/k00_run -nographic -s -no-reboot

run_k01: k01_paging
	pkill qemu-system-138 || true
	qemu-system-i386 -kernel ./build/k01_paging -nographic -s -no-reboot

run_k02: k02_test
	pkill qemu-system-138 || true
	qemu-system-i386 -kernel ./build/k02_test -nographic -s -no-reboot

run_k03: k03_map
	pkill qemu-system-138 || true
	qemu-system-i386 -kernel ./build/k03_map -nographic -s -no-reboot

run_k04: k04_read_effect
	pkill qemu-system-138 || true
	qemu-system-i386 -kernel ./build/k04_read_effect -nographic -s -no-reboot

run_k05: k05_write_effect
	pkill qemu-system-138 || true
	qemu-system-i386 -kernel ./build/k05_write_effect -nographic -s -no-reboot

run_k06: k06_remove_map
	pkill qemu-system-138 || true
	qemu-system-i386 -kernel ./build/k06_remove_map -nographic -s -no-reboot

run_k07: k07_invalidate_tlb
	pkill qemu-system-138 || true
	qemu-system-i386 -kernel ./build/k07_invalidate_tlb -nographic -s -no-reboot

run_k08: k08_readonly
	pkill qemu-system-138 || true
	qemu-system-i386 -kernel ./build/k08_readonly -nographic -s -no-reboot

run_k09: k09_exception_handler
	pkill qemu-system-138 || true
	qemu-system-i386 -kernel ./build/k09_exception_handler -nographic -s -no-reboot

run_k10: k10_custom_handler
	pkill qemu-system-138 || true
	qemu-system-i386 -kernel ./build/k10_custom_handler -nographic -s -no-reboot

run_desafio: kernel_desafio
	pkill qemu-system-138 || true
	qemu-system-i386 -kernel ./build/kernel_desafio -nographic -s -no-reboot

run_k11: k11_fault_details
	pkill qemu-system-138 || true
	qemu-system-i386 -kernel ./build/k11_fault_details -nographic -s -no-reboot

run_k12: k12_two_level
	pkill qemu-system-138 || true
	qemu-system-i386 -kernel ./build/k12_two_level -nographic -s -no-reboot

run_k13: k13_update_child
	pkill qemu-system-138 || true
	qemu-system-i386 -kernel ./build/k13_update_child -nographic -s -no-reboot

run_k14: k14_two_tables
	pkill qemu-system-138 || true
	qemu-system-i386 -kernel ./build/k14_two_tables -nographic -s -no-reboot

run: run_k00 run_k01 run_k02 run_k03 run_k04 run_k05 run_k06 run_k07 run_k08 run_k09 run_k10 run_desafio run_k11 run_k12 run_k13 run_k14
	echo "Ran."

clean:
	rm -rf build
