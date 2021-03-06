/**
 * @file   main.cpp
 * @author breadbread1984 <breadbread1984@163.com>
 * @date   Sat Jul 21 15:12:00 2012
 * 
 * @section DESCRIPTION 
 * 
 * openDrone Quadcopter Main function File
 * 
 * @section LICENSE
 * 
 * GPLv3 
 */


#include "wirish.h"
#include "GlobalXYZ.h"
#include "Pressure.h"
#include "Motor.h"

#define PWM_PIN 2

void setup()
{
    /* Set up the LED to blink  */
    pinMode(BOARD_LED_PIN, OUTPUT);

    /* Turn on PWM on pin PWM_PIN */
    pinMode(PWM_PIN, PWM);
    pwmWrite(PWM_PIN, 0x8000);

    /* Send a message out USART2  */
    Serial2.begin(9600);
	
	/* pin mode setup related to motor should has to be put here*/
	pinMode(D28,PWM);
	pinMode(D27,PWM);
	pinMode(D11,PWM);
	pinMode(D12,PWM);
	Timer3.setPeriod(2080);
}

void loop()
{
	while(1) {
#if 1
		Vector<double> quaternion = GlobalXYZ::getQuaternion();
		for(int i = 0 ; i < quaternion.size() ; i++) {
			float n = quaternion(i);
			unsigned char * ptr = reinterpret_cast<unsigned char*>(&n);
			for(int i = 0 ; i < sizeof(float) ; i++) {
				unsigned char b1 = (ptr[i] >> 4) & 0x0f;
				unsigned char b2 = (ptr[i] & 0x0f);
				char c1 = (b1 < 10) ? ('0' + b1) : 'A' + b1 - 10;
				char c2 = (b2 < 10) ? ('0' + b2) : 'A' + b2 - 10;
				SerialUSB.print(c1);
				SerialUSB.print(c2);
			}
			SerialUSB.print(",");
		}
#endif
#if 0
		Vector<double> x,y,z;
		GlobalXYZ::getXYZ(x,y,z);
		SerialUSB.print("X = ("); SerialUSB.print(x(0)); SerialUSB.print(","); SerialUSB.print(x(1)); SerialUSB.print(","); SerialUSB.print(x(2)); SerialUSB.print(") ");
		SerialUSB.print("Y = ("); SerialUSB.print(y(0)); SerialUSB.print(","); SerialUSB.print(y(1)); SerialUSB.print(","); SerialUSB.print(y(2)); SerialUSB.print(") ");
		SerialUSB.print("Z = ("); SerialUSB.print(z(0)); SerialUSB.print(","); SerialUSB.print(z(1)); SerialUSB.print(","); SerialUSB.print(z(2)); SerialUSB.print(")");
#endif
#if 0
		double roll = 0,pitch = 0,yaw = 0;
		GlobalXYZ::getRPY(roll,pitch,yaw);
		roll *= 180 / 3.1415926; pitch *= 180 / 3.1415926; yaw *= 180 / 3.1415926;
		SerialUSB.print("roll = "); SerialUSB.print(roll); SerialUSB.print("\t");
		SerialUSB.print("pitch = "); SerialUSB.print(pitch); SerialUSB.print("\t");
		SerialUSB.print("yaw = "); SerialUSB.print(yaw); SerialUSB.print("\t");
		Vector<double> pressure = Pressure::getReading();
		SerialUSB.print("pressure = "); SerialUSB.print(pressure(0)); SerialUSB.print("pa\t");
		SerialUSB.print("temperature = "); SerialUSB.print(pressure(1) * 0.1); SerialUSB.print("C\t");
		SerialUSB.print("altitude = "); SerialUSB.print(pressure(2)); SerialUSB.print("m\t");
		toggleLED();
		static int level = 0;
		Motor::control1(500 + (level++) % 500);
		Motor::control2(500 + (100 + level++) % 500);
		Motor::control3(500 + (200 + level++) % 500);
		Motor::control4(500 + (300 + level++) % 500);
#endif
#if 0
		Vector<double> retVal = Accelerometer::getReading();
		SerialUSB.print("x = "); SerialUSB.print(retVal(0)); 
		SerialUSB.print("\ty = "); SerialUSB.print(retVal(1)); 
		SerialUSB.print("\tz = "); SerialUSB.print(retVal(2));
#endif
#if 0
		Vector<double> retVal = Gyroscope::getReading();
		SerialUSB.print("x = "); SerialUSB.print(retVal(0)); 
		SerialUSB.print("\ty = "); SerialUSB.print(retVal(1)); 
		SerialUSB.print("\tz = "); SerialUSB.print(retVal(2));		
#endif
#if 0
		Vector<double> retVal = Compass::getReading();
		SerialUSB.print("x = "); SerialUSB.print(retVal(0));
		SerialUSB.print("\ty = "); SerialUSB.print(retVal(1));
		SerialUSB.print("\tz = "); SerialUSB.print(retVal(2));
#endif
#if 0
		Compass::calibrate();
#endif
#if 0
		static int k = 0;
		k = (k >= 1000)?1000:k+1;
		Motor::control1(k);
		Motor::control2(k);
		Motor::control3(k);
		Motor::control4(k);
		delay(3000);
#endif

		SerialUSB.println();
		delay(200);
    }
    
	SerialUSB.println();
}

/* Please Do Not Remove & Edit Following Code */
int main(void) {
    setup();

    while (true) {
        loop();
    }

    return 0;
}
