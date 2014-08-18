/**************************************************************************
 *  This program is free software: you can redistribute it and/or modify  *
 *  t under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or     *
 *  (at your option) any later version.                                   *
 *                                                                        *
 *  This program is distributed in the hope that it will be useful,       *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *  GNU General Public License for more details.                          *
 *                                                                        *
 *  You should have received a copy of the GNU General Public License     *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *************************************************************************/

/*
 *	author:	lisper <lisper.li@dfrobot.com> 2014-07-24
 *	example for encoder v3
 */

#define PinA 2	//int0
#define PinB 3	//int1

volatile int32_t count = 0; //
volatile int32_t count1 = 0; 

volatile int enState = 0;

//
void setup() {
	Serial.begin(9600);

	pinMode(PinA,INPUT_PULLUP);
	pinMode(PinB,INPUT_PULLUP);

	attachInterrupt(0, funcA, CHANGE); 
	attachInterrupt(1, funcB, CHANGE);
}

//
void loop() {
	//while count changed print it
	while (count1 != count) {
		count1 = count;
		Serial.println(count*2.25);
	}
}

//int0
void funcA () {
	int state = digitalRead (PinA);
	if (state) {
		if (enState == 0) 
			count++, enState = 2;
	}
	else if (enState == 1)
		enState = 0;
}

//int1
void funcB () {
	int state = digitalRead (PinB);
	if (state) {
		if (enState == 0)  
			count--, enState= 1;
	} 
	else if (enState == 2)
		enState = 0;
}


