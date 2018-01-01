#include<stdio.h>
#include<stdlib.h>
void loadGame(void);
void inputMap(void);
void ByeBye(void);
void mainMenu(void);
void mainKeyEventLoop(void);
void Mainicon(int x, int y);    
char menu_items[6][20] = {" ", "玩遊戲!!!  ", "載入已儲存的遊戲  ", "匯入遊戲圖形檔  ", "離開遊戲  " ," "};
char menu_details[6][30] = { " ", "開始進行隨機地圖遊戲", "讀取上一次的遊戲進度", "自檔案匯入地圖", "幹  ", " " };
int menu_selection = 0;

int main(void)
{
	mainKeyEventLoop();
	printf("功能建造中......");
	system("pause");
	return 0;
}

void mainKeyEventLoop(void){
	int keyin = 0, keytmp = 0;;
	while (!(keyin == 13)){
		keyin = 0;
		system("cls");
		mainMenu();
		while (!(keyin == 72 || keyin == 80)){
			keyin = getch();
			if (keyin == 13)break;
		}
		if (keyin == 72) menu_selection -= 1; else menu_selection += 1;
		if (menu_selection  < 0)menu_selection = 3;
		if (menu_selection > 3)menu_selection = 0;
	}
}

void mainMenu(void)
{
	printf("%43s\n","=========================================");
	printf("%43s\n","    SSSS   U   U  DDD    OOO   K   K  U   U");
	printf("%43s\n","   S       U   U  D  D  O   O  K K    U   U");
	printf("%43s\n","    SSSS   U   U  D   D O   O  KKK    U   U");
	printf("%43s\n","        S  U   U  D  D  O   O  K K    U   U");
	printf("%43s\n","    SSSS    UUU   DDD    OOO   K  K    UUU ");
	printf("%43s\n\n\n\n\n","=========================================");
	
	for (int c = 0; c < 6; c++){
		Mainicon(menu_selection, c);
		printf("%30s", menu_items[c]);
		if(menu_selection+1==c)printf("◎");
		printf("\n");

	}
	
	printf("\n%30s %s\n", "說明:", menu_details[menu_selection + 1]);
}


void Mainicon(int x,int y){
	char Main_icon_Play[6][14] = {
		{ "      |       " },
		{ "  ____|______ " },
		{ " |          | " },
		{ "|    ____    |" },
		{ "|   /    \\   |" },   
		{ " \\_/      \\_/ " } }; 
	char Main_icon_Load[6][14] = {
		{ "  ___________ " },
		{ " /  |____|   |" },
		{ "/  ________  |" },
		{ "| | ------ | |" },
		{ "| | ______ | |" },
		{ "|____________|" } };
	char Main_icon_Input[6][14] = {
		{ "  ________    " },
		{ " /  ____  \\  " },
		{ "/__/  _|___|_ " },
		{ "      \\     / " },
		{ "       \\   /  " },
		{ "        \\ /  "} };

	char Main_icon_Exit[6][14] = {
		{ "     _    _  " },
		{ "    |_|  |_| " },
		{ "     _____    " },
		{ "    /      \\  " },
		{ "   |        | " },
		{ "              " } };

	switch (x){
	case 0:
		for (int i = 0; i < 14; i++){ printf("%c", Main_icon_Play[y][i]); };
		break;
	case 1:
		for (int i = 0; i < 14; i++){ printf("%c", Main_icon_Load[y][i]); };
		break;
	case 2:
		for (int i = 0; i < 14; i++){ printf("%c", Main_icon_Input[y][i]); };
		break;
	case 3:
		for (int i = 0; i < 14; i++){ printf("%c", Main_icon_Exit[y][i]); };
		break;
	}



}

