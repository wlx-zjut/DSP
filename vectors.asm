
         .ref    _c_int00,_XINT2;
         .def    RSV, no_isr

         .sect ".vectors"

RSV:     .ivec    _c_int00, NO_RETA  ; Reset / Software Interrupt #0

NMI:     .ivec    no_isr             ; Nonmaskable / Software Interrupt #1

INT0:    .ivec    no_isr             ; Ext. User Interrupt #0 / Software Interrupt #2

INT2:    .ivec    _XINT2             ; Ext. User Interrupt #2 / Software Interrupt #3

TINT0:   .ivec    no_isr            ; Timer #0 / Software Interrupt #4

RINT0:   .ivec    no_isr             ; McBSP #0 Rec / Software Interrupt #5

RINT1:   .ivec    no_isr             ; McBSP #1 Rcv / Software Interrupt #6

XINT1:   .ivec    no_isr             ; McBSP #1 Xmit / Software Interrupt #7

SINT8:   .ivec    no_isr             ; Software Interrupt #8

DMAC1:   .ivec    no_isr             ; DMA Channel #1 / Software Interrupt #9

DSPINT:  .ivec    no_isr             ; Host Interrupt / Software Interrupt #10

INT3:    .ivec    no_isr             ; Ext. User Interrupt #3 / Software Interrupt #11

RINT2:   .ivec    no_isr             ; McBSP #2 Rcv / Software Interrupt #12

XINT2:   .ivec    no_isr             ; McBSP #2 Xmit / Software Interrupt #13

DMAC4:   .ivec    no_isr             ; DMA Channel #4 / Software Interrupt #14

DMAC5:   .ivec    no_isr             ; DMA Channel #5 / Software Interrupt #15

INT1:    .ivec    no_isr             ; Ext. User Interrupt #1 / Software Interrupt #16

XINT0:   .ivec    no_isr             ; McBSP #0 Xmit / Software Interrupt #17

DMAC0:   .ivec    no_isr             ; DMA Channel #5 / Software Interrupt #18

INT4:    .ivec    no_isr             ; Ext. User Interrupt #4 / Software Interrupt #19

DMAC2:   .ivec    no_isr             ; DMA Channel #2 / Software Interrupt #20

DMAC3:   .ivec    no_isr             ; DMA Channel #3 / Software Interrupt #21

TINT1:   .ivec    no_isr             ; Timer #1 / Software Interrupt #22

INT5:    .ivec    no_isr             ; Ext. User Interrupt #5 / Software Interrupt #23

BERR:    .ivec    no_isr             ; Bus Error / Software Interrupt #24

DLOG:    .ivec    no_isr             ; Emulation / Software Interrupt #25

RTOS:    .ivec    no_isr             ; Emulation / Software Interrupt #26

SINT27:  .ivec    no_isr             ; Software Interrupt #27

SINT28:  .ivec    no_isr             ; Software Interrupt #28

SINT29:  .ivec    no_isr             ; Software Interrupt #29

SINT30:  .ivec    no_isr             ; Software Interrupt #30

SINT31:  .ivec    no_isr             ; Software Interrupt #31


      .text

no_isr   B   no_isr
