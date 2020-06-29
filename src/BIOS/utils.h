#ifndef BIOS_UTILS_H_
#define BIOS_UTILS_H_

/***************************************
 * 		Include Libraries 			   *
 **************************************/
#include "system.h"

/**************************************************
 * 		Define						  			  *
 *************************************************/
#define BUFSIZE (sizeof(long) * 8 + 1)

/**************************************************
 * 		Function Prototype			  			  *
 *************************************************/
char *ltoa(long N, char *str, int base);

#endif /* BIOS_UTILS_H_ */
