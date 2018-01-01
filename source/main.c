#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <iostream> 
void loadGame(void);
void inputMap(void);
void ByeBye(void);
void mainMenu(void);
void mainKeyEventLoop(void);
void Mainicon(int x, int y);    
char menu_items[6][20] = {" ", "玩遊戲!!!  ", "載入已儲存的遊戲  ", "匯入遊戲圖形檔  ", "離開遊戲  " ," "};
char menu_details[6][30] = { " ", "開始進行隨機地圖遊戲", "讀取上一次的遊戲進度", "自檔案匯入地圖", "幹  ", " " };
int menu_selection = 0;
void sudokuDataGen(void);
void sudokuDataScan(void);
void GameGUI(void);
void selectionPointer(int x,int y,int z);
void keyProcess(void);
void Reset(void); 

int sudokuData[9][9];
int sudokuDataIO[9][9];
int selectionRow=0; //直列 
int selectionCol=0; //橫列 
int keyData; 
using namespace std; 

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
	int main(void){
	system("title 數獨遊戲"); 
	sudokuDataGen();
	sudokuDataScan(); 
	GameGUI();
	while(1){	 
		keyProcess();
	}
	exit:; 
		system("pause");
	return 0;
} 

void sudokuDataGen(void){ 
		srand(time(NULL));
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			sudokuData[i][j]=(rand()%10);
		}
	}
}
void sudokuDataScan(void){ 
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(sudokuData[i][j]==0)
				sudokuDataIO[i][j]=1; 
		}
	}
}

void GameGUI(void){
	system("cls"); 
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				if(selectionCol==i && selectionRow==j){
			    	selectionPointer(i,j,0); //目前選擇的游標 
				}
				else{
				if(sudokuDataIO[i][j]==0){
					selectionPointer(i,j,1); //題目格 
				} 
				else 
				if(sudokuData[i][j]==0){
					printf("  "); 
				}
				else
					printf(" %d",sudokuData[i][j]); 
				 // 
				} 
		}
		printf("\n");
	}
	if(sudokuDataIO[selectionCol][selectionRow]==1)  
	printf("\n%s","描述：答案格，數字鍵編輯此格",sudokuData[selectionCol][selectionRow]) ;
	else 
	printf("\n%s","描述：題目格，不可變更",sudokuData[selectionCol][selectionRow]) ;
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n%s","控制: Ctrl-E 回到主選單 | 重新開始 Ctrl-R | 儲存檔案 Ctrl-S  \n移動 ↑↓←→ | 輸入答案 Num0-9");
}


void keyProcess(void){ 
		keyData=getch(); 
	   if(keyData==72 || keyData==75||keyData==77||keyData==80){ 
	  	   switch(keyData){
				case 72:
					selectionCol--; 
		 			break; 
		 		case 75: 
		 			selectionRow--; 
		 			break;
		 		case 77: 
		 			selectionRow++; 
		 			break;
				case 80: 
					selectionCol++; 
		 			break;
			 } 
			 if(selectionRow>8)selectionRow=0; 
			 if(selectionCol>8)selectionCol=0; 
		 	 if(selectionRow<0)selectionRow=8; 
		 	 if(selectionCol<0)selectionCol=8; 
	    	 GameGUI();
       }
    	else if(keyData>=48 && keyData<=57 ){
    		if(sudokuDataIO[selectionCol][selectionRow]==1){
			
       		sudokuData[selectionCol][selectionRow]=keyData-48;
	    	GameGUI();
	    	Beep(500,10);
	    }
	     Beep(1500,10);
	   }
	   else if(keyData==18)
	   	Reset(); 
		else if(keyData==5){ 
			printf("function is now developing");
		} 
		else if(keyData==19){ 
			printf("function is now developing");
		} 
	   else
	   	Beep(100,10);
    
	}
	    


void selectionPointer(int x,int y,int z){ 
	printf ( " ");
	HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	if(z==0) 
	SetConsoleTextAttribute ( h, BACKGROUND_BLUE | FOREGROUND_INTENSITY );
	if(z==1) 
	SetConsoleTextAttribute ( h, FOREGROUND_RED | FOREGROUND_INTENSITY );
	printf ( "%d" ,sudokuData[x][y]); //
	SetConsoleTextAttribute ( h, wOldColorAttrs);
}

void Reset(void){
	selectionRow=0; 
	selectionCol=0;   		 
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(sudokuDataIO[i][j]==1)
				sudokuData[i][j]=0; 
		}
	}
	GameGUI();
} 




