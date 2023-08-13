#ifndef MAIN_H
#define MAIN_H

#include "includes.h"

#define INTDDR					DDRD
#define INTPORT					PORTD
#define INT0_PIN				PD2
#define INT1_PIN				PD3

#define SW_DDR					DDRD
#define SW_PORT					PORTD
#define SW_PIN					PIND
#define TOP_SW_PIN				PD6
#define BOT_SW_PIN				PD7

//DEFINE CONSTANT
#define MAX_CNT					3
#define LAT_DEVI				0.03000
#define LON_DEVI				0.03000

//DEFINE MACROS
#define StartTmr()			TCCR0  	|= _BV(CS01)
#define StopTmr()			TCCR0  	&= ~_BV(CS01)

//FUNCTION PROTOTYPES
static void		init		(void);
static void 	disptitl 	(void);
static void 	tmr1init	(void);
static void 	EXTINTinit	(void);
static void 	StoreLoc	(void);
static void 	TrackLoc	(void);
static void 	read_pass	(char  *pass_temp);
static int8u 	verpass 	(char  *pmsg);
static void 	moton		(void);
static void 	motoff		(void);
static void 	WriteLatLon	(int8u lat[], int8u lon[]);
static void 	ReadLatLon	(int8u lat[], int8u lon[]);
static int8u 	CompLoc		(int8u lat[], int8u lon[]);
static void		FlagsInit	(void);
static void		ProcVibr	(void);


#endif
