/*
 * main.c
 * 
 * Copyright 2013 Shimon <shimon@monistit.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
 
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include <utils.h>
#include <spi.h>
#include <mfrc522.h>
#define F_CPU 1000000UL

uint8_t SelfTestBuffer[64];
 
int main()
{
	uint8_t byte;
	uint8_t str[MAX_LEN];
	_delay_ms(50);
	lcd_init(LCD_DISP_ON); // initialize LCD
	lcd_clrscr();
	lcd_gotoxy(1,0);
	lcd_puts("RFID");
	//LCDWriteStringXY(2,0,"RFID Reader");
	//LCDWriteStringXY(5,1,VERSION_STR);
	
	
	spi_init();
	_delay_ms(1000);
	//LCDClear();
	
	//init reader
	mfrc522_init();
	unsigned int i=0;
	while(1)
	{	
	//check version of the reader
	byte = mfrc522_read(VersionReg);
	
	if(byte == 0x92)
	{
		
		unsigned char c;
		i++;
		itoa(i,c, 10);
		
		lcd_gotoxy(1,1);
		
		lcd_puts(c);
		
		//LCDWriteStringXY(2,0,"MIFARE RC522v2");
		//LCDWriteStringXY(4,1,"Detected");
	}
	else if(byte == 0x91 || byte==0x90)
	{
		
		lcd_gotoxy(1,1);
		lcd_puts("MIFARE RC522V1");
		//LCDWriteStringXY(2,0,"MIFARE RC522v1");
		//LCDWriteStringXY(4,1,"Detected");
	}
	else
	{
		
		
		lcd_gotoxy(1,1);
		lcd_puts("no reader found");
		_delay_ms(2000);
		//LCDWriteStringXY(0,0,"No reader found");
	}
	
	/*byte = mfrc522_read(ComIEnReg);
	mfrc522_write(ComIEnReg,byte|0x20);
	byte = mfrc522_read(DivIEnReg);
	mfrc522_write(DivIEnReg,byte|0x80);*/
	
	_delay_ms(1500);
	lcd_clrscr();
	
	}
	
	//----------------------------------------------------------------
	/*while(1)
	{
		byte = mfrc522_request(PICC_REQALL,str);
		lcd_gotoxy(3,2);
		lcd_puts(byte);
		_delay_ms(1000);
	}*/
	
}
