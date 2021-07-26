#include <stdio.h>
#include <stdlib.h>

// Dumps raw memory in hex byte and printable split format
void dump(const unsigned char *data_buffer, const unsigned int len){
	unsigned char byte;
	unsigned int i, j;

	for(i=0; i < len; i++){
		byte = data_buffer[i];
		printf("%02x ", data_buffer[i]);  // Display byte in hex
		if(((i%16)==15) || (i==len-1)) {
			for(j=0; j < 15-(i%16); j++) 
				printf("    ");
			printf("| ");
			for(j=(i-(i%16)); j <= i; j++) {
				byte = data_buffer[j];
				if((byte > 31) && (byte < 127))
					printf("%c", byte);
				else
					printf(".");
			}
			printf("\n");
		}  // End if
	}	// End for
}

int fatal(const char *msg){
	fprintf(stderr, "\x1b[31m[ERRO] %s\x1b[0m\n", msg);
	exit(1);
}
