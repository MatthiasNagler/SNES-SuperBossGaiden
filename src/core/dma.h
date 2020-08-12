.include "src/config/config.inc"

;defines
.def DMA_QUEUE_SLOTS 32	;must be power of two
.def TRANSFER_ACTIVE $8000

;dma transfer types
.enum 0 export
DMA_TRANSFER.VRAM	db
DMA_TRANSFER.VRAM.TILELINE.HORIZONTAL   db
DMA_TRANSFER.VRAM.TILELINE.VERTICAL   db
DMA_TRANSFER.VRAM.SPRITETILE.32X32   db
DMA_TRANSFER.OAM	db
DMA_TRANSFER.CGRAM	db
DMA_TRANSFER.MAX ds 0
.ende

.def DMA_TRANSFER.OPTION.FIXED_SOURCE $80
.def DMA_TRANSFER.OPTION.ACTIVE $40
.def DMA_TRANSFER.OPTION.REVERSE $20    ;switch transfer direction, b-bus to a-bus
.def DMA_TRANSFER.TRANSFER.MAX $b00 ;$e00 ;$800 ;$1800    ;$800 ntsc, maximum amount of bytes to transfer per frame

.export DMA_TRANSFER.OPTION.FIXED_SOURCE
.export DMA_TRANSFER.OPTION.REVERSE
.export DMA_TRANSFER.TRANSFER.MAX

;structs:
.struct dmaQueue	;must be 8 bytes in length
  transferLength dw
  targetAdress dw
  transferType db
  sourceAdress ds 3
.endst

;ram buffers
.ramsection "global dmafifo vars" bank 0 slot 5
DMA_QUEUE.GLOBAL.START ds 0

GLOBAL.currentDmaQueueSlot db
GLOBAL.dmaQueueChannel.id db
GLOBAL.dmaQueueChannel.flag db
GLOBAL.dmaQueueChannel.size.total dw
GLOBAL.dmaQueueChannel.index dw
GLOBAL.dmaQueue INSTANCEOF dmaQueue DMA_QUEUE_SLOTS
GLOBAL.dmaQueueImmediate INSTANCEOF dmaQueue

DMA_QUEUE.GLOBAL.END ds 0
.ends

.base BSL
.bank BANK.DATA

.section "dmaBitflagLut" superfree
dmaBitflagLut:
    .db 1 << 0
    .db 1 << 1
    .db 1 << 2
    .db 1 << 3
    .db 1 << 4
    .db 1 << 5
    .db 1 << 6
    .db 1 << 7
.ends

.base BSL
.bank BANK.PROGRAM


