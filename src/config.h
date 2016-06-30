// Drive type: tank drive
#define DRIVE_TYPE DRIVE_TANK

// Drive motors: left 1 and 2, right 7 and 8
#define DRIVE_TANK_LEFT MOTOR_OUT(1) MOTOR_OUT(2)
#define DRIVE_TANK_RIGHT MOTOR_OUT(7) MOTOR_OUT(8)

// Input type: simple, left and right y-axis joysticks
#define DRIVE_TANK_INPUT_TYPE DRIVE_TANK_INPUT_SIMPLE
DRIVE_TANK_INPUT_SIMPLE_JOYSTICKS(A, D)
