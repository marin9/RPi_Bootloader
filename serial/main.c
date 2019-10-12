#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "serial.h"


#define CMD_TEST	0
#define CMD_EXE		1
#define PACK_LEN	32


char *input_default="kernel.img";
char *serial_default="/dev/ttyUSB0";
char *input_path;
char *serial_path;



char* load_file(char *path, int *size){
	FILE *f;
	char *data;

	// open file	
	f=fopen(path, "rb");
	if(!f){
		printf("ERROR: file_open: %s.\n %s\n", strerror(errno), path);
		exit(1);
	}

	// get file size
	fseek(f, 0L, SEEK_END);
	*size=ftell(f);
	fseek(f, 0L, SEEK_SET);

	// allocate memory
	data=(char*)malloc(*size);
	if(!data){
		printf("ERROR: malloc: %s.\n", strerror(errno));
		exit(2);
	}

	// read file
	*size=fread(data, 1, *size, f);
	if(*size<0){
		printf("ERROR: fread: %s.\n %s\n", strerror(errno), path);
		exit(3);
	}
	fclose(f);
	return data;
}

void run_test(){
	char buf[PACK_LEN]={0};
	printf("TEST\t");
	serial_open(serial_path);
	serial_send(buf, PACK_LEN);
	serial_recv(buf, PACK_LEN);
	serial_close();
	printf("OK\n");
}

void send_prog(){
	int size;
	char *data;
	char msg[PACK_LEN];

	printf("Boot...\n");
	serial_open(serial_path);

	// load file
	data=load_file(input_path, &size);
	printf("1/5 File read\t\tOK\n");

	// send request
	printf("2/5 Send request\t");
	msg[0]=CMD_EXE;
	sprintf(msg+1, "%d", size);
	serial_send(msg, PACK_LEN);
	printf("OK\n");

	// recv response
	printf("3/5 Recv ack\t\t");
	serial_recv(msg, PACK_LEN);
	printf("OK\n");

	// send file
	printf("4/5 Send file\t\t");
	serial_send(data, size);
	printf("OK\n");	
	
	// recv response
	printf("5/5 Recv ack\t\t");
	serial_recv(msg, PACK_LEN);
	printf("OK\n");

	serial_close();
	printf("Finish\n");
}


int main(int argc, char **argv){
	int c, test=0;

	input_path=input_default;
	serial_path=serial_default;

	while((c=getopt(argc, argv, "s:i:th"))!=-1){
		switch(c){
		case 's':
			serial_path=optarg;
			break;
		case 'i':
			input_path=optarg;
			break;
		case 't':
			test=1;
			break;
		case 'h':
			printf("Usage:\n");
			printf(" -t        : run test\n");
			printf(" -h        : print help\n");
			printf(" -s [path] : set serial path\n");
			printf(" -i [path] : set executable path\n");
			exit(0);
		default:
			printf(" Illegal options.\n");
			exit(1);
		}
	}

	if(test)
		run_test();
	else
		send_prog();

	return 0;
}
