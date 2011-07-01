/* 
 * File:   lcdFramework.h
 * Author: scuzzy
 *
 * Created on 01 July 2011, 11:11 PM
 */

#ifndef _LCDFRAMEWORK_H
#define	_LCDFRAMEWORK_H


struct lcdData
{
	uint16_t width;
	uint16_t height;
	uint8_t bitDepth : 5;
	uint8_t colour : 1;
	uint8_t backlight : 1;
} __attribute__((packed));

#ifndef BITDEPTH
#define BITDEPTH 8
#endif

union pixelColour
{
	struct
	{
		uint8_t R : BITDEPTH;
		uint8_t G : BITDEPTH;
		uint8_t B : BITDEPTH;
	} RGB;

	struct
	{
		uint8_t M : BITDEPTH;
	} MONO;
};

#endif	/* _LCDFRAMEWORK_H */

