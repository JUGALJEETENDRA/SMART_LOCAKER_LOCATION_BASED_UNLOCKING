#ifndef _APP_H
#define _APP_H
/* Main settings */
#define PH_NUM	 "9819691341"
/*comment below line for release*/
#define EEPROM_DISPLAY				0
/******** STRUCTURE DEFINITION **********/
struct App {
	volatile char	vibr	:1;
	volatile char	sw		:1;
	volatile char	found	:1;
	volatile char	trac	:1;
	volatile char	Msg		:1;
};
/******** STRUCTURE DEFINITION **********/
/******** MAIN CONFIGURATION ENDS ****************/
/* LCD CONFIGURATION */
#define LCD_DDR           	   		DDRC
#define LCD_DATA_PORT          		PORTC
#define LCD_ENABLE_PIN        		PC3
#define LCD_REGISTER_SELECT_PIN     PC2
#define DISPLAY_INIT				1
#define LCD_NSCRL					0
#define FLOAT_T0_STRING				1
#define DECIMAL_PRECISION			10
/******** LCD CONFIGURATION ENDS ****************/
/* BUZZER: CONFIGURATION */
#define	BUZ_DDR						DDRC
#define	BUZ_PORT					PORTC
#define	BUZ_PIN						PC1
#define OFF_TIME					100
/******** BUZZER CONFIGURATION ENDS ****************/
/* LED: CONFIGURATION */
#define	LED_DDR			DDRC
#define	LED_PORT		PORTC
#define	LED_PIN			PC0
#define OFF_TIME		100
/******** LED CONFIGURATION ENDS ****************/
/* GSM: CONFIGURATION */
#define MSG_START					""
#define MSG_END						". Automated SMS By: LBU."
/******** ADC CONFIGURATION ENDS ****************/
#define REF_VOL_256
/*********** MOTOR CONFIGURATION ***************/
#define MOT_DDR			DDRA
#define MOT_PORT		PORTA
#define M1_AN			PA3
#define M1_CA			PA4
#define M2_AN			PA4
#define M2_CA			PA5
/******** MOTOR CONFIGURATION ENDS ****************/

/******** EEPROM CONFIGURATION ****************/
#define EEPROM_DISPLAY		0
/******** KEYBAORD CONFIGURATION *************/
#define KEYBOARD_DDR		DDRB
#define KEYBOARD_PORT		PORTB
#define key_data 			PINB
/******** CONFIGURATION ENDS  ***************/
#endif