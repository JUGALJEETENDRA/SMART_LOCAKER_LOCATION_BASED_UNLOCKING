
#include "otp.h"

int8u EEMEM MAGIC_ADDRESS;
int8u EEMEM RANDOM_ADDRESS;

int8u RandomNumber;

void chkEEPROM(void) {
	
	int8u MagicNumber;
	int8u Temporaryvariable;

	#if EEPROM_DISPLAY > 0
	lcdclr();
	lcdws("CHECKING EEPROM");
	lcdr2();
	dlyms(1000);
	#endif

	MagicNumber = eeprom_read_byte (&MAGIC_ADDRESS);
	if (MagicNumber == MAGIC_NO) {
		#if EEPROM_DISPLAY > 0
		lcdws("SUCCESSFULL.....");
		dlyms(1000);
		#endif
		RandomNumber = eeprom_read_byte (&RANDOM_ADDRESS);
		Temporaryvariable = RandomNumber + 1;
		eeprom_write_byte(&RANDOM_ADDRESS, Temporaryvariable);
		} else  {
		#if EEPROM_DISPLAY > 0
		lcdws("  NEW EEPROM");
		dlyms(1000);
		#endif
		MagicNumber = MAGIC_NO;
		eeprom_write_byte(&MAGIC_ADDRESS, MagicNumber);
		RandomNumber = 56;
		eeprom_write_byte(&RANDOM_ADDRESS, RandomNumber );
	}
	srand (RandomNumber);
	#if EEPROM_DISPLAY > 0
	lcdclr();
	#endif
}



void genOTP(char *OTP) {
	int8u i;
	OTP[4] = '\0';

	#if OTP_DISPLAY > 0
		lcdclr();
		lcdws("GENERATING......");
		lcdr2();
		lcdws("PASSWORD:");
	#else
		dlyms(500);
	#endif
	
	for (i = 0; i < 4; i++){
		OTP[i] = '0' + (rand() % 10);
		#if OTP_DISPLAY > 0
			LCDWriteData(OTP[i]);
		#endif
	}
	#if OTP_DISPLAY > 0
		dlyms(1000);
		lcdclr();
	#endif
}