#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <arpa/inet.h>

uint32_t convert_to_le(uint32_t num){
	uint32_t b0,b1,b2,b3;
	uint32_t res;
	b0 = (num & 0x000000ff) << 24;
	b1 = (num & 0x0000ff00) << 8;
	b2 = (num & 0x00ff0000) >> 8;
	b3 = (num & 0xff000000) >> 24;
	res = b0 | b1 | b2 | b3;
	return res;
}

uint32_t fileop(char *filename){
	FILE *stream = fopen(filename, "rb");
	uint32_t val;
	fread(&val, sizeof(val),1, stream);
	val = htonl(val);
	fclose(stream);
	return val;
}


int main(int argc, char *argv[]){
	uint32_t file1_byte = fileop(argv[1]);
	uint32_t file2_byte = fileop(argv[2]);	
	uint32_t sum = file1_byte + file2_byte;
	printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n", file1_byte,file1_byte,file2_byte,file2_byte, sum,sum);
}
