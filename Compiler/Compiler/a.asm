.386
.model flat,stdcall
.stack 100h
option casemap : none
include \masm32\include\kernel32.inc
 include \masm32\include\msvcrt.inc
includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\msvcrt.lib

.code
Fact PROC  N:dword

.IF N == 0
mov eax, 1
RET
.ELSE
mov eax, N
sub eax, 1
invoke Fact, eax
mov ebx, eax
mov eax, N
mul ebx
RET
.ENDIF
Fact ENDP
Begin: 
finit 
MOV ebx, 0
MOV i, ebx
lp1: 
invoke crt_printf, addr fmd, i
invoke crt_printf, addr fmt, addr b1
invoke Fact, i
invoke crt_printf, addr fmd, eax
invoke crt_printf, addr fmt, addr b2
mov eax, i
add eax, 1
MOV i, eax
.IF i == 10
invoke ExitProcess,0
.ENDIF
jmp lp1 
END Begin
