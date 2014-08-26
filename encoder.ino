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
 *	example for encoder v4
 */

#define PinA 2	//int0
#define PinB 3	//int1

volatile int32_t count = 0; //
volatile int32_t count1 = 0; 

volatile int enState = 0;

volatile int stateA,stateB;
volatile uint32_t delay_time;
volatile boolean direction = 0;


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
    Serial.print (count * 0.5625);  // *2.25/4
    Serial.print (" ");
    Serial.print (direction);
    Serial.print (" ");
    Serial.println (delay_time);
  }
}

//int0
void funcA () {
  static uint32_t start_time;
  stateA = digitalRead (PinA);
  if (stateA && stateB) {
    count--;
    direction = 0;
    uint32_t now_time = millis ();
    delay_time = now_time - start_time;
    start_time = now_time;    
  } else if (stateA && !stateB) {
    count++;
  } else if (!stateA && stateB) {
    count++;
  } else if (!stateA && !stateB) {
    count--;
  }
}

//int1
void funcB () {
  static uint32_t start_time;
  stateB = digitalRead (PinB);
  if (stateA && stateB) {
    count++;
    direction = 1;
    uint32_t now_time = millis ();
    delay_time = now_time - start_time;
    start_time = now_time;
  } else if (stateA && !stateB) {
    count--;
  } else if (!stateA && stateB) {
    count--;
  } else if (!stateA && !stateB) {
    count++;
  }
}



