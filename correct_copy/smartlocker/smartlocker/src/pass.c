#include "pass.h"

int8u verpass (char *str1, char  *str2)
{
	return (strcmp(str1,str2)) ? 0:1;
	
}
void read_pass(int8u symbol, char  *pass_temp)
{
	int8u i,x;
	
	lcdr2();
	lcdwc(0xCA);
	for (i = 0; i < 4; i++) {
		x = *pass_temp++ = get_data();
		
		if (symbol)
			lcdwd('*');
		else
			lcdwd(x);
			 
		beep(1,75);
	}
	*pass_temp = '\0';

}