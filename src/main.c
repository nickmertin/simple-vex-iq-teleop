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
#define MOTOR_OUT(n)																			motor[MOTOR(n)] =
#define DEVICE(n)																					port##n
#define JOYSTICK(l)																				Ch##l
#define ARRAY_LEN(a)																			(sizeof(a) ? sizeof(a) / sizeof(a[0]) : 0)
#define MAX(x, y)																					(x > y ? x : y)
#define MIN(x, y)																					(x < y ? x : y)
#define CLAMP(x, min, max)																MAX(MIN(x, max), min)
#define SIGN(x)																						((x > 0) - (0 > x))

// Options for DRIVE_TYPE
#define DRIVE_TANK																				0
#define DRIVE_X																						1

// Options for DRIVE_TANK_INPUT_TYPE
#define DRIVE_TANK_INPUT_SIMPLE														0
#define DRIVE_TANK_INPUT_COMPLEX													1

// Macros to be used with DRIVE_TANK_INPUT_SIMPLE
#define DRIVE_TANK_INPUT_SIMPLE_JOYSTICKS(left, right)		TVexJoysticks joy_left = JOYSTICK(left), joy_right = JOYSTICK(right);

// Macros to be used with DRIVE_TANK_INPUT_COMPLEX
#define DRIVE_TANK_INPUT_COMPLEX_SPEED_JOYSTICK(joy)			TVexJoysticks joy_speed = JOYSTICK(joy);
#define DRIVE_TANK_INPUT_COMPLEX_DIRECTION_JOYSTICK(joy)	TVexJoysticks joy_direction = JOYSTICK(joy);

// Macros to be used with DRIVE_X
#define DRIVE_X_FRONT_LEFT(n)															tMotor x_fl = MOTOR(n);
#define DRIVE_X_FRONT_RIGHT(n)														tMotor x_fr = MOTOR(n);
#define DRIVE_X_BACK_LEFT(n)															tMotor x_bl = MOTOR(n);
#define DRIVE_X_BACK_RIGHT(n)															tMotor x_br = MOTOR(n);
#define DRIVE_X_INPUT_AXIAL_JOYSTICK(joy)									TVexJoysticks joy_axial = JOYSTICK(joy);
#define DRIVE_X_INPUT_STRAFE_JOYSTICK(joy)								TVexJoysticks joy_strafe = JOYSTICK(joy);
#define DRIVE_X_INPUT_ROTATION_JOYSTICK(joy)							TVexJoysticks joy_rotation = JOYSTICK(joy);

///////////////////////
// Main control code //
///////////////////////

task main()
{
	// This file should contain current configuration information, created using macros defined above
	#include "config.h"
	while (true) {
		#ifndef DRIVE_TYPE
			#error "Drive type must be specified by defining DRIVE_TYPE in config.h!"
		#elif DRIVE_TYPE == DRIVE_TANK
			#ifndef DRIVE_TANK_INPUT_TYPE
				#error "Input type must be specified by defining DRIVE_TANK_INPUT_TYPE in config.h!"
			#elif DRIVE_TANK_INPUT_TYPE == DRIVE_TANK_INPUT_SIMPLE
				sbyte tank_left = vexRT[joy_left], tank_right = vexRT[joy_right];
			#elif DRIVE_TANK_INPUT_TYPE == DRIVE_TANK_INPUT_COMPLEX
				sbyte tank_speed = vexRT[joy_speed], tank_direction = vexRT[joy_direction];
				sbyte tank_left = CLAMP(tank_speed + tank_direction, -127, 127), tank_right = CLAMP(tank_speed - tank_direction, -127, 127);
			#endif
			direction_sign = SIGN(tank_left + tank_right);
			#ifndef DRIVE_TANK_LEFT
				#error "Left drive motors must be specified by defining DRIVE_TANK_LEFT in config.h!"
			#else
				DRIVE_TANK_LEFT tank_left;
			#endif
			#ifndef DRIVE_TANK_RIGHT
				#error "Right drive motors must be specified by defining DRIVE_TANK_RIGHT in config.h!"
			#else
				DRIVE_TANK_RIGHT -tank_right;
			#endif
		#elif DRIVE_TYPE == DRIVE_X
			sbyte x_axial = vexRT[joy_axial], x_strafe = vexRT[joy_strafe], x_rotation = vexRT[joy_rotation];
			motor[x_fl] = CLAMP(x_rotation + x_strafe + x_axial, -127, 127);
			motor[x_fr] = CLAMP(x_rotation + x_strafe - x_axial, -127, 127);
			motor[x_bl] = CLAMP(x_rotation - x_strafe + x_axial, -127, 127);
			motor[x_br] = CLAMP(x_rotation - x_strafe - x_axial, -127, 127);
			direction_sign = SIGN(x_axial);
		#endif
		sleep(10);
	}
}
