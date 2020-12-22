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
};//���� ����ü
node_ptr ptr, head;
struct player_type {
	int id;
	char name;
	int balance;
	int direction;
	node_ptr node_pos;
}player[2];//player ����ü �迭�� ����


void append_city(node_ptr node);//��ȯ���Ḯ��Ʈ ����
void show_info();//�������
void move_player(int i, int j, int n);//player �̵�
void show_action_menu(int i, int j);//���� ���
int turn1 = 0;//player[0]�� ��ȯ Ƚ��
int turn2 = 0;//player[1]�� ��ȯ Ƚ��
int turn = 0;// show_action_menu �� ��ȯ Ƚ��

void main() {

	node_ptr temp;
	head = (node_ptr)malloc(sizeof(struct node_type));
	temp = (node_ptr)malloc(sizeof(struct node_type));//���� ���� ������ ���� node_ptr
	head->id = 0;
	strcpy(head->name, "Home");
	head->llink = temp;
	head->owner = -1;
	head->price = 0;
	head->rlink = temp;

	ptr = head;//append_city ��� ������ ���� node_ptr

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

	free(temp);//temp ��ȯ

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

	srand((unsigned int)time(0));// ������ ���� �߻� �Լ�
	show_info();
	while (1) {
		int ans, dice;
		do {
			printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
			printf("1. Throw Dice\n2. Show City Info\n3. exit\n\n");
			printf("player [0], choose a menu : ");
			scanf_s("%d", &ans);//�޴� ����

			if (ans == 1) {
				dice = (rand() % 4) + 1;//���� �߻�

				printf("\n[Your Dice : %d]\n", dice);

				if (dice == 1 && player[0].direction == 1) {
					player[0].direction = 0;
					printf("\n[Your direction is RIGHT!]\n");
				}//���� ����ȯ
				else if (dice == 1) {
					player[0].direction = 1;
					printf("\n[Your direction is BACK!]\n");
				}//���� ��ȯ

				move_player(0, 1, dice);
				printf("\nplayer [0] moved to (%s)\n\n", player[0].node_pos->name);
				show_action_menu(0, 1);
				show_info();
				turn1 += turn;// player[0]�� �̵� �� ��ȯȽ��
				turn = 0;
			}
			else if (ans == 2) show_info();
			else if (ans == 3) break;
		} while (ans == 2);//player[0] ����

		if (ans == 3)break;
		if (player[0].balance <= 0) break;//player[0]�� �ܰ� ���� �� ���� ����

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
		} while (ans == 2);//player[1]�� ����

		if (ans == 3)break;
		if (player[1].balance <= 0) break;//player[1]�� �ܰ� ���� �� ���� ����

		if (turn1 == 3 || turn2 == 3) break;//��ȯ Ƚ�� �ִ�ġ(3ȸ)���� �� ���� ����

	}

	temp = head;//�� �ڻ� �ջ��� ����
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
	city = (node_ptr)malloc(sizeof(struct node_type));//������ ���� �޸� �Ҵ�
	strcpy(city->name, node->name);
	city->id = node->id;
	city->owner = -1;
	city->price = node->price;
	city->llink = ptr;
	ptr->rlink = city;//�ٷ� ���� ���� ����
	city->rlink = head;
	head->llink = city;// ��� ���� ����
	ptr = ptr->rlink;//�ٷ� ���� ��� ����

}
void show_info() {
	node_ptr node;
	node = head;
	printf("N0.\tCity\t(Owner)\tPrice\tUser\n");
	printf("---------------------------------------------------\n");
	do {
		printf("%d\t%10s", node->id, node->name);//id, name���

		if (node->owner != -1) printf("(%d)\t%d", node->owner, node->price);
		else printf("(-)\t%d", node->price);//������ ���

		if (node == player[0].node_pos)printf("\t[0]");
		if (node == player[1].node_pos)printf("\t[1]");//player���� ��ġ ���
		printf("\n");

		node = node->rlink;
	} while (node != head);

	printf("\n");

	printf("Player[0] at [%s]\tbalance (%d)\n", player[0].node_pos->name, player[0].balance);
	printf("Player[1] at [%s]\tbalance (%d)\n\n", player[1].node_pos->name, player[1].balance);//�ܰ� ���
}

void move_player(int i, int j, int n) {
	for (;n > 0;n--) {
		if (player[i].direction == 0) player[i].node_pos = player[i].node_pos->rlink; //������ �̵���
		else if (player[i].direction == 1) player[i].node_pos = player[i].node_pos->llink;//������ �̵���

		if (n != 1 && player[i].node_pos == head) {
			printf("\n[You get Salary!]\n");
			player[i].balance += 200;
			turn++;
		}//home�� ���� ��� ���� ����
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
			}//���� ����

		}
		else printf("\n[Your balance is not enough to buy (%s).]\n\n", player[i].node_pos->name);//�ܰ����

	}//home�� �ƴϰ�, �����ְ� ���� ������ ���
	else if (player[i].node_pos->owner == player[i].id) {
		int ans;
		printf("1. Sell\n2, Pass\n");
		printf("Your choose : ");
		scanf_s("%d", &ans);

		if (ans == 1) {
			player[i].balance += player[i].node_pos->price * 0.6;
			player[i].node_pos->owner = -1;
			printf("\nYou sold %s, your balance is (%d).\n", player[i].node_pos->name, player[i].balance);
		}//�Ǹ�

	}//������ ������ �ٽ� ���� ���
	else if (player[i].node_pos->owner == player[j].id) {
		player[j].balance += player[i].node_pos->price*0.2;
		player[i].balance -= player[i].node_pos->price*0.2;
		printf("[You should pay %d , your balance is (%d)]\n", player[i].node_pos->price / 100 * 20, player[i].balance);//����


	}//������ ������ ���� ���
	else if (player[i].node_pos == head) {
		printf("\n[You received Salary(200)!]\n");
		player[i].balance += 200;
		turn++;//��ȯȽ�� ����
	}//home�� ����
}