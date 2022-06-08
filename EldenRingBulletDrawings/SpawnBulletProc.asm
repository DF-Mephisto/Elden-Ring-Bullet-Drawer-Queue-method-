.DATA

.CODE

spawnBulletProc PROC

cmp byte ptr [data+25], 0
jne originalcode

cmp word ptr [data+26], 0
je originalcode

mov r8, qword ptr [data+16]

mov edx, dword ptr [data+28]
mov dword ptr [r8+14h], edx

push rdi
push rsi
push rax

mov rcx, 12
lea rsi, [data+32]
lea rdi, [r8+80h]
cld
rep movsb

mov rcx, 12
lea rsi, [data+44]
lea rdi, [r8+70h]
cld
rep movsb

dec word ptr [data+26]

cmp word ptr [data+26], 0
je callproc

mov rax, 28
movzx rcx, word ptr [data+26]
mul rcx

mov rcx, rax
lea rsi, [data+56]
lea rdi, [data+28]
cld
rep movsb

callproc:
pop rax
pop rsi
pop rdi

mov rcx, qword ptr [data+8]
mov rcx, qword ptr [rcx]
mov r9, r8
add r9, 7E0h
mov rdx, r8
add rdx, 7D0h

push rax
sub rsp,28h
call qword ptr [data]
add rsp,28h
pop rax

originalcode:
mov qword ptr [rax+1Ch], 0

nop
nop
nop
nop
nop
data:
ret

spawnBulletProc ENDP

END