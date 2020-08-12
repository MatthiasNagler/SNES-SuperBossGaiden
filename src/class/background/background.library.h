.include "src/config/config.inc"


.def BG.PALETTE.BITS %11100 
.export BG.PALETTE.BITS

;this is a hack, should be defined in animation file instead
.def BG.TILEMAP.LENGTH $800
.export BG.TILEMAP.LENGTH

;zp-vars,just a reference
.enum 0
  iterator INSTANCEOF iteratorStruct
  dimension INSTANCEOF dimensionStruct
  animation INSTANCEOF animationStruct
  background INSTANCEOF backgroundStruct
zpLen ds 0
.ende

;object class static flags, default properties and zero page 
.define CLASS.FLAGS OBJECT.FLAGS.Present
.define CLASS.PROPERTIES OBJECT.PROPERTIES.isLevelSortable
.define CLASS.ZP_LENGTH zpLen
.define CLASS.IMPLEMENTS interface.dimension

.base BSL
.bank BANK.DATA


.section "BgBitflagLUT" superfree
BgBitflagLUT:
  .db T_BG1_ENABLE
  .db T_BG2_ENABLE
  .db T_BG3_ENABLE
  .db T_BG4_ENABLE
.ends

.section "palette_granularity_lut" superfree
PALETTE.GRANULARITY.LUT:
  .dw PALETTE.GRANULARITY.1BPP
  .dw PALETTE.GRANULARITY.2BPP
  .dw PALETTE.GRANULARITY.4BPP
  .dw PALETTE.GRANULARITY.8BPP
  .dw PALETTE.GRANULARITY.8BPP
.ends

.section "palette_start_lut" superfree
PALETTE.START.LUT:
  .dw PALETTE.START.BG
  .dw PALETTE.START.BG.2BPP
  .dw PALETTE.START.BG.4BPP
  .dw PALETTE.START.BG.8BPP
  .dw PALETTE.START.BG.8BPP
.ends

.section "tilemap_length_lut" superfree
TILEMAP.LENGTH.LUT:
  .dw TILEMAP.SIZE.SINGLE
  .dw TILEMAP.SIZE.DUAL
  .dw TILEMAP.SIZE.DUAL
  .dw TILEMAP.SIZE.QUADRUPLE
.ends

.section "tiles_mask_lut" superfree
TILES.MASK.LUT:
  .dw $fff0
  .dw $ff0f
  .dw $f0ff
  .dw $0fff
.ends

.section "tiles_shift_lut" superfree
TILES.SHIFT.LUT:
  .dw 0
  .dw 4
  .dw 8
  .dw 12
.ends

.section "bppToIndex.LUT" superfree
bppToIndex.LUT:
  .db 0
  .db PALETTE.BPP.1
  .db PALETTE.BPP.2
  .db 0
  .db PALETTE.BPP.4
  .db 0
  .db 0
  .db 0
  .db PALETTE.BPP.8
  .db 0
  .db 0
  .db 0
  .db 0
  .db 0
  .db 0
  .db 0


.ends

.base BSL
.bank BANK.PROGRAM

.include "src/include/background.include"  
