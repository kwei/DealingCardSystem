#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>

#define RESET "\x1B[0m"			// color white
#define GRN   "\x1B[32m"		// color green
#define BLU   "\x1B[34m"		// color blue
#define RED   "\x1B[31m"		// color red

#define SERVERPORT 1234
#define SERVERIP "127.0.0.1"

struct pointers{
	FILE *file1;
	FILE *file2;
	FILE *file3;
	FILE *file4;
}STORAGE;

setupSocket(int *sock, struct sockaddr_in *addr){
	(*sock) = socket(AF_INET, SOCK_STREAM, 0);
	(*addr).sin_family = AF_INET;  
  	(*addr).sin_port = htons(SERVERPORT);  
 	(*addr).sin_addr.s_addr = INADDR_ANY;  
  	bind((*sock), (struct sockaddr*)addr, sizeof(*addr));
}

storage(){
	FILE *file1, *file2, *file3, *file4;

	file1 = fopen("cardset1.ods", "w+");
	file2 = fopen("cardset2.ods", "w+");
	file3 = fopen("cardset3.ods", "w+");
	file4 = fopen("cardset4.ods", "w+");

	if(file1 == NULL){
		printf(RED"cardset1");
		perror("fopen: "RESET);
		exit(-1);
	}
	if(file2 == NULL){
		printf(RED"cardset2");
		perror("fopen: "RESET);
		exit(-1);
	}
	if(file3 == NULL){
		printf(RED"cardset3");
		perror("fopen: "RESET);
		exit(-1);
	}
	if(file4 == NULL){
		printf(RED"cardset4");
		perror("fopen: "RESET);
		exit(-1);
	}

	STORAGE.file1 = file1;
	STORAGE.file2 = file2;
	STORAGE.file3 = file3;
	STORAGE.file4 = file4;
}

int main(int argc, char *argv[]){
	int sock, sock_client, status;  
  	struct sockaddr_in addr, client;
  	socklen_t len;
  	char info[6];

	setupSocket(&sock, &addr);
	status = listen(sock, 5);

	int exit_status = system("gnome-terminal --command=\"./deal 3\" ");			// This can open a new terminal window.


	printf(GRN"==== Waiting for dealing cards ====\n\n"RESET);
	
	len = sizeof(client);
	sock_client = accept(sock, (struct sockaddr *)&client, &len);				// blocking
	char *paddr_str = inet_ntoa(client.sin_addr);
	if(strcmp(paddr_str, SERVERIP) != 0){
		printf(RED"Not the same IP\n"RESET);
	}else{
		printf(GRN"Get!\n"RESET);
		storage();																// Open a file to store card set
	}																	



	fclose(STORAGE.file1);
	fclose(STORAGE.file2);
	fclose(STORAGE.file3);
	fclose(STORAGE.file4);

	close(sock_client);
	close(sock);

	return 0;
}