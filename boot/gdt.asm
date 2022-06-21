;GDT related structures

gdt_start:

gdt_null: ; mandatory null segment descriptor   placed at 0x00
dd 0
dd 0

gdt_kernel_code: ; code segment kernel descriptor   placed at 0x08
dw 0xffff ; Limit (bits 0-15)
dw 0x0 ; base (bits 0-15)
db 0x0 ; base (bits 16-23)
db 10011010b ; 1st flags&type flags.
db 11001111b ; 2nd flags, Limit (bits 16-19)
db 0x0 ; base (bits 24-31)

gdt_kernel_data: ; data segment kernel descriptor    placed at 0x10
dw 0xffff ; Limit (bits 0-15)
dw 0x0 ; base (bits 0-15)
db 0x0 ; base (bits 16-23)
db 10010010b ; 1st flags&type flags.
db 11001111b ; 2nd flags, Limit (bits 16-19)
db 0x0 ; base (bits 24-31)

gdt_user_code: ; code segment user descriptor   placed at 0x18
dw 0xffff ; Limit (bits 0-15)
dw 0x0 ; base (bits 0-15)
db 0x0 ; base (bits 16-23)
db 11111010b ; 1st flags&type flags.
db 11001111b ; 2nd flags, Limit (bits 16-19)
db 0x0 ; base (bits 24-31)

gdt_user_data: ; data segment user descriptor   placed at 0x20
dw 0xffff ; Limit (bits 0-15)
dw 0x0 ; base (bits 0-15)
db 0x0 ; base (bits 16-23)
db 11110010b ; 1st flags&type flags.
db 11001111b ; 2nd flags, Limit (bits 16-19)
db 0x0 ; base (bits 24-31)
gdt_end: ; for gdt length calculation

gdt_descriptor: ;the gdt descriptor struct
dw gdt_end - gdt_start - 1 ; gdt length
dd gdt_start ; start address of gdt

;constants to put on segment registers:
CODE_KERNEL_SEG equ 0x08 ; gdt_kernel_code - gdt_start
DATA_KERNEL_SEG equ 0x10 ; gdt_kernek_data - gdt_start