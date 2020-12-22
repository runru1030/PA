#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct node_type * node_ptr;
struct node_type {
	int id;
	char name[20];
	int price;
	int owner;
	node_ptr llink;
	node_ptr rlink;
};//도시 구조체
node_ptr ptr, head;
struct player_type {
	int id;
	char name;
	int balance;
	int direction;
	node_ptr node_pos;
}player[2];//player 구조체 배열로 선언


void append_city(node_ptr node);//순환연결리스트 연결
void show_info();//정보출력
void move_player(int i, int j, int n);//player 이동
void show_action_menu(int i, int j);//여러 기능
int turn1 = 0;//player[0]의 순환 횟수
int turn2 = 0;//player[1]의 순환 횟수
int turn = 0;// show_action_menu 속 순환 횟수

void main() {

	node_ptr temp;
	head = (node_ptr)malloc(sizeof(struct node_type));
	temp = (node_ptr)malloc(sizeof(struct node_type));//도시 정보 선언을 위한 node_ptr
	head->id = 0;
	strcpy(head->name, "Home");
	head->llink = temp;
	head->owner = -1;
	head->price = 0;
	head->rlink = temp;

	ptr = head;//append_city 노드 연결을 위한 node_ptr

	strcpy(temp->name, "Seoul");
	temp->id = 1;
	temp->price = 2000;
	append_city(temp);

	strcpy(temp->name, "Honkong");
	temp->id = 2;
	temp->price = 3500;
	append_city(temp);

	strcpy(temp->name, "Macao");
	temp->id = 3;
	temp->price = 2500;
	append_city(temp);

	strcpy(temp->name, "Osaka");
	temp->id = 4;
	temp->price = 1000;
	append_city(temp);

	strcpy(temp->name, "Beijing");
	temp->id = 5;
	temp->price = 1300;
	append_city(temp);

	strcpy(temp->name, "Paris");
	temp->id = 6;
	temp->price = 2300;
	append_city(temp);

	strcpy(temp->name, "London");
	temp->id = 7;
	temp->price = 2700;
	append_city(temp);

	strcpy(temp->name, "NewYork");
	temp->id = 8;
	temp->price = 2100;
	append_city(temp);

	strcpy(temp->name, "Bangkok");
	temp->id = 9;
	temp->price = 1200;
	append_city(temp);

	strcpy(temp->name, "Singapore");
	temp->id = 10;
	temp->price = 1800;
	append_city(temp);

	free(temp);//temp 반환

	player[0].balance = 4000;
	player[0].id = 0;
	player[0].name = 'A';
	player[0].direction = 0;
	player[0].node_pos = head;

	player[1].balance = 4000;
	player[1].id = 1;
	player[1].name = 'B';
	player[1].direction = 0;
	player[1].node_pos = head;

	srand((unsigned int)time(0));// 무작위 난수 발생 함수
	show_info();
	while (1) {
		int ans, dice;
		do {
			printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
			printf("1. Throw Dice\n2. Show City Info\n3. exit\n\n");
			printf("player [0], choose a menu : ");
			scanf_s("%d", &ans);//메뉴 선택

			if (ans == 1) {
				dice = (rand() % 4) + 1;//난수 발생

				printf("\n[Your Dice : %d]\n", dice);

				if (dice == 1 && player[0].direction == 1) {
					player[0].direction = 0;
					printf("\n[Your direction is RIGHT!]\n");
				}//방향 재전환
				else if (dice == 1) {
					player[0].direction = 1;
					printf("\n[Your direction is BACK!]\n");
				}//방향 전환

				move_player(0, 1, dice);
				printf("\nplayer [0] moved to (%s)\n\n", player[0].node_pos->name);
				show_action_menu(0, 1);
				show_info();
				turn1 += turn;// player[0]의 이동 후 순환횟수
				turn = 0;
			}
			else if (ans == 2) show_info();
			else if (ans == 3) break;
		} while (ans == 2);//player[0] 차례

		if (ans == 3)break;
		if (player[0].balance <= 0) break;//player[0]의 잔고 부족 시 게임 종료

		do {

			printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
			printf("1. Throw Dice\n2. Show City Info\n3. exit\n\n");
			printf("player [1], choose a menu : ");
			scanf_s("%d", &ans);

			if (ans == 1) {
				dice = (rand() % 4) + 1;
				printf("\n[Your Dice : %d]\n", dice);
				if (dice == 1 && player[1].direction == 1) {
					player[1].direction = 0;
					printf("\n[Your direction is RIGHT!]\n");
				}
				else if (dice == 1) {
					player[1].direction = 1;
					printf("\n[Your direction is BACK!]\n");
				}

				move_player(1, 0, dice);
				printf("\nplayer [1]  moved to (%s)\n\n", player[1].node_pos->name);
				show_action_menu(1, 0);
				show_info();
				turn2 += turn;
				turn = 0;
			}
			else if (ans == 2) show_info();
			else if (ans == 3) break;
		} while (ans == 2);//player[1]의 차례

		if (ans == 3)break;
		if (player[1].balance <= 0) break;//player[1]의 잔고 부족 시 게임 종료

		if (turn1 == 3 || turn2 == 3) break;//순환 횟수 최대치(3회)도달 시 게임 종료

	}

	temp = head;//총 자산 합산을 위한
	do {
		if (temp->owner == 0)player[0].balance += temp->price;
		else if (temp->owner == 1)player[1].balance += temp->price;
		temp = temp->rlink;
	} while (temp != head);

	if (player[0].balance > player[1].balance) {
		printf("\n=========================Game is over============================\n");
		printf("\nPlayer[0]'s assets : %d\n", player[0].balance);
		printf("\nPlayer[1]'s assets : %d\n", player[1].balance);
		printf("\n*****************Player[0] is Win!!******************\n");
	}
	else if (player[0].balance < player[1].balance) {
		printf("\n=========================Game is over============================\n");
		printf("\nPlayer[0]'s assets : %d\n", player[0].balance);
		printf("\nPlayer[1]'s assets: %d\n", player[1].balance);
		printf("\n*****************Player[1] is Win!!******************\n");
	}
	else {
		printf("\n=========================Game is over============================\n");
		printf("\nPlayer[0]'s assets : %d\n", player[0].balance);
		printf("\nPlayer[1]'s assets : %d\n", player[1].balance);
		printf("\n*****************Player's assets are SAME!*****************\n");
	}
	system("pause");
}
void append_city(node_ptr node) {

	node_ptr city;
	city = (node_ptr)malloc(sizeof(struct node_type));//연결할 도시 메모리 할당
	strcpy(city->name, node->name);
	city->id = node->id;
	city->owner = -1;
	city->price = node->price;
	city->llink = ptr;
	ptr->rlink = city;//바로 이전 노드와 연결
	city->rlink = head;
	head->llink = city;// 헤드 노드와 연결
	ptr = ptr->rlink;//바로 이전 노드 변경

}
void show_info() {
	node_ptr node;
	node = head;
	printf("N0.\tCity\t(Owner)\tPrice\tUser\n");
	printf("---------------------------------------------------\n");
	do {
		printf("%d\t%10s", node->id, node->name);//id, name출력

		if (node->owner != -1) printf("(%d)\t%d", node->owner, node->price);
		else printf("(-)\t%d", node->price);//소유주 출력

		if (node == player[0].node_pos)printf("\t[0]");
		if (node == player[1].node_pos)printf("\t[1]");//player들의 위치 출력
		printf("\n");

		node = node->rlink;
	} while (node != head);

	printf("\n");

	printf("Player[0] at [%s]\tbalance (%d)\n", player[0].node_pos->name, player[0].balance);
	printf("Player[1] at [%s]\tbalance (%d)\n\n", player[1].node_pos->name, player[1].balance);//잔고 출력
}

void move_player(int i, int j, int n) {
	for (;n > 0;n--) {
		if (player[i].direction == 0) player[i].node_pos = player[i].node_pos->rlink; //정방향 이동시
		else if (player[i].direction == 1) player[i].node_pos = player[i].node_pos->llink;//역방향 이동시

		if (n != 1 && player[i].node_pos == head) {
			printf("\n[You get Salary!]\n");
			player[i].balance += 200;
			turn++;
		}//home을 지날 경우 월급 지급
	}
}

void show_action_menu(int i, int j) {
	if (player[i].node_pos != head && player[i].node_pos->owner == -1) {
		if (player[i].balance >= player[i].node_pos->price) {
			int ans;
			printf("1. Buy\n2, Pass\n");
			printf("Your choose : ");
			scanf_s("%d", &ans);

			if (ans == 1) {
				player[i].node_pos->owner = player[i].id;
				player[i].balance -= player[i].node_pos->price;
				printf("\nYou baught %s, your balance is (%d).\n", player[i].node_pos->name, player[i].balance);
			}//지역 구매

		}
		else printf("\n[Your balance is not enough to buy (%s).]\n\n", player[i].node_pos->name);//잔고부족

	}//home이 아니고, 소유주가 없는 지역일 경우
	else if (player[i].node_pos->owner == player[i].id) {
		int ans;
		printf("1. Sell\n2, Pass\n");
		printf("Your choose : ");
		scanf_s("%d", &ans);

		if (ans == 1) {
			player[i].balance += player[i].node_pos->price * 0.6;
			player[i].node_pos->owner = -1;
			printf("\nYou sold %s, your balance is (%d).\n", player[i].node_pos->name, player[i].balance);
		}//판매

	}//본인의 지역에 다시 왔을 경우
	else if (player[i].node_pos->owner == player[j].id) {
		player[j].balance += player[i].node_pos->price*0.2;
		player[i].balance -= player[i].node_pos->price*0.2;
		printf("[You should pay %d , your balance is (%d)]\n", player[i].node_pos->price / 100 * 20, player[i].balance);//지불


	}//상대방의 지역에 왔을 경우
	else if (player[i].node_pos == head) {
		printf("\n[You received Salary(200)!]\n");
		player[i].balance += 200;
		turn++;//순환횟수 증가
	}//home에 도착
}