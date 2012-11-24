/*
 * memop.c
 *
 *  Created on: 24/11/2012
 *      Author: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
  */

#include "memop.h"
#include "../ColoredOutput.h"
#include "../../utils/ustdlib.h"

static volatile unsigned long address1, address2;
static volatile unsigned long amount;
static volatile unsigned char value;

#define PRINTABLE(x) (x > 0x1F)

int memcmp_2 (void) {
	unsigned long i;
	unsigned char *base1 = address1;
	unsigned char *base2 = address2;

	if (address1 > address2) {
		t_printf(BOLD_RED("Error") ": address1 must be smaller than address2\n");
		return 1;
	}

	if (amount == 0) {
		t_printf(BOLD_RED("Error") ": should set [amount] bytes bigger than zero\n");
		return 1;
	}

	for (i = 0; i < amount; i++)
		if (base1[i] != base2[i]) break;

	if (i == amount)
		t_printf (BOLD_GREEN("0x%X and 0x%X match perfectly\n"), address1, address2);
	else
		t_printf (BOLD_RED("0x%X and 0x%X don't match\n"), address1, address2);

	return 0;
}

void memcmp_2_args (char *command) {
	unsigned int i, base;

	base = 0;
	for (i = base; command[i] != ' '; i++);
	command[i] = '\0';
	address1 = ustrtoul (&command[base], 0, 16);

	base = i + 1;
	for (i = base; command[i] != ' '; i++);
	command[i] = '\0';
	address2 = ustrtoul (&command[base], 0, 16);

	base = i + 1;
	amount = ustrtoul (&command[base], 0, 10);

}

int memdump (void) {
	unsigned int i, j;
	unsigned char *base;

	if (amount == 0) {
		t_printf (BOLD_RED("Error") ": must set [amount] bigger than zero\n");
		return 1;
	}

	base = address1;

	for (j = 0; j < (amount >> 4); j++) {
		for (i = 0; i < 16; i++)
			t_printf ("%X ", base[i + (j<<4)]);

		t_printf (" | ");

		for (i = 0; i < 16; i++)
			if (PRINTABLE(base[i + (j<<4)]))
				t_printf ("%c", base[i + (j<<4)]);
			else
				t_printf (".");

		t_printf ("\n");
	}

	for (i = 0; i < (amount % 16); i++)
		t_printf ("%X ", base[i + (j<<4)]);

	t_printf (" | ");

	for (i = 0; i < (amount % 16); i++)
		if (PRINTABLE(base[i + (j<<4)]))
			t_printf ("%c", base[i + (j<<4)]);
		else
			t_printf (".");

	t_printf ("\n\n");

	return 0;
}

void memdump_args (char *command) {
	unsigned int i, base;

	base = 0;
	for (i = base; command[i] != ' '; i++);
	command[i] = '\0';
	address1 = ustrtoul (&command[base], 0, 16);

	base = i + 1;
	amount = ustrtoul (&command[base], 0, 10);
}

int memset_2 (void) {
	unsigned int i;
	unsigned char *base;

	base = address1;
	for (i = 0; i < amount; base[i] = value, i++) ;

	return 0;
}

void memset_2_args (char *command) {
	unsigned int i, base;

	base = 0;
	for (i = base; command[i] != ' '; i++);
	command[i] = '\0';
	address1 = ustrtoul (&command[base], 0, 16);

	base = i + 1;
	for (i = base; command[i] != ' '; i++);
	command[i] = '\0';
	amount = ustrtoul (&command[base], 0, 10);

	base = i + 1;
	value = ustrtoul (&command[base], 0, 16);
}
