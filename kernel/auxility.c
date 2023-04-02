#include "auxility.h"


void memset(char* pointer,char byte,uint32_t bytes_to_delete)
{
	for(uint32_t tmp = 0;tmp<bytes_to_delete;++tmp){
		*(pointer+tmp) = byte;
	}
}
