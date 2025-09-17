mkdir -p build
gcc -O3 -ffreestanding -o ./build/k00_run entry.s m00_run.c helper.c -nostdlib -m32 -g -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
pkill qemu-system-138 || true
qemu-system-i386 -kernel ./build/k00_run -nographic -s -no-reboot
c[?7l[2J[0mSeaBIOS (version Arch Linux 1.17.0-1-1)


iPXE (http://ipxe.org) 00:03.0 C900 PCI2.10 PnP PMM+06FD3F60+06F33F60 C900
Press Ctrl-B to configure iPXE (PCI 00:03.0)...                                                                               


Booting from ROM..
Olá mundo!
mkdir -p build
gcc -O3 -ffreestanding -o ./build/k01_paging entry.s m01_paging.c helper.c -nostdlib -m32 -g -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
pkill qemu-system-138 || true
qemu-system-i386 -kernel ./build/k01_paging -nographic -s -no-reboot
c[?7l[2J[0mSeaBIOS (version Arch Linux 1.17.0-1-1)


iPXE (http://ipxe.org) 00:03.0 C900 PCI2.10 PnP PMM+06FD3F60+06F33F60 C900
Press Ctrl-B to configure iPXE (PCI 00:03.0)...                                                                               


Booting from ROM..
Olá mundo!
mkdir -p build
gcc -O3 -ffreestanding -o ./build/k02_test entry.s m02_test.c helper.c -nostdlib -m32 -g -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
pkill qemu-system-138 || true
qemu-system-i386 -kernel ./build/k02_test -nographic -s -no-reboot
c[?7l[2J[0mSeaBIOS (version Arch Linux 1.17.0-1-1)


iPXE (http://ipxe.org) 00:03.0 C900 PCI2.10 PnP PMM+06FD3F60+06F33F60 C900
Press Ctrl-B to configure iPXE (PCI 00:03.0)...                                                                               


Booting from ROM..
Olá mundo!
mkdir -p build
gcc -O3 -ffreestanding -o ./build/k03_map entry.s m03_map.c helper.c -nostdlib -m32 -g -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
pkill qemu-system-138 || true
qemu-system-i386 -kernel ./build/k03_map -nographic -s -no-reboot
c[?7l[2J[0mSeaBIOS (version Arch Linux 1.17.0-1-1)


iPXE (http://ipxe.org) 00:03.0 C900 PCI2.10 PnP PMM+06FD3F60+06F33F60 C900
Press Ctrl-B to configure iPXE (PCI 00:03.0)...                                                                               


Booting from ROM..
Olá mundo!
mkdir -p build
gcc -O3 -ffreestanding -o ./build/k04_read_effect entry.s m04_read_effect.c helper.c -nostdlib -m32 -g -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
pkill qemu-system-138 || true
qemu-system-i386 -kernel ./build/k04_read_effect -nographic -s -no-reboot
c[?7l[2J[0mSeaBIOS (version Arch Linux 1.17.0-1-1)


iPXE (http://ipxe.org) 00:03.0 C900 PCI2.10 PnP PMM+06FD3F60+06F33F60 C900
Press Ctrl-B to configure iPXE (PCI 00:03.0)...                                                                               


Booting from ROM..
Olá mundo!
mkdir -p build
gcc -O3 -ffreestanding -o ./build/k05_write_effect entry.s m05_write_effect.c helper.c -nostdlib -m32 -g -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
pkill qemu-system-138 || true
qemu-system-i386 -kernel ./build/k05_write_effect -nographic -s -no-reboot
c[?7l[2J[0mSeaBIOS (version Arch Linux 1.17.0-1-1)


iPXE (http://ipxe.org) 00:03.0 C900 PCI2.10 PnP PMM+06FD3F60+06F33F60 C900
Press Ctrl-B to configure iPXE (PCI 00:03.0)...                                                                               


Booting from ROM..
Olá mundo!
mkdir -p build
gcc -O3 -ffreestanding -o ./build/k06_remove_map entry.s m06_remove_map.c helper.c -nostdlib -m32 -g -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
pkill qemu-system-138 || true
qemu-system-i386 -kernel ./build/k06_remove_map -nographic -s -no-reboot
c[?7l[2J[0mSeaBIOS (version Arch Linux 1.17.0-1-1)


iPXE (http://ipxe.org) 00:03.0 C900 PCI2.10 PnP PMM+06FD3F60+06F33F60 C900
Press Ctrl-B to configure iPXE (PCI 00:03.0)...                                                                               


Booting from ROM..
Olá mundo!
mkdir -p build
gcc -O3 -ffreestanding -o ./build/k07_invalidate_tlb entry.s m07_invalidate_tlb.c helper.c -nostdlib -m32 -g -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
pkill qemu-system-138 || true
qemu-system-i386 -kernel ./build/k07_invalidate_tlb -nographic -s -no-reboot
c[?7l[2J[0mSeaBIOS (version Arch Linux 1.17.0-1-1)


iPXE (http://ipxe.org) 00:03.0 C900 PCI2.10 PnP PMM+06FD3F60+06F33F60 C900
Press Ctrl-B to configure iPXE (PCI 00:03.0)...                                                                               


Booting from ROM..
Olá mundo!
mkdir -p build
gcc -O3 -ffreestanding -o ./build/k08_readonly entry.s m08_readonly.c helper.c -nostdlib -m32 -g -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
pkill qemu-system-138 || true
qemu-system-i386 -kernel ./build/k08_readonly -nographic -s -no-reboot
c[?7l[2J[0mSeaBIOS (version Arch Linux 1.17.0-1-1)


iPXE (http://ipxe.org) 00:03.0 C900 PCI2.10 PnP PMM+06FD3F60+06F33F60 C900
Press Ctrl-B to configure iPXE (PCI 00:03.0)...                                                                               


Booting from ROM..
Olá mundo!
mkdir -p build
gcc -O3 -ffreestanding -o ./build/k09_exception_handler entry.s m09_exception_handler.c helper.c -nostdlib -m32 -g -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
pkill qemu-system-138 || true
qemu-system-i386 -kernel ./build/k09_exception_handler -nographic -s -no-reboot
c[?7l[2J[0mSeaBIOS (version Arch Linux 1.17.0-1-1)


iPXE (http://ipxe.org) 00:03.0 C900 PCI2.10 PnP PMM+06FD3F60+06F33F60 C900
Press Ctrl-B to configure iPXE (PCI 00:03.0)...                                                                               


Booting from ROM..
Olá mundo!
mkdir -p build
gcc -O3 -ffreestanding -o ./build/k10_custom_handler entry.s m10_custom_handler.c helper.c -nostdlib -m32 -g -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
pkill qemu-system-138 || true
qemu-system-i386 -kernel ./build/k10_custom_handler -nographic -s -no-reboot
c[?7l[2J[0mSeaBIOS (version Arch Linux 1.17.0-1-1)


iPXE (http://ipxe.org) 00:03.0 C900 PCI2.10 PnP PMM+06FD3F60+06F33F60 C900
Press Ctrl-B to configure iPXE (PCI 00:03.0)...                                                                               


Booting from ROM..
Olá mundo!
mkdir -p build
gcc -O3 -ffreestanding -o ./build/kernel_desafio entry.s m10_desafio.c helper.c -nostdlib -m32 -g -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
pkill qemu-system-138 || true
qemu-system-i386 -kernel ./build/kernel_desafio -nographic -s -no-reboot
c[?7l[2J[0mSeaBIOS (version Arch Linux 1.17.0-1-1)


iPXE (http://ipxe.org) 00:03.0 C900 PCI2.10 PnP PMM+06FD3F60+06F33F60 C900
Press Ctrl-B to configure iPXE (PCI 00:03.0)...                                                                               


Booting from ROM..
Olá mundo!
mkdir -p build
gcc -O3 -ffreestanding -o ./build/k11_fault_details entry.s m11_fault_details.c helper.c -nostdlib -m32 -g -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
pkill qemu-system-138 || true
qemu-system-i386 -kernel ./build/k11_fault_details -nographic -s -no-reboot
c[?7l[2J[0mSeaBIOS (version Arch Linux 1.17.0-1-1)


iPXE (http://ipxe.org) 00:03.0 C900 PCI2.10 PnP PMM+06FD3F60+06F33F60 C900
Press Ctrl-B to configure iPXE (PCI 00:03.0)...                                                                               


Booting from ROM..
Olá mundo!
mkdir -p build
gcc -O3 -ffreestanding -o ./build/k12_two_level entry.s m12_two_level.c helper.c -nostdlib -m32 -g -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
pkill qemu-system-138 || true
qemu-system-i386 -kernel ./build/k12_two_level -nographic -s -no-reboot
c[?7l[2J[0mSeaBIOS (version Arch Linux 1.17.0-1-1)


iPXE (http://ipxe.org) 00:03.0 C900 PCI2.10 PnP PMM+06FD3F60+06F33F60 C900
Press Ctrl-B to configure iPXE (PCI 00:03.0)...                                                                               


Booting from ROM..
Olá mundo!
mkdir -p build
gcc -O3 -ffreestanding -o ./build/k13_update_child entry.s m13_update_child.c helper.c -nostdlib -m32 -g -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
pkill qemu-system-138 || true
qemu-system-i386 -kernel ./build/k13_update_child -nographic -s -no-reboot
c[?7l[2J[0mSeaBIOS (version Arch Linux 1.17.0-1-1)


iPXE (http://ipxe.org) 00:03.0 C900 PCI2.10 PnP PMM+06FD3F60+06F33F60 C900
Press Ctrl-B to configure iPXE (PCI 00:03.0)...                                                                               


Booting from ROM..
Olá mundo!
mkdir -p build
gcc -O3 -ffreestanding -o ./build/k14_two_tables entry.s m14_two_tables.c helper.c -nostdlib -m32 -g -T linker.ld -no-pie -mgeneral-regs-only -fno-stack-protector
pkill qemu-system-138 || true
qemu-system-i386 -kernel ./build/k14_two_tables -nographic -s -no-reboot
c[?7l[2J[0mSeaBIOS (version Arch Linux 1.17.0-1-1)


iPXE (http://ipxe.org) 00:03.0 C900 PCI2.10 PnP PMM+06FD3F60+06F33F60 C900
Press Ctrl-B to configure iPXE (PCI 00:03.0)...                                                                               


Booting from ROM..
Olá mundo!!!
echo "Ran."
Ran.
