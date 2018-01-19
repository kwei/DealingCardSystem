/****************************
*
*
*
*
*
*
*
*
*****************************/

/* include library */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* define color */
#define RESET "\x1B[0m"			// color white
#define GRN   "\x1B[32m"		// color green
#define BLU   "\x1B[34m"		// color blue
#define RED   "\x1B[31m"		// color red

#define NAME_SIZE 100
#define COLOR_SIZE 100
#define FEATURES_SIZE 100
#define NOTE_SIZE 100

/* define print out  */
//#define PRINTIBALE 1			// 1 for print out

#ifndef PRINTIBALE
#define PRINTIBALE 0			// 0 for no print out
#endif

/* define card node */
typedef struct cards{
	int id;
	int flag;						// check if chooesd
	int number;
	char color[COLOR_SIZE];
	char features[FEATURES_SIZE];
	char note[NOTE_SIZE];
	struct cards *next;
} Card;

/* final dealed node */
typedef struct node{
	char user[NAME_SIZE];
	Card *card;
	struct node *next;
} Node;

/* get a new card node */
void getCard(Card **card){
	*card = (Card*)malloc(sizeof(Card));
	if(*card == NULL){
		perror("card:\n");
		exit(-1);
	}
	(*card)->id = 0;
	(*card)->flag = 0;
	(*card)->number = 0;
	memset((*card)->color, 0, strlen((*card)->color));
	memset((*card)->features, 0, strlen((*card)->features));
	memset((*card)->note, 0, strlen((*card)->note));
	(*card)->next = NULL;
}

/* free the memory */
void freeCard(Card **card){
	Card *temp;
	while((*card) != NULL){
		temp = (*card);
		(*card) = (*card)->next;
		free(temp);
	}
	free(*card);
}

/* check the input */
void checkArg(int arg){
	if(arg != 3){
		printf(RED"Usage: ./dealcard <user number> <card number>\n"RESET);
		exit(-1);
	}
}

void checkRatio(int userNum, int cardNum){
	if(cardNum % userNum != 0){
		printf(RED"The card number can't be dealed fairly\n"RESET);
		exit(-1);
	}
}

/* get the card number */
void getArgu(Card **card, int cardNum){
	int i;
	Card *temp;
	getCard(card);
	temp = *card;
	for(i = 0 ; i < cardNum ; i++){
		Card *newCard;
		char content[FEATURES_SIZE], note[NOTE_SIZE], color[COLOR_SIZE];
		int number;
		getCard(&newCard);
		temp->next = newCard;

		printf("\nCard #%2d", i + 1);

		newCard->id = i + 1;

		printf(GRN"\n (key in card number)\n> "RESET);
		scanf("%d", &number);
		fflush(stdin);
		newCard->number = number;

		printf(GRN"\n (key in card color)\n> "RESET);
		scanf("%s", color);
		fflush(stdin);
		strcpy(newCard->color, color);

		printf(GRN"\n (key in card content)\n> "RESET);
		scanf("%s", content);
		fflush(stdin);
		strcpy(newCard->features, content);

		printf(GRN"\n (key in card note)\n> "RESET);
		scanf("%s", note);
		fflush(stdin);
		strcpy(newCard->note, note);

		temp->next = newCard;
		temp = newCard;

		if(PRINTIBALE){
			printf(BLU "< the info you set >\n card number = %2d,\n card color = %s,\n card content = %s,\n card note = %s\n"RESET, newCard->number, newCard->color, newCard->features, newCard->note);
		}
	}
}

void initUser(int userNum, char *user[]){
	int i;
	for(i = 0 ; i < userNum ; i++){
		user[i] = (char *)malloc(sizeof(char) * 100);
	}
}

void freeUser(int userNum, char *user[]){
	int i;
	for(i = 0 ; i < userNum ; i++){
		free(user[i]);
	}
}

/* get the number of users */
void getUser(int userNum, char *user[]){
	int i;
	for(i = 0 ; i < userNum ; i++){
		char *userName;
		printf("User #%2d's name is ?\n> ", i + 1);
		scanf("%s", userName);
		fflush(stdin);
		strcpy(user[i], userName);
	}
	if(PRINTIBALE){
		for(i = 0 ; i < userNum ; i++){
			printf(BLU "User #%2d is %s\n"RESET, i + 1, user[i]);
		}
	}
}

/* dealing cards in loop */
Node* loop(Card **card, int cardNum, char **user, int userNum){

	int ratio = cardNum / userNum, iterator, i, j, preCard = -1;
	printf("\n/Each person can get %2d cards /\n", ratio);
	Node *head, *temppacket;
	head = (Node*)malloc(sizeof(Node));
	temppacket = head;

	for(iterator = 0 ; iterator < userNum ; iterator++){
		Node *newpacket;
		Card *data;
		data = (Card*)malloc(sizeof(Card));
		newpacket = (Node*)malloc(sizeof(Node));
		newpacket->card = data;
		strcpy(newpacket->user, user[iterator]);
		int randCard, counter = 0;
		while(1){
			Card **temp;
			temp = &((*card)->next);
			Card *newdata;
			newdata = (Card*)malloc(sizeof(Card));
			srand(time(NULL));
			randCard = rand()%cardNum;
			for(j = 0 ; j < randCard ; j++){
				(*temp) = (*temp)->next;
			}
			if((*temp)->flag != 1){
				counter++;
				newdata = (*temp);
				(*temp)->flag = 1;
				data->next = newdata;
				data = newdata;
				printf("The random card's ID that user [ %s ] get is %d\n", newpacket->user, (*temp)->id);
			}
			if(counter == ratio){
				break;
			}
		}
		temppacket->next = newpacket;
		temppacket = newpacket;
	}
	return head;
}

void dump(Node *pkt){
	int count = 1;
	printf("\n==============================\n");
	printf(BLU "User [ %s ]\n\nRESET", pkt->user);
	while(pkt->card->next->next != NULL){
		printf("[ card %d ]\n", count);
		printf("card number  = %d\n", pkt->card->next->number);
		printf("card color   = %s\n", pkt->card->next->color);
		printf("card content = %s\n", pkt->card->next->features);
		printf("card note    = %s\n", pkt->card->next->note);
		printf("--------\n");
		pkt->card->next = pkt->card->next->next;
		count++;
	}
	printf("==============================\n");
}

void showResult(Node *pkt){
	Node *temp = pkt->next;
	while(temp != NULL){
		dump(temp);
		temp = temp->next;
	}
}

void freeNode(Node **node){
	Node *temp;
	while((*node) != NULL){
		temp = (*node);
		(*node) = (*node)->next;
		free(temp);
	}
	//free(*node);
}

/* main function */
/* Usage: ./dealcard <user number> <card number> */
int main(int argc, char *argv[]){

	Card *card;
	Node *result;
	getCard(&card);
	/*checkArg(argc);
	int userNum = atoi(argv[1]);
	int cardNum = atoi(argv[2]);*/
	int userNum = 2;
	int cardNum = 4;
	checkRatio(userNum, cardNum);
	if(PRINTIBALE){
		printf(BLU "user number is %2d, card number is %2d\n"RESET, userNum, cardNum);
	}
	char *user[userNum];

	*user = malloc(userNum * sizeof(char *));

	initUser(userNum, user);
	getUser(userNum, user);
	getArgu(&card, cardNum);

	result = loop(&card, cardNum, user, userNum);
	printf("[ loop done! ]\n");
	showResult(result);

	freeNode(&result);
	freeCard(&card);
	freeUser(userNum, user);
	free(*user);
	return 0;
}