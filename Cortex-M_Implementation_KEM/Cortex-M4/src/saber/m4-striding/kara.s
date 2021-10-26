.syntax unified
.cpu cortex-m4
.global schoolbook_gen
.type schoolbook_gen, %function
.align 2
schoolbook_gen:
push {lr}
ldr r6, [r1, #0]
ldr.w ip, [r1, #4]
ldr.w r3, [r1, #8]
ldr.w sl, [r1, #12]
ldr.w r7, [r1, #32]
ldr.w r8, [r1, #36]
ldr.w r4, [r1, #40]
ldr.w lr, [r1, #44]
str.w r1, [sp, #-4]!
smulbb r9, r7, r6
smuadx fp, r7, r6
pkhbt r9, r9, fp, lsl #16
str.w r9, [r0]
smuadx fp, r7, ip
smulbb r5, r7, ip
pkhbt r9, r8, r7
smladx fp, r8, r6, fp
smlad r5, r9, r6, r5
pkhbt fp, r5, fp, lsl #16
str.w fp, [r0, #4]
smulbb r5, r3, r7
smuadx fp, r3, r7
smlad r5, r9, ip, r5
pkhbt r2, r4, r8
smlad r5, r2, r6, r5
smladx fp, r8, ip, fp
smladx fp, r4, r6, fp
pkhbt fp, r5, fp, lsl #16
str.w fp, [r0, #8]
smulbb r5, sl, r7
smuadx fp, sl, r7
smlad r5, ip, r2, r5
smlad r5, r3, r9, r5
pkhbt r1, lr, r4
smlad r5, r6, r1, r5
smladx fp, r3, r8, fp
smladx fp, ip, r4, fp
smladx fp, r6, lr, fp
pkhbt fp, r5, fp, lsl #16
str.w fp, [r0, #12]
smultt r5, r6, lr
smuadx fp, sl, r8
smlad r5, ip, r1, r5
smlad r5, sl, r9, r5
smlad r5, r3, r2, r5
smladx fp, r3, r4, fp
smladx fp, ip, lr, fp
pkhbt fp, r5, fp, lsl #16
str.w fp, [r0, #16]
smultt r5, ip, lr
smuadx fp, sl, r4
smlad r5, sl, r2, r5
smlad r5, r3, r1, r5
smladx fp, r3, lr, fp
pkhbt fp, r5, fp, lsl #16
str.w fp, [r0, #20]
smuad r5, sl, r1
smuadx fp, sl, lr
smlatt r5, r3, lr, r5
pkhbt fp, r5, fp, lsl #16
ldr.w r1, [sp], #4
str.w fp, [r0, #24]
smultt fp, sl, lr
movt fp, #0
str.w fp, [r0, #28]
ldr.w r7, [r1, #48]
ldr.w r8, [r1, #52]
ldr.w r4, [r1, #56]
ldr.w lr, [r1, #60]
str.w r1, [sp, #-4]!
ldr.w r9, [r0, #16]
ldr.w r5, [r0, #20]
mov.w fp, r9, lsr #16
smlabb r9, r7, r6, r9
smladx fp, r7, r6, fp
pkhbt r9, r9, fp, lsl #16
str.w r9, [r0, #16]
mov.w fp, r5, lsr #16
smladx fp, r7, ip, fp
smlabb r5, r7, ip, r5
pkhbt r9, r8, r7
smladx fp, r8, r6, fp
smlad r5, r9, r6, r5
pkhbt fp, r5, fp, lsl #16
ldr.w r5, [r0, #24]
str.w fp, [r0, #20]
mov.w fp, r5, lsr #16
smlabb r5, r3, r7, r5
smladx fp, r3, r7, fp
smlad r5, r9, ip, r5
pkhbt r2, r4, r8
smlad r5, r2, r6, r5
smladx fp, r8, ip, fp
smladx fp, r4, r6, fp
pkhbt fp, r5, fp, lsl #16
ldr.w r5, [r0, #28]
str.w fp, [r0, #24]
mov.w fp, r5, lsr #16
smlabb r5, sl, r7, r5
smladx fp, sl, r7, fp
smlad r5, ip, r2, r5
smlad r5, r3, r9, r5
pkhbt r1, lr, r4
smlad r5, r6, r1, r5
smladx fp, r3, r8, fp
smladx fp, ip, r4, fp
smladx fp, r6, lr, fp
pkhbt fp, r5, fp, lsl #16
str.w fp, [r0, #28]
smultt r5, r6, lr
smuadx fp, sl, r8
smlad r5, ip, r1, r5
smlad r5, sl, r9, r5
smlad r5, r3, r2, r5
ldr.w r9, [r0]
smladx fp, r3, r4, fp
smladx fp, ip, lr, fp
pkhbt fp, r5, fp, lsl #16
usub16 fp, r9, fp
ldr.w r9, [r0, #4]
str.w fp, [r0]
smultt r5, ip, lr
smuadx fp, sl, r4
smlad r5, sl, r2, r5
smlad r5, r3, r1, r5
smladx fp, r3, lr, fp
pkhbt fp, r5, fp, lsl #16
usub16 fp, r9, fp
ldr.w r9, [r0, #8]
str.w fp, [r0, #4]
smuad r5, sl, r1
smuadx fp, sl, lr
smlatt r5, r3, lr, r5
pkhbt fp, r5, fp, lsl #16
usub16 fp, r9, fp
ldr.w r9, [r0, #12]
ldr.w r1, [sp], #4
str.w fp, [r0, #8]
smultt fp, sl, lr
movt fp, #0
usub16 fp, r9, fp
str.w fp, [r0, #12]
ldr.w r6, [r1, #16]
ldr.w ip, [r1, #20]
ldr.w r3, [r1, #24]
ldr.w sl, [r1, #28]
push {r1}
ldr r2, [r0, #0]
ldr.w r1, [r0, #4]
smulbb r9, r7, r6
smuadx fp, r7, r6
pkhbt r9, r9, fp, lsl #16
usub16 r9, r2, r9
str.w r9, [r0]
smuadx fp, r7, ip
smulbb r5, r7, ip
pkhbt r9, r8, r7
smladx fp, r8, r6, fp
smlad r5, r9, r6, r5
pkhbt fp, r5, fp, lsl #16
usub16 fp, r1, fp
ldr.w r1, [r0, #8]
str.w fp, [r0, #4]
smulbb r5, r3, r7
smuadx fp, r3, r7
smlad r5, r9, ip, r5
pkhbt r2, r4, r8
smlad r5, r2, r6, r5
smladx fp, r8, ip, fp
smladx fp, r4, r6, fp
pkhbt fp, r5, fp, lsl #16
usub16 fp, r1, fp
str.w fp, [r0, #8]
smulbb r5, sl, r7
smuadx fp, sl, r7
smlad r5, ip, r2, r5
smlad r5, r3, r9, r5
pkhbt r1, lr, r4
smlad r5, r6, r1, r5
ldr.w r9, [r0, #12]
smladx fp, r3, r8, fp
smladx fp, ip, r4, fp
smladx fp, r6, lr, fp
pkhbt fp, r5, fp, lsl #16
usub16 fp, r9, fp
str.w fp, [r0, #12]
smultt r5, r6, lr
smuadx fp, sl, r8
smlad r5, ip, r1, r5
pkhbt r9, r8, r7
smlad r5, sl, r9, r5
smlad r5, r3, r2, r5
ldr.w r9, [r0, #16]
smladx fp, r3, r4, fp
smladx fp, ip, lr, fp
pkhbt fp, r5, fp, lsl #16
usub16 fp, r9, fp
ldr.w r9, [r0, #20]
str.w fp, [r0, #16]
smultt r5, ip, lr
smuadx fp, sl, r4
smlad r5, sl, r2, r5
smlad r5, r3, r1, r5
smladx fp, r3, lr, fp
pkhbt fp, r5, fp, lsl #16
usub16 fp, r9, fp
ldr.w r9, [r0, #24]
str.w fp, [r0, #20]
smuad r5, sl, r1
smuadx fp, sl, lr
smlatt r5, r3, lr, r5
pkhbt fp, r5, fp, lsl #16
usub16 fp, r9, fp
ldr.w r9, [r0, #28]
ldr.w r1, [sp], #4
str.w fp, [r0, #24]
smultt fp, sl, lr
movt fp, #0
usub16 fp, r9, fp
str.w fp, [r0, #28]
ldr.w r7, [r1, #32]
ldr.w r8, [r1, #36]
ldr.w r4, [r1, #40]
ldr.w lr, [r1, #44]
str.w r1, [sp, #-4]!
ldr.w r9, [r0, #16]
ldr.w r5, [r0, #20]
mov.w fp, r9, lsr #16
smlabb r9, r7, r6, r9
smladx fp, r7, r6, fp
pkhbt r9, r9, fp, lsl #16
str.w r9, [r0, #16]
mov.w fp, r5, lsr #16
smladx fp, r7, ip, fp
smlabb r5, r7, ip, r5
pkhbt r9, r8, r7
smladx fp, r8, r6, fp
smlad r5, r9, r6, r5
pkhbt fp, r5, fp, lsl #16
ldr.w r5, [r0, #24]
str.w fp, [r0, #20]
mov.w fp, r5, lsr #16
smlabb r5, r3, r7, r5
smladx fp, r3, r7, fp
smlad r5, r9, ip, r5
pkhbt r2, r4, r8
smlad r5, r2, r6, r5
smladx fp, r8, ip, fp
smladx fp, r4, r6, fp
pkhbt fp, r5, fp, lsl #16
ldr.w r5, [r0, #28]
str.w fp, [r0, #24]
mov.w fp, r5, lsr #16
smlabb r5, sl, r7, r5
smladx fp, sl, r7, fp
smlad r5, ip, r2, r5
smlad r5, r3, r9, r5
pkhbt r1, lr, r4
smlad r5, r6, r1, r5
smladx fp, r3, r8, fp
smladx fp, ip, r4, fp
smladx fp, r6, lr, fp
pkhbt fp, r5, fp, lsl #16
str.w fp, [r0, #28]
smultt r5, r6, lr
smuadx fp, sl, r8
smlad r5, ip, r1, r5
smlad r5, sl, r9, r5
smlad r5, r3, r2, r5
ldr.w r9, [r0]
smladx fp, r3, r4, fp
smladx fp, ip, lr, fp
pkhbt fp, r5, fp, lsl #16
usub16 fp, r9, fp
ldr.w r9, [r0, #4]
str.w fp, [r0]
smultt r5, ip, lr
smuadx fp, sl, r4
smlad r5, sl, r2, r5
smlad r5, r3, r1, r5
smladx fp, r3, lr, fp
pkhbt fp, r5, fp, lsl #16
usub16 fp, r9, fp
ldr.w r9, [r0, #8]
str.w fp, [r0, #4]
smuad r5, sl, r1
smuadx fp, sl, lr
smlatt r5, r3, lr, r5
pkhbt fp, r5, fp, lsl #16
usub16 fp, r9, fp
ldr.w r9, [r0, #12]
ldr.w r1, [sp], #4
str.w fp, [r0, #8]
smultt fp, sl, lr
movt fp, #0
usub16 fp, r9, fp
str.w fp, [r0, #12]
ldr.w lr, [sp], #4
bx lr
.global kara_strd_mem_asm
.type kara_strd_mem_asm, %function
.align 2
kara_strd_mem_asm:
stmdb sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
ldr r4, [r0, #0]
ldr r5, [r0, #4]
ldr r6, [r0, #8]
ldr r7, [r0, #12]
ldr.w r8, [r0, #16]
ldr.w r9, [r0, #20]
ldr.w sl, [r0, #24]
ldr.w fp, [r0, #28]
pkhbt ip, r4, r5, lsl #16
str.w ip, [r0]
pkhtb lr, r5, r4, asr #16
str.w lr, [r2, #64]
uadd16 ip, ip, lr
str.w ip, [r2]
pkhbt ip, r6, r7, lsl #16
str.w ip, [r0, #4]
pkhtb lr, r7, r6, asr #16
str.w lr, [r2, #68]
uadd16 ip, ip, lr
str.w ip, [r2, #4]
pkhbt ip, r8, r9, lsl #16
str.w ip, [r0, #8]
pkhtb lr, r9, r8, asr #16
str.w lr, [r2, #72]
uadd16 ip, ip, lr
str.w ip, [r2, #8]
pkhbt ip, sl, fp, lsl #16
str.w ip, [r0, #12]
pkhtb lr, fp, sl, asr #16
str.w lr, [r2, #76]
uadd16 ip, ip, lr
str.w ip, [r2, #12]
ldr r4, [r0, #32]
ldr r5, [r0, #36]
ldr r6, [r0, #40]
ldr r7, [r0, #44]
ldr.w r8, [r0, #48]
ldr.w r9, [r0, #52]
ldr.w sl, [r0, #56]
ldr.w fp, [r0, #60]
pkhbt ip, r4, r5, lsl #16
str.w ip, [r0, #16]
pkhtb lr, r5, r4, asr #16
str.w lr, [r2, #80]
uadd16 ip, ip, lr
str.w ip, [r2, #16]
pkhbt ip, r6, r7, lsl #16
str.w ip, [r0, #20]
pkhtb lr, r7, r6, asr #16
str.w lr, [r2, #84]
uadd16 ip, ip, lr
str.w ip, [r2, #20]
pkhbt ip, r8, r9, lsl #16
str.w ip, [r0, #24]
pkhtb lr, r9, r8, asr #16
str.w lr, [r2, #88]
uadd16 ip, ip, lr
str.w ip, [r2, #24]
pkhbt ip, sl, fp, lsl #16
str.w ip, [r0, #28]
pkhtb lr, fp, sl, asr #16
str.w lr, [r2, #92]
uadd16 ip, ip, lr
str.w ip, [r2, #28]
ldr r4, [r0, #64]
ldr r5, [r0, #68]
ldr r6, [r0, #72]
ldr r7, [r0, #76]
ldr.w r8, [r0, #80]
ldr.w r9, [r0, #84]
ldr.w sl, [r0, #88]
ldr.w fp, [r0, #92]
pkhbt ip, r4, r5, lsl #16
str.w ip, [r0, #32]
pkhtb lr, r5, r4, asr #16
str.w lr, [r2, #96]
uadd16 ip, ip, lr
str.w ip, [r2, #32]
pkhbt ip, r6, r7, lsl #16
str.w ip, [r0, #36]
pkhtb lr, r7, r6, asr #16
str.w lr, [r2, #100]
uadd16 ip, ip, lr
str.w ip, [r2, #36]
pkhbt ip, r8, r9, lsl #16
str.w ip, [r0, #40]
pkhtb lr, r9, r8, asr #16
str.w lr, [r2, #104]
uadd16 ip, ip, lr
str.w ip, [r2, #40]
pkhbt ip, sl, fp, lsl #16
str.w ip, [r0, #44]
pkhtb lr, fp, sl, asr #16
str.w lr, [r2, #108]
uadd16 ip, ip, lr
str.w ip, [r2, #44]
ldr r4, [r0, #96]
ldr r5, [r0, #100]
ldr r6, [r0, #104]
ldr r7, [r0, #108]
ldr.w r8, [r0, #112]
ldr.w r9, [r0, #116]
ldr.w sl, [r0, #120]
ldr.w fp, [r0, #124]
pkhbt ip, r4, r5, lsl #16
str.w ip, [r0, #48]
pkhtb lr, r5, r4, asr #16
str.w lr, [r2, #112]
uadd16 ip, ip, lr
str.w ip, [r2, #48]
pkhbt ip, r6, r7, lsl #16
str.w ip, [r0, #52]
pkhtb lr, r7, r6, asr #16
str.w lr, [r2, #116]
uadd16 ip, ip, lr
str.w ip, [r2, #52]
pkhbt ip, r8, r9, lsl #16
str.w ip, [r0, #56]
pkhtb lr, r9, r8, asr #16
str.w lr, [r2, #120]
uadd16 ip, ip, lr
str.w ip, [r2, #56]
pkhbt ip, sl, fp, lsl #16
str.w ip, [r0, #60]
pkhtb lr, fp, sl, asr #16
str.w lr, [r2, #124]
uadd16 ip, ip, lr
str.w ip, [r2, #60]
ldr r4, [r1, #0]
ldr r5, [r1, #4]
ldr r6, [r1, #8]
ldr r7, [r1, #12]
ldr.w r8, [r1, #16]
ldr.w r9, [r1, #20]
ldr.w sl, [r1, #24]
ldr.w fp, [r1, #28]
pkhbt ip, r4, r5, lsl #16
str.w ip, [r1]
pkhtb lr, r5, r4, asr #16
str.w lr, [r3]
uadd16 ip, ip, lr
str.w ip, [r0, #64]
pkhbt ip, r6, r7, lsl #16
str.w ip, [r1, #4]
pkhtb lr, r7, r6, asr #16
str.w lr, [r3, #4]
uadd16 ip, ip, lr
str.w ip, [r0, #68]
pkhbt ip, r8, r9, lsl #16
str.w ip, [r1, #8]
pkhtb lr, r9, r8, asr #16
str.w lr, [r3, #8]
uadd16 ip, ip, lr
str.w ip, [r0, #72]
pkhbt ip, sl, fp, lsl #16
str.w ip, [r1, #12]
pkhtb lr, fp, sl, asr #16
str.w lr, [r3, #12]
uadd16 ip, ip, lr
str.w ip, [r0, #76]
ldr r4, [r1, #32]
ldr r5, [r1, #36]
ldr r6, [r1, #40]
ldr r7, [r1, #44]
ldr.w r8, [r1, #48]
ldr.w r9, [r1, #52]
ldr.w sl, [r1, #56]
ldr.w fp, [r1, #60]
pkhbt ip, r4, r5, lsl #16
str.w ip, [r1, #16]
pkhtb lr, r5, r4, asr #16
str.w lr, [r3, #16]
uadd16 ip, ip, lr
str.w ip, [r0, #80]
pkhbt ip, r6, r7, lsl #16
str.w ip, [r1, #20]
pkhtb lr, r7, r6, asr #16
str.w lr, [r3, #20]
uadd16 ip, ip, lr
str.w ip, [r0, #84]
pkhbt ip, r8, r9, lsl #16
str.w ip, [r1, #24]
pkhtb lr, r9, r8, asr #16
str.w lr, [r3, #24]
uadd16 ip, ip, lr
str.w ip, [r0, #88]
pkhbt ip, sl, fp, lsl #16
str.w ip, [r1, #28]
pkhtb lr, fp, sl, asr #16
str.w lr, [r3, #28]
uadd16 ip, ip, lr
str.w ip, [r0, #92]
ldr r4, [r1, #64]
ldr r5, [r1, #68]
ldr r6, [r1, #72]
ldr r7, [r1, #76]
ldr.w r8, [r1, #80]
ldr.w r9, [r1, #84]
ldr.w sl, [r1, #88]
ldr.w fp, [r1, #92]
pkhbt ip, r4, r5, lsl #16
str.w ip, [r1, #32]
pkhtb lr, r5, r4, asr #16
str.w lr, [r3, #32]
uadd16 ip, ip, lr
str.w ip, [r0, #96]
pkhbt ip, r6, r7, lsl #16
str.w ip, [r1, #36]
pkhtb lr, r7, r6, asr #16
str.w lr, [r3, #36]
uadd16 ip, ip, lr
str.w ip, [r0, #100]
pkhbt ip, r8, r9, lsl #16
str.w ip, [r1, #40]
pkhtb lr, r9, r8, asr #16
str.w lr, [r3, #40]
uadd16 ip, ip, lr
str.w ip, [r0, #104]
pkhbt ip, sl, fp, lsl #16
str.w ip, [r1, #44]
pkhtb lr, fp, sl, asr #16
str.w lr, [r3, #44]
uadd16 ip, ip, lr
str.w ip, [r0, #108]
ldr r4, [r1, #96]
ldr r5, [r1, #100]
ldr r6, [r1, #104]
ldr r7, [r1, #108]
ldr.w r8, [r1, #112]
ldr.w r9, [r1, #116]
ldr.w sl, [r1, #120]
ldr.w fp, [r1, #124]
pkhbt ip, r4, r5, lsl #16
str.w ip, [r1, #48]
pkhtb lr, r5, r4, asr #16
str.w lr, [r3, #48]
uadd16 ip, ip, lr
str.w ip, [r0, #112]
pkhbt ip, r6, r7, lsl #16
str.w ip, [r1, #52]
pkhtb lr, r7, r6, asr #16
str.w lr, [r3, #52]
uadd16 ip, ip, lr
str.w ip, [r0, #116]
pkhbt ip, r8, r9, lsl #16
str.w ip, [r1, #56]
pkhtb lr, r9, r8, asr #16
str.w lr, [r3, #56]
uadd16 ip, ip, lr
str.w ip, [r0, #120]
pkhbt ip, sl, fp, lsl #16
str.w ip, [r1, #60]
pkhtb lr, fp, sl, asr #16
str.w lr, [r3, #60]
uadd16 ip, ip, lr
str.w ip, [r0, #124]
ldr r4, [r0, #0]
ldr r5, [r0, #4]
ldr r6, [r0, #8]
ldr r7, [r0, #12]
ldr.w r8, [r0, #16]
ldr.w r9, [r0, #20]
ldr.w sl, [r0, #24]
ldr.w fp, [r0, #28]
pkhbt ip, r4, r5, lsl #16
str.w ip, [r0]
pkhtb lr, r5, r4, asr #16
str.w lr, [r3, #64]
uadd16 ip, ip, lr
str.w ip, [r1, #64]
pkhbt ip, r6, r7, lsl #16
str.w ip, [r0, #4]
pkhtb lr, r7, r6, asr #16
str.w lr, [r3, #68]
uadd16 ip, ip, lr
str.w ip, [r1, #68]
pkhbt ip, r8, r9, lsl #16
str.w ip, [r0, #8]
pkhtb lr, r9, r8, asr #16
str.w lr, [r3, #72]
uadd16 ip, ip, lr
str.w ip, [r1, #72]
pkhbt ip, sl, fp, lsl #16
str.w ip, [r0, #12]
pkhtb lr, fp, sl, asr #16
str.w lr, [r3, #76]
uadd16 ip, ip, lr
str.w ip, [r1, #76]
ldr r4, [r0, #32]
ldr r5, [r0, #36]
ldr r6, [r0, #40]
ldr r7, [r0, #44]
ldr.w r8, [r0, #48]
ldr.w r9, [r0, #52]
ldr.w sl, [r0, #56]
ldr.w fp, [r0, #60]
pkhbt ip, r4, r5, lsl #16
str.w ip, [r0, #16]
pkhtb lr, r5, r4, asr #16
str.w lr, [r3, #80]
uadd16 ip, ip, lr
str.w ip, [r1, #80]
pkhbt ip, r6, r7, lsl #16
str.w ip, [r0, #20]
pkhtb lr, r7, r6, asr #16
str.w lr, [r3, #84]
uadd16 ip, ip, lr
str.w ip, [r1, #84]
pkhbt ip, r8, r9, lsl #16
str.w ip, [r0, #24]
pkhtb lr, r9, r8, asr #16
str.w lr, [r3, #88]
uadd16 ip, ip, lr
str.w ip, [r1, #88]
pkhbt ip, sl, fp, lsl #16
str.w ip, [r0, #28]
pkhtb lr, fp, sl, asr #16
str.w lr, [r3, #92]
uadd16 ip, ip, lr
str.w ip, [r1, #92]
ldr r4, [r1, #0]
ldr r5, [r1, #4]
ldr r6, [r1, #8]
ldr r7, [r1, #12]
ldr.w r8, [r1, #16]
ldr.w r9, [r1, #20]
ldr.w sl, [r1, #24]
ldr.w fp, [r1, #28]
pkhbt ip, r4, r5, lsl #16
str.w ip, [r0, #32]
pkhtb lr, r5, r4, asr #16
str.w lr, [r3, #96]
uadd16 ip, ip, lr
str.w ip, [r1, #96]
pkhbt ip, r6, r7, lsl #16
str.w ip, [r0, #36]
pkhtb lr, r7, r6, asr #16
str.w lr, [r3, #100]
uadd16 ip, ip, lr
str.w ip, [r1, #100]
pkhbt ip, r8, r9, lsl #16
str.w ip, [r0, #40]
pkhtb lr, r9, r8, asr #16
str.w lr, [r3, #104]
uadd16 ip, ip, lr
str.w ip, [r1, #104]
pkhbt ip, sl, fp, lsl #16
str.w ip, [r0, #44]
pkhtb lr, fp, sl, asr #16
str.w lr, [r3, #108]
uadd16 ip, ip, lr
str.w ip, [r1, #108]
ldr r4, [r1, #32]
ldr r5, [r1, #36]
ldr r6, [r1, #40]
ldr r7, [r1, #44]
ldr.w r8, [r1, #48]
ldr.w r9, [r1, #52]
ldr.w sl, [r1, #56]
ldr.w fp, [r1, #60]
pkhbt ip, r4, r5, lsl #16
str.w ip, [r0, #48]
pkhtb lr, r5, r4, asr #16
str.w lr, [r3, #112]
uadd16 ip, ip, lr
str.w ip, [r1, #112]
pkhbt ip, r6, r7, lsl #16
str.w ip, [r0, #52]
pkhtb lr, r7, r6, asr #16
str.w lr, [r3, #116]
uadd16 ip, ip, lr
str.w ip, [r1, #116]
pkhbt ip, r8, r9, lsl #16
str.w ip, [r0, #56]
pkhtb lr, r9, r8, asr #16
str.w lr, [r3, #120]
uadd16 ip, ip, lr
str.w ip, [r1, #120]
pkhbt ip, sl, fp, lsl #16
str.w ip, [r0, #60]
pkhtb lr, fp, sl, asr #16
str.w lr, [r3, #124]
uadd16 ip, ip, lr
str.w ip, [r1, #124]
push {r0, r1, r2, r3}
mov ip, r0
mov r0, r1
mov r1, ip
bl schoolbook_gen
add.w r1, r0, #64
add.w r0, r0, #32
bl schoolbook_gen
ldr.w ip, [sp, #12]
mov.w r0, r1
add.w r1, ip, #64
bl schoolbook_gen
pop {r0, r1, r2, r3}
ldr r4, [r1, #0]
ldr r5, [r1, #4]
ldr r6, [r1, #32]
ldr.w r7, [r1, #36]
ldr.w r8, [r1, #64]
ldr.w r9, [r1, #68]
ldr.w fp, [r1, #66]
usub16 r6, r6, r4
usub16 r7, r7, r5
usub16 r6, r6, r8
usub16 r7, r7, r9
mov.w sl, r8, lsl #16
uadd16 r4, r4, sl
uadd16 r5, r5, fp
pkhbt ip, r4, r6, lsl #16
str.w ip, [r0]
pkhtb ip, r6, r4, asr #16
str.w ip, [r0, #4]
pkhbt ip, r5, r7, lsl #16
str.w ip, [r0, #8]
pkhtb ip, r7, r5, asr #16
str.w ip, [r0, #12]
ldr r4, [r1, #8]
ldr r5, [r1, #12]
ldr r6, [r1, #40]
ldr r7, [r1, #44]
ldr.w r8, [r1, #72]
ldr.w r9, [r1, #76]
ldr.w sl, [r1, #70]
ldr.w fp, [r1, #74]
usub16 r6, r6, r4
usub16 r7, r7, r5
usub16 r6, r6, r8
usub16 r7, r7, r9
uadd16 r4, r4, sl
uadd16 r5, r5, fp
pkhbt ip, r4, r6, lsl #16
str.w ip, [r0, #16]
pkhtb ip, r6, r4, asr #16
str.w ip, [r0, #20]
pkhbt ip, r5, r7, lsl #16
str.w ip, [r0, #24]
pkhtb ip, r7, r5, asr #16
str.w ip, [r0, #28]
ldr r4, [r1, #16]
ldr r5, [r1, #20]
ldr r6, [r1, #48]
ldr r7, [r1, #52]
ldr.w r8, [r1, #80]
ldr.w r9, [r1, #84]
ldr.w sl, [r1, #78]
ldr.w fp, [r1, #82]
usub16 r6, r6, r4
usub16 r7, r7, r5
usub16 r6, r6, r8
usub16 r7, r7, r9
uadd16 r4, r4, sl
uadd16 r5, r5, fp
pkhbt ip, r4, r6, lsl #16
str.w ip, [r0, #32]
pkhtb ip, r6, r4, asr #16
str.w ip, [r0, #36]
pkhbt ip, r5, r7, lsl #16
str.w ip, [r0, #40]
pkhtb ip, r7, r5, asr #16
str.w ip, [r0, #44]
ldr r4, [r1, #24]
ldr r5, [r1, #28]
ldr r6, [r1, #56]
ldr r7, [r1, #60]
ldr.w r8, [r1, #88]
ldr.w r9, [r1, #92]
ldr.w sl, [r1, #86]
ldr.w fp, [r1, #90]
usub16 r6, r6, r4
usub16 r7, r7, r5
usub16 r6, r6, r8
usub16 r7, r7, r9
uadd16 r4, r4, sl
uadd16 r5, r5, fp
pkhbt ip, r4, r6, lsl #16
str.w ip, [r0, #48]
pkhtb ip, r6, r4, asr #16
str.w ip, [r0, #52]
ldrh.w r4, [r0]
pkhbt ip, r5, r7, lsl #16
str.w ip, [r0, #56]
pkhtb ip, r7, r5, asr #16
str.w ip, [r0, #60]
sub.w ip, r4, r9, asr #16
strh.w ip, [r0]
ldr r4, [r2, #0]
ldr r5, [r2, #4]
ldr r6, [r2, #8]
ldr r7, [r2, #12]
ldr.w r8, [r2, #16]
ldr.w r9, [r2, #20]
ldr.w sl, [r2, #24]
ldr.w fp, [r2, #28]
pkhbt ip, r4, r5, lsl #16
str.w ip, [r1]
pkhtb lr, r5, r4, asr #16
str.w lr, [r3, #64]
uadd16 ip, ip, lr
str.w ip, [r1, #64]
pkhbt ip, r6, r7, lsl #16
str.w ip, [r1, #4]
pkhtb lr, r7, r6, asr #16
str.w lr, [r3, #68]
uadd16 ip, ip, lr
str.w ip, [r1, #68]
pkhbt ip, r8, r9, lsl #16
str.w ip, [r1, #8]
pkhtb lr, r9, r8, asr #16
str.w lr, [r3, #72]
uadd16 ip, ip, lr
str.w ip, [r1, #72]
pkhbt ip, sl, fp, lsl #16
str.w ip, [r1, #12]
pkhtb lr, fp, sl, asr #16
str.w lr, [r3, #76]
uadd16 ip, ip, lr
str.w ip, [r1, #76]
ldr r4, [r2, #32]
ldr r5, [r2, #36]
ldr r6, [r2, #40]
ldr r7, [r2, #44]
ldr.w r8, [r2, #48]
ldr.w r9, [r2, #52]
ldr.w sl, [r2, #56]
ldr.w fp, [r2, #60]
pkhbt ip, r4, r5, lsl #16
str.w ip, [r1, #16]
pkhtb lr, r5, r4, asr #16
str.w lr, [r3, #80]
uadd16 ip, ip, lr
str.w ip, [r1, #80]
pkhbt ip, r6, r7, lsl #16
str.w ip, [r1, #20]
pkhtb lr, r7, r6, asr #16
str.w lr, [r3, #84]
uadd16 ip, ip, lr
str.w ip, [r1, #84]
pkhbt ip, r8, r9, lsl #16
str.w ip, [r1, #24]
pkhtb lr, r9, r8, asr #16
str.w lr, [r3, #88]
uadd16 ip, ip, lr
str.w ip, [r1, #88]
pkhbt ip, sl, fp, lsl #16
str.w ip, [r1, #28]
pkhtb lr, fp, sl, asr #16
str.w lr, [r3, #92]
uadd16 ip, ip, lr
str.w ip, [r1, #92]
ldr r4, [r0, #64]
ldr r5, [r0, #68]
ldr r6, [r0, #72]
ldr r7, [r0, #76]
ldr.w r8, [r0, #80]
ldr.w r9, [r0, #84]
ldr.w sl, [r0, #88]
ldr.w fp, [r0, #92]
pkhbt ip, r4, r5, lsl #16
str.w ip, [r1, #32]
pkhtb lr, r5, r4, asr #16
str.w lr, [r3, #96]
uadd16 ip, ip, lr
str.w ip, [r1, #96]
pkhbt ip, r6, r7, lsl #16
str.w ip, [r1, #36]
pkhtb lr, r7, r6, asr #16
str.w lr, [r3, #100]
uadd16 ip, ip, lr
str.w ip, [r1, #100]
pkhbt ip, r8, r9, lsl #16
str.w ip, [r1, #40]
pkhtb lr, r9, r8, asr #16
str.w lr, [r3, #104]
uadd16 ip, ip, lr
str.w ip, [r1, #104]
pkhbt ip, sl, fp, lsl #16
str.w ip, [r1, #44]
pkhtb lr, fp, sl, asr #16
str.w lr, [r3, #108]
uadd16 ip, ip, lr
str.w ip, [r1, #108]
ldr r4, [r0, #96]
ldr r5, [r0, #100]
ldr r6, [r0, #104]
ldr r7, [r0, #108]
ldr.w r8, [r0, #112]
ldr.w r9, [r0, #116]
ldr.w sl, [r0, #120]
ldr.w fp, [r0, #124]
pkhbt ip, r4, r5, lsl #16
str.w ip, [r1, #48]
pkhtb lr, r5, r4, asr #16
str.w lr, [r3, #112]
uadd16 ip, ip, lr
str.w ip, [r1, #112]
pkhbt ip, r6, r7, lsl #16
str.w ip, [r1, #52]
pkhtb lr, r7, r6, asr #16
str.w lr, [r3, #116]
uadd16 ip, ip, lr
str.w ip, [r1, #116]
pkhbt ip, r8, r9, lsl #16
str.w ip, [r1, #56]
pkhtb lr, r9, r8, asr #16
str.w lr, [r3, #120]
uadd16 ip, ip, lr
str.w ip, [r1, #120]
pkhbt ip, sl, fp, lsl #16
str.w ip, [r1, #60]
pkhtb lr, fp, sl, asr #16
str.w lr, [r3, #124]
uadd16 ip, ip, lr
str.w ip, [r1, #124]
push {r0, r1, r2, r3}
mov r0, r2
bl schoolbook_gen
add.w r1, r1, #64
add.w r0, r0, #32
bl schoolbook_gen
ldr.w ip, [sp, #12]
sub.w r0, r1, #64
add.w r1, ip, #64
bl schoolbook_gen
pop {r0, r1, r2, r3}
ldr r4, [r2, #0]
ldr r5, [r2, #4]
ldr r6, [r2, #32]
ldr.w r7, [r2, #36]
ldr.w r8, [r1]
ldr.w r9, [r1, #4]
ldr.w fp, [r1, #2]
usub16 r6, r6, r4
usub16 r7, r7, r5
usub16 r6, r6, r8
usub16 r7, r7, r9
mov.w sl, r8, lsl #16
uadd16 r4, r4, sl
uadd16 r5, r5, fp
pkhbt ip, r4, r6, lsl #16
str.w ip, [r0, #64]
pkhtb ip, r6, r4, asr #16
str.w ip, [r0, #68]
pkhbt ip, r5, r7, lsl #16
str.w ip, [r0, #72]
pkhtb ip, r7, r5, asr #16
str.w ip, [r0, #76]
ldr r4, [r2, #8]
ldr r5, [r2, #12]
ldr r6, [r2, #40]
ldr r7, [r2, #44]
ldr.w r8, [r1, #8]
ldr.w r9, [r1, #12]
ldr.w sl, [r1, #6]
ldr.w fp, [r1, #10]
usub16 r6, r6, r4
usub16 r7, r7, r5
usub16 r6, r6, r8
usub16 r7, r7, r9
uadd16 r4, r4, sl
uadd16 r5, r5, fp
pkhbt ip, r4, r6, lsl #16
str.w ip, [r0, #80]
pkhtb ip, r6, r4, asr #16
str.w ip, [r0, #84]
pkhbt ip, r5, r7, lsl #16
str.w ip, [r0, #88]
pkhtb ip, r7, r5, asr #16
str.w ip, [r0, #92]
ldr r4, [r2, #16]
ldr r5, [r2, #20]
ldr r6, [r2, #48]
ldr r7, [r2, #52]
ldr.w r8, [r1, #16]
ldr.w r9, [r1, #20]
ldr.w sl, [r1, #14]
ldr.w fp, [r1, #18]
usub16 r6, r6, r4
usub16 r7, r7, r5
usub16 r6, r6, r8
usub16 r7, r7, r9
uadd16 r4, r4, sl
uadd16 r5, r5, fp
pkhbt ip, r4, r6, lsl #16
str.w ip, [r0, #96]
pkhtb ip, r6, r4, asr #16
str.w ip, [r0, #100]
pkhbt ip, r5, r7, lsl #16
str.w ip, [r0, #104]
pkhtb ip, r7, r5, asr #16
str.w ip, [r0, #108]
ldr r4, [r2, #24]
ldr r5, [r2, #28]
ldr r6, [r2, #56]
ldr r7, [r2, #60]
ldr.w r8, [r1, #24]
ldr.w r9, [r1, #28]
ldr.w sl, [r1, #22]
ldr.w fp, [r1, #26]
usub16 r6, r6, r4
usub16 r7, r7, r5
usub16 r6, r6, r8
usub16 r7, r7, r9
uadd16 r4, r4, sl
uadd16 r5, r5, fp
pkhbt ip, r4, r6, lsl #16
str.w ip, [r0, #112]
pkhtb ip, r6, r4, asr #16
str.w ip, [r0, #116]
ldrh.w r4, [r0, #64]
pkhbt ip, r5, r7, lsl #16
str.w ip, [r0, #120]
pkhtb ip, r7, r5, asr #16
str.w ip, [r0, #124]
sub.w ip, r4, r9, asr #16
strh.w ip, [r0, #64]
ldr r4, [r2, #64]
ldr r5, [r2, #68]
ldr r6, [r2, #72]
ldr r7, [r2, #76]
ldr.w r8, [r2, #80]
ldr.w r9, [r2, #84]
ldr.w sl, [r2, #88]
ldr.w fp, [r2, #92]
pkhbt ip, r4, r5, lsl #16
str.w ip, [r1]
pkhtb lr, r5, r4, asr #16
str.w lr, [r3, #64]
uadd16 ip, ip, lr
str.w ip, [r1, #64]
pkhbt ip, r6, r7, lsl #16
str.w ip, [r1, #4]
pkhtb lr, r7, r6, asr #16
str.w lr, [r3, #68]
uadd16 ip, ip, lr
str.w ip, [r1, #68]
pkhbt ip, r8, r9, lsl #16
str.w ip, [r1, #8]
pkhtb lr, r9, r8, asr #16
str.w lr, [r3, #72]
uadd16 ip, ip, lr
str.w ip, [r1, #72]
pkhbt ip, sl, fp, lsl #16
str.w ip, [r1, #12]
pkhtb lr, fp, sl, asr #16
str.w lr, [r3, #76]
uadd16 ip, ip, lr
str.w ip, [r1, #76]
ldr r4, [r2, #96]
ldr r5, [r2, #100]
ldr r6, [r2, #104]
ldr r7, [r2, #108]
ldr.w r8, [r2, #112]
ldr.w r9, [r2, #116]
ldr.w sl, [r2, #120]
ldr.w fp, [r2, #124]
pkhbt ip, r4, r5, lsl #16
str.w ip, [r1, #16]
pkhtb lr, r5, r4, asr #16
str.w lr, [r3, #80]
uadd16 ip, ip, lr
str.w ip, [r1, #80]
pkhbt ip, r6, r7, lsl #16
str.w ip, [r1, #20]
pkhtb lr, r7, r6, asr #16
str.w lr, [r3, #84]
uadd16 ip, ip, lr
str.w ip, [r1, #84]
pkhbt ip, r8, r9, lsl #16
str.w ip, [r1, #24]
pkhtb lr, r9, r8, asr #16
str.w lr, [r3, #88]
uadd16 ip, ip, lr
str.w ip, [r1, #88]
pkhbt ip, sl, fp, lsl #16
str.w ip, [r1, #28]
pkhtb lr, fp, sl, asr #16
str.w lr, [r3, #92]
uadd16 ip, ip, lr
str.w ip, [r1, #92]
ldr r4, [r3, #0]
ldr r5, [r3, #4]
ldr r6, [r3, #8]
ldr r7, [r3, #12]
ldr.w r8, [r3, #16]
ldr.w r9, [r3, #20]
ldr.w sl, [r3, #24]
ldr.w fp, [r3, #28]
pkhbt ip, r4, r5, lsl #16
str.w ip, [r1, #32]
pkhtb lr, r5, r4, asr #16
str.w lr, [r3, #96]
uadd16 ip, ip, lr
str.w ip, [r1, #96]
pkhbt ip, r6, r7, lsl #16
str.w ip, [r1, #36]
pkhtb lr, r7, r6, asr #16
str.w lr, [r3, #100]
uadd16 ip, ip, lr
str.w ip, [r1, #100]
pkhbt ip, r8, r9, lsl #16
str.w ip, [r1, #40]
pkhtb lr, r9, r8, asr #16
str.w lr, [r3, #104]
uadd16 ip, ip, lr
str.w ip, [r1, #104]
pkhbt ip, sl, fp, lsl #16
str.w ip, [r1, #44]
pkhtb lr, fp, sl, asr #16
str.w lr, [r3, #108]
uadd16 ip, ip, lr
str.w ip, [r1, #108]
ldr r4, [r3, #32]
ldr r5, [r3, #36]
ldr r6, [r3, #40]
ldr r7, [r3, #44]
ldr.w r8, [r3, #48]
ldr.w r9, [r3, #52]
ldr.w sl, [r3, #56]
ldr.w fp, [r3, #60]
pkhbt ip, r4, r5, lsl #16
str.w ip, [r1, #48]
pkhtb lr, r5, r4, asr #16
str.w lr, [r3, #112]
uadd16 ip, ip, lr
str.w ip, [r1, #112]
pkhbt ip, r6, r7, lsl #16
str.w ip, [r1, #52]
pkhtb lr, r7, r6, asr #16
str.w lr, [r3, #116]
uadd16 ip, ip, lr
str.w ip, [r1, #116]
pkhbt ip, r8, r9, lsl #16
str.w ip, [r1, #56]
pkhtb lr, r9, r8, asr #16
str.w lr, [r3, #120]
uadd16 ip, ip, lr
str.w ip, [r1, #120]
pkhbt ip, sl, fp, lsl #16
str.w ip, [r1, #60]
pkhtb lr, fp, sl, asr #16
str.w lr, [r3, #124]
uadd16 ip, ip, lr
str.w ip, [r1, #124]
push {r0, r1, r2, r3}
mov r0, r2
bl schoolbook_gen
add.w r1, r1, #64
add.w r0, r0, #32
bl schoolbook_gen
ldr.w ip, [sp, #12]
sub.w r0, r1, #64
add.w r1, ip, #64
bl schoolbook_gen
pop {r0, r1, r2, r3}
ldr r4, [r2, #0]
ldr r5, [r2, #4]
ldr r6, [r2, #32]
ldr.w r7, [r2, #36]
ldr.w r8, [r1]
ldr.w r9, [r1, #4]
ldr.w fp, [r1, #2]
usub16 r6, r6, r4
usub16 r7, r7, r5
usub16 r6, r6, r8
usub16 r7, r7, r9
mov.w sl, r8, lsl #16
uadd16 r4, r4, sl
uadd16 r5, r5, fp
pkhbt ip, r4, r6, lsl #16
str.w ip, [r1, #64]
pkhtb ip, r6, r4, asr #16
str.w ip, [r1, #68]
pkhbt ip, r5, r7, lsl #16
str.w ip, [r1, #72]
pkhtb ip, r7, r5, asr #16
str.w ip, [r1, #76]
ldr r4, [r2, #8]
ldr r5, [r2, #12]
ldr r6, [r2, #40]
ldr r7, [r2, #44]
ldr.w r8, [r1, #8]
ldr.w r9, [r1, #12]
ldr.w sl, [r1, #6]
ldr.w fp, [r1, #10]
usub16 r6, r6, r4
usub16 r7, r7, r5
usub16 r6, r6, r8
usub16 r7, r7, r9
uadd16 r4, r4, sl
uadd16 r5, r5, fp
pkhbt ip, r4, r6, lsl #16
str.w ip, [r1, #80]
pkhtb ip, r6, r4, asr #16
str.w ip, [r1, #84]
pkhbt ip, r5, r7, lsl #16
str.w ip, [r1, #88]
pkhtb ip, r7, r5, asr #16
str.w ip, [r1, #92]
ldr r4, [r2, #16]
ldr r5, [r2, #20]
ldr r6, [r2, #48]
ldr r7, [r2, #52]
ldr.w r8, [r1, #16]
ldr.w r9, [r1, #20]
ldr.w sl, [r1, #14]
ldr.w fp, [r1, #18]
usub16 r6, r6, r4
usub16 r7, r7, r5
usub16 r6, r6, r8
usub16 r7, r7, r9
uadd16 r4, r4, sl
uadd16 r5, r5, fp
pkhbt ip, r4, r6, lsl #16
str.w ip, [r1, #96]
pkhtb ip, r6, r4, asr #16
str.w ip, [r1, #100]
pkhbt ip, r5, r7, lsl #16
str.w ip, [r1, #104]
pkhtb ip, r7, r5, asr #16
str.w ip, [r1, #108]
ldr r4, [r2, #24]
ldr r5, [r2, #28]
ldr r6, [r2, #56]
ldr r7, [r2, #60]
ldr.w r8, [r1, #24]
ldr.w r9, [r1, #28]
ldr.w sl, [r1, #22]
ldr.w fp, [r1, #26]
usub16 r6, r6, r4
usub16 r7, r7, r5
usub16 r6, r6, r8
usub16 r7, r7, r9
uadd16 r4, r4, sl
uadd16 r5, r5, fp
pkhbt ip, r4, r6, lsl #16
str.w ip, [r1, #112]
pkhtb ip, r6, r4, asr #16
str.w ip, [r1, #116]
ldrh.w r4, [r1, #64]
pkhbt ip, r5, r7, lsl #16
str.w ip, [r1, #120]
pkhtb ip, r7, r5, asr #16
str.w ip, [r1, #124]
sub.w ip, r4, r9, asr #16
strh.w ip, [r1, #64]
ldr r4, [r0, #0]
ldr r5, [r0, #4]
ldr r6, [r0, #64]
ldr r7, [r0, #68]
ldr.w r8, [r1, #64]
ldr.w r9, [r1, #68]
ldr.w fp, [r1, #66]
usub16 r6, r6, r4
usub16 r7, r7, r5
usub16 r6, r6, r8
usub16 r7, r7, r9
mov.w sl, r8, lsl #16
uadd16 r4, r4, sl
uadd16 r5, r5, fp
pkhbt ip, r4, r6, lsl #16
str.w ip, [r2]
pkhtb ip, r6, r4, asr #16
str.w ip, [r2, #4]
pkhbt ip, r5, r7, lsl #16
str.w ip, [r2, #8]
pkhtb ip, r7, r5, asr #16
str.w ip, [r2, #12]
ldr r4, [r0, #8]
ldr r5, [r0, #12]
ldr r6, [r0, #72]
ldr r7, [r0, #76]
ldr.w r8, [r1, #72]
ldr.w r9, [r1, #76]
ldr.w sl, [r1, #70]
ldr.w fp, [r1, #74]
usub16 r6, r6, r4
usub16 r7, r7, r5
usub16 r6, r6, r8
usub16 r7, r7, r9
uadd16 r4, r4, sl
uadd16 r5, r5, fp
pkhbt ip, r4, r6, lsl #16
str.w ip, [r2, #16]
pkhtb ip, r6, r4, asr #16
str.w ip, [r2, #20]
pkhbt ip, r5, r7, lsl #16
str.w ip, [r2, #24]
pkhtb ip, r7, r5, asr #16
str.w ip, [r2, #28]
ldr r4, [r0, #16]
ldr r5, [r0, #20]
ldr r6, [r0, #80]
ldr r7, [r0, #84]
ldr.w r8, [r1, #80]
ldr.w r9, [r1, #84]
ldr.w sl, [r1, #78]
ldr.w fp, [r1, #82]
usub16 r6, r6, r4
usub16 r7, r7, r5
usub16 r6, r6, r8
usub16 r7, r7, r9
uadd16 r4, r4, sl
uadd16 r5, r5, fp
pkhbt ip, r4, r6, lsl #16
str.w ip, [r2, #32]
pkhtb ip, r6, r4, asr #16
str.w ip, [r2, #36]
pkhbt ip, r5, r7, lsl #16
str.w ip, [r2, #40]
pkhtb ip, r7, r5, asr #16
str.w ip, [r2, #44]
ldr r4, [r0, #24]
ldr r5, [r0, #28]
ldr r6, [r0, #88]
ldr r7, [r0, #92]
ldr.w r8, [r1, #88]
ldr.w r9, [r1, #92]
ldr.w sl, [r1, #86]
ldr.w fp, [r1, #90]
usub16 r6, r6, r4
usub16 r7, r7, r5
usub16 r6, r6, r8
usub16 r7, r7, r9
uadd16 r4, r4, sl
uadd16 r5, r5, fp
pkhbt ip, r4, r6, lsl #16
str.w ip, [r2, #48]
pkhtb ip, r6, r4, asr #16
str.w ip, [r2, #52]
pkhbt ip, r5, r7, lsl #16
str.w ip, [r2, #56]
pkhtb ip, r7, r5, asr #16
str.w ip, [r2, #60]
ldr r4, [r0, #32]
ldr r5, [r0, #36]
ldr r6, [r0, #96]
ldr r7, [r0, #100]
ldr.w r8, [r1, #96]
ldr.w r9, [r1, #100]
ldr.w sl, [r1, #94]
ldr.w fp, [r1, #98]
usub16 r6, r6, r4
usub16 r7, r7, r5
usub16 r6, r6, r8
usub16 r7, r7, r9
uadd16 r4, r4, sl
uadd16 r5, r5, fp
pkhbt ip, r4, r6, lsl #16
str.w ip, [r2, #64]
pkhtb ip, r6, r4, asr #16
str.w ip, [r2, #68]
pkhbt ip, r5, r7, lsl #16
str.w ip, [r2, #72]
pkhtb ip, r7, r5, asr #16
str.w ip, [r2, #76]
ldr r4, [r0, #40]
ldr r5, [r0, #44]
ldr r6, [r0, #104]
ldr r7, [r0, #108]
ldr.w r8, [r1, #104]
ldr.w r9, [r1, #108]
ldr.w sl, [r1, #102]
ldr.w fp, [r1, #106]
usub16 r6, r6, r4
usub16 r7, r7, r5
usub16 r6, r6, r8
usub16 r7, r7, r9
uadd16 r4, r4, sl
uadd16 r5, r5, fp
pkhbt ip, r4, r6, lsl #16
str.w ip, [r2, #80]
pkhtb ip, r6, r4, asr #16
str.w ip, [r2, #84]
pkhbt ip, r5, r7, lsl #16
str.w ip, [r2, #88]
pkhtb ip, r7, r5, asr #16
str.w ip, [r2, #92]
ldr r4, [r0, #48]
ldr r5, [r0, #52]
ldr r6, [r0, #112]
ldr r7, [r0, #116]
ldr.w r8, [r1, #112]
ldr.w r9, [r1, #116]
ldr.w sl, [r1, #110]
ldr.w fp, [r1, #114]
usub16 r6, r6, r4
usub16 r7, r7, r5
usub16 r6, r6, r8
usub16 r7, r7, r9
uadd16 r4, r4, sl
uadd16 r5, r5, fp
pkhbt ip, r4, r6, lsl #16
str.w ip, [r2, #96]
pkhtb ip, r6, r4, asr #16
str.w ip, [r2, #100]
pkhbt ip, r5, r7, lsl #16
str.w ip, [r2, #104]
pkhtb ip, r7, r5, asr #16
str.w ip, [r2, #108]
ldr r4, [r0, #56]
ldr r5, [r0, #60]
ldr r6, [r0, #120]
ldr r7, [r0, #124]
ldr.w r8, [r1, #120]
ldr.w r9, [r1, #124]
ldr.w sl, [r1, #118]
ldr.w fp, [r1, #122]
usub16 r6, r6, r4
usub16 r7, r7, r5
usub16 r6, r6, r8
usub16 r7, r7, r9
uadd16 r4, r4, sl
uadd16 r5, r5, fp
pkhbt ip, r4, r6, lsl #16
str.w ip, [r2, #112]
pkhtb ip, r6, r4, asr #16
str.w ip, [r2, #116]
ldrh.w r4, [r2]
pkhbt ip, r5, r7, lsl #16
str.w ip, [r2, #120]
pkhtb ip, r7, r5, asr #16
str.w ip, [r2, #124]
sub.w ip, r4, r9, asr #16
strh.w ip, [r2]
ldmia.w sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
bx lr
