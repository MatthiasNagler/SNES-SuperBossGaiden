.include "src/config/config.inc"


;defines

.define oopStackTst	$aa55
.define maxExecTime 10	;number of frames oop handler may spend on a single obj before nmi watchdog throws error
.define object.parameter.void 0 ;inband void declaration sucks, but whatever...
.export object.parameter.void

;obj return codes
.ENUM 0	export
OBJR_noErr	db
OBJR_kill	db
.ende

;zp-vars,just a reference
.enum 0
  iterator INSTANCEOF iteratorStruct
zpLen ds 0
.ende

;oop structures
.STRUCT oopStackObj
flags		db	;@see OBJECT.FLAGS
id			db	;class id
num			dw	;number of core.object.create calls at obj instanciation time. used for fingerprint
properties	dw
dp			dw	;absolute direct page adress on object variable buffer
init		dw	;obj init subroutine absolute adress
play		dw	;obj play subroutine absolute adress
pause        dw  ;obj play subroutine absolute adress
current dw  ;obj current play routine (either play or pause)
.ENDST

.def oopStackObj.length _sizeof_oopStackObj
.export oopStackObj.length

;changing the enum below means youll also have to modfiy the macro that generates objects
.ENUM 0	export
OOPR.flags	db	;bit0: singleton
OOPR.id			db	;generated by saving number of class macro calls here
OOPR.zpLen	db	;length of required zeropage-buffer
OOPR.properties dw	;property flags
OOPR.rCount	db	;number of routines
OOPR.rInit	dw	;adress of obj init routine
OOPR.rPlay	dw 	;adress of obj play routine
OOPR.rPause  dw  ;adress of obj pause routine
OOPR.rDisable  dw  ;adress of obj pause routine
OOPR.rEnable  dw  ;adress of obj pause routine
OOPR.rKill	dw 	;adress of obj terminate routine
OOPR.rAdd		dw 	;adress of obj additional routine
.ENDE

.enum 0
Hash INSTANCEOF oopObjHash
.ende

;ram buffers
.ramsection "oop ram" bank 0 slot 1
OopStack INSTANCEOF oopStackObj maxNumberOopObjs
OopStackEnd ds 0
.ends

;ram buffers
.ramsection "global oop vars" bank 0 slot 1
GLOBAL.OopObjIndex dw
GLOBAL.OopObjRamPtr dw
GLOBAL.OopObjStackPtr dw
GLOBAL.OopObjSlotPtr dw
GLOBAL.garbagePresent	dw
GLOBAL.execFrame		dw
.ends


.ramsection "oop obj ram zp" bank 0 slot 5
OopObjRam ds $1a60
OopObjRamEnd ds 0
.ends

.include "src/include/object.include"

.base BSL
.bank BANK.PROGRAM
