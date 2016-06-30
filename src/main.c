// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

////////////////////////////////
// Macros for use in config.h //
////////////////////////////////

// General useful macros
#define MOTOR(n)																					motor##n
#define DEVICE(n)																					port##n
#define JOYSTICK(l)																				Ch##l
#define ARRAY_LEN(a)																			(sizeof(a) ? sizeof(a) / sizeof(a[0]) : 0)

// Options for DRIVE_TYPE
#define DRIVE_TANK																				0
#define DRIVE_X																						1

// Macros to be used with DRIVE_TANK
#define DRIVE_TANK_LEFT(motors)														int drive_left[] = { motors };
#define DRIVE_TANK_RIGHT(motors)													int drive_right[] = { motors };

// Options for DRIVE_TANK_INPUT_TYPE
#define DRIVE_TANK_INPUT_SIMPLE			0
#define DRIVE_TANK_INPUT_COMPLEX		1

// Macros to be used with DRIVE_TANK_INPUT_SIMPLE
#define DRIVE_TANK_INPUT_SIMPLE_JOYSTICKS(left, right)		TVexJoysticks joy_left = JOYSTICK(left), joy_right = JOYSTICK(right);

// Macros to be used with DRIVE_TANK_INPUT_COMPLEX
#define DRIVE_TANK_INPUT_COMPLEX_SPEED_JOYSTICK(joy)			TVexJoysticks joy_speed = JOYSTICK(joy);
#define DRIVE_TANK_INPUT_COMPLEX_DIRECTION_JOYSTICK(joy)	TVexJoysticks joy_direction = JOYSTICK(joy);

//TODO: everything with DRIVE_X

///////////////////////
// Main control code //
///////////////////////

task main()
{
	// This file should contain current configuration information, created using macros defined above
	#include "config.h"
	#if DRIVE_TYPE == DRIVE_TANK
		#if DRIVE_TANK_INPUT_TYPE = DRIVE_TANK_INPUT_SIMPLE
			//TODO: grab input
		#endif
	#endif
}
