#include <Wire.h>

class ServoHelper
{
public:
	int getPulseWidth(int angle){
		int pulseWidth, analogValue;
		pulseWidth = (angle - 0) * (MAX_PULSE_WIDTH - MIN_PULSE_WIDTH) / (180 - 0) + MIN_PULSE_WIDTH;
		analogValue = int(float(pulseWidth)/ 1000000 * FREQ * 4096);
		return analogValue;
	}
}