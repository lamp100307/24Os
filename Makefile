CC := gcc -m32 -ffreestanding -O3 -fno-stack-protector -fno-stack-check -nostdlib -Isrc/core/inc
AS := nasm -f elf32
LD := ld -m elf_i386

S_DIR := src
B_DIR := bin
ISO_D := $(B_DIR)/iso
TAR := $(B_DIR)/24Oskernel.bin
ISO := $(B_DIR)/24Os.iso

SRCS := $(shell find $(S_DIR) -type f \( -name "*.c" -o -name "*.asm" \))
OBJS := $(patsubst $(S_DIR)/%.c,$(B_DIR)/%.o,$(patsubst $(S_DIR)/%.asm,$(B_DIR)/%.o,$(SRCS)))
DEPS := $(OBJS:.o=.d)

G := \033[32m
R := \033[31m
N := \033[0m

.PHONY: all run clean

all: $(ISO)

$(ISO): $(TAR)
	@mkdir -p $(ISO_D)/boot/grub
	@cp $(TAR) $(ISO_D)/boot/
	@printf 'set timeout=0\nset default=0\nmenuentry "24OS" {\n\tmultiboot /boot/24Oskernel.bin\n\tboot\n}\n' > $(ISO_D)/boot/grub/grub.cfg
	@grub-mkrescue -o $@ $(ISO_D) 2>/dev/null && echo -e "Build $(ISO) $$G[OK]$$N" || (echo -e "Build $(ISO) $$R[BAD]$$N"; exit 1)

$(TAR): $(OBJS)
	@$(LD) -T link.ld -o $@ $^ && echo -e "Link $(TAR) $$G[OK]$$N" || (echo -e "Link $(TAR) $$R[BAD]$$N"; exit 1)

$(B_DIR)/%.o: $(S_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $< -o $@ -MMD -MP 2>/dev/null && echo -e "$< $$G[OK]$$N" || (echo -e "$< $$R[BAD]$$N"; exit 1)

$(B_DIR)/%.o: $(S_DIR)/%.asm
	@mkdir -p $(dir $@)
	@$(AS) $< -o $@ 2>/dev/null && echo -e "$< $$G[OK]$$N" || (echo -e "$< $$R[BAD]$$N"; exit 1)

run: $(ISO)
	@qemu-system-i386 -cdrom $(ISO) -serial stdio

clean:
	@rm -rf $(B_DIR)

-include $(DEPS)
