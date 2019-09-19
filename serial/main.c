#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "serial.h"


#define CN	"\x1B[0m"
#define CR	"\x1B[31m"
#define CG	"\x1B[32m"
#define CY	"\x1B[33m"
#define PACK_LEN	32

#define CMD_TEST	0
#define CMD_EXE		1


char* load_file(char *path, int *size){
	FILE *f;
	char *data;

	// open file	
	f=fopen(path, "rb");
	if(!f){
		printf("%sFAIL%s\n", CR, CN);
		printf("ERROR: file_open: %s.\n", strerror(errno));
		exit(10);
	}

	// get file size
	fseek(f, 0L, SEEK_END);
	*size=ftell(f);
	fseek(f, 0L, SEEK_SET);

	// allocate memory
	data=(char*)malloc(*size);
	if(!data){
		printf("%sFAIL%s\n", CR, CN);
		printf("ERROR: malloc: %s.\n", strerror(errno));
		exit(11);
	}

	// read file
	*size=fread(data, 1, *size, f);
	if(*size<0){
		printf("%sFAIL%s\n", CR, CN);
		printf("ERROR: file_read: fread: %s.\n", strerror(errno));
		exit(12);
	}
	fclose(f);
	return data;
}



void run_test(){
	char buf[PACK_LEN];

	printf("Test...\n");

	memset(buf, 0, PACK_LEN);
	serial_send(buf, PACK_LEN);
	serial_recv(buf, PACK_LEN);

	printf("1/1 Ready\t%sOK%s\n", CG, CN);
}

void send_prog(char *path){
	int size;
	char *data;
	char msg[PACK_LEN];

	printf("Boot...\n");

	// load file
	data=load_file(path, &size);
	printf("1/5 File read\t%sOK%s\n", CG, CN);

	// send request
	printf("2/5 Send request\t");
	msg[0]=CMD_EXE;
	sprintf(msg+1, "%d", size);
	serial_send(msg, PACK_LEN);
	printf("%sOK%s\n", CG, CN);

	// recv response
	printf("3/5 Recv ack\t");
	serial_recv(msg, PACK_LEN);
	printf("%sOK%s\n", CG, CN);

	// send file
	printf("4/5 Send file\t");
	serial_send(data, size);
	printf("%sOK%s\n", CG, CN);	
	
	// recv response
	printf("5/5 Recv ack\t");
	serial_recv(msg, PACK_LEN);
	printf("%sOK%s\n", CG, CN);

	printf("%sFinish%s\n", CG, CN);
}


int main(int argc, char **argv){
	if(argc==2){
		// Run test
		serial_open(argv[1]);
		run_test();
		serial_close();
		return 0;

	}else if(argc==3){
		// Execute program
		serial_open(argv[1]);
		send_prog(argv[2]);
		serial_close();
		return 0;

	}else{
		// Print help
		printf("%sWARNING: Illegal arguments.%s\n", CY, CN);
		printf("Usage:\n");
		printf("For boot: rpiloader [serial] [file]\n");
		printf("For test: rpiloader [serial]\n");
		return 1;
	}
}
