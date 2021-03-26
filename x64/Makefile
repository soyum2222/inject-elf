GCC =gcc
LD =ld
NASM =nasm
OBJCOPY =objcopy
OBJDUMP =objdump
BOOTSIZE =0
RDATA =.rodata

ifndef NEW_ENTER
NEW_ENTER=0
endif

ifndef ORIGIN_ENTER
ORIGIN_ENTER=0
endif

ifndef SIZE
SIZE=0
endif

build:boot  link

boot: init boot.asm
	$(NASM) -dNEW_ENTER=$(NEW_ENTER) -dORIGIN_ENTER=$(ORIGIN_ENTER)  -dFILESIZE=$(FILESIZE) -f bin -o boot.bin boot.asm

init:func.o
	$(eval TEXESIZE=$(shell $(OBJDUMP) -h func.o|grep .text |awk '{print $$3}'))
	$(eval RODATASIZE =$(shell $(OBJDUMP) -h func.o|grep $(RDATA) |awk '{print $$3}'))
	$(eval HEXTEXESIZE = $(shell  printf %d 0x$(TEXESIZE)))
	$(eval RODATABEGIN =$(shell expr $(HEXTEXESIZE) + 64))
	$(eval HEXRODATABEGIN = 0x$(shell  printf %x $(RODATABEGIN)))
	$(eval LDFLAG = $(if $(RODATASIZE), --section-start=.text=0x00 --section-start=$(RDATA)=$(HEXRODATABEGIN) -e entry -o func.bin func.o , --section-start=.text=0x00 -e entry -o func.bin func.o))
	$(eval FILESIZE =$(shell ls -l|grep linux |awk '{print $$5}'))
	$(eval OBJCOPYFLAG = $(if $(RODATASIZE), -O binary -j .text -j $(RDATA) func.bin , -O binary -j .text func.bin))

boot.asm:func.bin
	cat boot.asm.template > boot.asm

	../tool-chain/gen func.bin Clang >> boot.asm
	../tool-chain/gen linux ELF >> boot.asm


func.o:
	$(GCC) -Qn -fno-stack-protector -fno-pie -m64 -c -o func.o func.c

func.bin:func.o
	$(GCC) -Qn -fno-stack-protector -fno-pie -m64 -c -o func.o func.c
	$(LD)  $(LDFLAG)
	$(OBJCOPY) $(OBJCOPYFLAG)

link:func.bin
	cat boot.bin > inject.bin
	cat func.bin >> inject.bin
