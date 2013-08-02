/*
 ============================================================================
 Name        : ccc.c
 Author      : dufann@gmail.com
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ccc.h"

int main(void) {
	int x = 0x11223344;
	int k = 1;
	int s = sra(x, k);
	printf("sra=%2.x", s);
	return 0;
}

/**
 * 用逻辑右移完成算数右移
 * k 0--(w-1)
 */
int sra(int x, int k) {
	int w = sizeof(int);
	int xsrl = (unsigned) x >> k;
	int mod = 0xff;
	mod = mod << ((w - k) << 3);
	printf("xsrl=%d,w=%d,mod=%2.x", xsrl, w, mod);
	printf("\n");
	return mod | xsrl;
}

/**
 * 用算术右移完成逻辑右移
 */
unsigned srl(unsigned x, int k) {
	unsigned xsra = (int) x >> k;
	return x;
}
/**
 * 2.60
 * x = 0x 12 34 56 78
 * b = 0x AB
 * i = 1;
 *
 * 0xFF左移1位 --> 0x00 00 FF 00
 * 取非 0xFF FF 00 FF
 * 和X&操作 newX = 0x 12 34 00 78
 * b 左移1位 --> 0x 00 00 AB 00
 * 和newX | 操作 --> 0x 12 34 AB 78
 *
 */
void replace_byte2(unsigned x, unsigned char b, int i) {
	int left_move = i << 3;
	int mod = 0xff;
	mod = mod << left_move;
	mod = ~mod;
	int newB = b << left_move;
	int newX = x & mod;
	newX = newX | newB;
	printf("newX=%2.x", newX);
}
/**
 * 2.60
 * 0 1 2 3
 * 0x12 34 56 78
 *
 *	unsigned x = 0x12345678;
 *	unsigned char b = 0xAB;
 * 	0x12 AB 56 78
 *
 * 1111 1111
 * 1010 1011
 *
 * i == 0 左移 4，右移 1
 * i == 1 左移 3，右移 2
 * i == 2 左移 2，右移 3
 * i == 3 左移 1，右移 4
 *  TODO fix bug when i = 0 or 3
 */
void replace_byte(unsigned x, unsigned char b, int i) {
	//左移2字
	int left_move = (sizeof(int) - i) << 3;
	//右移3字
	int right_move = (i + 1) << 3;
	printf("left_move=%d,right_move=%d", left_move, right_move);
	printf("\n");

	//0x12000000
	int left = x >> right_move;
	left = left << right_move;
	printf("left=%2.x", left);
	printf("\n");
	//0x00005678
	int right = x << left_move;
	printf("right1=%2.x", right);
	printf("\n");
	right = right >> left_move;
	printf("right=%2.x", right);
	printf("\n");
	int mod = b;
	printf("mod = %2.x", mod);
	printf("\n");
	int mod_move = i << 3;
	int newB = b << mod_move;
	printf("newB = %2.x", newB);
	printf("\n");
	int newX = left | right | newB;
	printf("%2.x", newX);
}

/**
 * 获取int类型的最高有效位
 * 2.60
 * int 32位，最高有效字节是24-32位，所以右移24位
 */
int get_msb(int x) {
	int shift_val = (sizeof(int) - 1) << 3;
	printf("shift_val = %d", shift_val);
	int xright = x >> shift_val;
	printf("\n");
	printf("xright = %d", xright);
	return xright & 0xff;
}

/**
 * 2.58
 * return 0 -- big endian/ 1 -- litten endian
 */
int is_little_endian() {
	int word = 0xff;
	byte_pointer start = (byte_pointer) &word;
	int frist = start[0];
	if (frist == 0xff) {
		return 1;
	} else {
		return 0;
	}
}

void in() {
	const char *s = "abcdef";
	showByte((byte_pointer) s, sizeof(s));
	int a = 1;
	int b = 1;
	int c = a ^ b;
	printf("%d", c);
	int arr[] = { 1, 2, 3, 4, 5, 6 };
	reverse_array(arr, 6);
	int i;
	for (i = 0; i < 6; i++) {
		printf("%d", arr[i]);
	}
	printf("\n--show int--\n");
	showInt(100);
}

void reverse_array(int a[], int cnt) {
	int frist, last;
	for (frist = 0, last = cnt - 1; frist <= last; frist++, last--) {
		inplace_swap(&a[frist], &a[last]);
	}
}

void showByte(byte_pointer start, int len) {
	int i;
	for (i = 0; i < len; i++) {
		printf(" %.2x", start[i]);
	}
	printf("\n");
}

void showInt(int x) {
	showByte((byte_pointer) &x, sizeof(x));
}

void showFloat(float x) {
	showByte((byte_pointer) &x, sizeof(x));
}
void showPointer(void *x) {
	showByte((byte_pointer) &x, sizeof(x));
}

void inplace_swap(int *x, int *y) {
	*y = *x ^ *y;
	*x = *x ^ *y;
	*y = *x ^ *y;
}

