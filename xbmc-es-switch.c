/* XBMC-ES-Switch
*
* Copyright 2014 Patrick Ulbrich <zulu99@gmx.net>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
* MA 02110-1301, USA.
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <linux/joystick.h>

#define DEVICE			"/dev/input/js0"

#define BUTTON_A		1u
#define BUTTON_B		2u

#define XBMC_SERVICE	"xbmc.service"
#define ES_SERVICE		"emulationstation.service"

int main(int argc, char* argv[])
{
	int fd;
	struct JS_DATA_TYPE js;
	bool err = false;
	bool button_pressed = false;
	char strbuf[255];
	unsigned int timeout_counter = 10; // timeout = counter * 10ms
	
	if ((fd = open(DEVICE, O_RDONLY)) < 0)
	{
		perror("Failed to open joystick device");
		err = true;
	}
	
	while (!err && !button_pressed && (timeout_counter > 0))
	{
		if (read(fd, &js, JS_RETURN) != JS_RETURN)
		{
			perror("Error reading joystick button");
			err = true;
		}
		else
		{
			if ((js.buttons & BUTTON_A) || (js.buttons & BUTTON_B))
			{
				button_pressed = true;
			}
			else
			{		
				usleep(10 * 1000);
				timeout_counter--;
			}
		}
	}
	
	if (button_pressed)
	{
		snprintf(strbuf, sizeof(strbuf), 
			"%s %s", "/usr/bin/systemctl start ", ES_SERVICE);
	}
	else
	{
		snprintf(strbuf, sizeof(strbuf), 
			"%s %s", "/usr/bin/systemctl start ", XBMC_SERVICE);
	}

	system(strbuf);
	
	if (fd >= 0)
	{
		close(fd);
	}
	
	return 0;
}
