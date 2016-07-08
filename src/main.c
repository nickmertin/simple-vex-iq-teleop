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

//////////////////
// Fancy Colors //
//////////////////
#include "color.c"

///////////////////////
// Utility Functions //
///////////////////////
bool button_down_RUp()
{
	static bool down_RUp = false;
	bool value = vexRT[BtnRUp];
	bool result = value && !down_RUp;
	down_RUp = value;
	return result;
}
bool button_down_LUp()
{
	static bool down_LUp = false;
	bool value = vexRT[BtnLUp];
	bool result = value && !down_LUp;
	down_LUp = value;
	return result;
}
bool button_down_EUp()
{
	static bool down_EUp = false;
	bool value = vexRT[BtnEUp];
	bool result = value && !down_EUp;
	down_EUp = value;
	return result;
}
bool button_down_FUp()
{
	static bool down_FUp = false;
	bool value = vexRT[BtnFUp];
	bool result = value && !down_FUp;
	down_FUp = value;
	return result;
}
bool button_down_RDown()
{
	static bool down_RDown = false;
	bool value = vexRT[BtnRDown];
	bool result = value && !down_RDown;
	down_RDown = value;
	return result;
}
bool button_down_LDown()
{
	static bool down_LDown = false;
	bool value = vexRT[BtnLDown];
	bool result = value && !down_LDown;
	down_LDown = value;
	return result;
}
bool button_down_EDown()
{
	static bool down_EDown = false;
	bool value = vexRT[BtnEDown];
	bool result = value && !down_EDown;
	down_EDown = value;
	return result;
}
bool button_down_FDown()
{
	static bool down_FDown = false;
	bool value = vexRT[BtnFDown];
	bool result = value && !down_FDown;
	down_FDown = value;
	return result;
}

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
#define SIGN(x)																						sgn(x)
#define BUTTON(id)																				vexRT[Btn##id]
#define BUTTON_DOWN(id)																		button_down_##id ()
#define INIT(x)																						if (!i) { x }

#define JOY_VALUE(j)																			(abs(vexRT[j]) > 15 ? vexRT[j] : 0)

// Control macros
#define CONDITIONAL(c, o)																	if (c) { o }

// Low-level i/o macros
#define SET_MOTOR(n, value)																MOTOR_OUT(n) value;

// Options for DRIVE_TYPE
#define DRIVE_NONE																				0
#define DRIVE_TANK																				1
#define DRIVE_X																						2
#define DRIVE_TRIPLE																			3

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

// Macros to be used with DRIVE_TRIPLE
#define DRIVE_TRIPLE_BACK(n)															tMotor triple_back = MOTOR(n);
#define DRIVE_TRIPLE_LEFT(n)															tMotor triple_left = MOTOR(n);
#define DRIVE_TRIPLE_RIGHT(n)															tMotor triple_right = MOTOR(n);
#define DRIVE_TRIPLE_INPUT_AXIAL_JOYSTICK(joy)						TVexJoysticks joy_axial = JOYSTICK(joy);
#define DRIVE_TRIPLE_INPUT_STRAFE_JOYSTICK(joy)						TVexJoysticks joy_strafe = JOYSTICK(joy);
#define DRIVE_TRIPLE_INPUT_ROTATION_JOYSTICK(joy)					TVexJoysticks joy_rotation = JOYSTICK(joy);

// Macros to set position of motors
#define POSITION_GET(n)																		getServoEncoder(MOTOR(n))
#define POSITION_SET(n, pos)															setServoTarget(MOTOR(n), pos);
#define POSITION_MAINTAIN(n1, n2, sign)										static int offset_##n1 = 0; \
																													POSITION_SET(n1, offset_##n1 sign getServoEncoder(MOTOR(n2)))
#define POSITION_MAINTAIN_INC(n)													++offset_##n;
#define POSITION_MAINTAIN_DEC(n)													--offset_##n;
#define POSITION_RESET(m, p, dir)													if (!i) { \
																														m dir 100; \
																														SetMotorBrakeMode(MOTOR(p), motorCoast); \
																														sleep(100); \
																														while (getMotorZeroVelocity(MOTOR(p))) \
																															sleep(10); \
																														while (!getMotorZeroVelocity(MOTOR(p))) \
																															sleep(10); \
																														m dir 0; \
																														sleep(100); \
																														setMotorBrakeMode(MOTOR(p), motorHold); \
																													}
#define POSITION_ADJUST(n, amount)												POSITION_SET(n, POSITION_GET(n) + (amount))
#define BRAKE_MODE(n, mode)																SetMotorBrakeMode(MOTOR(n), motor##mode);

// Macros to set speed of motors
#define TARGET_SPEED_GET(n)																target_speed_##n
#define TARGET_SPEED_SET(n, s)														target_speed_##n = s;
#define TARGET_SPEED_ALTER(n, s)													TARGET_SPEED_SET(n, TARGET_SPEED_GET(n) + (s))
#define TARGET_SPEED_MAINTAIN(n)													static int target_speed_##n = 0, target_last_enc_##n = 0; \
																													{ int current = getMotorEncoder(MOTOR(n)); \
																														MOTOR_OUT(n) SIGN(target_speed_##n - current + target_last_enc_##n) * 100; \
																														target_last_enc_##n = current; \
																													}

// Macros to enable Touch LED usage
#define TOUCH_LED_SOLID(n, color)													setTouchLEDColor(DEVICE(n), color);
#define TOUCH_LED_DIRECTION_BASED(n)											setTouchLEDColor(DEVICE(n), direction_sign ? (direction_sign == 1 ? colorGreen : colorRed) : colorYellow);
#define TOUCH_LED_BLINK(n, color1, color2)								setTouchLEDColor(DEVICE(n), (i % 2) ? color1 : color2);
#define TOUCH_LED_BLINK3(n, color1, color2, color3)				setTouchLEDColor(DEVICE(n), !(i % 3) ? color1 : (i % 3) == 1 ? color2 : color3);
#define TOUCH_LED_CYCLE(n, time)													{ static int rgb_##n; \
																													if (i >= rgb_##n) { nextColor(DEVICE(n)); rgb_##n = i + time; } }

// Macros to enable ultrasonic sensor usage
#define ULTRASONIC(n, name)																int name = getDistanceValue(DEVICE(n));

// Macros to enable gyroscopic sensor usage
#define GYROSCOPE(n, name)																float name = getGyroDegreesFloat(DEVICE(n));

// Macros for PID controller
#define PID(kP, kI, kD, error, name)											{ static float name##_last = 0, name##_sum = 0; \
																													float name = (kP) * error + (kI) * (name##_sum += error) + (kD) * (error - name##_last); \
																													name##_last = error; }

///////////////////////
// Main control code //
///////////////////////

task main()
{
	int direction_sign = 0, rotation_sign = 0;
	for (int i = 0; ; ++i) {
		// This file should contain current configuration information, created using macros defined above
		#include "config.h"
		#ifndef DRIVE_TYPE
			#error "Drive type must be specified by defining DRIVE_TYPE in config.h!"
		#elif DRIVE_TYPE == DRIVE_NONE
			#warn "No drive configured!"
		#elif DRIVE_TYPE == DRIVE_TANK
			#ifndef DRIVE_TANK_INPUT_TYPE
				#error "Input type must be specified by defining DRIVE_TANK_INPUT_TYPE in config.h!"
			#elif DRIVE_TANK_INPUT_TYPE == DRIVE_TANK_INPUT_SIMPLE
				sbyte tank_left = JOY_VALUE(joy_left), tank_right = JOY_VALUE(joy_right);
			#elif DRIVE_TANK_INPUT_TYPE == DRIVE_TANK_INPUT_COMPLEX
				sbyte tank_speed = JOY_VALUE(joy_speed), tank_direction = JOY_VALUE(joy_direction);
				sbyte tank_left = CLAMP(tank_speed + tank_direction, -100, 100), tank_right = CLAMP(tank_speed - tank_direction, -100, 100);
			#endif
			direction_sign = SIGN(tank_left + tank_right);
			rotation_sign = SIGN(tank_left - tank_right);
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
			sbyte x_axial = JOY_VALUE(joy_axial), x_strafe = JOY_VALUE(joy_strafe), x_rotation = JOY_VALUE(joy_rotation);
			motor[x_fl] = CLAMP(x_rotation + x_strafe + x_axial, -100, 100);
			motor[x_fr] = CLAMP(x_rotation + x_strafe - x_axial, -100, 100);
			motor[x_bl] = CLAMP(x_rotation - x_strafe + x_axial, -100, 100);
			motor[x_br] = CLAMP(x_rotation - x_strafe - x_axial, -100, 100);
			direction_sign = SIGN(x_axial);
			rotation_sign = SIGN(x_rotation);
		#elif DRIVE_TYPE == DRIVE_TRIPLE
			sbyte triple_axial = JOY_VALUE(joy_axial), triple_strafe = JOY_VALUE(joy_strafe), triple_rotation = JOY_VALUE(joy_rotation);
			motor[triple_back] = CLAMP(triple_rotation - triple_strafe, -100, 100);
			motor[triple_left] = CLAMP(triple_rotation + triple_axial + triple_strafe, -100, 100);
			motor[triple_right] = CLAMP(triple_rotation - triple_axial + triple_strafe, -100, 100);
		#else
			#error "Unknown value for DRIVE_TYPE!"
		#endif
		sleep(10 - nPgmTime % 10);
	}
}
