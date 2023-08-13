
#include "main.h"

const char *MSG[] = { "Your OTP for unlocking is:",
					  "Locker trying to open at "
					};
int8u EEMEM LAT_ADDR[11];
int8u EEMEM LON_ADDR[11];
int8u OTP[5];
extern int8u lcdptr;
struct App Flags;

int main(void) {
	init();
	while (TRUE) {
		if (Flags.trac && !Flags.found)
			TrackLoc();
		if (Flags.vibr)
			ProcVibr();
		if (Flags.sw)
			StoreLoc();
		sleep_cpu();
	}
	return 0;
}
static void init(void) {
	buzinit();
	ledinit();
	SW_DDR  &= ~(_BV(TOP_SW_PIN) | _BV(BOT_SW_PIN));
	SW_PORT |= (_BV(TOP_SW_PIN) | _BV(BOT_SW_PIN));
	beep(2,100);
	lcdinit();
	M1Init();
	uartinit();
	EXTINTinit();
	GPSInit();
	GSMinit();
	chkEEPROM();
	tmr1init();
	FlagsInit();
	disptitl();
	sei();
	sleep_enable();
	sleep_cpu();
}
static void ProcVibr(void) {
	lcdclrr(1);
	lcdws("Vibra'n Occurred");
	SendLinkLoc(PH_NUM, MSG[1]);
	lcdclrr(1);
	buzoff();
	Flags.vibr = FALSE;
}
static void TrackLoc(void) {
	int8u lat[11], lon[11];
	int8u InVldCnt = 0;
	int8u pass[5];
	int8u i;

	for (i = 0; i < 10; i++)
		lat[i] = lon[i] = '0';

	lat[10] = lon[10] = '\0';

	Flags.trac = FALSE;
	lcdclrr(1);
	beep(1,100);
	lcdws("Find'g Location");
	GPSgetloc(lat,lon);
	if (CompLoc(lat,lon)) {
		lcdclrr(1);
		lcdws("Location Found");
		beep(1,100);
		dlyms(1000);
		SendOTP(PH_NUM, MSG[0]);
		Flags.found = TRUE;
CHK_PASS:
		lcdclr();
		lcdws(" ENTER PASSWORD");
		beep(1,100);
		read_pass(pass);
		switch(verpass(pass)) {
			case 1:
				beep(1,100);
				lcdws("    Verified");
				dlyms(1000);
				moton();
				lcdclr();
				lcdws(" Collect Items");
				beep(1,250);
				dlyms(5000);
				motoff();
				InVldCnt = 0;
				lcdclr();
				lcdws("   Thank You");
				ledoff();
				cli();
				for(;;);
				break;
		default:
				buzon();
				lcdclr();
				lcdws("Wrong Password");
				beep(1,250);
				dlyms(500);
				buzoff();
				if (++InVldCnt >= MAX_CNT) {
					lcdclr();
					lcdws(" System Locked!");
					ledon();
					cli();
					for(;;);
				} else goto CHK_PASS;
				break;
		}
	}
	lcdclrr(1);
}
static void moton(void) {
	lcdclr();
	lcdws(" Locker Opening");
	beep(1,100);
	MotClk();
	while (SW_PIN & _BV(TOP_SW_PIN));
	MotStop();
}
static void motoff(void) {
	lcdclr();
	lcdws(" Locker Closing");
	beep(1,100);
	MotAclk();
	while (SW_PIN & _BV(BOT_SW_PIN));
	MotStop();
	beep(1,100);
}
static int8u verpass (char  *pmsg) {
	return (strcmp(OTP,pmsg)) ? 0:1;
}
static void read_pass(char  *pass_temp) {
	int8u i;
	lcdr2();
	lcdwc(0xC6);
	for (i = 0; i < 4; i++) {  
		*pass_temp++ = get_data();	
		lcdwd('*');
		beep(1,75);
	}
	*pass_temp = '\0';
}
static int8u CompLoc(int8u lat[], int8u lon[]) {
	double LatRef, LonRef, latD, lonD;
	int8u latEE[11], lonEE[11];
	int8u pass[5], i, InVldCnt = 0;

	for (i = 0; i < 10; i++)
		latEE[i] = lonEE[i] = '0';

	latEE[10] = lonEE[10] = '\0';

	ReadLatLon(latEE,lonEE);		/* Read REF from EEPROM */	

	LatRef = atof(latEE);
	LonRef = atof(lonEE);

	latD = atof(lat);
	lonD = atof(lon);

	if ((latD >= (LatRef - LAT_DEVI)) && (latD <= (LatRef + LAT_DEVI))) 
		if ((lonD >= (LonRef - LON_DEVI)) && (lonD <= (LonRef + LON_DEVI))) 
			return 1;
	return 0;
}	
static void StoreLoc(void) {
	double latD, lonD;
	int8u lat[11], lon[11], i;

	for (i = 0; i < 10; i++)
		lat[i] = lon[i] = '0';
	lat[10] = lon[10] = '\0';

	lcdclrr(1);
	lcdws("Stor'g Location");
	beep(1,100);
	GPSgetloc(lat,lon);
	latD = atof(lat);
	lonD = atof(lon);
	WriteLatLon(lat,lon);
	Flags.sw = FALSE;
	lcdclrr(1);
}
static void EXTINTinit(void) {
	INTDDR 	&= ~_BV(INT0_PIN);
	INTPORT |= _BV(INT0_PIN);

	INTDDR 	&= ~_BV(INT1_PIN);
	INTPORT |= _BV(INT1_PIN);

	GICR |= _BV(INT0) | _BV(INT1);			//ENABLE EXTERNAL INTERRUPT
	MCUCR |= _BV(ISC01) | _BV(ISC11);		//FALLING EDGE INTERRUPT

}
static void disptitl(void) {
	lcdclr();
	lcdws("Loc'n B'd unLock");
}
static void tmr1init(void) {
	TCNT1H   = 225;					/* overflows at every 250msec */
	TCNT1L   = 123;
	TIMSK   |= _BV(TOIE1);			/* ENABLE OVERFLOW INTERRUPT */
	TCCR1A   = 0x00;
	TCCR1B  |= _BV(CS12);			 /* PRESCALAR BY 256 */
}
/* overflows at every 250msec */
ISR(TIMER1_OVF_vect) {
	static int8u i, j;
	TCNT1H   = 225;					/* overflows at every 250msec */
	TCNT1L   = 123;
	if (++j >= 20) {
		Flags.trac = TRUE;
		j = 0;
	}
	if (++i >= 20)
		i = 0;
	switch(i) {
		case 0: case 2: ledon(); break;
		case 1: case 3: ledoff(); break;
	}
}
ISR(INT0_vect) { 
	Flags.sw = TRUE;
	GICR |= _BV(INT0);
}
ISR(INT1_vect) { 
	Flags.vibr = TRUE;
	buzon();
	GICR |= _BV(INT1);
}
void WriteLatLon(int8u lat[], int8u lon[]){
	eeprom_update_block ((const void *)lat, (void *)LAT_ADDR, 11);
	eeprom_update_block ((const void *)lon, (void *)LON_ADDR, 11);
}
void ReadLatLon(int8u lat[], int8u lon[]){
	eeprom_read_block ((void *)lat , (const void *)LAT_ADDR, 11) ;
	eeprom_read_block ((void *)lon, (const void *)LON_ADDR, 11) ;
		
}
static void FlagsInit(void) {
	Flags.found = FALSE;
	Flags.sw	= FALSE;
	Flags.vibr	= FALSE;
	Flags.trac	= FALSE;
}

