#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <iostream>

#define p1(x) (((x)/9/3)*27+((x)%9/3)*3)

void sudokuDataGen(void);
void GameGUI(void);
void selectionPointer(int x, int y, int z);
void keyMainProcess(void);
//void saveFile(void);
void Reset(void);
void loadGame(void);
void inputMap(void);
void mainMenu(void);
void mainKeyEventLoop(void);
void Mainicon(int x, int y);
void GameSound(int ver);
void complete(void);

void pop(void);
int Hpanduan(int i, int s);
int Lpanduan(int j, int s);
int Npanduan(int i, int j, int s);

char menu_items[4][20] = { " ", "玩遊戲!!!  ", "離開遊戲  ", " " };
//char menu_items[6][20] = { " ", "玩遊戲!!!  ", "載入已儲存的遊戲  ", "匯入遊戲圖形檔  ", "離開遊戲  ", " " };
//char menu_details[6][30] = { " ", "開始進行隨機地圖遊戲", "讀取上一次的遊戲進度", "自檔案匯入地圖", "幹  ", " " };
char menu_details[4][30] = { " ", "開始進行隨機地圖遊戲", "幹  ", " " };

int menu_selection = 0;
int currentMode = 0;

int sudokuData[9][9];
int sudokuDataIO[9][9];
int sudokuAnswer[9][9];
int selectionRow = 0; //直列
int selectionCol = 0; //橫列
int keyData = 0;
bool soundOn = true;
bool oneTimeInit = false;

using namespace std;



//上72 下80 左75 右77

//===================


//===================


int main(void) {
	srand(time(NULL));

	system("title 數獨遊戲");
	mainMenu();

	while (currentMode != 4) {
		if (!oneTimeInit) {
			sudokuDataGen();
			oneTimeInit = true;
			//for (int i = 0; i < 9; i++) {
			//	for (int j = 0; j < 9; j++) {
			//		printf("%d ", sudokuAnswer[i][j]);
			//	}
			//	printf("\n");
			//}
			//system("pause");
			//system("cls");
		}
		if (currentMode == 0) {
			mainMenu();
		}
		else if (currentMode == 1) {
			GameGUI();
			complete();
		}
		keyMainProcess();
	}
	return 0;
}




void sudokuDataGen(void) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			sudokuData[i][j] = 0;

		}
	}
	pop();

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			sudokuDataIO[i][j] = 0;
			if (sudokuData[i][j] == 0)
				sudokuDataIO[i][j] = 1;
		}
	}

}


void mainMenu(void)
{
	system("cls");
	printf("%43s\n", "=========================================");
	printf("%43s\n", "    SSSS   U   U  DDD    OOO   K   K  U   U");
	printf("%43s\n", "   S       U   U  D  D  O   O  K K    U   U");
	printf("%43s\n", "    SSSS   U   U  D   D O   O  KKK    U   U");
	printf("%43s\n", "        S  U   U  D  D  O   O  K K    U   U");
	printf("%43s\n", "    SSSS    UUU   DDD    OOO   K  K    UUU ");
	printf("%43s\n\n\n\n\n", "=========================================");

	for (int c = 0; c < 6; c++) {
		Mainicon(menu_selection, c);
		printf("%30s", menu_items[c]);
		if (menu_selection + 1 == c)printf("◎");
		printf("\n");
	}
	printf("\n%30s %s\n", "說明:", menu_details[menu_selection + 1]);
}


void Mainicon(int x, int y) {
	char Main_icon_Play[6][15] = {
		{ "      |       " },
		{ "  ____|______ " },
		{ " |          | " },
		{ "|    ____    |" },
		{ "|   /    \\   |" },
		{ " \\_/      \\_/ " }
	};
	char Main_icon_Load[6][15] = {
		{ "  ___________ " },
		{ " /  |____|   |" },
		{ "/  ________  |" },
		{ "| | ------ | |" },
		{ "| | ______ | |" },
		{ "|____________|" }
	};
	char Main_icon_Input[6][15] = {
		{ "  ________    " },
		{ " /  ____  \\  " },
		{ "/__/  _|___|_ " },
		{ "      \\     / " },
		{ "       \\   /  " },
		{ "        \\ /  " }
	};

	char Main_icon_Exit[6][15] = {
		{ "     _    _  " },
		{ "    |_|  |_| " },
		{ "     _____    " },
		{ "    /      \\  " },
		{ "   |        | " },
		{ "              " }
	};

	switch (x) {
	case 0:
		for (int i = 0; i < 14; i++) {
			printf("%c", Main_icon_Play[y][i]);
		};
		break;
	case 1:
		for (int i = 0; i < 14; i++) {
			printf("%c", Main_icon_Exit[y][i]);
			//printf("%c", Main_icon_Load[y][i]);
		};
		break;
	case 2:
		for (int i = 0; i < 14; i++) {
			printf("%c", Main_icon_Input[y][i]);
		};
		break;
	case 3:
		for (int i = 0; i < 14; i++) {
			printf("%c", Main_icon_Exit[y][i]);
		};
		break;
	}



}


void GameGUI(void) {
	system("cls");
	for (int i = 0; i < 9; i++) {
		if (i == 0 || i == 3 || i == 6)printf(" == == == == == == == == == == == == ==\n");
		else printf("\n");
		for (int j = 0; j < 9; j++) {
			if (selectionCol == i && selectionRow == j) {
				if (j != 0 && j != 3 && j != 6) {
					printf("  ");
				}
				else {
					printf("∥ ");
				}
				selectionPointer(i, j, 0); //目前選擇的游標
				printf(" ");
			}
			else {
				if (sudokuDataIO[i][j] == 0) {
					if (j != 0 && j != 3 && j != 6) {
						printf("  ");
					}
					else { 
						printf("∥ ");
					}
					selectionPointer(i, j, 1); //題目格
					printf(" ");
				}

				else {
					if (sudokuData[i][j] == 0) {
						if (j != 0 && j != 3 && j != 6) {
							printf("    ");
						}
						else
							printf("∥   ");

					}
					else {
						if (j != 0 && j != 3 && j != 6) {
							printf("  %d ", sudokuData[i][j]);
						}
						else
							printf("∥ %d ", sudokuData[i][j]);

					}
				}

			}
			if (j == 8)printf("║ ");
		}
		if (i == 8)printf("\n== == == == == == == == == == == == ==");
		printf("\n");
	}
	if (sudokuDataIO[selectionCol][selectionRow] == 1)
		printf("\n%s", "描述：答案格，數字鍵編輯此格", sudokuData[selectionCol][selectionRow]);
	else
		printf("\n%s", "描述：題目格，不可變更", sudokuData[selectionCol][selectionRow]);
	//printf("\n\n\n\n\n\n\n%s", "控制: Ctrl-E 回到主選單 | 重新開始 Ctrl-R | 儲存檔案 Ctrl-S  \n移動 ↑↓←→ | 輸入答案 Num0-9");
	printf("\n\n\n\n\n\n\n%s", "控制: Ctrl-E 回到主選單 | 重新開始 Ctrl-R | \n移動 ↑↓←→ | 輸入答案 Num0-9");
}


void keyMainProcess(void) {
	keyData = _getch();
	if (currentMode == 0) {
		//if (keyData == 72) menu_selection -= 1; else if (keyData == 80) menu_selection += 1;
		//if (menu_selection  < 0)menu_selection = 3;
		//if (menu_selection > 3)menu_selection = 0;

		if (keyData == 72) menu_selection -= 1; else if (keyData == 80) menu_selection += 1;
		if (menu_selection  < 0)menu_selection = 1;
		if (menu_selection > 1)menu_selection = 0;
		if (keyData == 13) {
			if (menu_selection == 0) {
				currentMode = 1;
				GameSound(4);
			}
			if (menu_selection == 3)
				currentMode = 4;
		}
	}


	else if (currentMode == 1) {
		if (keyData == 72 || keyData == 75 || keyData == 77 || keyData == 80) {
			switch (keyData) {
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
			if (selectionRow > 8)selectionRow = 0;
			if (selectionCol > 8)selectionCol = 0;
			if (selectionRow < 0)selectionRow = 8;
			if (selectionCol < 0)selectionCol = 8;
		}
		else if (keyData >= 48 && keyData <= 57) {
			if (sudokuDataIO[selectionCol][selectionRow] == 1) {
				sudokuData[selectionCol][selectionRow] = keyData - 48;
				GameSound(4);
			}
			else
				GameSound(1);

		}
		else if (keyData == 18)
			Reset();
		else if (keyData == 5) {
			currentMode = 0;
			oneTimeInit = false;
		}
		else if (keyData == 19) {
			//saveFile();
		}
		else
			GameSound(3);
	}


}



void selectionPointer(int x, int y, int z) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	if (z == 0)
		SetConsoleTextAttribute(h, BACKGROUND_BLUE | FOREGROUND_INTENSITY);
	if (z == 1)
		SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("%d", sudokuData[x][y]); //
	SetConsoleTextAttribute(h, wOldColorAttrs);
}

void Reset(void) {
	selectionRow = 0;
	selectionCol = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (sudokuDataIO[i][j] == 1)
				sudokuData[i][j] = 0;
		}
	}
	GameGUI();
}

//void saveFile(void) {
//	FILE *SavePath;
//	SavePath = fopen("C:\\Users\\Public\\Documents\\Sudoku_save.dat", "w");
//	fprintf(SavePath, "[Sudoku Game File]");
//	fprintf(SavePath, "\n%d", time(0));
//	for (int i = 0; i < 9; i++) {
//		for (int j = 0; j < 9; j++) {
//			fprintf(SavePath, "%d", sudokuData[i][j]);
//		}
//		fprintf(SavePath, "\n");
//	}
//	for (int i = 0; i < 9; i++) {
//		for (int j = 0; j < 9; j++) {
//			fprintf(SavePath, "%d", sudokuDataIO[i][j]);
//		}
//		fprintf(SavePath, "\n");
//	}
//	fclose(SavePath);
//	system("cls");
//	printf("File has been successful save to C:\\Users\\Public\\Documents\\ \n");
//	printf("   __             ____    ____  ____     __    __  \n ");
//	printf("/      |    |   /       /      |      /     /      \n");
//	printf(" \\ __   |    |   |       |      |___   \\ __  \\ __   \n");
//	printf("     \\  |    |   |       |      |          \\     \\  \n");
//	printf("  ___/   \\___/   \\____   \\____  |____   ___/  ___/  \n\n\n\n\n");
//
//
//	system("pause");
//	GameGUI();
//}

void GameSound(int ver) {
	if (soundOn) {
		switch (ver) {
		case 1:
			Beep(100, 10);
			break;
		case 2:
			Beep(500, 10);
			break;
		case 3:
			Beep(4000, 10);
			break;
		case 4:
			Beep(500, 10);
			Beep(1000, 10);
			break;
		}
	}
}




void complete(void) {
	int counter=0,status=0;
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			counter += sudokuData[i][j];
		}
		if (counter == 45)status++;
		counter = 0;
	}
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			counter += sudokuData[j][i];
		}
		if (counter == 45)status++;
		counter = 0;
	}
	printf("(%d,%d)", counter, status);
if (status >= 18) {
	system("cls");
	printf("   __             ____    ____  ____     __    __  \n ");
	printf("/      |    |   /       /      |      /     /      \n");
	printf(" \\ __   |    |   |       |      |___   \\ __  \\ __   \n");
	printf("     \\  |    |   |       |      |          \\     \\  \n");
	printf("  ___/   \\___/   \\____   \\____  |____   ___/  ___/  \n\n\n\n\n");
	system("pause");
	system("pause");
	currentMode = 0;
	oneTimeInit = false;
	mainMenu();
}


}
int Hpanduan(int i, int s)
{
	int cont = 0, t;
	for (t = 0; t < 9; t++)
	if (s == sudokuData[i][t]) cont++;
	return cont;
}
int Lpanduan(int j, int s)
{
	int cont = 0, t;
	for (t = 0; t < 9; t++)
	if (s == sudokuData[t][j]) cont++;
	return cont;
}

int Npanduan(int i, int j, int s)
{
	int a, b, cont = 0, t, q;
	a = p1(i * 9 + j) / 9;
	b = p1(i * 9 + j) % 9;
	for (t = a; t < 3 + a; t++)
	for (q = b; q < 3 + b; q++)
	if (s == sudokuData[t][q]) cont++;
	return cont;
}

void pop(void)
{
	void guding(int i, int j);
	int i, t, j, H[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, L[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, s;
	srand(time(NULL));
	for (t = 1; t < 33; t++)
	{
		i = rand() % 9;
		j = rand() % 9;
		s = rand() % 9 + 1;
		if ((Hpanduan(i, s) < 1 && Lpanduan(j, s) < 1 && Npanduan(i, j, s) < 1))
		{
			if (sudokuData[i][j] == 0)
			{
				H[i]++; L[j]++;
				if (H[i] < 4 && L[j] < 4)
				{
					sudokuData[i][j] = s;
				}
			}
			else t--;
		}
	}
}
