.include "src/config/config.inc"

.def SPIKED_MINE.JUMP.IMPULSE -1300
.def SPIKED_MINE.JUMP.ACCEL -20

.def SPIKED_MINE.DEATH.TIMER 200
.export SPIKED_MINE.DEATH.TIMER

;zp-vars
.enum 0
  iterator INSTANCEOF iteratorStruct
  dimension INSTANCEOF dimensionStruct
  animation INSTANCEOF animationStruct
  oam INSTANCEOF oamStruct
  lifeform INSTANCEOF lifeformStruct
  this.jump.count dw
  this.deathTimer dw
  zpLen ds 0
.ende

;object class static flags, default properties and zero page 
.define CLASS.FLAGS OBJECT.FLAGS.Present
.define CLASS.PROPERTIES (OBJECT.PROPERTIES.isSprite | OBJECT.PROPERTIES.isCollidable | OBJECT.PROPERTIES.isLifeform | OBJECT.PROPERTIES.isEnemy | OBJECT.PROPERTIES.isGrabbable | OBJECT.PROPERTIES.isLevelMember | OBJECT.PROPERTIES.isLevelSortable)
.define CLASS.ZP_LENGTH zpLen
.define CLASS.IMPLEMENTS interface.dimension

;external parameters
.enum 0 export
  lifeform.spiked_mine.parameter.pos.x db
  lifeform.spiked_mine.parameter.pos.y db
  lifeform.spiked_mine.parameter.size.x db
  lifeform.spiked_mine.parameter.size.y db
  lifeform.spiked_mine.parameter.berzerk.yield db
.ende

.base BSL
.bank BANK.PROGRAM

