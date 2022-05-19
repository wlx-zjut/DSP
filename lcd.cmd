-w
-stack 500
-sysstack 500
-l rts55x.lib
-l 55xdspx.lib
MEMORY
{
    DARAM:	o=0x100,	l=0x07f00
    VECT:	o=0x8000,	l=0x100			//中断向量表，256字
    DARAM2:	o=0x8200,	l=0x7f00
    SDRAM:	o=0x40000,	l=0x3e0000
}

SECTIONS
{
    .text:    {} > DARAM
    .trcinit: {} > DARAM
    .gblinit: {} > DARAM
     frt:     {} > DARAM
	.vectors: {} > VECT
    .cinit:   {} > DARAM
    .pinit:   {} > DARAM
    .sysinit: {} > DARAM
    .data     {} > DARAM2
    .fftcode  {} > DARAM2
    .bss:     {} > DARAM2
    .far:     {} > DARAM2
    .const:   {} > DARAM
    .switch:  {} > DARAM
    .sysmem:  {} > DARAM
    .cio:     {} > DARAM
    .MEM$obj: {} > DARAM
    .sysheap: {} > DARAM
    .sysstack {} > DARAM
    .stack:   {} > DARAM

}


