/*
 * tinyshell_task.c
 *
 *  Created on: 15/11/2012
 *      Author: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 */

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "TinyShell.h"

#include "utils/uartstdio.h"

#include "commands/about.h"
#include "commands/rgbled.h"

static Command_t commands[] = {
	{"about", about, 0, "About this shell"},
	{"rgbled", rgbled, rgbled_args, "Controls RGB Led: on, off, set RRRR GGGG BBBB 0-FFFF"},
	NULL_TERMINATOR
};

void tinyshell_init (void) {

	TinyShellInit (commands, UARTprintf, UARTgets);

	xTaskCreate (TinyShellRun, "TinyShell", configMINIMAL_STACK_SIZE, 0, 1, 0);
}

