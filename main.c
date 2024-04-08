/*Headers*/
#include "config_header.h"
#include "adc_header.h"
#include "lcd_header.h"
#include <pic18f4550.h>
#include <stdio.h>
#include <string.h>
# define _XTAL_FREQ 8000000 /* Set external oscillator to 8Mhz */
void main() {
/* Configuration variables & initialization functions*/
OSCCON = 0x72; /* Internal Oscillator - 8 MHz*/
ADC_Init(); /* Initialize 10-bit ADC*/
LCD_Init(); /* Initialize & Clear LCD*/
TRISA = 0x3C; /* RA0 & RA1 - input, RA2-RA5 - output */
TRISCbits.TRISC2 = 0; /* RC2 - output */
TRISAbits.RA2 = 0; /* RA2-RA5 - LOW */
TRISAbits.RA3 = 0;
TRISAbits.RA4 = 0;
TRISAbits.RA5 = 0;
/* Temperature variables */
int set_temperature = 25;
/* Data variables*/
char Temperature[10]; /* ADC values - strings */
float temp; /* ADC values - decimal numbers */
while (1) {
/* ADC readings*/
temp = (ADC_Read(0) * 4.88) / 10.00; /* ADC values to degrees/percentage */
/* ADC data conversion */
sprintf(Temperature, "%d%cC", (int) temp, 0xdf); /* Convert INT values to ASCII
strings */
/* Parameters display */
LCD_Clear();
LCD_String_xy(1, 0, "T: "); /* Display data */
LCD_String_xy(1, 4, Temperature);
/* Data storage */
memset(Temperature, 0, 10); /* Store parameters in memory */
/* Conditions*/
LATAbits.LATA2 = temp < 25 ? 1 : 0; /* Heating condition */
LATAbits.LATA5 = temp < set_temperature; /* Status LED condition */
}
}