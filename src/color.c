#define NXT(val) (val < 2 ? val + 1 : 0)
#define LST(val) (val > 0 ? val - 1 : 2)

void nextColor(tSensors led)
{
	ubyte RGB[3];
	RGB[0] = getTouchLEDRed(led);
	RGB[1] = getTouchLEDGreen(led);
	RGB[2] = getTouchLEDBlue(led);

	for (ubyte i = 0; i < 3; ++i)
	{
		if (RGB[i] == 255)
		{
			ubyte n, l;
			if (RGB[l = LST(i)] == 0)
			{
				if (RGB[n = NXT(i)] < 255)
				{
					RGB[n]++;
					goto RGB_END;
				}
			}
			else
			{
				RGB[l]--;
				goto RGB_END;
			}
		}
	}
	RGB[0] = 255; RGB[1]= RGB[2] = 0;
	RGB_END: setTouchLEDRGB(led, RGB[0], RGB[1], RGB[2]);
}
