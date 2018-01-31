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

#define CARDS 13
#define TYPE 4
#define SERVERPORT 1234
#define SERVERIP "127.0.0.1"

int chosencardseq, chosentypeseq;

struct pointers{
	FILE *file1;
	FILE *file2;
	FILE *file3;
	FILE *file4;
}STORAGE;

int throw(const int members){
	int number = 0;
	srand(time(NULL));
	number = rand()%members;
	return number + 1;
}

getcard(int member, const char *cards, const char *types){
	printf("+--------------------+\n");
	printf("| ");
	printf("User #%d            ", member);
	printf("|\n");
	printf("| ");
	printf(GRN"Type %c             "RESET, *types);
	printf("|\n");
	printf("| ");
	printf(BLU "Card %2s            "RESET, cards);
	printf("|\n");
	printf("+--------------------+\n");
}

delegation(const int members, const char *cards[], const char *types[]){
	int member1 = 0, member2 = 0, member3 = 0, member4 = 0, iter_card = 0, iter_type = 0;
	char temp[4];

	for(iter_type = 0 ; iter_type < TYPE ; iter_type++){			// for every each type
		for(iter_card = 0 ; iter_card < CARDS ; iter_card++){		// for every each card
			while(1){
				sleep(1);
				int number = throw(members);
				if(members == 4){
					if(number == 1 && member1 != 52/members){
						member1++;
						strncpy(temp, cards[iter_card], sizeof(cards[iter_card]));
						fwrite(temp, 1, strlen(temp), STORAGE.file1);
						strncpy(temp, types[iter_type], sizeof(types[iter_type]));
						fwrite("\t", 1, 2, STORAGE.file1);
						fwrite(temp, 1, strlen(temp), STORAGE.file1);
						getcard(number, cards[iter_card], types[iter_type]);
						fwrite("\n", 1, 2, STORAGE.file1);
						break;
					}else if(number == 2 && member2 != 52/members){
						member2++;
						strncpy(temp, cards[iter_card], sizeof(cards[iter_card]));
						fwrite(temp, 1, strlen(temp), STORAGE.file2);
						strncpy(temp, types[iter_type], sizeof(types[iter_type]));
						fwrite("\t", 1, 2, STORAGE.file2);
						fwrite(temp, 1, strlen(temp), STORAGE.file2);
						getcard(number, cards[iter_card], types[iter_type]);
						fwrite("\n", 1, 2, STORAGE.file2);
						break;
					}else if(number == 3 && member3 != 52/members){
						member3++;
						strncpy(temp, cards[iter_card], sizeof(cards[iter_card]));
						fwrite(temp, 1, strlen(temp), STORAGE.file3);
						strncpy(temp, types[iter_type], sizeof(types[iter_type]));
						fwrite("\t", 1, 2, STORAGE.file3);
						fwrite(temp, 1, strlen(temp), STORAGE.file3);
						getcard(number, cards[iter_card], types[iter_type]);
						fwrite("\n", 1, 2, STORAGE.file3);
						break;
					}else if(number == 4 && member4 != 52/members){
						member4++;
						strncpy(temp, cards[iter_card], sizeof(cards[iter_card]));
						fwrite(temp, 1, strlen(temp), STORAGE.file4);
						strncpy(temp, types[iter_type], sizeof(types[iter_type]));
						fwrite("\t", 1, 2, STORAGE.file4);
						fwrite(temp, 1, strlen(temp), STORAGE.file4);
						getcard(number, cards[iter_card], types[iter_type]);
						fwrite("\n", 1, 2, STORAGE.file4);
						break;
					}else if((member1 + member2 + member3 + member4) == 52){
						break;
					}
				}else{
					if(iter_card == chosencardseq && iter_type == chosentypeseq){
						break;
					}else if(number == 1 && member1 != 52/members){
						member1++;
						strncpy(temp, cards[iter_card], sizeof(cards[iter_card]));
						fwrite(temp, 1, strlen(temp), STORAGE.file1);
						strncpy(temp, types[iter_type], sizeof(types[iter_type]));
						fwrite("\t", 1, 2, STORAGE.file1);
						fwrite(temp, 1, strlen(temp), STORAGE.file1);
						getcard(number, cards[iter_card], types[iter_type]);
						fwrite("\n", 1, 2, STORAGE.file1);
						break;
					}else if(number == 2 && member2 != 52/members){
						member2++;
						strncpy(temp, cards[iter_card], sizeof(cards[iter_card]));
						fwrite(temp, 1, strlen(temp), STORAGE.file2);
						strncpy(temp, types[iter_type], sizeof(types[iter_type]));
						fwrite("\t", 1, 2, STORAGE.file2);
						fwrite(temp, 1, strlen(temp), STORAGE.file2);
						getcard(number, cards[iter_card], types[iter_type]);
						fwrite("\n", 1, 2, STORAGE.file2);
						break;
					}else if(number == 3 && member3 != 52/members){
						member3++;
						strncpy(temp, cards[iter_card], sizeof(cards[iter_card]));
						fwrite(temp, 1, strlen(temp), STORAGE.file3);
						strncpy(temp, types[iter_type], sizeof(types[iter_type]));
						fwrite("\t", 1, 2, STORAGE.file3);
						fwrite(temp, 1, strlen(temp), STORAGE.file3);
						getcard(number, cards[iter_card], types[iter_type]);
						fwrite("\n", 1, 2, STORAGE.file3);
						break;
					}else if((member1 + member2 + member3) == 51){
						break;
					}
				}
			}
		}
	}


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

ps(){
	printf("====================\n");
	printf(BLU "S : Spade\n"RESET);
	printf(BLU "H : Heart\n"RESET);
	printf(BLU "D : Diamond\n"RESET);
	printf(BLU "C : clubs\n"RESET);
	printf("====================\n\n");
}

int main(int argc, char *argv[]){
	struct sockaddr_in server;  
  	int sock;  
  	char buf[6];

	//int exit_status = system("gnome-terminal");			// This can open a new terminal window.

	const char *cards[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
	const char *types[] = {"S", "H", "D", "C"};

	storage();												// Open a file to store card set

	if(argc != 2){
		printf(RED"Usage : ./deal <user numbers>\n"RESET);
		exit(-1);
	}

	const int members = atoi(argv[1]);

	if(members == 4){
		delegation(members, cards, types);

	}else if(members == 3){
		int number = throw(13);
		char temp[4];
		sleep(1);
		chosencardseq = number;
		number = throw(3);
		chosentypeseq = number;
		sleep(1);
		printf("\n+--------------------+\n");
		printf("| ");
		printf(GRN"Type %c             "RESET, *types[chosentypeseq]);
		printf("|\n");
		printf("| ");
		printf(BLU "Card %2s            "RESET, cards[chosencardseq]);
		printf("|\n");
		printf("+--------------------+\n\n");
		strncpy(temp, cards[chosencardseq], sizeof(cards[chosencardseq]));
		fwrite(temp, 1, strlen(temp), STORAGE.file4);
		strncpy(temp, types[chosentypeseq], sizeof(types[chosentypeseq]));
		fwrite("\t", 1, 2, STORAGE.file4);
		fwrite(temp, 1, strlen(temp), STORAGE.file4);
		delegation(members, cards, types);

	}else{
		printf(RED"Invalid user number. Should be 3 or 4 members.\n"RESET);
		exit(-1);
	}

	ps();

	fclose(STORAGE.file1);
	fclose(STORAGE.file2);
	fclose(STORAGE.file3);
	fclose(STORAGE.file4);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;  
  	server.sin_port = htons(SERVERPORT);
  	inet_pton(AF_INET, SERVERIP, &server.sin_addr.s_addr);
  	if(connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0 ){
	    printf("connect failed\n");
	    exit(-1);
	}else{
		printf("connect success\n");
	    char message[6] = "end";
	    if(send(sock, message, strlen(message), 0) < 0 ){
	      	printf("send error\n");
	    }
	}

	printf(GRN"Done!\n"RESET);
	sleep(3);

	close(sock);

	return 0;
}