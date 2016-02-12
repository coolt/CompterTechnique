	.286
	ifndef	??version
?debug	macro
	endm
publicdll macro	name
	public	name
	endm
$comm	macro	name,dist,size,count
	comm	dist name:BYTE:count*size
	endm
	else
$comm	macro	name,dist,size,count
	comm	dist name[size]:BYTE:count
	endm
	endif
	?debug	V 300h
	?debug	S "flare.c"
	?debug	C E9AD5B344107666C6172652E63
	?debug	C E9AA73213F20443A5C74696E5F73775C626F726C616E64635C696E+
	?debug	C 636C7564655C646F732E68
	?debug	C E9AA73213F22443A5C74696E5F73775C626F726C616E64635C696E+
	?debug	C 636C7564655C5F646566732E68
_TEXT	segment byte public 'CODE'
_TEXT	ends
DGROUP	group	_DATA,_BSS
	assume	cs:_TEXT,ds:DGROUP
_DATA	segment word public 'DATA'
d@	label	byte
d@w	label	word
_DATA	ends
_BSS	segment word public 'BSS'
b@	label	byte
b@w	label	word
_BSS	ends
_TEXT	segment byte public 'CODE'
   ;	
   ;	void main(void) {
   ;	
	assume	cs:_TEXT
_main	proc	near
	push	bp
	mov	bp,sp
@1@30:
   ;	
   ;	    
   ;	    while (1) {
   ;	        outportb(LED_LOW_ADDR,LIGHT_LEFT_LEDS);
   ;	
	mov	dx,1792
	mov	al,15
	out	dx,al
   ;	
   ;	        outportb(LED_LOW_ADDR,LIGHT_RIGHT_LEDS);
   ;	
	mov	dx,1792
	mov	al,240
	out	dx,al
	jmp	short @1@30
   ;	
   ;	    }
   ;	}
   ;	
	pop	bp
	ret	
_main	endp
	?debug	C E9
	?debug	C FA00000000
_TEXT	ends
_DATA	segment word public 'DATA'
s@	label	byte
_DATA	ends
_TEXT	segment byte public 'CODE'
_TEXT	ends
	public	_main
_s@	equ	s@
	end
