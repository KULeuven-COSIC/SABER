.syntax unified
.cpu cortex-m4
.global toom_cook_4way_striding_asm
.type toom_cook_4way_striding_asm, %function
.align 2
toom_cook_4way_striding_asm:
stmdb sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
sub.w sp, sp, #1664
ldr r4, [r0, #0]
ldr r6, [r0, #8]
ldr r5, [r0, #4]
ldr r7, [r0, #12]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #256]
str.w fp, [sp, #384]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #512]
str.w fp, [sp, #640]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #128]
str.w ip, [sp, #768]
str r7, [sp, #0]
ldr r4, [r0, #16]
ldr r6, [r0, #24]
ldr r5, [r0, #20]
ldr.w r7, [r0, #28]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #260]
str.w fp, [sp, #388]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #516]
str.w fp, [sp, #644]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #132]
str.w ip, [sp, #772]
str r7, [sp, #4]
ldr r4, [r0, #32]
ldr r6, [r0, #40]
ldr r5, [r0, #36]
ldr.w r7, [r0, #44]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #264]
str.w fp, [sp, #392]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #520]
str.w fp, [sp, #648]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #136]
str.w ip, [sp, #776]
str r7, [sp, #8]
ldr r4, [r0, #48]
ldr r6, [r0, #56]
ldr r5, [r0, #52]
ldr.w r7, [r0, #60]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #268]
str.w fp, [sp, #396]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #524]
str.w fp, [sp, #652]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #140]
str.w ip, [sp, #780]
str r7, [sp, #12]
ldr r4, [r0, #64]
ldr r6, [r0, #72]
ldr r5, [r0, #68]
ldr.w r7, [r0, #76]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #272]
str.w fp, [sp, #400]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #528]
str.w fp, [sp, #656]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #144]
str.w ip, [sp, #784]
str r7, [sp, #16]
ldr r4, [r0, #80]
ldr r6, [r0, #88]
ldr r5, [r0, #84]
ldr.w r7, [r0, #92]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #276]
str.w fp, [sp, #404]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #532]
str.w fp, [sp, #660]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #148]
str.w ip, [sp, #788]
str r7, [sp, #20]
ldr r4, [r0, #96]
ldr r6, [r0, #104]
ldr r5, [r0, #100]
ldr.w r7, [r0, #108]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #280]
str.w fp, [sp, #408]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #536]
str.w fp, [sp, #664]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #152]
str.w ip, [sp, #792]
str r7, [sp, #24]
ldr r4, [r0, #112]
ldr r6, [r0, #120]
ldr r5, [r0, #116]
ldr.w r7, [r0, #124]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #284]
str.w fp, [sp, #412]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #540]
str.w fp, [sp, #668]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #156]
str.w ip, [sp, #796]
str.w r7, [sp, #28]
ldr.w r4, [r0, #128]
ldr.w r6, [r0, #136]
ldr.w r5, [r0, #132]
ldr.w r7, [r0, #140]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #288]
str.w fp, [sp, #416]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #544]
str.w fp, [sp, #672]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #160]
str.w ip, [sp, #800]
str.w r7, [sp, #32]
ldr.w r4, [r0, #144]
ldr.w r6, [r0, #152]
ldr.w r5, [r0, #148]
ldr.w r7, [r0, #156]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #292]
str.w fp, [sp, #420]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #548]
str.w fp, [sp, #676]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #164]
str.w ip, [sp, #804]
str.w r7, [sp, #36]
ldr.w r4, [r0, #160]
ldr.w r6, [r0, #168]
ldr.w r5, [r0, #164]
ldr.w r7, [r0, #172]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #296]
str.w fp, [sp, #424]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #552]
str.w fp, [sp, #680]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #168]
str.w ip, [sp, #808]
str.w r7, [sp, #40]
ldr.w r4, [r0, #176]
ldr.w r6, [r0, #184]
ldr.w r5, [r0, #180]
ldr.w r7, [r0, #188]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #300]
str.w fp, [sp, #428]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #556]
str.w fp, [sp, #684]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #172]
str.w ip, [sp, #812]
str.w r7, [sp, #44]
ldr.w r4, [r0, #192]
ldr.w r6, [r0, #200]
ldr.w r5, [r0, #196]
ldr.w r7, [r0, #204]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #304]
str.w fp, [sp, #432]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #560]
str.w fp, [sp, #688]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #176]
str.w ip, [sp, #816]
str.w r7, [sp, #48]
ldr.w r4, [r0, #208]
ldr.w r6, [r0, #216]
ldr.w r5, [r0, #212]
ldr.w r7, [r0, #220]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #308]
str.w fp, [sp, #436]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #564]
str.w fp, [sp, #692]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #180]
str.w ip, [sp, #820]
str.w r7, [sp, #52]
ldr.w r4, [r0, #224]
ldr.w r6, [r0, #232]
ldr.w r5, [r0, #228]
ldr.w r7, [r0, #236]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #312]
str.w fp, [sp, #440]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #568]
str.w fp, [sp, #696]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #184]
str.w ip, [sp, #824]
str.w r7, [sp, #56]
ldr.w r4, [r0, #240]
ldr.w r6, [r0, #248]
ldr.w r5, [r0, #244]
ldr.w r7, [r0, #252]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #316]
str.w fp, [sp, #444]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #572]
str.w fp, [sp, #700]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #188]
str.w ip, [sp, #828]
str.w r7, [sp, #60]
ldr.w r4, [r0, #256]
ldr.w r6, [r0, #264]
ldr.w r5, [r0, #260]
ldr.w r7, [r0, #268]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #320]
str.w fp, [sp, #448]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #576]
str.w fp, [sp, #704]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #192]
str.w ip, [sp, #832]
str.w r7, [sp, #64]
ldr.w r4, [r0, #272]
ldr.w r6, [r0, #280]
ldr.w r5, [r0, #276]
ldr.w r7, [r0, #284]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #324]
str.w fp, [sp, #452]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #580]
str.w fp, [sp, #708]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #196]
str.w ip, [sp, #836]
str.w r7, [sp, #68]
ldr.w r4, [r0, #288]
ldr.w r6, [r0, #296]
ldr.w r5, [r0, #292]
ldr.w r7, [r0, #300]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #328]
str.w fp, [sp, #456]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #584]
str.w fp, [sp, #712]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #200]
str.w ip, [sp, #840]
str.w r7, [sp, #72]
ldr.w r4, [r0, #304]
ldr.w r6, [r0, #312]
ldr.w r5, [r0, #308]
ldr.w r7, [r0, #316]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #332]
str.w fp, [sp, #460]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #588]
str.w fp, [sp, #716]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #204]
str.w ip, [sp, #844]
str.w r7, [sp, #76]
ldr.w r4, [r0, #320]
ldr.w r6, [r0, #328]
ldr.w r5, [r0, #324]
ldr.w r7, [r0, #332]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #336]
str.w fp, [sp, #464]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #592]
str.w fp, [sp, #720]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #208]
str.w ip, [sp, #848]
str.w r7, [sp, #80]
ldr.w r4, [r0, #336]
ldr.w r6, [r0, #344]
ldr.w r5, [r0, #340]
ldr.w r7, [r0, #348]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #340]
str.w fp, [sp, #468]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #596]
str.w fp, [sp, #724]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #212]
str.w ip, [sp, #852]
str.w r7, [sp, #84]
ldr.w r4, [r0, #352]
ldr.w r6, [r0, #360]
ldr.w r5, [r0, #356]
ldr.w r7, [r0, #364]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #344]
str.w fp, [sp, #472]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #600]
str.w fp, [sp, #728]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #216]
str.w ip, [sp, #856]
str.w r7, [sp, #88]
ldr.w r4, [r0, #368]
ldr.w r6, [r0, #376]
ldr.w r5, [r0, #372]
ldr.w r7, [r0, #380]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #348]
str.w fp, [sp, #476]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #604]
str.w fp, [sp, #732]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #220]
str.w ip, [sp, #860]
str.w r7, [sp, #92]
ldr.w r4, [r0, #384]
ldr.w r6, [r0, #392]
ldr.w r5, [r0, #388]
ldr.w r7, [r0, #396]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #352]
str.w fp, [sp, #480]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #608]
str.w fp, [sp, #736]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #224]
str.w ip, [sp, #864]
str.w r7, [sp, #96]
ldr.w r4, [r0, #400]
ldr.w r6, [r0, #408]
ldr.w r5, [r0, #404]
ldr.w r7, [r0, #412]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #356]
str.w fp, [sp, #484]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #612]
str.w fp, [sp, #740]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #228]
str.w ip, [sp, #868]
str.w r7, [sp, #100]
ldr.w r4, [r0, #416]
ldr.w r6, [r0, #424]
ldr.w r5, [r0, #420]
ldr.w r7, [r0, #428]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #360]
str.w fp, [sp, #488]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #616]
str.w fp, [sp, #744]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #232]
str.w ip, [sp, #872]
str.w r7, [sp, #104]
ldr.w r4, [r0, #432]
ldr.w r6, [r0, #440]
ldr.w r5, [r0, #436]
ldr.w r7, [r0, #444]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #364]
str.w fp, [sp, #492]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #620]
str.w fp, [sp, #748]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #236]
str.w ip, [sp, #876]
str.w r7, [sp, #108]
ldr.w r4, [r0, #448]
ldr.w r6, [r0, #456]
ldr.w r5, [r0, #452]
ldr.w r7, [r0, #460]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #368]
str.w fp, [sp, #496]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #624]
str.w fp, [sp, #752]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #240]
str.w ip, [sp, #880]
str.w r7, [sp, #112]
ldr.w r4, [r0, #464]
ldr.w r6, [r0, #472]
ldr.w r5, [r0, #468]
ldr.w r7, [r0, #476]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #372]
str.w fp, [sp, #500]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #628]
str.w fp, [sp, #756]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #244]
str.w ip, [sp, #884]
str.w r7, [sp, #116]
ldr.w r4, [r0, #480]
ldr.w r6, [r0, #488]
ldr.w r5, [r0, #484]
ldr.w r7, [r0, #492]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #376]
str.w fp, [sp, #504]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #632]
str.w fp, [sp, #760]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #248]
str.w ip, [sp, #888]
str.w r7, [sp, #120]
ldr.w r4, [r0, #496]
ldr.w r6, [r0, #504]
ldr.w r5, [r0, #500]
ldr.w r7, [r0, #508]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #380]
str.w fp, [sp, #508]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #636]
str.w fp, [sp, #764]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #252]
str.w ip, [sp, #892]
str r7, [sp, #124]
ldr r4, [r1, #0]
ldr r6, [r1, #8]
ldr r5, [r1, #4]
ldr.w r7, [r1, #12]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1024]
str.w fp, [sp, #1152]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1280]
str.w fp, [sp, #1408]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #896]
str.w ip, [sp, #1536]
str r7, [r1, #0]
ldr r4, [r1, #16]
ldr r6, [r1, #24]
ldr r5, [r1, #20]
ldr.w r7, [r1, #28]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1028]
str.w fp, [sp, #1156]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1284]
str.w fp, [sp, #1412]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #900]
str.w ip, [sp, #1540]
str r7, [r1, #4]
ldr r4, [r1, #32]
ldr r6, [r1, #40]
ldr r5, [r1, #36]
ldr.w r7, [r1, #44]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1032]
str.w fp, [sp, #1160]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1288]
str.w fp, [sp, #1416]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #904]
str.w ip, [sp, #1544]
str r7, [r1, #8]
ldr r4, [r1, #48]
ldr r6, [r1, #56]
ldr r5, [r1, #52]
ldr.w r7, [r1, #60]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1036]
str.w fp, [sp, #1164]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1292]
str.w fp, [sp, #1420]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #908]
str.w ip, [sp, #1548]
str r7, [r1, #12]
ldr r4, [r1, #64]
ldr r6, [r1, #72]
ldr r5, [r1, #68]
ldr.w r7, [r1, #76]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1040]
str.w fp, [sp, #1168]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1296]
str.w fp, [sp, #1424]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #912]
str.w ip, [sp, #1552]
str r7, [r1, #16]
ldr r4, [r1, #80]
ldr r6, [r1, #88]
ldr r5, [r1, #84]
ldr.w r7, [r1, #92]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1044]
str.w fp, [sp, #1172]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1300]
str.w fp, [sp, #1428]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #916]
str.w ip, [sp, #1556]
str r7, [r1, #20]
ldr r4, [r1, #96]
ldr r6, [r1, #104]
ldr r5, [r1, #100]
ldr.w r7, [r1, #108]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1048]
str.w fp, [sp, #1176]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1304]
str.w fp, [sp, #1432]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #920]
str.w ip, [sp, #1560]
str r7, [r1, #24]
ldr r4, [r1, #112]
ldr r6, [r1, #120]
ldr r5, [r1, #116]
ldr.w r7, [r1, #124]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1052]
str.w fp, [sp, #1180]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1308]
str.w fp, [sp, #1436]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #924]
str.w ip, [sp, #1564]
str.w r7, [r1, #28]
ldr.w r4, [r1, #128]
ldr.w r6, [r1, #136]
ldr.w r5, [r1, #132]
ldr.w r7, [r1, #140]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1056]
str.w fp, [sp, #1184]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1312]
str.w fp, [sp, #1440]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #928]
str.w ip, [sp, #1568]
str.w r7, [r1, #32]
ldr.w r4, [r1, #144]
ldr.w r6, [r1, #152]
ldr.w r5, [r1, #148]
ldr.w r7, [r1, #156]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1060]
str.w fp, [sp, #1188]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1316]
str.w fp, [sp, #1444]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #932]
str.w ip, [sp, #1572]
str.w r7, [r1, #36]
ldr.w r4, [r1, #160]
ldr.w r6, [r1, #168]
ldr.w r5, [r1, #164]
ldr.w r7, [r1, #172]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1064]
str.w fp, [sp, #1192]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1320]
str.w fp, [sp, #1448]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #936]
str.w ip, [sp, #1576]
str.w r7, [r1, #40]
ldr.w r4, [r1, #176]
ldr.w r6, [r1, #184]
ldr.w r5, [r1, #180]
ldr.w r7, [r1, #188]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1068]
str.w fp, [sp, #1196]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1324]
str.w fp, [sp, #1452]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #940]
str.w ip, [sp, #1580]
str.w r7, [r1, #44]
ldr.w r4, [r1, #192]
ldr.w r6, [r1, #200]
ldr.w r5, [r1, #196]
ldr.w r7, [r1, #204]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1072]
str.w fp, [sp, #1200]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1328]
str.w fp, [sp, #1456]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #944]
str.w ip, [sp, #1584]
str.w r7, [r1, #48]
ldr.w r4, [r1, #208]
ldr.w r6, [r1, #216]
ldr.w r5, [r1, #212]
ldr.w r7, [r1, #220]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1076]
str.w fp, [sp, #1204]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1332]
str.w fp, [sp, #1460]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #948]
str.w ip, [sp, #1588]
str.w r7, [r1, #52]
ldr.w r4, [r1, #224]
ldr.w r6, [r1, #232]
ldr.w r5, [r1, #228]
ldr.w r7, [r1, #236]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1080]
str.w fp, [sp, #1208]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1336]
str.w fp, [sp, #1464]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #952]
str.w ip, [sp, #1592]
str.w r7, [r1, #56]
ldr.w r4, [r1, #240]
ldr.w r6, [r1, #248]
ldr.w r5, [r1, #244]
ldr.w r7, [r1, #252]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1084]
str.w fp, [sp, #1212]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1340]
str.w fp, [sp, #1468]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #956]
str.w ip, [sp, #1596]
str.w r7, [r1, #60]
ldr.w r4, [r1, #256]
ldr.w r6, [r1, #264]
ldr.w r5, [r1, #260]
ldr.w r7, [r1, #268]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1088]
str.w fp, [sp, #1216]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1344]
str.w fp, [sp, #1472]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #960]
str.w ip, [sp, #1600]
str.w r7, [r1, #64]
ldr.w r4, [r1, #272]
ldr.w r6, [r1, #280]
ldr.w r5, [r1, #276]
ldr.w r7, [r1, #284]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1092]
str.w fp, [sp, #1220]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1348]
str.w fp, [sp, #1476]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #964]
str.w ip, [sp, #1604]
str.w r7, [r1, #68]
ldr.w r4, [r1, #288]
ldr.w r6, [r1, #296]
ldr.w r5, [r1, #292]
ldr.w r7, [r1, #300]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1096]
str.w fp, [sp, #1224]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1352]
str.w fp, [sp, #1480]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #968]
str.w ip, [sp, #1608]
str.w r7, [r1, #72]
ldr.w r4, [r1, #304]
ldr.w r6, [r1, #312]
ldr.w r5, [r1, #308]
ldr.w r7, [r1, #316]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1100]
str.w fp, [sp, #1228]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1356]
str.w fp, [sp, #1484]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #972]
str.w ip, [sp, #1612]
str.w r7, [r1, #76]
ldr.w r4, [r1, #320]
ldr.w r6, [r1, #328]
ldr.w r5, [r1, #324]
ldr.w r7, [r1, #332]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1104]
str.w fp, [sp, #1232]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1360]
str.w fp, [sp, #1488]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #976]
str.w ip, [sp, #1616]
str.w r7, [r1, #80]
ldr.w r4, [r1, #336]
ldr.w r6, [r1, #344]
ldr.w r5, [r1, #340]
ldr.w r7, [r1, #348]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1108]
str.w fp, [sp, #1236]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1364]
str.w fp, [sp, #1492]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #980]
str.w ip, [sp, #1620]
str.w r7, [r1, #84]
ldr.w r4, [r1, #352]
ldr.w r6, [r1, #360]
ldr.w r5, [r1, #356]
ldr.w r7, [r1, #364]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1112]
str.w fp, [sp, #1240]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1368]
str.w fp, [sp, #1496]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #984]
str.w ip, [sp, #1624]
str.w r7, [r1, #88]
ldr.w r4, [r1, #368]
ldr.w r6, [r1, #376]
ldr.w r5, [r1, #372]
ldr.w r7, [r1, #380]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1116]
str.w fp, [sp, #1244]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1372]
str.w fp, [sp, #1500]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #988]
str.w ip, [sp, #1628]
str.w r7, [r1, #92]
ldr.w r4, [r1, #384]
ldr.w r6, [r1, #392]
ldr.w r5, [r1, #388]
ldr.w r7, [r1, #396]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1120]
str.w fp, [sp, #1248]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1376]
str.w fp, [sp, #1504]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #992]
str.w ip, [sp, #1632]
str.w r7, [r1, #96]
ldr.w r4, [r1, #400]
ldr.w r6, [r1, #408]
ldr.w r5, [r1, #404]
ldr.w r7, [r1, #412]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1124]
str.w fp, [sp, #1252]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1380]
str.w fp, [sp, #1508]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #996]
str.w ip, [sp, #1636]
str.w r7, [r1, #100]
ldr.w r4, [r1, #416]
ldr.w r6, [r1, #424]
ldr.w r5, [r1, #420]
ldr.w r7, [r1, #428]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1128]
str.w fp, [sp, #1256]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1384]
str.w fp, [sp, #1512]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #1000]
str.w ip, [sp, #1640]
str.w r7, [r1, #104]
ldr.w r4, [r1, #432]
ldr.w r6, [r1, #440]
ldr.w r5, [r1, #436]
ldr.w r7, [r1, #444]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1132]
str.w fp, [sp, #1260]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1388]
str.w fp, [sp, #1516]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #1004]
str.w ip, [sp, #1644]
str.w r7, [r1, #108]
ldr.w r4, [r1, #448]
ldr.w r6, [r1, #456]
ldr.w r5, [r1, #452]
ldr.w r7, [r1, #460]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1136]
str.w fp, [sp, #1264]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1392]
str.w fp, [sp, #1520]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #1008]
str.w ip, [sp, #1648]
str.w r7, [r1, #112]
ldr.w r4, [r1, #464]
ldr.w r6, [r1, #472]
ldr.w r5, [r1, #468]
ldr.w r7, [r1, #476]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1140]
str.w fp, [sp, #1268]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1396]
str.w fp, [sp, #1524]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #1012]
str.w ip, [sp, #1652]
str.w r7, [r1, #116]
ldr.w r4, [r1, #480]
ldr.w r6, [r1, #488]
ldr.w r5, [r1, #484]
ldr.w r7, [r1, #492]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1144]
str.w fp, [sp, #1272]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1400]
str.w fp, [sp, #1528]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #1016]
str.w ip, [sp, #1656]
str.w r7, [r1, #120]
ldr.w r4, [r1, #496]
ldr.w r6, [r1, #504]
ldr.w r5, [r1, #500]
ldr.w r7, [r1, #508]
pkhbt ip, r4, r6, lsl #16
pkhtb r6, r6, r4, asr #16
pkhbt lr, r5, r7, lsl #16
pkhtb r7, r7, r5, asr #16
uadd16 r8, ip, r6
uadd16 r9, lr, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1148]
str.w fp, [sp, #1276]
uadd16 r8, ip, ip
uadd16 r8, r8, r8
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r9, lr, lr
uadd16 r9, r9, r9
uadd16 r9, r9, r7
uadd16 sl, r8, r9
usub16 fp, r8, r9
str.w sl, [sp, #1404]
str.w fp, [sp, #1532]
uadd16 r8, r7, r7
uadd16 r8, r8, r6
uadd16 r8, r8, r8
uadd16 r8, r8, lr
uadd16 r8, r8, r8
uadd16 r8, r8, ip
str.w r8, [sp, #1020]
str.w ip, [sp, #1660]
str r7, [r1, #124]
mov r3, sp
push {r0, r1, r2}
mov r0, r3
add.w r2, r1, #128
add.w r3, r1, #256
bl kara_strd_mem_asm
mov.w r2, r1
add.w r1, r0, #896
add.w r0, r0, #128
bl kara_strd_mem_asm
mov.w r2, r1
add.w r1, r1, #128
add.w r0, r0, #128
bl kara_strd_mem_asm
mov.w r2, r1
add.w r1, r1, #128
add.w r0, r0, #128
bl kara_strd_mem_asm
mov.w r2, r1
add.w r1, r1, #128
add.w r0, r0, #128
bl kara_strd_mem_asm
mov.w r2, r1
add.w r1, r1, #128
add.w r0, r0, #128
bl kara_strd_mem_asm
mov.w r2, r1
add.w r1, r1, #128
add.w r0, r0, #128
bl kara_strd_mem_asm
ldmia.w sp!, {r0, r1, r2}
eor.w r9, r9, r9
eor.w r8, r8, r8
ldr.w r4, [r1, #128]
ldr r5, [r1, #0]
ldr r6, [sp, #896]
ldr.w r7, [sp, #1024]
ldr.w r8, [sp, #1152]
ldr.w r9, [sp, #1280]
ldr.w sl, [sp, #1408]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr r4, [r2, #0]
ldr r5, [r2, #4]
ldr.w r6, [r2, #8]
ldr.w fp, [r2, #12]
uadd16 r4, r4, r0
str.w r4, [r2]
uadd16 r5, r5, r3
str.w r5, [r2, #4]
uadd16 r6, r6, r9
str.w r6, [r2, #8]
uadd16 fp, fp, sl
str.w fp, [r2, #12]
ldr.w r4, [r1, #132]
ldr r5, [r1, #4]
ldr r6, [sp, #900]
ldr.w r7, [sp, #1028]
ldr.w r8, [sp, #1156]
ldr.w r9, [sp, #1284]
ldr.w sl, [sp, #1412]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr r4, [r2, #16]
ldr r5, [r2, #20]
ldr.w r6, [r2, #24]
ldr.w fp, [r2, #28]
uadd16 r4, r4, r0
str.w r4, [r2, #16]
uadd16 r5, r5, r3
str.w r5, [r2, #20]
uadd16 r6, r6, r9
str.w r6, [r2, #24]
uadd16 fp, fp, sl
str.w fp, [r2, #28]
ldr.w r4, [r1, #136]
ldr r5, [r1, #8]
ldr r6, [sp, #904]
ldr.w r7, [sp, #1032]
ldr.w r8, [sp, #1160]
ldr.w r9, [sp, #1288]
ldr.w sl, [sp, #1416]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr r4, [r2, #32]
ldr r5, [r2, #36]
ldr.w r6, [r2, #40]
ldr.w fp, [r2, #44]
uadd16 r4, r4, r0
str.w r4, [r2, #32]
uadd16 r5, r5, r3
str.w r5, [r2, #36]
uadd16 r6, r6, r9
str.w r6, [r2, #40]
uadd16 fp, fp, sl
str.w fp, [r2, #44]
ldr.w r4, [r1, #140]
ldr r5, [r1, #12]
ldr r6, [sp, #908]
ldr.w r7, [sp, #1036]
ldr.w r8, [sp, #1164]
ldr.w r9, [sp, #1292]
ldr.w sl, [sp, #1420]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr r4, [r2, #48]
ldr r5, [r2, #52]
ldr.w r6, [r2, #56]
ldr.w fp, [r2, #60]
uadd16 r4, r4, r0
str.w r4, [r2, #48]
uadd16 r5, r5, r3
str.w r5, [r2, #52]
uadd16 r6, r6, r9
str.w r6, [r2, #56]
uadd16 fp, fp, sl
str.w fp, [r2, #60]
ldr.w r4, [r1, #144]
ldr r5, [r1, #16]
ldr r6, [sp, #912]
ldr.w r7, [sp, #1040]
ldr.w r8, [sp, #1168]
ldr.w r9, [sp, #1296]
ldr.w sl, [sp, #1424]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr r4, [r2, #64]
ldr r5, [r2, #68]
ldr.w r6, [r2, #72]
ldr.w fp, [r2, #76]
uadd16 r4, r4, r0
str.w r4, [r2, #64]
uadd16 r5, r5, r3
str.w r5, [r2, #68]
uadd16 r6, r6, r9
str.w r6, [r2, #72]
uadd16 fp, fp, sl
str.w fp, [r2, #76]
ldr.w r4, [r1, #148]
ldr r5, [r1, #20]
ldr r6, [sp, #916]
ldr.w r7, [sp, #1044]
ldr.w r8, [sp, #1172]
ldr.w r9, [sp, #1300]
ldr.w sl, [sp, #1428]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr r4, [r2, #80]
ldr r5, [r2, #84]
ldr.w r6, [r2, #88]
ldr.w fp, [r2, #92]
uadd16 r4, r4, r0
str.w r4, [r2, #80]
uadd16 r5, r5, r3
str.w r5, [r2, #84]
uadd16 r6, r6, r9
str.w r6, [r2, #88]
uadd16 fp, fp, sl
str.w fp, [r2, #92]
ldr.w r4, [r1, #152]
ldr r5, [r1, #24]
ldr r6, [sp, #920]
ldr.w r7, [sp, #1048]
ldr.w r8, [sp, #1176]
ldr.w r9, [sp, #1304]
ldr.w sl, [sp, #1432]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr r4, [r2, #96]
ldr r5, [r2, #100]
ldr.w r6, [r2, #104]
ldr.w fp, [r2, #108]
uadd16 r4, r4, r0
str.w r4, [r2, #96]
uadd16 r5, r5, r3
str.w r5, [r2, #100]
uadd16 r6, r6, r9
str.w r6, [r2, #104]
uadd16 fp, fp, sl
str.w fp, [r2, #108]
ldr.w r4, [r1, #156]
ldr r5, [r1, #28]
ldr r6, [sp, #924]
ldr.w r7, [sp, #1052]
ldr.w r8, [sp, #1180]
ldr.w r9, [sp, #1308]
ldr.w sl, [sp, #1436]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr r4, [r2, #112]
ldr r5, [r2, #116]
ldr.w r6, [r2, #120]
ldr.w fp, [r2, #124]
uadd16 r4, r4, r0
str.w r4, [r2, #112]
uadd16 r5, r5, r3
str.w r5, [r2, #116]
uadd16 r6, r6, r9
str.w r6, [r2, #120]
uadd16 fp, fp, sl
str.w fp, [r2, #124]
ldr.w r4, [r1, #160]
ldr r5, [r1, #32]
ldr r6, [sp, #928]
ldr.w r7, [sp, #1056]
ldr.w r8, [sp, #1184]
ldr.w r9, [sp, #1312]
ldr.w sl, [sp, #1440]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr.w r4, [r2, #128]
ldr.w r5, [r2, #132]
ldr.w r6, [r2, #136]
ldr.w fp, [r2, #140]
uadd16 r4, r4, r0
str.w r4, [r2, #128]
uadd16 r5, r5, r3
str.w r5, [r2, #132]
uadd16 r6, r6, r9
str.w r6, [r2, #136]
uadd16 fp, fp, sl
str.w fp, [r2, #140]
ldr.w r4, [r1, #164]
ldr r5, [r1, #36]
ldr r6, [sp, #932]
ldr.w r7, [sp, #1060]
ldr.w r8, [sp, #1188]
ldr.w r9, [sp, #1316]
ldr.w sl, [sp, #1444]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr.w r4, [r2, #144]
ldr.w r5, [r2, #148]
ldr.w r6, [r2, #152]
ldr.w fp, [r2, #156]
uadd16 r4, r4, r0
str.w r4, [r2, #144]
uadd16 r5, r5, r3
str.w r5, [r2, #148]
uadd16 r6, r6, r9
str.w r6, [r2, #152]
uadd16 fp, fp, sl
str.w fp, [r2, #156]
ldr.w r4, [r1, #168]
ldr r5, [r1, #40]
ldr r6, [sp, #936]
ldr.w r7, [sp, #1064]
ldr.w r8, [sp, #1192]
ldr.w r9, [sp, #1320]
ldr.w sl, [sp, #1448]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr.w r4, [r2, #160]
ldr.w r5, [r2, #164]
ldr.w r6, [r2, #168]
ldr.w fp, [r2, #172]
uadd16 r4, r4, r0
str.w r4, [r2, #160]
uadd16 r5, r5, r3
str.w r5, [r2, #164]
uadd16 r6, r6, r9
str.w r6, [r2, #168]
uadd16 fp, fp, sl
str.w fp, [r2, #172]
ldr.w r4, [r1, #172]
ldr r5, [r1, #44]
ldr r6, [sp, #940]
ldr.w r7, [sp, #1068]
ldr.w r8, [sp, #1196]
ldr.w r9, [sp, #1324]
ldr.w sl, [sp, #1452]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr.w r4, [r2, #176]
ldr.w r5, [r2, #180]
ldr.w r6, [r2, #184]
ldr.w fp, [r2, #188]
uadd16 r4, r4, r0
str.w r4, [r2, #176]
uadd16 r5, r5, r3
str.w r5, [r2, #180]
uadd16 r6, r6, r9
str.w r6, [r2, #184]
uadd16 fp, fp, sl
str.w fp, [r2, #188]
ldr.w r4, [r1, #176]
ldr r5, [r1, #48]
ldr r6, [sp, #944]
ldr.w r7, [sp, #1072]
ldr.w r8, [sp, #1200]
ldr.w r9, [sp, #1328]
ldr.w sl, [sp, #1456]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr.w r4, [r2, #192]
ldr.w r5, [r2, #196]
ldr.w r6, [r2, #200]
ldr.w fp, [r2, #204]
uadd16 r4, r4, r0
str.w r4, [r2, #192]
uadd16 r5, r5, r3
str.w r5, [r2, #196]
uadd16 r6, r6, r9
str.w r6, [r2, #200]
uadd16 fp, fp, sl
str.w fp, [r2, #204]
ldr.w r4, [r1, #180]
ldr r5, [r1, #52]
ldr r6, [sp, #948]
ldr.w r7, [sp, #1076]
ldr.w r8, [sp, #1204]
ldr.w r9, [sp, #1332]
ldr.w sl, [sp, #1460]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr.w r4, [r2, #208]
ldr.w r5, [r2, #212]
ldr.w r6, [r2, #216]
ldr.w fp, [r2, #220]
uadd16 r4, r4, r0
str.w r4, [r2, #208]
uadd16 r5, r5, r3
str.w r5, [r2, #212]
uadd16 r6, r6, r9
str.w r6, [r2, #216]
uadd16 fp, fp, sl
str.w fp, [r2, #220]
ldr.w r4, [r1, #184]
ldr r5, [r1, #56]
ldr r6, [sp, #952]
ldr.w r7, [sp, #1080]
ldr.w r8, [sp, #1208]
ldr.w r9, [sp, #1336]
ldr.w sl, [sp, #1464]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr.w r4, [r2, #224]
ldr.w r5, [r2, #228]
ldr.w r6, [r2, #232]
ldr.w fp, [r2, #236]
uadd16 r4, r4, r0
str.w r4, [r2, #224]
uadd16 r5, r5, r3
str.w r5, [r2, #228]
uadd16 r6, r6, r9
str.w r6, [r2, #232]
uadd16 fp, fp, sl
str.w fp, [r2, #236]
ldr.w r4, [r1, #188]
ldr r5, [r1, #60]
ldr r6, [sp, #956]
ldr.w r7, [sp, #1084]
ldr.w r8, [sp, #1212]
ldr.w r9, [sp, #1340]
ldr.w sl, [sp, #1468]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr.w r4, [r2, #240]
ldr.w r5, [r2, #244]
ldr.w r6, [r2, #248]
ldr.w fp, [r2, #252]
uadd16 r4, r4, r0
str.w r4, [r2, #240]
uadd16 r5, r5, r3
str.w r5, [r2, #244]
uadd16 r6, r6, r9
str.w r6, [r2, #248]
uadd16 fp, fp, sl
str.w fp, [r2, #252]
ldr.w r4, [r1, #192]
ldr r5, [r1, #64]
ldr r6, [sp, #960]
ldr.w r7, [sp, #1088]
ldr.w r8, [sp, #1216]
ldr.w r9, [sp, #1344]
ldr.w sl, [sp, #1472]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr.w r4, [r2, #256]
ldr.w r5, [r2, #260]
ldr.w r6, [r2, #264]
ldr.w fp, [r2, #268]
uadd16 r4, r4, r0
str.w r4, [r2, #256]
uadd16 r5, r5, r3
str.w r5, [r2, #260]
uadd16 r6, r6, r9
str.w r6, [r2, #264]
uadd16 fp, fp, sl
str.w fp, [r2, #268]
ldr.w r4, [r1, #196]
ldr r5, [r1, #68]
ldr r6, [sp, #964]
ldr.w r7, [sp, #1092]
ldr.w r8, [sp, #1220]
ldr.w r9, [sp, #1348]
ldr.w sl, [sp, #1476]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr.w r4, [r2, #272]
ldr.w r5, [r2, #276]
ldr.w r6, [r2, #280]
ldr.w fp, [r2, #284]
uadd16 r4, r4, r0
str.w r4, [r2, #272]
uadd16 r5, r5, r3
str.w r5, [r2, #276]
uadd16 r6, r6, r9
str.w r6, [r2, #280]
uadd16 fp, fp, sl
str.w fp, [r2, #284]
ldr.w r4, [r1, #200]
ldr r5, [r1, #72]
ldr r6, [sp, #968]
ldr.w r7, [sp, #1096]
ldr.w r8, [sp, #1224]
ldr.w r9, [sp, #1352]
ldr.w sl, [sp, #1480]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr.w r4, [r2, #288]
ldr.w r5, [r2, #292]
ldr.w r6, [r2, #296]
ldr.w fp, [r2, #300]
uadd16 r4, r4, r0
str.w r4, [r2, #288]
uadd16 r5, r5, r3
str.w r5, [r2, #292]
uadd16 r6, r6, r9
str.w r6, [r2, #296]
uadd16 fp, fp, sl
str.w fp, [r2, #300]
ldr.w r4, [r1, #204]
ldr r5, [r1, #76]
ldr r6, [sp, #972]
ldr.w r7, [sp, #1100]
ldr.w r8, [sp, #1228]
ldr.w r9, [sp, #1356]
ldr.w sl, [sp, #1484]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr.w r4, [r2, #304]
ldr.w r5, [r2, #308]
ldr.w r6, [r2, #312]
ldr.w fp, [r2, #316]
uadd16 r4, r4, r0
str.w r4, [r2, #304]
uadd16 r5, r5, r3
str.w r5, [r2, #308]
uadd16 r6, r6, r9
str.w r6, [r2, #312]
uadd16 fp, fp, sl
str.w fp, [r2, #316]
ldr.w r4, [r1, #208]
ldr r5, [r1, #80]
ldr r6, [sp, #976]
ldr.w r7, [sp, #1104]
ldr.w r8, [sp, #1232]
ldr.w r9, [sp, #1360]
ldr.w sl, [sp, #1488]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr.w r4, [r2, #320]
ldr.w r5, [r2, #324]
ldr.w r6, [r2, #328]
ldr.w fp, [r2, #332]
uadd16 r4, r4, r0
str.w r4, [r2, #320]
uadd16 r5, r5, r3
str.w r5, [r2, #324]
uadd16 r6, r6, r9
str.w r6, [r2, #328]
uadd16 fp, fp, sl
str.w fp, [r2, #332]
ldr.w r4, [r1, #212]
ldr r5, [r1, #84]
ldr r6, [sp, #980]
ldr.w r7, [sp, #1108]
ldr.w r8, [sp, #1236]
ldr.w r9, [sp, #1364]
ldr.w sl, [sp, #1492]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr.w r4, [r2, #336]
ldr.w r5, [r2, #340]
ldr.w r6, [r2, #344]
ldr.w fp, [r2, #348]
uadd16 r4, r4, r0
str.w r4, [r2, #336]
uadd16 r5, r5, r3
str.w r5, [r2, #340]
uadd16 r6, r6, r9
str.w r6, [r2, #344]
uadd16 fp, fp, sl
str.w fp, [r2, #348]
ldr.w r4, [r1, #216]
ldr r5, [r1, #88]
ldr r6, [sp, #984]
ldr.w r7, [sp, #1112]
ldr.w r8, [sp, #1240]
ldr.w r9, [sp, #1368]
ldr.w sl, [sp, #1496]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr.w r4, [r2, #352]
ldr.w r5, [r2, #356]
ldr.w r6, [r2, #360]
ldr.w fp, [r2, #364]
uadd16 r4, r4, r0
str.w r4, [r2, #352]
uadd16 r5, r5, r3
str.w r5, [r2, #356]
uadd16 r6, r6, r9
str.w r6, [r2, #360]
uadd16 fp, fp, sl
str.w fp, [r2, #364]
ldr.w r4, [r1, #220]
ldr r5, [r1, #92]
ldr r6, [sp, #988]
ldr.w r7, [sp, #1116]
ldr.w r8, [sp, #1244]
ldr.w r9, [sp, #1372]
ldr.w sl, [sp, #1500]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr.w r4, [r2, #368]
ldr.w r5, [r2, #372]
ldr.w r6, [r2, #376]
ldr.w fp, [r2, #380]
uadd16 r4, r4, r0
str.w r4, [r2, #368]
uadd16 r5, r5, r3
str.w r5, [r2, #372]
uadd16 r6, r6, r9
str.w r6, [r2, #376]
uadd16 fp, fp, sl
str.w fp, [r2, #380]
ldr.w r4, [r1, #224]
ldr r5, [r1, #96]
ldr r6, [sp, #992]
ldr.w r7, [sp, #1120]
ldr.w r8, [sp, #1248]
ldr.w r9, [sp, #1376]
ldr.w sl, [sp, #1504]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr.w r4, [r2, #384]
ldr.w r5, [r2, #388]
ldr.w r6, [r2, #392]
ldr.w fp, [r2, #396]
uadd16 r4, r4, r0
str.w r4, [r2, #384]
uadd16 r5, r5, r3
str.w r5, [r2, #388]
uadd16 r6, r6, r9
str.w r6, [r2, #392]
uadd16 fp, fp, sl
str.w fp, [r2, #396]
ldr.w r4, [r1, #228]
ldr r5, [r1, #100]
ldr r6, [sp, #996]
ldr.w r7, [sp, #1124]
ldr.w r8, [sp, #1252]
ldr.w r9, [sp, #1380]
ldr.w sl, [sp, #1508]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr.w r4, [r2, #400]
ldr.w r5, [r2, #404]
ldr.w r6, [r2, #408]
ldr.w fp, [r2, #412]
uadd16 r4, r4, r0
str.w r4, [r2, #400]
uadd16 r5, r5, r3
str.w r5, [r2, #404]
uadd16 r6, r6, r9
str.w r6, [r2, #408]
uadd16 fp, fp, sl
str.w fp, [r2, #412]
ldr.w r4, [r1, #232]
ldr r5, [r1, #104]
ldr r6, [sp, #1000]
ldr.w r7, [sp, #1128]
ldr.w r8, [sp, #1256]
ldr.w r9, [sp, #1384]
ldr.w sl, [sp, #1512]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr.w r4, [r2, #416]
ldr.w r5, [r2, #420]
ldr.w r6, [r2, #424]
ldr.w fp, [r2, #428]
uadd16 r4, r4, r0
str.w r4, [r2, #416]
uadd16 r5, r5, r3
str.w r5, [r2, #420]
uadd16 r6, r6, r9
str.w r6, [r2, #424]
uadd16 fp, fp, sl
str.w fp, [r2, #428]
ldr.w r4, [r1, #236]
ldr r5, [r1, #108]
ldr r6, [sp, #1004]
ldr.w r7, [sp, #1132]
ldr.w r8, [sp, #1260]
ldr.w r9, [sp, #1388]
ldr.w sl, [sp, #1516]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr.w r4, [r2, #432]
ldr.w r5, [r2, #436]
ldr.w r6, [r2, #440]
ldr.w fp, [r2, #444]
uadd16 r4, r4, r0
str.w r4, [r2, #432]
uadd16 r5, r5, r3
str.w r5, [r2, #436]
uadd16 r6, r6, r9
str.w r6, [r2, #440]
uadd16 fp, fp, sl
str.w fp, [r2, #444]
ldr.w r4, [r1, #240]
ldr r5, [r1, #112]
ldr r6, [sp, #1008]
ldr.w r7, [sp, #1136]
ldr.w r8, [sp, #1264]
ldr.w r9, [sp, #1392]
ldr.w sl, [sp, #1520]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr.w r4, [r2, #448]
ldr.w r5, [r2, #452]
ldr.w r6, [r2, #456]
ldr.w fp, [r2, #460]
uadd16 r4, r4, r0
str.w r4, [r2, #448]
uadd16 r5, r5, r3
str.w r5, [r2, #452]
uadd16 r6, r6, r9
str.w r6, [r2, #456]
uadd16 fp, fp, sl
str.w fp, [r2, #460]
ldr.w r4, [r1, #244]
ldr r5, [r1, #116]
ldr r6, [sp, #1012]
ldr.w r7, [sp, #1140]
ldr.w r8, [sp, #1268]
ldr.w r9, [sp, #1396]
ldr.w sl, [sp, #1524]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr.w r4, [r2, #464]
ldr.w r5, [r2, #468]
ldr.w r6, [r2, #472]
ldr.w fp, [r2, #476]
uadd16 r4, r4, r0
str.w r4, [r2, #464]
uadd16 r5, r5, r3
str.w r5, [r2, #468]
uadd16 r6, r6, r9
str.w r6, [r2, #472]
uadd16 fp, fp, sl
str.w fp, [r2, #476]
ldr.w r4, [r1, #248]
ldr r5, [r1, #120]
ldr r6, [sp, #1016]
ldr.w r7, [sp, #1144]
ldr.w r8, [sp, #1272]
ldr.w r9, [sp, #1400]
ldr.w sl, [sp, #1528]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr.w r4, [r2, #480]
ldr.w r5, [r2, #484]
ldr.w r6, [r2, #488]
ldr.w fp, [r2, #492]
uadd16 r4, r4, r0
str.w r4, [r2, #480]
uadd16 r5, r5, r3
str.w r5, [r2, #484]
uadd16 r6, r6, r9
str.w r6, [r2, #488]
uadd16 fp, fp, sl
str.w fp, [r2, #492]
ldr.w r4, [r1, #252]
ldr r5, [r1, #124]
ldr r6, [sp, #1020]
ldr.w r7, [sp, #1148]
ldr.w r8, [sp, #1276]
ldr.w r9, [sp, #1404]
ldr.w sl, [sp, #1532]
uadd16 r5, r5, r8
usub16 r9, r9, r8
usub16 r7, r7, r6
usub16 r8, r8, r4
mov.w r0, sl, lsr #16
mov.w r3, sl, lsl #6
pkhbt r3, r3, r0, lsl #22
usub16 r8, r8, r3
mov.w r0, r7, lsl #16
mov.w r3, r7, lsr #1
pkhtb r7, r3, r0, asr #17
uadd16 r6, r6, r7
mov.w r0, r8, lsr #16
mov.w r3, r8, lsl #1
pkhbt r3, r3, r0, lsl #17
uadd16 r8, r9, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #6
pkhbt r3, r3, r0, lsl #22
uadd16 r3, r6, r3
usub16 r5, r5, r3
usub16 r6, r6, sl
usub16 r6, r6, r4
mov.w r3, #45
smulbb r0, r6, r3
smultb r3, r6, r3
pkhbt r3, r0, r3, lsl #16
uadd16 r5, r5, r3
mov.w r0, r6, lsr #16
mov.w r3, r6, lsl #3
pkhbt r3, r3, r0, lsl #19
usub16 r8, r8, r3
movw r3, #43691
smulbb r0, r8, r3
smultb r3, r8, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #3
pkhtb r8, r3, r0, asr #19
uadd16 r9, r5, r9
mov.w r0, r7, lsr #16
mov.w r3, r7, lsl #4
pkhbt r3, r3, r0, lsl #20
uadd16 r5, r5, r3
movw r3, #36409
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #1
pkhtb r5, r3, r0, asr #17
usub16 r6, r6, r8
uadd16 r7, r7, r5
mov.w r3, #0
usub16 r7, r3, r7
mov.w r3, #30
smulbb r0, r5, r3
smultb r3, r5, r3
pkhbt r3, r0, r3, lsl #16
usub16 r9, r3, r9
movw r3, #61167
smulbb r0, r9, r3
smultb r3, r9, r3
pkhbt r3, r0, r3, lsl #16
mov.w r0, r3, lsl #16
mov.w r3, r3, lsr #2
pkhtb r9, r3, r0, asr #18
usub16 r5, r5, r9
pkhbt r0, sl, r9, lsl #16
pkhbt r3, r8, r7, lsl #16
uadd16 r0, r0, lr
uadd16 r3, r3, ip
pkhtb lr, r5, r6, asr #16
pkhtb ip, ip, r4, asr #16
pkhbt r5, r6, r5, lsl #16
pkhbt r4, r4, ip
pkhtb r9, r9, sl, asr #16
pkhtb sl, r7, r8, asr #16
uadd16 r9, r9, r5
uadd16 sl, sl, r4
ldr.w r4, [r2, #496]
ldr.w r5, [r2, #500]
ldr.w r6, [r2, #504]
ldr.w fp, [r2, #508]
uadd16 r4, r4, r0
str.w r4, [r2, #496]
uadd16 r5, r5, r3
str.w r5, [r2, #500]
uadd16 r6, r6, r9
str.w r6, [r2, #504]
uadd16 fp, fp, sl
str.w fp, [r2, #508]
ldr r0, [r2, #0]
ldr r3, [r2, #4]
usub16 r0, r0, lr
str.w r0, [r2]
usub16 r3, r3, ip
str.w r3, [r2, #4]
add.w sp, sp, #1664
ldmia.w sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
bx lr
