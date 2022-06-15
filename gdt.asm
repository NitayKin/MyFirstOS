;GDT related structures

gdt_start:

gdt_null: ; mandatory null segment descriptor
dd 0
dd 0

gdt_code: ; code segment descriptor
dw 0xffff ; Limit (bits 0-15)
dw 0x0 ; base (bits 0-15)
db 0x0 ; base (bits 16-23)
db 10011010b ; 1st flags&type flags.
db 11001111b ; 2nd flags, Limit (bits 16-19)
db 0x0 ; base (bits 24-31)

gdt_data: ; data segment descriptor
dw 0xffff ; Limit (bits 0-15)
dw 0x0 ; base (bits 0-15)
db 0x0 ; base (bits 16-23)
db 10010010b ; 1st flags&type flags.
db 11001111b ; 2nd flags, Limit (bits 16-19)
db 0x0 ; base (bits 24-31)
gdt_end: ; for gdt length calculation

gdt_descriptor: ;the gdt descriptor struct
dw gdt_end - gdt_start - 1 ; gdt length
dd gdt_start ; start address of gdt

;constants to put on segment registers:
CODE_SEG equ gdt_code-gdt_start
DATA_SEG equ gdt_data-gdt_start