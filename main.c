/*LED Dice Prototype
SeungBum Kim <picxenk_at_gmail.com>
2010/9/26

== References ==
- http://www.instructables.com/id/Faraday-For-Fun-An-Electronic-Batteryless-Dice/
- http://www.instructables.com/id/Simple-electronic-dice
- http://brownsofa.org/blog/archives/50
*/

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

const char ledcode[] PROGMEM= {0xfc, 0xee, 0xf8, 0xf2, 0xf0, 0xe2, 0xfe};

int main(void)
{
	unsigned char temp=0;
	int i, mixed;
	mixed = 0;
	DDRB=0xfe; 
	TCCR0B=2;
	TCCR0A=0;
	TCNT0= 0;

	PORTB=254; /*disable all LEDs*/
	uint8_t randSeed = eeprom_read_byte ((uint8_t*)1);
	randSeed = randSeed + rand() / (RAND_MAX / 6 + 1);
	srand (randSeed);
	temp= rand() / (RAND_MAX / 6 + 1);
	temp = pgm_read_byte(&ledcode[temp]);

	while(1)
	{
		if (mixed == 0) {
			for (i=0; i<7; i++) {
				temp = rand() / (RAND_MAX / 6 + 1);
				temp = pgm_read_byte(&ledcode[temp]);
				PORTB = temp;
				_delay_ms(70);
				PORTB = 254;
				randSeed = randSeed + rand() / (RAND_MAX / 6 + 1);
				srand(randSeed);	
			}
			mixed = 1;
		}
		PORTB=temp;
		_delay_loop_2(50000);	 		
		eeprom_write_byte ((uint8_t*)1, randSeed);

	}

	return 0;
}
