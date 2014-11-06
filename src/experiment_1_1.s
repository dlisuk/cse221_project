	.arch armv6
	.eabi_attribute 27, 3
	.eabi_attribute 28, 1
	.fpu vfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"experiment_1_1.c"
	.comm	gettime_now,8,4
	.text
	.align	2
	.type	ccnt_read, %function
ccnt_read:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	mov	r0, #0
	ldr	r1, .L3
	bl	clock_gettime
	ldr	r3, .L3
	ldr	r3, [r3, #4]
	mov	r0, r3
	ldmfd	sp!, {fp, pc}
.L4:
	.align	2
.L3:
	.word	gettime_now
	.size	ccnt_read, .-ccnt_read
	.align	2
	.global	absdiff
	.type	absdiff, %function
absdiff:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	str	r0, [fp, #-8]
	str	r1, [fp, #-12]
	ldr	r2, [fp, #-12]
	ldr	r3, [fp, #-8]
	cmp	r2, r3
	bcs	.L6
	ldr	r2, [fp, #-12]
	ldr	r3, .L8
	add	r3, r2, r3
	str	r3, [fp, #-12]
.L6:
	ldr	r2, [fp, #-12]
	ldr	r3, [fp, #-8]
	rsb	r3, r3, r2
	mov	r0, r3
	sub	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
.L9:
	.align	2
.L8:
	.word	1000000000
	.size	absdiff, .-absdiff
	.align	2
	.global	c
	.type	c, %function
c:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #20
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	ldr	r3, [fp, #-16]
	ldr	r3, [r3]
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-20]
	ldr	r3, [r3]
	str	r3, [fp, #-12]
	ldr	r2, [fp, #-8]
	ldr	r3, [fp, #-12]
	cmp	r2, r3
	bcs	.L11
	mvn	r3, #0
	b	.L12
.L11:
	ldr	r2, [fp, #-8]
	ldr	r3, [fp, #-12]
	cmp	r2, r3
	bls	.L13
	mov	r3, #1
	b	.L12
.L13:
	mov	r3, #0
.L12:
	mov	r0, r3
	sub	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	c, .-c
	.section	.rodata
	.align	2
.LC0:
	.ascii	"RUNNING MEASURE %d TIMES\012\012\000"
	.align	2
.LC1:
	.ascii	"trial:%d\012\000"
	.align	2
.LC2:
	.ascii	"sorting\000"
	.align	2
.LC3:
	.ascii	"sorted\000"
	.align	2
.LC4:
	.ascii	"OUTER MEASRUES\000"
	.align	2
.LC5:
	.ascii	"Total\011%lu\012\000"
	.align	2
.LC6:
	.ascii	"Mean\011%f\012\012\000"
	.align	2
.LC7:
	.ascii	"INNER MEASURES\000"
	.align	2
.LC8:
	.ascii	"MEAN\011%f\012STD_DEV\011%f\012\012\000"
	.align	2
.LC9:
	.ascii	"MEDIAN\011%d\012\000"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #72
	mov	r2, #0
	mov	r3, #0
	strd	r2, [fp, #-20]
	mov	r2, #0
	mov	r3, #0
	strd	r2, [fp, #-36]
	ldr	r0, .L19+16
	bl	malloc
	mov	r3, r0
	str	r3, [fp, #-44]
	bl	setup
	ldr	r0, .L19+20
	ldr	r1, .L19+24
	bl	printf
	bl	ccnt_read
	str	r0, [fp, #-48]
	mov	r3, #1
	str	r3, [fp, #-40]
	b	.L15
.L18:
	bl	measure
	str	r0, [fp, #-52]
	ldr	r3, [fp, #-40]
	sub	r3, r3, #-1073741823
	mov	r3, r3, asl #2
	ldr	r2, [fp, #-44]
	add	r3, r2, r3
	ldr	r2, [fp, #-52]
	str	r2, [r3]
	ldr	r3, [fp, #-52]
	fmsr	s11, r3	@ int
	fuitod	d7, s11
	fstd	d7, [fp, #-60]
	ldr	r0, .L19+28
	ldr	r1, [fp, #-40]
	bl	printf
	ldr	r3, [fp, #-40]
	cmp	r3, #1
	bne	.L16
	ldrd	r2, [fp, #-60]
	strd	r2, [fp, #-20]
	ldrd	r2, [fp, #-20]
	strd	r2, [fp, #-12]
	b	.L17
.L16:
	fldd	d6, [fp, #-60]
	fldd	d7, [fp, #-12]
	fsubd	d6, d6, d7
	ldr	r3, [fp, #-40]
	fmsr	s11, r3	@ int
	fsitod	d7, s11
	fdivd	d6, d6, d7
	fldd	d7, [fp, #-12]
	faddd	d7, d6, d7
	fstd	d7, [fp, #-20]
	ldr	r3, [fp, #-40]
	sub	r3, r3, #1
	fmsr	s15, r3	@ int
	fsitod	d6, s15
	fldd	d7, [fp, #-28]
	fmuld	d6, d6, d7
	fldd	d5, [fp, #-60]
	fldd	d7, [fp, #-12]
	fsubd	d5, d5, d7
	fldd	d4, [fp, #-60]
	fldd	d7, [fp, #-20]
	fsubd	d7, d4, d7
	fmuld	d7, d5, d7
	faddd	d6, d6, d7
	ldr	r3, [fp, #-40]
	fmsr	s11, r3	@ int
	fsitod	d7, s11
	fdivd	d7, d6, d7
	fstd	d7, [fp, #-36]
	ldrd	r2, [fp, #-20]
	strd	r2, [fp, #-12]
	ldrd	r2, [fp, #-36]
	strd	r2, [fp, #-28]
.L17:
	ldr	r3, [fp, #-40]
	add	r3, r3, #1
	str	r3, [fp, #-40]
.L15:
	ldr	r2, [fp, #-40]
	ldr	r3, .L19+24
	cmp	r2, r3
	ble	.L18
	bl	ccnt_read
	str	r0, [fp, #-64]
	bl	teardown
	ldr	r0, .L19+32
	bl	puts
	ldr	r0, [fp, #-44]
	ldr	r1, .L19+24
	mov	r2, #4
	ldr	r3, .L19+36
	bl	qsort
	ldr	r0, .L19+40
	bl	puts
	fldd	d6, [fp, #-36]
	fldd	d7, .L19
	fdivd	d7, d6, d7
	fcpyd	d0, d7
	bl	sqrt
	fstd	d0, [fp, #-36]
	ldr	r0, .L19+44
	bl	puts
	ldr	r2, [fp, #-64]
	ldr	r3, [fp, #-48]
	rsb	r3, r3, r2
	ldr	r0, .L19+48
	mov	r1, r3
	bl	printf
	ldr	r2, [fp, #-64]
	ldr	r3, [fp, #-48]
	rsb	r3, r3, r2
	fmsr	s15, r3	@ int
	fuitod	d6, s15
	fldd	d7, .L19+8
	fdivd	d7, d6, d7
	ldr	r0, .L19+52
	fmrrd	r2, r3, d7
	bl	printf
	ldr	r0, .L19+56
	bl	puts
	ldrd	r2, [fp, #-36]
	strd	r2, [sp]
	ldr	r0, .L19+60
	ldrd	r2, [fp, #-20]
	bl	printf
	ldr	r3, [fp, #-44]
	add	r3, r3, #1998848
	add	r3, r3, #1152
	ldr	r3, [r3]
	ldr	r0, .L19+64
	mov	r1, r3
	bl	printf
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L20:
	.align	3
.L19:
	.word	0
	.word	1093567614
	.word	0
	.word	1093567616
	.word	4000000
	.word	.LC0
	.word	1000000
	.word	.LC1
	.word	.LC2
	.word	c
	.word	.LC3
	.word	.LC4
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LC8
	.word	.LC9
	.size	main, .-main
	.align	2
	.global	setup
	.type	setup, %function
setup:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	setup, .-setup
	.align	2
	.global	teardown
	.type	teardown, %function
teardown:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	teardown, .-teardown
	.align	2
	.global	measure
	.type	measure, %function
measure:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #16
	sub	r3, fp, #12
	mov	r0, #1
	mov	r1, r3
	bl	clock_gettime
	sub	r3, fp, #20
	mov	r0, #1
	mov	r1, r3
	bl	clock_gettime
	ldr	r2, [fp, #-16]
	ldr	r3, [fp, #-8]
	cmp	r2, r3
	bge	.L24
	ldr	r2, [fp, #-16]
	ldr	r3, .L26
	add	r3, r2, r3
	str	r3, [fp, #-16]
.L24:
	ldr	r2, [fp, #-16]
	ldr	r3, [fp, #-8]
	rsb	r3, r3, r2
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L27:
	.align	2
.L26:
	.word	1000000000
	.size	measure, .-measure
	.ident	"GCC: (Raspbian 4.8.3-11) 4.8.3"
	.section	.note.GNU-stack,"",%progbits
