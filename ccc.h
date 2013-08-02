/*
 * ccc.h
 *
 *  Created on: Jul 29, 2013
 *      Author: tobon
 */
#include <stdio.h>
#include <stdlib.h>
#ifndef CCC_H_
#define CCC_H_
typedef unsigned char *byte_pointer;

void showInt(int x);
void showFloat(float x);
void showByte(byte_pointer start, int len);
void inplace_swap(int *x, int *y);
void reverse_array(int a[], int cnt);
int is_little_endian();
int get_msb(int x);
void replace_byte(unsigned x, unsigned char b, int i);
void replace_byte2(unsigned x, unsigned char b, int i);

int sra(int x, int k);

#endif /* CCC_H_ */
