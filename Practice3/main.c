#include "blinking_led.h"
#include "led_blinking_TC0.h"
//#include "led_blinking_TC0_ints.h"
//#include "fan.h"
#include "lm35.h"

int main(void) {
	int c = 4;
	switch(c) {
		case 0:
			return blinking_led();
		case 1:
			return led_blinking_TC0();
		case 2:
			return lm35();
//		case 3:
//			return fan();
		case 4:
			return dist_sensor();
		default:
			return 0;
	}
		
}
