# The objects to build
OBJECTS = loader.o kmain.o fb.o io.o serial.o util.o

# The C compiler
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
         -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c

# The linker
LDFLAGS = -T ../src/link.ld -melf_i386

# The assembler
AS = nasm
ASFLAGS = -f elf

# Find some prequisites
VPATH = src/

all: kernel.elf

kernel.elf: $(OBJECTS)
	cd build/ && ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

os.iso: kernel.elf
	cp build/kernel.elf iso/boot/kernel.elf
	genisoimage -R                       \
                -b boot/grub/stage2_eltorito \
                -no-emul-boot                \
                -boot-load-size 4            \
                -A os                        \
                -input-charset utf8          \
                -quiet                       \
                -boot-info-table             \
                -o os.iso                    \
                iso

run: os.iso
	bochs -f config/bochsrc.txt -q -rc config/debug.rc

%.o: %.c
	$(CC) $(CFLAGS)  $< -o build/$@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o build/$@

clean:
	rm -rf *.o build/* os.iso
