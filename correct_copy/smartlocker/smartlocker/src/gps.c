/* gps.c: device driver for GPS receiver interface */

static const char PwrOff[] 		= "AT+CGNSPWR=0\r";
static const char PwrOn[] 		= "AT+CGNSPWR=1\r";
static const char Info[]  		= "AT+CGNSINF\r";

#include"gps.h"

void GPSInit(void) {
//	GSM_GPS_DDR |= _BV(GSM_GPS_PIN);
//	GSM_GPS_PORT &= ~_BV(GSM_GPS_PIN);
	puts(PwrOff);
	dlyms(100);
	puts(PwrOn);
}/*
void GPSgetloc(int8u *Lat, int8u *Lon)
{
	int8u i;
ReadAgain:
	while(getchar() != '$');
	if(getchar() != 'G')
		goto ReadAgain;
	if(getchar() != 'P')
 		goto ReadAgain;
	if(getchar() != 'G')
		goto ReadAgain;
	if(getchar() != 'G')
		goto ReadAgain;
	if(getchar() != 'A')
		goto ReadAgain;
	while(getchar() != ',');
	while(getchar() != ',');
	for(i = 0; i < 9; i++)
		*Lat++ = getchar();
	while(getchar() != 'N');
	while(getchar() != ',');
	for(i = 0; i < 10; i++)
		*Lon++ = getchar();
} */
void GPSgetloc(int8u *Lat, int8u *Lon) {
	int8u i;
	puts(Info);
	
	while(getchar() != '+');
	while(getchar() != ',');
	while(getchar() != ',');
	while(getchar() != ',');
	for(i = 0; i < 9; i++)
		*Lat++ = getchar();
	while(getchar() != ',');
	for(i = 0; i < 10; i++)
		*Lon++ = getchar();
}
