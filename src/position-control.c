int position_reset(tMotor m, sbyte p)
{
	motor[m] = p;
	while (getMotorSpeed(m))
		sleep(10);
	motor[m] = 0;
	sleep(100);
	return 0;
}
