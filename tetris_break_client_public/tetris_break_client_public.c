#define _WINSOCKAPI_ 
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <process.h>
#include <Windows.h>
#include <assert.h>
#include <winsock2.h>
#include <ws2tcpip.h>



//서버관련
void draw_wait_borad();
void draw_listmap();
unsigned WINAPI RecvMsg(void* arg);//쓰레드 수신함수
HANDLE recvThread;
SOCKET serversock;
unsigned char nameMsg[256];
char Tmsg[256];
void SendMsg(char* msg, int len);
char seq[4][20];//이름보관
char clear[4][20];//이름보관 클리어
int seq_cnt[5][1] = { 0,0,0,0,0 };//점수보관
int usercnt = 0;
int nowuser = 1;
int nowcnt = 1;
int  GAMEOVER = 0;
int LIGHT = 0;
int clearcnt = 0;
int nextrnd = 0;
int THUNDER = 0;
int i = 0;
//끝
//UDP서버부분
HANDLE udpThread;
char msg[100];
char roomList[4][100] = { { '\0', },{ '\0', },{ '\0', },{ '\0', } };
unsigned WINAPI Udpsend(void);
#define BUFFER_SIZE 1024
char getKey();
int jcntKey = 0;
//끝
int ThunderStatus[4][7][13] = {
	{
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,4,3,1,5,3,1,6,3,1,7,3,1 },
		{ 1,0,0,1,0,0,1,0,0,1,0,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,2,2,1,0,0,1,0,0,1,0,0,1 },
		{ 1,2,2,1,0,0,1,0,0,1,0,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1 } },
		{ { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,4,3,1,5,3,1,6,3,1,7,3,1 },
		{ 1,0,0,1,0,0,1,0,0,1,0,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,0,1,2,2,1,0,0,1,0,0,1 },
		{ 1,0,0,1,2,2,1,0,0,1,0,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1 } },
		{ { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,4,3,1,5,3,1,6,3,1,7,3,1 },
		{ 1,0,0,1,0,0,1,0,0,1,0,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,0,1,0,0,1,2,2,1,0,0,1 },
		{ 1,0,0,1,0,0,1,2,2,1,0,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1 } },
		{ { 1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,4,3,1,5,3,1,6,3,1,7,3,1 },
		{ 1,0,0,1,0,0,1,0,0,1,0,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,0,1,0,0,1,0,0,1,2,2,1 },
		{ 1,0,0,1,0,0,1,0,0,1,2,2,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1 } }
};
#define LEFT 75 //좌로 이동    //키보드값들 
#define RIGHT 77 //우로 이동 
#define UP 72 //회전 
#define DOWN 80 //soft drop
#define SPACE 32 //hard drop
#define p 112 //일시정지 
#define P 80 //일시정지
#define ESC 27 //게임종료 

#define false 0
#define true 1

#define ACTIVE_BLOCK -2 // 게임판배열에 저장될 블록의 상태들 
#define CEILLING -1     // 블록이 이동할 수 있는 공간은 0 또는 음의 정수료 표현 
#define EMPTY 0         // 블록이 이동할 수 없는 공간은 양수로 표현 
#define WALL 1
#define INACTIVE_BLOCK 2 // 이동이 완료된 블록값 

#define MAIN_X 15 //게임판 가로크기  테트리스 게임판 가로크기
#define MAIN_Y 28 //게임판 세로크기  테트리스 게임판 세로크기
#define MAIN_X_ADJ 1 //게임판 위치조정 
#define MAIN_Y_ADJ 1 //게임판 위치조정 
#define BACK_X 26
#define BACK_Y 26
#define NEXT_X 40
#define NEXT_Y 29
#define NEXT_X_ADJ 1
#define NEXT_Y_ADJ 1

#define COMBO_TYPE 5 // 콤보 1,2,3,4
#define COMBO_Y 5 // 콤보 그리는 배열 Y축
#define COMBO_X 24

#define STATUS_X_ADJ MAIN_X_ADJ+MAIN_X+1 //게임정보표시 위치조정 

#define FACE_TYPE 5 // 얼굴그리는 종류
#define FACE_Y 7 // 얼굴그리는 배열y축
#define FACE_X 17 // 얼굴그리는 배열x축
#define FACE_Y_ADJ 22 // 좌표에서 얼굴 찍기위한 Y값
#define FACE_X_ADJ STATUS_X_ADJ + 3 // 좌표에서 얼굴 찍기위한 X값
#define BOT_Y 14 // 바텀 세로축 
#define STATE_Y 32 // 위치 y값  
#define PRISON_TYPE 2 // 철창 타입
#define PRISON_Y 12 // 프리즌 Y값
char IP[100];
char ip_List[4][100] = { { '\0', },{ '\0', },{ '\0', },{ '\0', } };
char PORT[100];
char NAME[20] = "[DEFAULT]";

int TARGET_SCORE; //우리가 줄 수 정하는거임
int thunderType;
int STATUS_Y_GOAL; //GOAL 정보표시위치Y 좌표 저장 
int STATUS_Y_ROUND; //ROUND 정보표시위치Y 좌표 저장
int STATUS_Y_SCORE; //SCORE 정보표시위치Y 좌표 저장
int STATUS_Y_First;
int STATUS_Y_Second;
int STATUS_Y_Third;
int STATUS_Y_Fourth;


int blocks[7][4][4][4] = {
	{ { 0,0,0,0,
	0,1,1,0,
	0,1,1,0,
	0,0,0,0 },
	{ 0,0,0,0,
	0,1,1,0,
	0,1,1,0,
	0,0,0,0 },
	{ 0,0,0,0,
	0,1,1,0,
	0,1,1,0,
	0,0,0,0 },
	{ 0,0,0,0,
	0,1,1,0,
	0,1,1,0,
	0,0,0,0 } },    //  ㅁ

	{ { 0,0,0,0,
	0,0,0,0,
	1,1,1,1,
	0,0,0,0 },
	{ 0,1,0,0,
	0,1,0,0,
	0,1,0,0,
	0,1,0,0 },
	{ 0,0,0,0,
	0,0,0,0,
	1,1,1,1,
	0,0,0,0 },
	{ 0,1,0,0,
	0,1,0,0,
	0,1,0,0,
	0,1,0,0 } },  //  ㅣ

	{ { 0,0,0,0,
	1,1,0,0,
	0,1,1,0,
	0,0,0,0 },
	{ 0,0,0,0,
	0,0,1,0,
	0,1,1,0,
	0,1,0,0 },
	{ 0,0,0,0,
	1,1,0,0,
	0,1,1,0,
	0,0,0,0 },
	{ 0,0,0,0,
	0,0,1,0,
	0,1,1,0,
	0,1,0,0 } },  //  ㄱㄴ

	{ { 0,0,0,0,
	0,1,1,0,
	1,1,0,0,
	0,0,0,0 },
	{ 0,0,0,0,
	1,0,0,0,
	1,1,0,0,
	0,1,0,0 },
	{ 0,0,0,0,
	0,1,1,0,
	1,1,0,0,
	0,0,0,0 },
	{ 0,0,0,0,
	1,0,0,0,
	1,1,0,0,
	0,1,0,0 } }, // 역ㄱㄴ

	{ { 0,0,0,0,
	0,0,1,0,
	1,1,1,0,
	0,0,0,0 },
	{ 0,0,0,0,
	0,1,0,0,
	0,1,0,0,
	0,1,1,0 },
	{ 0,0,0,0,
	0,0,0,0,
	1,1,1,0,
	1,0,0,0 },
	{ 0,0,0,0,
	1,1,0,0,
	0,1,0,0,
	0,1,0,0 } }, // ㄱ

	{ { 0,0,0,0,
	1,0,0,0,
	1,1,1,0,
	0,0,0,0 },
	{ 0,0,0,0,
	0,1,1,0,
	0,1,0,0,
	0,1,0,0 } ,
	{ 0,0,0,0,
	0,0,0,0,
	1,1,1,0,
	0,0,1,0 },
	{ 0,0,0,0,
	0,1,0,0,
	0,1,0,0,
	1,1,0,0 } }, // ㄴ

	{ { 0,0,0,0,
	0,1,0,0,
	1,1,1,0,
	0,0,0,0 },
	{ 0,0,0,0,
	0,1,0,0,
	0,1,1,0,
	0,1,0,0 },
	{ 0,0,0,0,
	0,0,0,0,
	1,1,1,0,
	0,1,0,0 },
	{ 0,0,0,0,
	0,1,0,0,
	1,1,0,0,
	0,1,0,0 } } // ㅏ
}; //블록모양 저장 4*4공간에 블록을 표현 blcoks[b_type][b_rotation][i][j]로 사용 
void draw_thunderstatus(void);
int b_type; //블록 종류를 저장 
int b_rotation; //블록 회전값 저장 
int b_type_next; //다음 블록값 저장 
int b_type_before1; // 이전 움직이는 블록 색값 저장
					// 고정되는 블록색 저장하는데 사용되는 값

int FaceType;//면상 배열조정
int ComboType; //콤보 배열 조정
int PrisonType; // 감옥 배열조정

int main_org[MAIN_Y][MAIN_X]; //게임판의 정보를 저장하는 배열 모니터에 표시후에 main_cpy로 복사됨 
int main_cpy[MAIN_Y][MAIN_X]; //즉 maincpy는 게임판이 모니터에 표시되기 전의 정보를 가지고 있음 
							  //main의 전체를 계속 모니터에 표시하지 않고(이렇게 하면 모니터가 깜빡거림) 
							  //main_cpy와 배열을 비교해서 값이 달라진 곳만 모니터에 고침 
int back_org[BACK_Y][BACK_X];
int next_org[NEXT_Y][NEXT_X];
int bot_org[BOT_Y][NEXT_X];
int bots_org[BOT_Y][NEXT_X];
int prison_org[PRISON_TYPE][PRISON_Y - 1][COMBO_X - 1] =
{
	{ { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } },
	{
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,1,0,1,0,1,0,1,2,1,2,1,2,1,0,1,0,1,0,1,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,1,0,1,0,1,2,1,2,1,2,1,2,1,2,1,0,1,0,1,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,1,0,1,0,1,2,1,2,1,2,1,2,1,2,1,0,1,0,1,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,1,0,1,0,1,2,1,2,1,2,1,2,1,2,1,0,1,0,1,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,1,0,1,0,1,0,1,2,1,2,1,2,1,0,1,0,1,0,1,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } }
};
int Face[FACE_TYPE][FACE_Y][FACE_X] =
{ { { 0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0 },
{ 0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0 },
{ 0,0,0,0,0,1,0,2,0,0,0,2,0,1,0,0,0 },
{ 0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0 },
{ 0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0 },
{ 0,0,0,0,0,0,1,0,1,1,1,0,1,0,0,0,0 },
{ 0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0 } },// :D
{ { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1 },
{ 0,0,1,1,0,0,0,1,1,1,1,0,0,0,1,1,0 },
{ 0,1,1,0,0,0,1,0,0,0,0,1,0,1,1,0,0 },
{ 0,1,1,0,0,0,1,2,0,0,2,1,0,1,1,0,0 },
{ 0,0,1,1,0,0,1,4,3,3,4,1,0,0,1,1,0 },
{ 0,0,0,1,1,0,0,1,1,1,1,0,0,0,0,1,1 } },// (O(
{ { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0 },
{ 0,0,1,1,0,0,0,1,1,1,1,0,0,0,1,1,0 },
{ 0,0,1,1,0,0,1,0,0,0,0,1,0,0,1,1,0 },
{ 0,0,1,1,0,0,1,2,0,0,2,1,0,0,1,1,0 },
{ 0,0,1,1,0,0,1,4,3,3,4,1,0,0,1,1,0 },
{ 0,0,1,1,0,0,0,1,1,1,1,0,0,0,1,1,0 } },// IOI
{ { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0 },
{ 0,0,1,1,0,0,0,1,1,1,1,0,0,0,1,1,0 },
{ 0,0,0,1,1,0,1,0,0,0,0,1,0,0,0,1,1 },
{ 0,0,0,1,1,0,1,2,0,0,2,1,0,0,0,1,1 },
{ 0,0,1,1,0,0,1,4,3,3,4,1,0,0,1,1,0 },
{ 0,1,1,0,0,0,0,1,1,1,1,0,0,1,1,0,0 } },
{ { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 } }
// )0)
};


int Combo[COMBO_TYPE][COMBO_Y][COMBO_X] = {
	{ { 1,1,1,1,0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,0,0,0,1,1 },
	{ 1,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,1,1 },
	{ 1,0,1,1,0,1,1,1,0,1,1,0,0,1,0,1,1,0,1,1,1,0,1,1 },
	{ 1,0,0,1,0,1,0,1,0,0,0,0,0,1,0,0,1,0,1,0,1,0,0,0 },
	{ 1,1,1,1,0,1,1,1,0,1,1,0,0,1,1,1,1,0,1,1,1,0,1,1 } },

	{ { 1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,0,0,1 },
	{ 1,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,1,0 },
	{ 1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,0,0 },
	{ 1,0,0,1,0,1,0,1,0,0,1,0,0,0,0,1,0,0,1,0,1,0,1,0 },
	{ 1,1,1,1,0,1,0,0,1,0,1,1,1,1,0,1,0,0,1,0,1,0,0,1 } },

	{ { 1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0 },
	{ 0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0 },
	{ 1,1,1,0,1,0,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1 },
	{ 1,0,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1 },
	{ 1,1,1,0,1,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1 } },

	{ { 1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0 },
	{ 0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0 },
	{ 1,1,1,0,1,0,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1 },
	{ 0,0,1,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1 },
	{ 1,1,1,0,1,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1 } },

	{ { 1,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0 },
	{ 1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0 },
	{ 1,1,1,0,1,0,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1 },
	{ 0,0,1,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1 },
	{ 0,0,1,0,1,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1 } }
};


int bx, by; //이동중인 블록의 게임판상의 x,y좌표를 저장 

int key; //키보드로 입력받은 키값을 저장 

int speed; //게임진행속도 
int ROUND; //현재 ROUND 
int cnt; //현재 레벨에서 제거한 줄 수를 저장  + 부신 줄 수
int x = 1;
int combo;
int new_block_on = 0; //새로운 블럭이 필요함을 알리는 flag 
int crush_on = 0; //현재 이동중인 블록이 충돌상태인지 알려주는 flag 
int ROUND_up_on = 0; //다음레벨로 진행(현재 레벨목표가 완료되었음을) 알리는 flag 
int space_key_on = 0; //hard drop상태임을 알려주는 flag 
int statustype;
int score[4] = { 0,0,0,0 };

void ErrorHandling(char msg); // 에러 헨들링
void title(void); //게임시작화면 
void reset(void); //게임판 초기화 
void reset_main(void); //메인 게임판(main_org[][]를 초기화)
void draw_map(void); //게임 전체 인터페이스를 표시 
void draw_main(void); //게임판을 그림 
void new_block(void); //새로운 블록을 하나 만듦 
void check_key(void); //키보드로 키를 입력받음 
void drop_block(void); //블록을 아래로 떨어트림 
int check_crush(int bx, int by, int rotation); //bx, by위치에 rotation회전값을 같는 경우 충돌 판단 
void move_block(int dir); //dir방향으로 블록을 움직임 
void check_line(void); //줄이 가득찼는지를 판단하고 지움 
void check_ROUND_up(void); //레벨목표가 달성되었는지를 판단하고 levelup시킴 
void check_game_over(void); //게임오버인지 판단하고 게임오버를 진행 
void pause(void);//게임을 일시정지시킴 
void draw_combo(void); // 콤보 부분을 도형으로 바꿔줌
void draw_face(void);// 면상 그림
void Wait_board(void); // 리스트 기다리는거 출력
void draw_nextround(void);
void draw_bot_background(void); //밑에 틀 그리는거
void draw_state(void);
void draw_livestate(void);
void draw_bot_backimage(void);
void draw_cf(void);//콤보랑 얼굴 그리는거
void draw_prison(void);
void draw_ending(void);
void draw_storyboard(void);
void playlist(void);
void draw_realending(void);
void draw_thunder(void);
void draw_secondstory(void);
void draw_join_borad(void);
void ErrorHandling(char msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}

void color(int set_color) {     // 색넣는 함수
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), set_color);
}

void figurecolor(int set_color) {  // 도형 색 넣는 함수
	switch (set_color) {
	case 0:
		color(12); // 빨강
		break;
	case 1:
		color(9); // 파랑
		break;
	case 2:
		color(13); // 분홍
		break;
	case 3:
		color(10); // 초록
		break;
	case 4:
		color(14); // 노랑
		break;
	case 5:
		color(11); // 하늘
		break;
	case 6:
		color(8);  // 회색
		break;
	}
}

void gotoxy(int x, int y) { //gotoxy함수 
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE; //커서숨기는 함수에 사용되는 열거형 
void setcursortype(CURSOR_TYPE c) { //커서숨기는 함수 
	CONSOLE_CURSOR_INFO CurInfo;

	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}
void main_background(void) { //게임판을 초기화  
	int i, j;

	for (i = 1; i < BACK_Y - 1; i++) { //좌우 벽을 만듦  
		back_org[i][0] = WALL;
		back_org[i][BACK_X - 1] = WALL;
	}
	for (j = 0; j < BACK_X; j++) { //바닥벽을 만듦 
		back_org[BACK_Y - 1][j] = WALL;
	}
	for (i = 0; i < BACK_Y; i++) {
		for (j = 0; j < BACK_X; j++) {

			gotoxy(MAIN_X_ADJ + 1 + j, MAIN_Y_ADJ + i);
			switch (back_org[i][j]) {
			case WALL: //벽모양 
				printf("▩");
				break;

			}
		}
	}


}



int main() {
	//서버부분
	WSADATA wsaData, udpWsaData;;
	SOCKET sock, udpsenSock;
	SOCKADDR_IN serverAddr, udpsenAddr;
	HANDLE  recvThread, udpThread;
	char msg[100];
	memset(seq, NULL, sizeof(seq));
	//끝
	int i;

	srand((unsigned)time(NULL)); //난수표생성 
	setcursortype(NOCURSOR); //커서 없앰 
	system("mode con:cols=60 lines=29"); // 타이틀 화면 크기 지정
	title(); //메인타이틀 호출 

	system("mode con:cols=56 lines=25"); // IP, PORT 입력란 화면 크기 지정
	IP_input();
	udpThread = (HANDLE)_beginthreadex(NULL, 0, Udpsend, 0, 0, NULL);
	Sleep(2000);
	draw_listmap();
	//playlist();
	//서버부분
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)// 윈도우 소켓을 사용한다고 운영체제에 알림
		ErrorHandling("WSAStartup() error!");
	sock = socket(PF_INET, SOCK_STREAM, 0);//소켓을 하나 생성한다.
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(IP);
	serverAddr.sin_port = htons(atoi(PORT));
	serversock = sock;
	if (connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)//서버에 접속한다.
		ErrorHandling("connect() error");

	sprintf(msg, "%s:%s", NAME, "NAME");
	SendMsg(msg, *msg);
	recvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&sock, 0, NULL);//메시지 수신용 쓰레드가 실행된다.
																				  //끝

	system("mode con:cols=56 lines=25");
	Wait_board();
	draw_storyboard();
	system("mode con:cols=84 lines=45");

	color(7);
	reset(); //게임판 리셋 

	while (1) {

		draw_map();

		if (ROUND == 1) {
			draw_prison();
			draw_thunderstatus();

		}


		if (ROUND == 2) {
			draw_thunder();
		}


		for (i = 0; i < 5; i++) { //블록이 한칸떨어지는동안 5번 키입력받을 수 있음 
			check_key(); //키입력확인 
			draw_main(); //화면을 그림

			if (new_block_on == 1)
				new_block();

			if (space_key_on == 0) {
				Sleep(speed); //게임속도조절 이걸 if 문 밖에 뺏을시 스페이스바 눌러도 한칸 움직이는 버그가 생기니 절대!!! 만지지말자
				draw_cf();

			}
			else { //스페이스바를 누른경우(hard drop) 추가로 이동및 회전할수 없음 break; 
				space_key_on = 0;

				break;
			}

		}
		drop_block();

		check_ROUND_up(); // 레벨업을 체크 
		check_game_over(); //게임오버를 체크 
						   // 뉴 블럭 flag가 있는 경우 새로운 블럭 생성 
	}
}

void background_block(void) { //새로운 블록 생성 

	int i, j;
	for (i = 1; i < 3; i++) { //게임상태표시에 다음에 나올블럭을 그림 ㅡ자
		for (j = 0; j < 4; j++) {
			if (blocks[1][0][i][j] == 1) {
				color(10);
				gotoxy(3 + j, i + 23);
				printf("■");
			}
		}
	}
	for (i = 1; i < 3; i++) { //게임상태표시에 다음에 나올블럭을 그림 역 ㄴ
		for (j = 0; j < 4; j++) {
			if (blocks[4][0][i][j] == 1) {
				color(12);
				gotoxy(4 + j, i + 22);
				printf("■");
			}
		}
	}
	for (i = 1; i < 5; i++) { //게임상태표시에 다음에 나올블럭을 그림 역 ㄱ
		for (j = 0; j < 4; j++) {
			if (blocks[4][2][i][j] == 1) {
				color(15);
				gotoxy(3 + j, i + 21);
				printf("■");
			}
		}
	}
	for (i = 1; i < 5; i++) { //게임상태표시에 다음에 나올블럭을 그림 ㅗ
		for (j = 0; j < 4; j++) {
			if (blocks[6][0][i][j] == 1) {
				color(14);
				gotoxy(3 + j, i + 20);
				printf("■");
			}
		}
	}
	for (i = 1; i < 5; i++) { //게임상태표시에 다음에 나올블럭을 그림 ㅁ
		for (j = 0; j < 4; j++) {
			if (blocks[0][0][i][j] == 1) {
				color(9);
				gotoxy(6 + j, i + 23);
				printf("■");
			}
		}
	}
	for (i = 1; i < 5; i++) { //게임상태표시에 다음에 나올블럭을 그림 ㅗ
		for (j = 0; j < 4; j++) {
			if (blocks[6][0][i][j] == 1) {
				color(11);
				gotoxy(12 + j, i + 23);
				printf("■");
			}
		}
	}
	for (i = 1; i < 3; i++) { //게임상태표시에 다음에 나올블럭을 그림 ㅡ자
		for (j = 0; j < 4; j++) {
			if (blocks[1][0][i][j] == 1) {
				gotoxy(15 + j, i + 23);
				color(10);
				printf("■");
			}
		}
	}
	for (i = 1; i < 4; i++) { //게임상태표시에 다음에 나올블럭을 그림 ㅡ자
		for (j = 0; j < 4; j++) {
			if (blocks[1][1][i][j] == 1) {
				gotoxy(25 + j, i + 22);
				color(1);
				printf("■");
				gotoxy(25, 25); printf("■");
			}
		}
	}

}
void draw_join_borad() {
	int y = 1;
	gotoxy(6, y + 9); printf("%s", roomList[0]);


	gotoxy(6, y + 12); printf("%s", roomList[1]);


	gotoxy(6, y + 15); printf("%s", roomList[2]);


	gotoxy(6, y + 18); printf("%s", roomList[3]);
}
void draw_wait_borad() {
	int y = 1;
	gotoxy(10, y + 9); printf("%s", seq[0]);


	gotoxy(10, y + 12); printf("%s", seq[1]);


	gotoxy(10, y + 15); printf("%s", seq[2]);


	gotoxy(10, y + 18); printf("%s", seq[3]);
}
void Wait_board(void) {   // IP PORT입력하는 창

	int y = 1;
	int x = 15;
	int n = 10;
	char inputIp[100];
	char inputport[100];
	char inputName[100];
	system("mode con:cols=56 lines=25");
	color(7);


	gotoxy(3, y + 8); printf(" │    ");
	gotoxy(3, y + 9); printf(" │    ");
	gotoxy(3, y + 10); printf(" └─ ");
	gotoxy(3, y + 11); printf("  ┬  ");
	gotoxy(3, y + 12); printf("  │  ");
	gotoxy(3, y + 13); printf("  ┴  ");
	gotoxy(3, y + 14); printf(" ┌─  ");
	gotoxy(3, y + 15); printf(" └-┐ ");
	gotoxy(3, y + 16); printf("  ─┘ ");
	gotoxy(3, y + 17); printf(" -┬- ");
	gotoxy(3, y + 18); printf("  │  ");
	gotoxy(3, y + 19); printf("  │  ");
	gotoxy(3, y + 20); printf("      ");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 | (8 << 4));
	gotoxy(2, y); printf("■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(2, y + 1); printf("■");	gotoxy(2, y + 2); printf("■");	gotoxy(2, y + 3); printf("■");
	gotoxy(2, y + 4); printf("■");	gotoxy(2, y + 5); printf("■");
	gotoxy(2, y + 6); printf("■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(2, y + 7); printf("■");	gotoxy(2, y + 8); printf("■");	gotoxy(2, y + 9); printf("■");
	gotoxy(2, y + 10); printf("■"); gotoxy(2, y + 11); printf("■"); gotoxy(2, y + 12); printf("■");
	gotoxy(2, y + 13); printf("■"); gotoxy(2, y + 14); printf("■"); gotoxy(2, y + 15); printf("■");
	gotoxy(2, y + 16); printf("■"); gotoxy(2, y + 17); printf("■"); gotoxy(2, y + 18); printf("■");
	gotoxy(2, y + 19); printf("■"); gotoxy(2, y + 20); printf("■"); gotoxy(25, y + 1); printf("■");
	gotoxy(6, y + 7); printf("■"); gotoxy(6, y + 8); printf("■"); gotoxy(6, y + 9); printf("■");
	gotoxy(6, y + 10); printf("■"); gotoxy(6, y + 11); printf("■"); gotoxy(6, y + 12); printf("■");
	gotoxy(6, y + 13); printf("■"); gotoxy(6, y + 14); printf("■"); gotoxy(6, y + 15); printf("■");
	gotoxy(6, y + 16); printf("■"); gotoxy(6, y + 17); printf("■"); gotoxy(6, y + 18); printf("■");
	gotoxy(6, y + 19); printf("■"); gotoxy(6, y + 20); printf("■");
	gotoxy(25, y + 2); printf("■"); gotoxy(25, y + 3); printf("■"); gotoxy(25, y + 4); printf("■");
	gotoxy(25, y + 5); printf("■"); gotoxy(25, y + 6); printf("■"); gotoxy(25, y + 7); printf("■");
	gotoxy(25, y + 8); printf("■"); gotoxy(25, y + 9); printf("■"); gotoxy(25, y + 10); printf("■");
	gotoxy(25, y + 11); printf("■"); gotoxy(25, y + 12); printf("■"); gotoxy(25, y + 13); printf("■");
	gotoxy(25, y + 14); printf("■"); gotoxy(25, y + 15); printf("■"); gotoxy(25, y + 16); printf("■");
	gotoxy(25, y + 17); printf("■"); gotoxy(25, y + 18); printf("■"); gotoxy(25, y + 19); printf("■");
	gotoxy(25, y + 20); printf("■"); gotoxy(2, y + 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■");


	color(7);
	gotoxy(3, y + 1); printf("  ■  ■  ■    ■■■    ■■■    ■■■  ");
	gotoxy(3, y + 2); printf("  ■  ■  ■    ■  ■      ■        ■    ");
	gotoxy(3, y + 3); printf("  ■  ■  ■    ■■■      ■        ■    ");
	gotoxy(3, y + 4); printf("  ■  ■  ■    ■  ■      ■        ■    ");
	gotoxy(3, y + 5); printf("  ■■■■■    ■  ■    ■■■      ■    ");

	gotoxy(x, y + 8); printf("  △   : Shift");
	gotoxy(x, y + 10); printf("  ◁   : Left ");
	gotoxy(x, y + 12); printf("  ▷   : Right");
	gotoxy(x, y + 14); printf("  ▽   : Soft Drop");
	gotoxy(x, y + 16); printf("SPACE  : Hard Drop");
	gotoxy(x, y + 19); printf(" ESC   : Quit");
	gotoxy(8, y + 9); printf("●"); gotoxy(8, y + 12); printf("●"); gotoxy(8, y + 15); printf("●");
	gotoxy(8, y + 18); printf("●");
	//서버
	for (n = 50; n >= 0; n--) {
		draw_wait_borad();

		/*gotoxy(10, y + 9); printf("%s", seq[0]);


		gotoxy(10, y + 12); printf("%s", seq[1]);


		gotoxy(10, y + 15); printf("%s", seq[2]);


		gotoxy(10, y + 18); printf("%s", seq[3]);*/

		if (n % 5 == 0) {
			gotoxy(18, 23); printf("WAITING FOR...%2d", n / 5);
		}
		Sleep(200);
		if (nowuser < usercnt) { nowuser++; Wait_board(); break; }
		if (n == 0) break;

	}

	system("cls");
	//끝
}

int IP_input(void) {   // IP PORT입력하는 창

	int y = 1;
	char inputIp[100];
	char inputport[100];
	char inputName[100];
	system("mode con:cols=56 lines=23");
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 | (8 << 4));
	while (1) {

		gotoxy(3, y + 8); printf("■■■■■■■■■■■■■■■■■■■■■");
		gotoxy(3, y + 9); printf("■");
		gotoxy(3, y + 10); printf("■■■■■■■■■■■■■■■■■■■■■");
		gotoxy(3, y + 11); printf("■");
		gotoxy(3, y + 12); printf("■■■■■■■■■■■■■■■■■■■■■■");
		gotoxy(24, y + 8); printf("■");
		gotoxy(24, y + 9); printf("■");
		gotoxy(24, y + 10); printf("■");
		gotoxy(24, y + 11); printf("■");

		gotoxy(8, y + 9); printf("■");
		gotoxy(8, y + 11); printf("■");
		color(8);
		gotoxy(5, y + 9); printf("PORT");
		gotoxy(5, y + 11); printf("NAME");



		gotoxy(9, y + 9); gets(inputport);
		sprintf(PORT, "%s", inputport); //입력받아서 전역변수로 보내줌

		gotoxy(9, y + 11); gets(inputName);
		sprintf(NAME, "%s", inputName);

		break;
	}
	system("cls");

}

void title(void) {
	int x = 5; //타이틀화면이 표시되는 x좌표 
	int y = 4; //타이틀화면이 표시되는 y좌표 
	int cnt; //타이틀 프레임을 세는 변수  
	int c = 9;
	main_background();

	color(7);

	for (cnt = 0;; cnt++) { //cnt를 1씩 증가시키면서 계속 반복    //하나도 안중요한 별 반짝이는 애니메이션효과 
		int x = 5;
		int y = 7;
		if (cnt % 200 == 0) {
			for (int i = 1; i < BACK_Y; i++) {
				color(7);
				background_block();

				color(9);
				gotoxy(11, i); printf("■");
				gotoxy(10, i); printf("■");
				gotoxy(11, i - 2); printf(" ");
				gotoxy(10, i - 2); printf(" ");

				color(7);

				color(1 + (c + 11) % 15);
				gotoxy(4, 3); printf("■■■");
				gotoxy(5, 4);   printf("■");
				gotoxy(5, 5);   printf("■");
				gotoxy(5, 6);   printf("■");
				gotoxy(5, 7);   printf("■");

				color(1 + (c + 10) % 15);
				gotoxy(8, 3); printf("■■■");
				gotoxy(8, 4); printf("■");
				gotoxy(8, 5); printf("■■■");
				gotoxy(8, 6); printf("■");
				gotoxy(8, 7); printf("■■■");

				color(1 + (c + 9) % 15);
				gotoxy(12, 3); printf("■■■");
				gotoxy(13, 4);   printf("■");
				gotoxy(13, 5);   printf("■");
				gotoxy(13, 6);   printf("■");
				gotoxy(13, 7);   printf("■");

				color(1 + (c + 8) % 15);
				gotoxy(16, 3); printf("■■■");
				gotoxy(16, 4); printf("■  ■");
				gotoxy(16, 5); printf("■■■");
				gotoxy(16, 6); printf("■ ■");
				gotoxy(16, 7); printf("■  ■");

				color(1 + (c + 7) % 15);
				gotoxy(20, 3); printf("■■");
				gotoxy(20, 4); printf(" ■");
				gotoxy(20, 5); printf(" ■");
				gotoxy(20, 6); printf(" ■");
				gotoxy(20, 7); printf("■■");

				color(1 + (c + 6) % 15);
				gotoxy(23, 3); printf("■■■");
				gotoxy(23, 4); printf("■");
				gotoxy(23, 5); printf("■■■");
				gotoxy(25, 6);     printf("■");
				gotoxy(23, 7); printf("■■■");

				color(1 + (c + 5) % 15);
				gotoxy(x, y + 3); printf("■■■");
				gotoxy(x, y + 4); printf("■  ■");
				gotoxy(x, y + 5); printf("■■■");
				gotoxy(x, y + 6); printf("■  ■");
				gotoxy(x, y + 7); printf("■■■");

				color(1 + (c + 4) % 15);
				gotoxy(x + 4, y + 3); printf("■■■");
				gotoxy(x + 4, y + 4); printf("■  ■");
				gotoxy(x + 4, y + 5); printf("■■■");
				gotoxy(x + 4, y + 6); printf("■ ■");
				gotoxy(x + 4, y + 7); printf("■  ■");

				color(1 + (c + 3) % 15);
				gotoxy(x + 8, y + 3); printf("■■■");
				gotoxy(x + 8, y + 4); printf("■");
				gotoxy(x + 8, y + 5); printf("■■■");
				gotoxy(x + 8, y + 6); printf("■");
				gotoxy(x + 8, y + 7); printf("■■■");

				color(1 + (c + 2) % 15);
				gotoxy(x + 12, y + 3); printf("■■■");
				gotoxy(x + 12, y + 4);  printf("■  ■");
				gotoxy(x + 12, y + 5);  printf("■■■");
				gotoxy(x + 12, y + 6);  printf("■  ■");
				gotoxy(x + 12, y + 7);  printf("■  ■");

				color(1 + (c + 1) % 15);
				gotoxy(x + 16, y + 3); printf("■  ■");
				gotoxy(x + 16, y + 4); printf("■ ■");
				gotoxy(x + 16, y + 5); printf("■■");
				gotoxy(x + 16, y + 6);   printf("■ ■");
				gotoxy(x + 16, y + 7);   printf("■  ■");

				color(1 + c % 15);
				gotoxy(x + 20, y + 3); printf("■");
				gotoxy(x + 20, y + 4); printf("■");
				gotoxy(x + 20, y + 5); printf("■");
				gotoxy(x + 20, y + 7); printf("■");

				c++;

				Sleep(500);


				if (_kbhit()) break;
			}
		}
		if (_kbhit()) break;
		if ((cnt % 200 - 100) == 0) {

			gotoxy(11, BACK_Y - 1); printf("  ");
			gotoxy(11, BACK_Y - 2); printf("  ");
			gotoxy(10, BACK_Y - 1); printf("  ");
			gotoxy(10, BACK_Y - 2); printf("  ");
		} //위 카운트에서 100카운트 간격으로 도형을 지움 

		if ((cnt % 200) == 0) {
			for (int i = 1; i < BACK_Y - 1; i++) {
				color(7);
				background_block();

				color(14);
				gotoxy(16, i); printf("■");
				gotoxy(17, i); printf("■");
				gotoxy(18, i); printf("■");
				gotoxy(16, i - 1); printf(" ");
				gotoxy(17, i - 2); printf(" ");
				gotoxy(18, i - 1); printf(" ");

				color(1 + (c + 11) % 15);
				gotoxy(4, 3); printf("■■■");
				gotoxy(5, 4);   printf("■");
				gotoxy(5, 5);   printf("■");
				gotoxy(5, 6);   printf("■");
				gotoxy(5, 7);   printf("■");

				color(1 + (c + 10) % 15);
				gotoxy(8, 3); printf("■■■");
				gotoxy(8, 4); printf("■");
				gotoxy(8, 5); printf("■■■");
				gotoxy(8, 6); printf("■");
				gotoxy(8, 7); printf("■■■");

				color(1 + (c + 9) % 15);
				gotoxy(12, 3); printf("■■■");
				gotoxy(13, 4);   printf("■");
				gotoxy(13, 5);   printf("■");
				gotoxy(13, 6);   printf("■");
				gotoxy(13, 7);   printf("■");

				color(1 + (c + 8) % 15);
				gotoxy(16, 3); printf("■■■");
				gotoxy(16, 4); printf("■  ■");
				gotoxy(16, 5); printf("■■■");
				gotoxy(16, 6); printf("■ ■");
				gotoxy(16, 7); printf("■  ■");

				color(1 + (c + 7) % 15);
				gotoxy(20, 3); printf("■■");
				gotoxy(20, 4); printf(" ■");
				gotoxy(20, 5); printf(" ■");
				gotoxy(20, 6); printf(" ■");
				gotoxy(20, 7); printf("■■");

				color(1 + (c + 6) % 15);
				gotoxy(23, 3); printf("■■■");
				gotoxy(23, 4); printf("■");
				gotoxy(23, 5); printf("■■■");
				gotoxy(25, 6);     printf("■");
				gotoxy(23, 7); printf("■■■");

				color(1 + (c + 5) % 15);
				gotoxy(x, y + 3); printf("■■■");
				gotoxy(x, y + 4); printf("■  ■");
				gotoxy(x, y + 5); printf("■■■");
				gotoxy(x, y + 6); printf("■  ■");
				gotoxy(x, y + 7); printf("■■■");

				color(1 + (c + 4) % 15);
				gotoxy(x + 4, y + 3); printf("■■■");
				gotoxy(x + 4, y + 4); printf("■  ■");
				gotoxy(x + 4, y + 5); printf("■■■");
				gotoxy(x + 4, y + 6); printf("■ ■");
				gotoxy(x + 4, y + 7); printf("■  ■");

				color(1 + (c + 3) % 15);
				gotoxy(x + 8, y + 3); printf("■■■");
				gotoxy(x + 8, y + 4); printf("■");
				gotoxy(x + 8, y + 5); printf("■■■");
				gotoxy(x + 8, y + 6); printf("■");
				gotoxy(x + 8, y + 7); printf("■■■");

				color(1 + (c + 2) % 15);
				gotoxy(x + 12, y + 3); printf("■■■");
				gotoxy(x + 12, y + 4);  printf("■  ■");
				gotoxy(x + 12, y + 5);  printf("■■■");
				gotoxy(x + 12, y + 6);  printf("■  ■");
				gotoxy(x + 12, y + 7);  printf("■  ■");

				color(1 + (c + 1) % 15);
				gotoxy(x + 16, y + 3); printf("■  ■");
				gotoxy(x + 16, y + 4); printf("■ ■");
				gotoxy(x + 16, y + 5); printf("■■");
				gotoxy(x + 16, y + 6);   printf("■ ■");
				gotoxy(x + 16, y + 7);   printf("■  ■");

				color(1 + c % 15);
				gotoxy(x + 20, y + 3); printf("■");
				gotoxy(x + 20, y + 4); printf("■");
				gotoxy(x + 20, y + 5); printf("■");
				gotoxy(x + 20, y + 7); printf("■");

				c++;

				Sleep(500);

				if (_kbhit()) break;
			}
		}//윗별과 같지만 시간차를 뒀음 
		if (_kbhit()) break;
		if ((cnt % 200) == 0) {

			gotoxy(16, BACK_Y - 2); printf("  ");
			gotoxy(17, BACK_Y - 3); printf("  ");
			gotoxy(17, BACK_Y - 2); printf("  ");
			gotoxy(18, BACK_Y - 2); printf("  ");
		}

	}

	while (_kbhit()) _getch(); //버퍼에 기록된 키값을 버림 

}

void reset(void) {
	char msg[100];
	ROUND = 1; //각종변수 초기화 
	key = 0;
	crush_on = 0;
	cnt = 0;
	speed = 100;
	FaceType = 0;
	ComboType = 0;
	//PrisonType = 0;	
	system("cls"); //화면지움 
	reset_main(); // main_org를 초기화 
	sprintf(msg, "%s:GAMESTART", NAME);
	SendMsg(msg, *msg);
}

void reset_main(void) { //게임판을 초기화  
	int i, j;

	if (ROUND == 1)  //  라운드에 따른 목표 줄수
		TARGET_SCORE = 1;
	else
		TARGET_SCORE = 10;

	for (i = 0; i < MAIN_Y; i++) { // 게임판을 0으로 초기화  
		for (j = 0; j < MAIN_X; j++) {
			main_org[i][j] = 0;
			main_cpy[i][j] = 100;
		}
	}
	for (j = 1; j < MAIN_X; j++) { //y값이 3인 위치에 천장을 만듦 
		main_org[3][j] = CEILLING;
	}
	for (i = 1; i < MAIN_Y - 1; i++) { //좌우 벽을 만듦  
		main_org[i][0] = WALL;
		main_org[i][MAIN_X - 1] = WALL;
	}
	for (j = 0; j < MAIN_X; j++) { //바닥벽을 만듦 
		main_org[MAIN_Y - 1][j] = WALL;
	}
	draw_combo();
	draw_prison();
	draw_bot_background();
	draw_bot_backimage();
	b_type_next = rand() % 7; //다음번에 나올 블록 종류를 랜덤하게 생성 
	new_block(); //새로운 블록을 하나 만듦  
	draw_map();
	draw_main(); // 게임판을 그림 
	i = 0;
}



void draw_map(void) { //게임 상태 표시를 나타내는 함수  
	int y = 2, i, j;             // level, goal, score만 게임중에 값이 바뀔수 도 있음 그 y값을 따로 저장해둠 
								 // 그래서 혹시 게임 상태 표시 위치가 바뀌어도 그 함수에서 안바꿔도 되게.. 
	gotoxy(STATUS_X_ADJ, STATUS_Y_ROUND = y); printf(" ROUND : %5d", ROUND); // 레벨을 없앰 화면에 나오는 점수부분 이다 
	gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL = y + 1); printf(" GOAL  : %5d", TARGET_SCORE);
	gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE = y + 2); printf(" SCORE : %5d", cnt);
	gotoxy(STATUS_X_ADJ, y + 3); printf(" TOTAL : %5d", seq_cnt[4][0]);
	gotoxy(STATUS_X_ADJ, y + 4); printf("+-  N E X T  -+ ");
	gotoxy(STATUS_X_ADJ, y + 5); printf("|             | ");
	gotoxy(STATUS_X_ADJ, y + 6); printf("|             | ");
	gotoxy(STATUS_X_ADJ, y + 7); printf("|             | ");
	gotoxy(STATUS_X_ADJ, y + 8); printf("|             | ");
	gotoxy(STATUS_X_ADJ, y + 9); printf("+-------------+ ");


	for (i = 1; i < 3; i++) { //게임상태표시에 다음에 나올블럭을 그림 
		for (j = 0; j < 4; j++) {
			if (blocks[b_type_next][0][i][j] == 1) {
				figurecolor(b_type_next);
				gotoxy(STATUS_X_ADJ + 2 + j, i + 7);
				printf("■");
				color(7);
			}
			else {
				gotoxy(STATUS_X_ADJ + 2 + j, i + 7);
				printf("  ");
			}
		}
	}
}

void draw_combo() {
	int i, j;

	for (i = 0; i < 24; i++) {
		for (j = 0; j < 5; j++) {
			//cpy랑 비교해서 값이 달라진 부분만 새로 그려줌.
			//이게 없으면 게임판전체를 계속 그려서 느려지고 반짝거림
			gotoxy(STATUS_X_ADJ + i, 12 + j);
			switch (Combo[ComboType][j][i]) {
			case EMPTY: //빈칸모양 
				printf("  ");
				break;
			case 1: //굳은 블럭 모양  

				color(7);
				printf("■");
				break;
			}

		}
	}
}
void draw_prison(void) {
	int i, j;

	for (i = 0; i < 23; i++) {
		for (j = 0; j < 11; j++) {
			gotoxy(STATUS_X_ADJ + 1 + i, 18 + j);
			switch (prison_org[PrisonType][j][i]) {
			case EMPTY: //빈칸모양 
				printf("  ");
				break;
			case 1: //굳은 블럭 모양  
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (7 << 4));
				printf("■");
				color(7);
				break;
			case 2: //움직이고있는 블럭 모양  
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14 | (14 << 4));
				printf("■");
				color(7);
				break;
			}
		}
	}
}

void draw_main(void) { //게임판 그리는 함수 
	int i, j;

	for (j = 1; j < MAIN_X - 1; j++) { //천장은 계속 새로운블럭이 지나가서 지워지면 새로 그려줌 
		if (main_org[3][j] == EMPTY) main_org[3][j] = CEILLING;
	}
	for (i = 0; i < MAIN_Y; i++) {
		for (j = 0; j < MAIN_X; j++) {
			if (main_cpy[i][j] != main_org[i][j]) { //cpy랑 비교해서 값이 달라진 부분만 새로 그려줌.
													//이게 없으면 게임판전체를 계속 그려서 느려지고 반짝거림
				gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i);
				switch (main_org[i][j]) {
				case EMPTY: //빈칸모양 
					printf("  ");
					break;
				case CEILLING: //천장모양 
					printf(". ");
					break;
				case WALL: //벽모양 
					printf("▩");
					break;
				case INACTIVE_BLOCK: //굳은 블럭 모양  
					printf("■");
					color(7);
					break;
				case ACTIVE_BLOCK: //움직이고있는 블럭 모양  
					figurecolor(b_type_before1);
					printf("■");
					color(7);
					break;
				}
			}
		}
	}
	for (i = 0; i < MAIN_Y; i++) { //게임판을 그린 후 main_cpy에 복사  
		for (j = 0; j < MAIN_X; j++) {
			main_cpy[i][j] = main_org[i][j];
		}
	}

}

void new_block(void) { //새로운 블록 생성  
	int i, j;
	b_type_before1 = b_type_next;
	bx = (MAIN_X / 2) - 1; //블록 생성 위치x좌표(게임판의 가운데) 
	by = 0;  //블록 생성위치 y좌표(제일 위) 
	b_type = b_type_next; //다음블럭값을 가져옴 
	b_type_next = rand() % 7; //다음 블럭을 만듦 
	b_rotation = 0;  //회전은 0번으로 가져옴 

	new_block_on = 0; //new_block flag를 끔  

	for (i = 0; i < 4; i++) { //게임판 bx, by위치에 블럭생성  
		for (j = 0; j < 4; j++) {
			if (blocks[b_type][b_rotation][i][j] == 1)  main_org[by + i][bx + j] = ACTIVE_BLOCK;
		}
	}
}

void check_key(void) {
	key = 0; //키값 초기화  

	if (_kbhit()) { //키입력이 있는 경우  
		key = _getch(); //키값을 받음
		if (LIGHT == 1 && key != 0) {
			char msg[30];
			sprintf(msg, "%s:GAMEOVER", NAME);
			int len = *msg;
			SendMsg(msg, len);
		}
		if (key == 224) { //방향키인경우 

			key = _getch();//방향키지시값을 버림 

			if (key == LEFT) {
				if (check_crush(bx - 1, by, b_rotation) == true) move_block(LEFT);
			}

			else if (key == RIGHT) { //오른쪽 방향키 눌렀을때- 위와 동일하게 처리됨 
				if (check_crush(bx + 1, by, b_rotation) == true) move_block(RIGHT);
			}

			else if (key == DOWN) { //아래쪽 방향키 눌렀을때-위와 동일하게 처리됨
				if (check_crush(bx, by + 1, b_rotation) == true) move_block(DOWN);
			}

			else if (key == UP) { //위쪽 방향키 눌렀을때 
				if (check_crush(bx, by, (b_rotation + 1) % 4) == true) move_block(UP);
				//회전할 수 있는지 체크 후 가능하면 회전
				else if (crush_on == 1 && check_crush(bx, by - 1, (b_rotation + 1) % 4) == true) move_block(100);
			}
		}                    //바닥에 닿은 경우 위쪽으로 한칸띄워서 회전이 가능하면 그렇게 함(특수동작)

		else if (key == SPACE) {

			while (crush_on == 0) { //바닥에 닿을때까지 이동시킴 				
				drop_block();
			}
			space_key_on = 1; //스페이스키 flag를 띄움
		}

		else if (key == ESC) { //ESC눌렀을때 
			system("cls"); //화면을 지우고 
						   //게임종료 
		}

	}
	while (_kbhit()) _getch(); //키버퍼를 비움 
}

void drop_block(void) {
	int i, j;
	if (crush_on && check_crush(bx, by + 1, b_rotation) == true) crush_on = 0; //밑이 비어있으면 crush flag 끔 
	if (crush_on && check_crush(bx, by + 1, b_rotation) == false) { //밑이 비어있지않고 crush flag가 켜저있으면 
		for (i = 0; i < MAIN_Y; i++) { //현재 조작중인 블럭을 굳힘 
			for (j = 0; j < MAIN_X; j++) {
				if (main_org[i][j] == ACTIVE_BLOCK) {
					main_org[i][j] = INACTIVE_BLOCK;
				}
			}
		}
		crush_on = 0; //flag를 끔 
		check_line(); //라인체크를 함 	
		new_block_on = 1; //새로운 블럭생성 flag를 켬  
		return; //함수 종료 
	}
	if (check_crush(bx, by + 1, b_rotation) == true) move_block(DOWN); //밑이 비어있으면 밑으로 한칸 이동
	if (check_crush(bx, by + 1, b_rotation) == false) crush_on++; //밑으로 이동이 안되면  crush flag를 켬
}

int check_crush(int bx, int by, int b_rotation) { //지정된 좌표와 회전값으로 충돌이 있는지 검사 
	int i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) { //지정된 위치의 게임판과 블럭모양을 비교해서 겹치면 false를 리턴 
			if (blocks[b_type][b_rotation][i][j] == 1 && main_org[by + i][bx + j] > 0) return false;
		}
	}
	return true; //하나도 안겹치면 true리턴 
};

void move_block(int dir) { //블록을 이동시킴 
	int i, j;

	switch (dir) {
	case LEFT: //왼쪽방향 
		for (i = 0; i < 4; i++) { //현재좌표의 블럭을 지움 
			for (j = 0; j < 4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
			}
		}
		for (i = 0; i < 4; i++) { //왼쪽으로 한칸가서 active block을 찍음 
			for (j = 0; j < 4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j - 1] = ACTIVE_BLOCK;
			}
		}
		bx--; //좌표값 이동 
		break;

	case RIGHT:    //오른쪽 방향. 왼쪽방향이랑 같은 원리로 동작 
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
			}
		}
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j + 1] = ACTIVE_BLOCK;
			}
		}
		bx++;
		break;

	case DOWN:    //아래쪽 방향. 왼쪽방향이랑 같은 원리로 동작
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
			}
		}
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i + 1][bx + j] = ACTIVE_BLOCK;
			}
		}
		by++;
		break;

	case UP: //키보드 위쪽 눌렀을때 회전시킴. 
		for (i = 0; i < 4; i++) { //현재좌표의 블럭을 지움  
			for (j = 0; j < 4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
			}
		}
		b_rotation = (b_rotation + 1) % 4; //회전값을 1증가시킴(3에서 4가 되는 경우는 0으로 되돌림) 
		for (i = 0; i < 4; i++) { //회전된 블록을 찍음 
			for (j = 0; j < 4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = ACTIVE_BLOCK;
			}
		}
		break;

	case 100: //블록이 바닥, 혹은 다른 블록과 닿은 상태에서 한칸위로 올려 회전이 가능한 경우 
			  //이를 동작시키는 특수동작 
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
			}
		}
		b_rotation = (b_rotation + 1) % 4;
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i - 1][bx + j] = ACTIVE_BLOCK;
			}
		}
		by--;
		break;
	}
}

void check_line(void) {
	int i, j, k, l;
	int y = 3;

	int block_amount; //한줄의 블록갯수를 저장하는 변수 
	combo = 0; //콤보갯수 저장하는 변수 지정및 초기화 
	for (i = 1; i < MAIN_X - 2; i++) {

		if (main_org[3][i] > 0) {
			//서버
			char msg[30];
			sprintf(msg, "%s:GAMEOVER", NAME);
			int len = *msg;
			SendMsg(msg, len);
			//끝

		}
	}
	for (i = MAIN_Y - 2; i > 3;) { //i=MAIN_Y-2 : 밑쪽벽의 윗칸부터,  i>3 : 천장(3)아래까지 검사 
		block_amount = 0; //블록갯수 저장 변수 초기화 
		for (j = 1; j < MAIN_X - 1; j++) { //벽과 벽사이의 블록갯루를 셈 
			if (main_org[i][j] > 0) block_amount++;
		}
		if (block_amount == MAIN_X - 2) { //블록이 가득 찬 경우 
			if (ROUND == 2)
				if (THUNDER == 0) {
					char msg[30];
					sprintf(msg, "%s:GAMEOVER", NAME);
					int len = *msg;
					SendMsg(msg, len);
				}
			if (ROUND_up_on == 0) { //레벨업상태가 아닌 경우에(레벨업이 되면 자동 줄삭제가 있음)  
				cnt++; //지운 줄 갯수 카운트 증가 
					   //서버부분
				char msg[30];
				sprintf(msg, "%d:%s SYSTEMCNT", cnt, NAME);
				int len = *msg;
				SendMsg(msg, len);
				//끝
				combo++; //콤보수 증가  
				draw_livestate(cnt);
			}
			for (k = i; k > 1; k--) { //윗줄을 한칸씩 모두 내림(윗줄이 천장이 아닌 경우에만) 
				for (l = 1; l < MAIN_X - 1; l++) {
					if (main_org[k - 1][l] != CEILLING) main_org[k][l] = main_org[k - 1][l];
					if (main_org[k - 1][l] == CEILLING) main_org[k][l] = EMPTY;
					//윗줄이 천장인 경우에는 천장을 한칸 내리면 안되니까 빈칸을 넣음 
				}
			}

		}
		else i--;
	}

}

void check_ROUND_up(void) {
	int i, j;

	if ((cnt >= TARGET_SCORE && ROUND == 1) || (seq_cnt[4][0] >= TARGET_SCORE && ROUND == 2)) { //레벨별로 10줄씩 없애야함. 10줄이상 없앤 경우 
		draw_main();
		LIGHT = 0;
		ROUND_up_on = 1; //레벨업 flag를 띄움 
		char msg[30];
		sprintf(msg, "%s:R%dCLEAR", NAME, ROUND);
		SendMsg(msg, *msg);
		ROUND += 1; //레벨을 1 올림 
		cnt = 0; //지운 줄수 초기화 
		combo = 0;
		if (ROUND == 2) {
			draw_nextround();
			for (int z = 0; z < 4; z++) {
				seq_cnt[z][0] = 0;
			}
		}
		if (ROUND == 3)
			draw_realending();

		switch (ROUND) { //레벨별로 속도를 조절해줌. 
		case 2:
			speed = 50;
			break;
		case 3:
			speed = 25;
			break;
		case 4:
			speed = 10;
			break;
		case 5:
			speed = 5;
			break;
		case 6:
			speed = 4;
			break;
		case 7:
			speed = 3;
			break;
		case 8:
			speed = 2;
			break;
		case 9:
			speed = 1;
			break;
		case 10:
			speed = 0;
			break;
		}
		ROUND_up_on = 0; //레벨업 flag꺼줌

		reset_main();
	}
}

void check_game_over(void) {
	int x = 4;
	int i, j, count = 0;
	if (GAMEOVER == true) {//사망부분 서버~
		system("cls");
		system("mode con:cols=84 lines=40");
		gotoxy(x, 0); printf("          ■■■■■■■■■■■■■■■■■■■■■");
		gotoxy(x, 1); printf("          ■■■■■■■■■■■■■■■■■■■■■");
		gotoxy(x, 2); printf("      ■■■■■■■■■■■■■■■■■■■■■■■■");
		gotoxy(x, 3); printf("    ■  ■■■■■■■■■■■■■■■■■■■■■■  ■");
		gotoxy(x, 4); printf("    ■    ■■■■■■■■■■■■■■■■■■■■    ■■");
		gotoxy(x, 5); printf("      ■    ■■■■■■■■■■■■■■■■■     ■■■■");
		gotoxy(x, 6); printf("        ■                                      ■■■■■■");
		gotoxy(x, 7); printf("    ■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
		gotoxy(x, 8); printf("  ■      ■■                                        ■■■■■");
		gotoxy(x, 9); printf("  ■  ■  ■    ■■■              ■■■■          ■■■    ■");
		gotoxy(x, 10); printf("  ■  ■  ■  ■      ■          ■        ■        ■■■■    ■");
		gotoxy(x, 11); printf("  ■      ■  ■  ■  ■          ■    ■  ■        ■■■  ■  ■");
		gotoxy(x, 12); printf("  ■    ■    ■  ■  ■          ■    ■  ■        ■■    ■  ■");
		gotoxy(x, 13); printf("    ■■      ■      ■          ■    ■  ■        ■    ■    ■");
		gotoxy(x, 14); printf("    ■          ■■■            ■        ■          ■      ■");
		gotoxy(x, 15); printf("    ■                  ■■■■    ■■■■            ■    ■");
		gotoxy(x, 16); printf("    ■            ■    ■■■■                        ■  ■");
		gotoxy(x, 17); printf("      ■        ■                    ■              ■■■");
		gotoxy(x, 18); printf("      ■          ■■■■■■■■■■■■            ■");
		gotoxy(x, 19); printf("        ■          ■              ■    ■        ■");
		gotoxy(x, 20); printf("          ■        ■            ■              ■");
		gotoxy(x, 21); printf("            ■■  ■  ■■■■■■    ■    ■■■");
		gotoxy(x, 22); printf("                ■■                  ■■■");
		gotoxy(x, 23); printf("                    ■■■■■■■■■■");
		gotoxy(x, 24); printf("                  ■  ■    ■      ■  ■");
		gotoxy(x, 25); printf("                ■  ■      ■■  ■      ■");
		gotoxy(x, 26); printf("              ■      ■■■    ■          ■");
		gotoxy(x, 27); printf("              ■      ■  ■             ■■■");
		gotoxy(x, 28); printf("              ■      ■    ■           ■  ■");
		gotoxy(1, 30); printf("■■■■■  ■        ■■    ■      ■■■■  ■        ■■    ■      ■");
		gotoxy(1, 31); printf("    ■      ■■    ■    ■  ■■    ■        ■      ■    ■  ■      ■■■");
		gotoxy(1, 32); printf("  ■  ■    ■      ■    ■  ■      ■        ■■    ■    ■  ■");
		gotoxy(1, 33); printf("■      ■  ■        ■■    ■      ■        ■        ■■    ■        ■");
		gotoxy(1, 34); printf("                                      ■■■■  ■                ■    ■■■■■");
		gotoxy(1, 35); printf("      ■    ■                                  ■                ■");
		gotoxy(1, 36); printf("      ■■■■        ■      ■                                          ■■■");
		gotoxy(1, 37); printf("      ■    ■      ■  ■  ■  ■                                        ■  ■");
		gotoxy(1, 38); printf("      ■■■■                                                            ■■■");
		while (1) {

			if (count % 2 == 0) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				count++;
				Sleep(200);

			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
				count++;
				Sleep(200);

			}
			gotoxy(x + 21, 24); printf("■■■■■");
			gotoxy(x + 20, 25); printf("■■■■■■■");
			gotoxy(x + 20, 26); printf("■■■■■■■");
			gotoxy(x + 20, 27); printf("■■■■■■■");
			gotoxy(x + 21, 28); printf("■■■■■");


		}
		char msg[30];
		sprintf(msg, "ENDGAME");
		int len = *msg;
		SendMsg(msg, len);

		system("cls");
		exit(0);
	}//끝



}
void draw_secondstory(void) {

	int i, j, z, y = 1, x = 16, n = 10, h = 5;
	color(7);
	system("mode con:cols=84 lines=43");
	for (z = 0; z < 34; z = z + 14) {
		for (i = 0; i < NEXT_X; i++) {
			bot_org[1][i] = WALL;
		}
		for (i = 0; i < BOT_Y; i++) { //좌우 벽을 만듦  
			bot_org[i][0] = WALL;
			bot_org[i][NEXT_X - 1] = WALL;
		}
		for (j = 0; j < NEXT_X; j++) { //바닥벽을 만듦 
			bot_org[BOT_Y - 1][j] = WALL;
		}
		for (i = 1; i < BOT_Y; i++) {
			for (j = 0; j < NEXT_X; j++) {

				gotoxy(NEXT_X_ADJ + j, i + z);
				switch (bot_org[i][j]) {
				case WALL: //벽모양 
					printf("▩");
					break;

				}
			}
		}
	}
	Sleep(100);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(NEXT_X_ADJ + 1, 2); printf("        ■■");
	gotoxy(NEXT_X_ADJ + 1, 3); printf("        ■  ■");
	gotoxy(NEXT_X_ADJ + 1, 4); printf("        ■  ■");
	gotoxy(NEXT_X_ADJ + 1, 5); printf("      ■■    ■■■■■■■■■");
	gotoxy(NEXT_X_ADJ + 1, 6); printf("■■■                        ■");
	gotoxy(NEXT_X_ADJ + 1, 7); printf("                    ■■■■■■■");
	gotoxy(NEXT_X_ADJ + 1, 8); printf("                                ■");
	gotoxy(NEXT_X_ADJ + 1, 9); printf("                  ■■■■■■■■");
	gotoxy(NEXT_X_ADJ + 1, 10); printf("                              ■");
	gotoxy(NEXT_X_ADJ + 1, 11); printf("■■            ■■■■■■■");
	gotoxy(NEXT_X_ADJ + 1, 12); printf("    ■■■■■■■■■■■");
	gotoxy(NEXT_X_ADJ + 22, 2); printf("                    ■■");
	gotoxy(NEXT_X_ADJ + 26, 3); printf("          ■  ■");
	gotoxy(NEXT_X_ADJ + 26, 4); printf("          ■  ■");
	gotoxy(NEXT_X_ADJ + 23, 5); printf("■■■■■■■■■    ■■");
	gotoxy(NEXT_X_ADJ + 22, 6); printf("  ■                        ■■■");
	gotoxy(NEXT_X_ADJ + 22, 7); printf("■■■■■■■");
	gotoxy(NEXT_X_ADJ + 22, 8); printf("■                                ");
	gotoxy(NEXT_X_ADJ + 22, 9); printf("■■■■■■■■");
	gotoxy(NEXT_X_ADJ + 22, 10); printf("  ■                            ");
	gotoxy(NEXT_X_ADJ + 22, 11); printf("    ■■■■■■■            ■■");
	gotoxy(NEXT_X_ADJ + 22, 12); printf("        ■■■■■■■■■■■");
	color(7);
	Sleep(500); gotoxy(NEXT_X_ADJ + 15, 3); printf("다 살아서 도착했군.."); Sleep(500); gotoxy(NEXT_X_ADJ + 18, 5); printf("함께 가자!");
	Sleep(500); color(0); gotoxy(NEXT_X_ADJ + 15, 3); printf("다 살아서 도착했군.."); gotoxy(NEXT_X_ADJ + 18, 5); printf("함께 가자!");
	gotoxy(NEXT_X_ADJ + 1, 2); printf("        ■■");
	gotoxy(NEXT_X_ADJ + 1, 3); printf("        ■  ■");
	gotoxy(NEXT_X_ADJ + 1, 4); printf("        ■  ■");
	gotoxy(NEXT_X_ADJ + 1, 5); printf("      ■■    ■■■■■■■■■");
	gotoxy(NEXT_X_ADJ + 1, 6); printf("■■■                        ■");
	gotoxy(NEXT_X_ADJ + 1, 7); printf("                    ■■■■■■■");
	gotoxy(NEXT_X_ADJ + 1, 8); printf("                                ■");
	gotoxy(NEXT_X_ADJ + 1, 9); printf("                  ■■■■■■■■");
	gotoxy(NEXT_X_ADJ + 1, 10); printf("                              ■");
	gotoxy(NEXT_X_ADJ + 1, 11); printf("■■            ■■■■■■■");
	gotoxy(NEXT_X_ADJ + 1, 12); printf("    ■■■■■■■■■■■");
	gotoxy(NEXT_X_ADJ + 22, 2); printf("                    ■■");
	gotoxy(NEXT_X_ADJ + 22, 3); printf("                    ■  ■");
	gotoxy(NEXT_X_ADJ + 22, 4); printf("                    ■  ■");
	gotoxy(NEXT_X_ADJ + 22, 5); printf("  ■■■■■■■■■    ■■");
	gotoxy(NEXT_X_ADJ + 22, 6); printf("  ■                        ■■■");
	gotoxy(NEXT_X_ADJ + 22, 7); printf("■■■■■■■");
	gotoxy(NEXT_X_ADJ + 22, 8); printf("■                                ");
	gotoxy(NEXT_X_ADJ + 22, 9); printf("■■■■■■■■");
	gotoxy(NEXT_X_ADJ + 22, 10); printf("  ■                            ");
	gotoxy(NEXT_X_ADJ + 22, 11); printf("    ■■■■■■■            ■■");
	gotoxy(NEXT_X_ADJ + 22, 12); printf("        ■■■■■■■■■■■");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(NEXT_X_ADJ + 10, 2); printf("            ■■■■■■■■    ■■");
	gotoxy(NEXT_X_ADJ + 10, 3); printf("■        ■                ■■    ");
	gotoxy(NEXT_X_ADJ + 10, 4); printf("  ■  ■■    ■■■■■■        ");
	gotoxy(NEXT_X_ADJ + 10, 5); printf("    ■  ■■■            ■          ■");
	gotoxy(NEXT_X_ADJ + 10, 6); printf("                            ■      ■");
	gotoxy(NEXT_X_ADJ + 10, 7); printf("                        ■    ■  ■");
	gotoxy(NEXT_X_ADJ + 10, 8); printf("                    ■    ■  ■■");
	gotoxy(NEXT_X_ADJ + 10, 9); printf("    ■                ■    ■■");
	gotoxy(NEXT_X_ADJ + 10, 10); printf("■■  ■■      ■    ■■■");
	gotoxy(NEXT_X_ADJ + 10, 11); printf("  ■■■  ■      ■■■");
	gotoxy(NEXT_X_ADJ + 10, 12); printf("    ■■■■■■■■");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 | (8 << 4));
	Sleep(500);
	gotoxy(NEXT_X_ADJ + 7, x); printf("■■■■■");
	gotoxy(NEXT_X_ADJ + 6, x + 1); printf("■■■■■■■");
	gotoxy(NEXT_X_ADJ + 5, x + 2); printf("■■■■■■■■■");
	gotoxy(NEXT_X_ADJ + 4, x + 3); printf("■■■■■■■■■■■");
	gotoxy(NEXT_X_ADJ + 4, x + 4); printf("■■■■■■■■■■■");
	gotoxy(NEXT_X_ADJ + 4, x + 5); printf("■■■■■■■■■■■");
	gotoxy(NEXT_X_ADJ + 4, x + 6); printf("■■■■■■■■■■■");
	gotoxy(NEXT_X_ADJ + 4, x + 7); printf("■■■■■■■■■■■");
	gotoxy(NEXT_X_ADJ + 4, x + 8); printf("■■■■■■■■■■■");
	gotoxy(NEXT_X_ADJ + 4, x + 9); printf("■■■■■■■■■■■");
	gotoxy(NEXT_X_ADJ + 4, x + 10); printf("■■■■■■■■■■■");

	color(7);
	Sleep(500); gotoxy(NEXT_X_ADJ + 24, x + 1); printf("지금 우리 위에 경비대가 있어");	Sleep(500); gotoxy(NEXT_X_ADJ + 24, x + 3); printf("소리가 나면안돼"); Sleep(500); gotoxy(NEXT_X_ADJ + 24, x + 5); printf("번개가 칠때만 움직여");
	Sleep(500); gotoxy(NEXT_X_ADJ + 24, x + 7); printf("소리가 새어나가면 끝이야"); Sleep(500); gotoxy(NEXT_X_ADJ + 24, x + 9); printf("천천히 가자!");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14 | (14 << 4)); Sleep(500);
	gotoxy(NEXT_X_ADJ + 4 + h, 2 * x - 1); printf("■");
	gotoxy(NEXT_X_ADJ + 3 + h, 2 * x); printf("■■");
	gotoxy(NEXT_X_ADJ + 2 + h, 2 * x + 1); printf("■■■");
	gotoxy(NEXT_X_ADJ + 1 + h, 2 * x + 2); printf("■■■■■");
	gotoxy(NEXT_X_ADJ + 2 + h, 2 * x + 3); printf("■■■■■");
	gotoxy(NEXT_X_ADJ + 3 + h, 2 * x + 4); printf("■■■");
	gotoxy(NEXT_X_ADJ + 3 + h, 2 * x + 5); printf("■■");
	gotoxy(NEXT_X_ADJ + 3 + h, 2 * x + 6); printf("■");
	color(7);
	Sleep(500); gotoxy(NEXT_X_ADJ + 26, 2 * x + 2); printf("번개가 칠때 움직여"); Sleep(500); gotoxy(NEXT_X_ADJ + 26, 2 * x + 4); printf("아님 걸려");
	Sleep(500); gotoxy(NEXT_X_ADJ + 26, 2 * x + 2); printf("                     "); gotoxy(NEXT_X_ADJ + 26, 2 * x + 4); printf("         ");
	gotoxy(NEXT_X_ADJ + 26, 2 * x + 3); printf("가자 밖으로 !!!!");
	color(7);
	system("mode con:cols=84 lines=45");
	system("cls");

}
void draw_nextround(void) {

	int y = 1;
	int x = 15;
	int n = 10;
	int t = 2;
	system("cls");
	system("mode con:cols=84 lines=45");

	color(7);
	int i, j;
	for (i = 0; i < NEXT_X; i++) {
		next_org[1][i] = WALL;
	}
	for (i = 0; i < NEXT_Y; i++) { //좌우 벽을 만듦  
		next_org[i][0] = WALL;
		next_org[i][NEXT_X - 1] = WALL;
	}
	for (j = 0; j < NEXT_X; j++) { //바닥벽을 만듦 
		next_org[NEXT_Y - 1][j] = WALL;
	}
	for (i = 1; i < NEXT_Y; i++) {
		for (j = 0; j < NEXT_X; j++) {

			gotoxy(NEXT_X_ADJ + j, i);
			switch (next_org[i][j]) {
			case WALL: //벽모양 
				printf("▩");
				break;

			}
		}
	}
	draw_bot_background();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 | (8 << 4));
	gotoxy(t, 2); printf("■■■");	 gotoxy(NEXT_X - 3, 2); printf("■■■");
	gotoxy(t + 2, 3); printf("■■■"); gotoxy(NEXT_X - 5, 3); printf("■■■");
	gotoxy(t + 4, 4); printf("■■■"); gotoxy(NEXT_X - 7, 4); printf("■■■");
	gotoxy(t + 6, 5); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(t + 6, 6); printf("■"); gotoxy(NEXT_X - 8, 6); printf("■");
	gotoxy(t + 6, 7); printf("■"); gotoxy(NEXT_X - 8, 7); printf("■");
	gotoxy(t + 6, 8); printf("■"); gotoxy(NEXT_X - 8, 8); printf("■");
	gotoxy(t + 6, 9); printf("■"); gotoxy(NEXT_X - 8, 9); printf("■");
	gotoxy(t + 6, 10); printf("■"); gotoxy(NEXT_X - 8, 10); printf("■");
	gotoxy(t + 6, 11); printf("■");  gotoxy(NEXT_X - 8, 11); printf("■");
	gotoxy(t + 6, 12); printf("■");  gotoxy(NEXT_X - 8, 12); printf("■");
	gotoxy(t + 6, 13); printf("■");  gotoxy(NEXT_X - 8, 13); printf("■");
	gotoxy(t + 6, 14); printf("■");  gotoxy(NEXT_X - 8, 14); printf("■");
	gotoxy(t + 6, 15); printf("■");  gotoxy(NEXT_X - 8, 15); printf("■");
	gotoxy(t + 6, 16); printf("■");  gotoxy(NEXT_X - 8, 16); printf("■");
	gotoxy(t + 6, 17); printf("■");  gotoxy(NEXT_X - 8, 17); printf("■");
	gotoxy(t + 6, 18); printf("■");  gotoxy(NEXT_X - 8, 18); printf("■");
	gotoxy(t + 6, 19); printf("■");  gotoxy(NEXT_X - 8, 19); printf("■");
	gotoxy(t + 6, 20); printf("■");  gotoxy(NEXT_X - 8, 20); printf("■");
	gotoxy(t + 6, 21); printf("■");  gotoxy(NEXT_X - 8, 21); printf("■");
	gotoxy(t + 6, 22); printf("■"); gotoxy(NEXT_X - 8, 22); printf("■");
	gotoxy(t + 6, 23); printf("■");  gotoxy(NEXT_X - 8, 23); printf("■");
	gotoxy(t + 6, 24); printf("■");  gotoxy(NEXT_X - 8, 24); printf("■");
	gotoxy(t + 6, 25); printf("■");  gotoxy(NEXT_X - 8, 25); printf("■");
	gotoxy(t + 6, 26); printf("■");  gotoxy(NEXT_X - 8, 26); printf("■");
	gotoxy(t + 4, 27); printf("■■■"); gotoxy(NEXT_X - 8, 27); printf("■■■");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14 | (14 << 4));
	gotoxy(NEXT_X - 23, 13); printf("              ");
	gotoxy(NEXT_X - 24, 14); printf("                  ");	gotoxy(NEXT_X - 24, 15); printf("                  ");	gotoxy(NEXT_X - 24, 16); printf("                  ");
	gotoxy(NEXT_X - 24, 17); printf("                  ");	gotoxy(NEXT_X - 24, 18); printf("                  ");	gotoxy(NEXT_X - 24, 19); printf("                  ");
	gotoxy(NEXT_X - 24, 20); printf("                  ");	gotoxy(NEXT_X - 24, 21); printf("                  ");	gotoxy(NEXT_X - 24, 22); printf("                  ");
	gotoxy(NEXT_X - 24, 23); printf("                  ");  gotoxy(NEXT_X - 24, 24); printf("                  ");  gotoxy(NEXT_X - 24, 25); printf("                  ");
	gotoxy(NEXT_X - 24, 26); printf("                  ");  gotoxy(NEXT_X - 26, 27); printf("                          ");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 | (15 << 4));
	gotoxy(NEXT_X - 23, 12); printf("■■■■■■■");
	gotoxy(NEXT_X - 24, 13); printf("■"); gotoxy(NEXT_X - 16, 13); printf("■");
	gotoxy(NEXT_X - 25, 14); printf("■"); gotoxy(NEXT_X - 15, 14); printf("■");
	gotoxy(NEXT_X - 25, 15); printf("■"); gotoxy(NEXT_X - 15, 15); printf("■");
	gotoxy(NEXT_X - 25, 16); printf("■"); gotoxy(NEXT_X - 15, 16); printf("■");
	gotoxy(NEXT_X - 25, 17); printf("■"); gotoxy(NEXT_X - 15, 17); printf("■");
	gotoxy(NEXT_X - 25, 18); printf("■"); gotoxy(NEXT_X - 15, 18); printf("■");
	gotoxy(NEXT_X - 25, 19); printf("■"); gotoxy(NEXT_X - 15, 19); printf("■");
	gotoxy(NEXT_X - 25, 20); printf("■"); gotoxy(NEXT_X - 15, 20); printf("■");
	gotoxy(NEXT_X - 25, 21); printf("■"); gotoxy(NEXT_X - 15, 21); printf("■");
	gotoxy(NEXT_X - 25, 22); printf("■"); gotoxy(NEXT_X - 15, 22); printf("■");
	gotoxy(NEXT_X - 25, 23); printf("■"); gotoxy(NEXT_X - 15, 23); printf("■");
	gotoxy(NEXT_X - 25, 24); printf("■"); gotoxy(NEXT_X - 15, 24); printf("■");
	gotoxy(NEXT_X - 25, 25); printf("■"); gotoxy(NEXT_X - 15, 25); printf("■");
	gotoxy(NEXT_X - 25, 26); printf("■"); gotoxy(NEXT_X - 15, 26); printf("■");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (7 << 4));
	gotoxy(NEXT_X - 12, 10); printf("■■");
	gotoxy(NEXT_X - 13, 11); printf("■■■"); gotoxy(NEXT_X - 10, 11); printf("■");
	gotoxy(NEXT_X - 14, 12); printf("■■■■"); gotoxy(NEXT_X - 10, 12); printf("■");
	gotoxy(NEXT_X - 14, 13); printf("■■■■"); gotoxy(NEXT_X - 10, 13); printf("■");
	gotoxy(NEXT_X - 14, 14); printf("■■■■"); gotoxy(NEXT_X - 10, 14); printf("■");
	gotoxy(NEXT_X - 14, 15); printf("■■■■"); gotoxy(NEXT_X - 10, 15); printf("■");
	gotoxy(NEXT_X - 14, 16); printf("■■■"); gotoxy(NEXT_X - 10, 16); printf("■");
	gotoxy(NEXT_X - 14, 17); printf("■■■■"); gotoxy(NEXT_X - 10, 17); printf("■");
	gotoxy(NEXT_X - 14, 18); printf("■■■■"); gotoxy(NEXT_X - 10, 18); printf("■");
	gotoxy(NEXT_X - 14, 19); printf("■■■■"); gotoxy(NEXT_X - 10, 19); printf("■");
	gotoxy(NEXT_X - 14, 20); printf("■■■■"); gotoxy(NEXT_X - 10, 20); printf("■");
	gotoxy(NEXT_X - 14, 21); printf("■■■■"); gotoxy(NEXT_X - 10, 21); printf("■");
	gotoxy(NEXT_X - 14, 22); printf("■■■"); gotoxy(NEXT_X - 11, 22); printf("■");
	gotoxy(NEXT_X - 14, 23); printf("■■"); gotoxy(NEXT_X - 12, 23); printf("■");
	gotoxy(NEXT_X - 14, 24); printf("■"); gotoxy(NEXT_X - 13, 24); printf("■");
	gotoxy(NEXT_X - 14, 25); printf("■");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (7 << 4));
	gotoxy(t + 2, 10); printf("■"); gotoxy(NEXT_X - 3, 10); printf("■");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14 | (14 << 4));
	gotoxy(t + 2, 9); printf("■"); gotoxy(NEXT_X - 3, 9); printf("■");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12 | (12 << 4));
	gotoxy(t + 1, 9); printf("■"); gotoxy(t + 3, 9); printf("■"); gotoxy(NEXT_X - 4, 9); printf("■"); gotoxy(NEXT_X - 2, 9); printf("■");
	gotoxy(t + 1, 8); printf("■■■"); gotoxy(NEXT_X - 4, 8); printf("■■■");
	gotoxy(t + 2, 7); printf("■"); gotoxy(NEXT_X - 3, 7); printf("■");

	color(7);
	if (nextrnd != 1) {
		for (int i = 0; 1; i++) {

			if (i % 5 == 0) {
				gotoxy(18, 30); printf("WAITING FOR nextround %d명 CLEAR %d SECOND", clearcnt, i / 5);
			}
			Sleep(200);
			if (nowcnt < clearcnt) { nowcnt++; draw_nextround(); return 0; }
			if (nextrnd == 1)
				break;
		}

	}
	gotoxy(18, 30); printf("                                              ");
	for (int i = 25; i >= 0; i--) {

		if (i % 5 == 0) {
			gotoxy(18, 30); printf("WAITING FOR...%2d", i / 5);
		}
		Sleep(200);

	}

	/*while (1) {

	gotoxy(10, y + 9);  //gets(inputIp);//여기서부터 값 넣으면 됭

	gotoxy(10, y + 12); //gets(inputport);

	gotoxy(10, y + 15); //gets(inputName);

	gotoxy(10, y + 18);// gets(inputName);

	gotoxy(NEXT_X - 7, 27); printf("WAITING FOR %2d", n);
	Sleep(1000);

	n--;
	if (n == 0) break;

	}*/
	//화면 지우고 새로 그림

	system("cls");
	draw_secondstory();
	char msg[30];
	sprintf(msg, "%s:R%dSTART", NAME, ROUND);
	SendMsg(msg, *msg);


}

void pause(void) { //게임 일시정지 함수 
	int i, j;
	int y = 1;
	int x = 15;
	int n = 10;
	system("cls");
	system("mode con:cols=56 lines=25");


	color(7);

	gotoxy(2, y); printf("■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(2, y + 1); printf("■   ■  ■  ■    ■■■    ■■■    ■■■  ");
	gotoxy(2, y + 2); printf("■   ■  ■  ■    ■  ■      ■        ■    ");
	gotoxy(2, y + 3); printf("■   ■  ■  ■    ■■■      ■        ■    ");
	gotoxy(2, y + 4); printf("■   ■  ■  ■    ■  ■      ■        ■    ");
	gotoxy(2, y + 5); printf("■   ■■■■■    ■  ■    ■■■      ■    ");
	gotoxy(2, y + 6); printf("■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(2, y + 7); printf("■      ■");
	gotoxy(2, y + 8); printf("■ │    ■");
	gotoxy(2, y + 9); printf("■ │    ■  ●");
	gotoxy(2, y + 10); printf("■ └─   ■");
	gotoxy(2, y + 11); printf("■  ┬   ■");
	gotoxy(2, y + 12); printf("■  │   ■  ●");
	gotoxy(2, y + 13); printf("■  ┴   ■");
	gotoxy(2, y + 14); printf("■ ┌─   ■");
	gotoxy(2, y + 15); printf("■ └-┐  ■  ●");
	gotoxy(2, y + 16); printf("■  ─┘  ■");
	gotoxy(2, y + 17); printf("■ -┬-  ■");
	gotoxy(2, y + 18); printf("■  │   ■  ●");
	gotoxy(2, y + 19); printf("■  │   ■");
	gotoxy(2, y + 20); printf("■      ■");

	gotoxy(25, y + 1); printf("■");
	gotoxy(25, y + 2); printf("■");
	gotoxy(25, y + 3); printf("■");
	gotoxy(25, y + 4); printf("■");
	gotoxy(25, y + 5); printf("■");
	gotoxy(25, y + 6); printf("■");
	gotoxy(25, y + 7); printf("■");
	gotoxy(25, y + 8); printf("■");
	gotoxy(25, y + 9); printf("■");
	gotoxy(25, y + 10); printf("■");
	gotoxy(25, y + 11); printf("■");
	gotoxy(25, y + 12); printf("■");
	gotoxy(25, y + 13); printf("■");
	gotoxy(25, y + 14); printf("■");
	gotoxy(25, y + 15); printf("■");
	gotoxy(25, y + 16); printf("■");
	gotoxy(25, y + 17); printf("■");
	gotoxy(25, y + 18); printf("■");
	gotoxy(25, y + 19); printf("■");
	gotoxy(25, y + 20); printf("■");
	gotoxy(x, y + 8); printf("  △   : Shift");
	gotoxy(x, y + 10); printf("  ◁   : Left ");
	gotoxy(x, y + 12); printf("  ▷   : Right");
	gotoxy(x, y + 14); printf("  ▽   : Soft Drop");
	gotoxy(x, y + 16); printf("SPACE  : Hard Drop");
	gotoxy(x, y + 19); printf(" ESC   : Quit");
	gotoxy(2, y + 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■");

	/*while (1) {


	gotoxy(10, y + 9);  //gets(inputIp);//여기서부터 값 넣으면 됭


	gotoxy(10, y + 12); //gets(inputport);


	gotoxy(10, y + 15); //gets(inputName);


	gotoxy(10, y + 18);// gets(inputName);

	gotoxy(18, 23); printf("WAITING FOR...%2d", n);
	Sleep(1000);

	n--;
	if (n == 0) break;

	}*/
	//화면 지우고 새로 그림 
	_getch(); //키입력시까지 대기 

	system("cls");
	system("mode con:cols=84 lines=45");
	reset_main();

	color(7);
} //끝! 

void draw_bot_background(void) {
	int i, j;

	for (i = 0; i < NEXT_X; i++) {
		bot_org[1][i] = WALL;
	}
	for (i = 0; i < BOT_Y; i++) { //좌우 벽을 만듦  
		bot_org[i][0] = WALL;
		bot_org[i][NEXT_X - 1] = WALL;
	}
	for (j = 0; j < NEXT_X; j++) { //바닥벽을 만듦 
		bot_org[BOT_Y - 1][j] = WALL;
	}
	for (i = 1; i < BOT_Y; i++) {
		for (j = 0; j < NEXT_X; j++) {

			gotoxy(NEXT_X_ADJ + j, i + 30);
			switch (bot_org[i][j]) {
			case WALL: //벽모양 
				printf("▩");
				break;

			}
		}
	}
}

void draw_state(void) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (7 << 4));
	gotoxy(3, STATE_Y); printf("■■"); gotoxy(4, STATE_Y + 1); printf("■■"); gotoxy(5, STATE_Y + 2); printf("■■"); gotoxy(6, STATE_Y + 3); printf("■■");
	gotoxy(7, STATE_Y + 4); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(2, STATE_Y + 4); printf("■"); gotoxy(2, STATE_Y + 5); printf("■■"); gotoxy(3, STATE_Y + 6); printf("■■"); gotoxy(4, STATE_Y + 7); printf("■■"); gotoxy(5, STATE_Y + 8); printf("■■");
	gotoxy(7, STATE_Y + 8); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(34, STATE_Y + 3); printf("■■"); gotoxy(35, STATE_Y + 2); printf("■■"); gotoxy(36, STATE_Y + 1); printf("■■"); gotoxy(37, STATE_Y); printf("■■");
	gotoxy(39, STATE_Y + 4); printf("■"); gotoxy(38, STATE_Y + 5); printf("■■"); gotoxy(37, STATE_Y + 6); printf("■■"); gotoxy(36, STATE_Y + 7); printf("■■"); gotoxy(35, STATE_Y + 8); printf("■■");
	color(7);
}
void draw_bot_backimage(void) {
	color(7);
	gotoxy(10 + 1, STATE_Y + 2); printf("                      ■");
	gotoxy(10 + 1, STATE_Y + 3); printf("              ■    ■      ■");
	gotoxy(10 + 1, STATE_Y + 4); printf("    ■■    ■    ■    ■      ■");
	gotoxy(10 + 1, STATE_Y + 5); printf("  ■■■    ■    ■    ■    ■      ■■");
	gotoxy(10 + 1, STATE_Y + 6); printf("■■  ■    ■    ■    ■    ■    ■■");
	gotoxy(10 + 1, STATE_Y + 7); printf("■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(10 + 1, STATE_Y + 8); printf("  ■■■    ■    ■    ■      ■  ■■");
	gotoxy(10 + 1, STATE_Y + 9); printf("    ■■      ■    ■    ■          ■■");
	gotoxy(10 + 1, STATE_Y + 10); printf("                      ■");

	gotoxy(NEXT_X - 6, STATE_Y + 5); printf("    ■■");		gotoxy(5, STATE_Y + 2); printf("■■      ■■");
	gotoxy(NEXT_X - 6, STATE_Y + 6); printf("    ■■");		gotoxy(5, STATE_Y + 3); printf("  ■■■■■");
	gotoxy(NEXT_X - 6, STATE_Y + 7); printf("■■■■");		gotoxy(5, STATE_Y + 4); printf("■■      ■■");
	gotoxy(NEXT_X - 6, STATE_Y + 8); printf("■■■■■");
	gotoxy(NEXT_X - 6, STATE_Y + 9); printf("      ■■■");
	gotoxy(NEXT_X - 6, STATE_Y + 10); printf("        ■■");


}
void draw_livestate(void) {
	int j;


	if (ROUND == 1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (7 << 4));
		if (cnt == 1) {

			gotoxy(x + 1, STATE_Y); printf("■"); gotoxy(x + 1, STATE_Y + 1); printf("■"); gotoxy(x + 1, STATE_Y + 2); printf("■"); gotoxy(x + 1, STATE_Y + 3); printf("■");
			gotoxy(x + 1, STATE_Y + 4); printf("■"); gotoxy(x + 1, STATE_Y + 5); printf("■");	gotoxy(x + 1, STATE_Y + 6); printf("■"); gotoxy(x + 1, STATE_Y + 7); printf("■");
			gotoxy(x + 1, STATE_Y + 8); printf("■"); gotoxy(x + 1, STATE_Y + 9); printf("■"); gotoxy(x + 1, STATE_Y + 10); printf("■");
			gotoxy(x + 2, STATE_Y + 1); printf("■"); gotoxy(x + 2, STATE_Y + 2); printf("■"); gotoxy(x + 2, STATE_Y + 3); printf("■");
			gotoxy(x + 2, STATE_Y + 4); printf("■"); gotoxy(x + 2, STATE_Y + 5); printf("■");	gotoxy(x + 2, STATE_Y + 6); printf("■"); gotoxy(x + 2, STATE_Y + 7); printf("■");
			gotoxy(x + 2, STATE_Y + 8); printf("■"); gotoxy(x + 2, STATE_Y + 9); printf("■"); gotoxy(x + 2, STATE_Y + 10); printf("■");
			gotoxy(x + 3, STATE_Y + 2); printf("■"); gotoxy(x + 3, STATE_Y + 3); printf("■");
			gotoxy(x + 3, STATE_Y + 4); printf("■"); gotoxy(x + 3, STATE_Y + 5); printf("■");	gotoxy(x + 3, STATE_Y + 6); printf("■"); gotoxy(x + 3, STATE_Y + 7); printf("■");
			gotoxy(x + 3, STATE_Y + 8); printf("■"); gotoxy(x + 3, STATE_Y + 9); printf("■"); gotoxy(x + 3, STATE_Y + 10); printf("■");
		}
		else if (cnt == 2) {
			gotoxy(x + 4, STATE_Y + 3); printf("■");
			gotoxy(x + 4, STATE_Y + 4); printf("■"); gotoxy(x + 4, STATE_Y + 5); printf("■");	gotoxy(x + 4, STATE_Y + 6); printf("■"); gotoxy(x + 4, STATE_Y + 7); printf("■");
			gotoxy(x + 4, STATE_Y + 8); printf("■"); gotoxy(x + 4, STATE_Y + 9); printf("■"); gotoxy(x + 4, STATE_Y + 10); printf("■");
			gotoxy(x + 5, STATE_Y + 4); printf("■"); gotoxy(x + 5, STATE_Y + 5); printf("■");	gotoxy(x + 5, STATE_Y + 6); printf("■"); gotoxy(x + 5, STATE_Y + 7); printf("■");
			gotoxy(x + 5, STATE_Y + 8); printf("■"); gotoxy(x + 5, STATE_Y + 9); printf("■"); gotoxy(x + 5, STATE_Y + 10); printf("■");
		}
		else if (cnt == 3) {
			gotoxy(x + 6, STATE_Y + 5); printf("■"); gotoxy(x + 6, STATE_Y + 6); printf("■"); gotoxy(x + 6, STATE_Y + 7); printf("■");
			gotoxy(x + 6, STATE_Y + 8); printf("■"); gotoxy(x + 6, STATE_Y + 9); printf("■"); gotoxy(x + 6, STATE_Y + 10); printf("■");
			gotoxy(x + 7, STATE_Y + 6); printf("■"); gotoxy(x + 7, STATE_Y + 7); printf("■");
			gotoxy(x + 7, STATE_Y + 8); printf("■"); gotoxy(x + 7, STATE_Y + 9); printf("■"); gotoxy(x + 7, STATE_Y + 10); printf("■");
		}
		else {
			for (j = 0; j < 5; j++) {
				gotoxy(x + i + 8, STATE_Y + 6); printf("■"); gotoxy(x + i + 8, STATE_Y + 7); printf("■");
				gotoxy(x + i + 8, STATE_Y + 8); printf("■"); gotoxy(x + i + 8, STATE_Y + 9); printf("■"); gotoxy(x + i + 8, STATE_Y + 10); printf("■");
				i++;
			}

		}

	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (7 << 4));
		if (cnt == 8) {
			gotoxy(34, STATE_Y + 6); printf("■"); gotoxy(34, STATE_Y + 7); printf("■");
			gotoxy(34, STATE_Y + 8); printf("■"); gotoxy(34, STATE_Y + 9); printf("■"); gotoxy(34, STATE_Y + 10); printf("■");
			gotoxy(35, STATE_Y + 5); printf("■"); gotoxy(35, STATE_Y + 6); printf("■"); gotoxy(35, STATE_Y + 7); printf("■");
			gotoxy(35, STATE_Y + 8); printf("■"); gotoxy(35, STATE_Y + 9); printf("■"); gotoxy(35, STATE_Y + 10); printf("■");
		}
		else if (cnt == 9) {

			gotoxy(36, STATE_Y + 4); printf("■"); gotoxy(36, STATE_Y + 5); printf("■");
			gotoxy(36, STATE_Y + 6); printf("■"); gotoxy(36, STATE_Y + 7); printf("■");
			gotoxy(36, STATE_Y + 8); printf("■"); gotoxy(36, STATE_Y + 9); printf("■"); gotoxy(36, STATE_Y + 10); printf("■");
			gotoxy(37, STATE_Y + 3); printf("■"); gotoxy(37, STATE_Y + 4); printf("■"); gotoxy(37, STATE_Y + 5); printf("■");
			gotoxy(37, STATE_Y + 6); printf("■"); gotoxy(37, STATE_Y + 7); printf("■");
			gotoxy(37, STATE_Y + 8); printf("■"); gotoxy(37, STATE_Y + 9); printf("■"); gotoxy(37, STATE_Y + 10); printf("■");
		}
		else if (cnt == 10) {
			gotoxy(38, STATE_Y + 2); printf("■"); gotoxy(38, STATE_Y + 3); printf("■"); gotoxy(38, STATE_Y + 4); printf("■"); gotoxy(38, STATE_Y + 5); printf("■");
			gotoxy(38, STATE_Y + 6); printf("■"); gotoxy(38, STATE_Y + 7); printf("■");
			gotoxy(38, STATE_Y + 8); printf("■"); gotoxy(38, STATE_Y + 9); printf("■"); gotoxy(38, STATE_Y + 10); printf("■");
			gotoxy(39, STATE_Y + 1); printf("■"); gotoxy(39, STATE_Y + 2); printf("■"); gotoxy(39, STATE_Y + 3); printf("■"); gotoxy(39, STATE_Y + 4); printf("■"); gotoxy(39, STATE_Y + 5); printf("■");
			gotoxy(39, STATE_Y + 6); printf("■"); gotoxy(39, STATE_Y + 7); printf("■");
			gotoxy(39, STATE_Y + 8); printf("■"); gotoxy(39, STATE_Y + 9); printf("■"); gotoxy(39, STATE_Y + 10); printf("■");
			gotoxy(40, STATE_Y + 0); printf("■"); gotoxy(40, STATE_Y + 1); printf("■"); gotoxy(40, STATE_Y + 2); printf("■"); gotoxy(40, STATE_Y + 3); printf("■"); gotoxy(40, STATE_Y + 4); printf("■");
			gotoxy(40, STATE_Y + 5); printf("■"); gotoxy(40, STATE_Y + 6); printf("■"); gotoxy(40, STATE_Y + 7); printf("■");
			gotoxy(40, STATE_Y + 8); printf("■"); gotoxy(40, STATE_Y + 9); printf("■"); gotoxy(40, STATE_Y + 10); printf("■");
		}
		else {
			for (j = 0; j < 5; j++) {
				gotoxy(x + i + 1, STATE_Y + 6); printf("■"); gotoxy(x + i + 1, STATE_Y + 7); printf("■");
				gotoxy(x + i + 1, STATE_Y + 8); printf("■"); gotoxy(x + i + 1, STATE_Y + 9); printf("■"); gotoxy(x + i + 1, STATE_Y + 10); printf("■");
				i++;
			}
		}
	}




	color(7);
}

void draw_cf(void) {
	if (combo) { //줄 삭제가 있는 경우 점수와 레벨 목표를 새로 표시함 
		if (combo == 1) {
			ComboType = 1;
			draw_combo();
			Sleep(300);
		}
		if (combo == 2) {
			ComboType = 2;
			draw_combo();
			Sleep(300);
		}
		if (combo == 3) {
			ComboType = 3;
			draw_combo();
			Sleep(300);
		}
		if (combo == 4) {
			ComboType = 4;
			draw_combo();
			Sleep(300);
		}
	}
	if (ComboType != 0) {
		ComboType = 0;
		combo = 0;
		draw_combo();
	}
}

void SendMsg(char* msg, int len) {

	send(serversock, msg, len, 0);
}

unsigned WINAPI RecvMsg(void* arg) {
	SOCKET sock = *((SOCKET*)arg);//서버용 소켓을 전달한다.
	int strLen;
	while (1) {//반복
		strLen = recv(sock, nameMsg, 100, 0);//서버로부터 메시지를 수신한다.
		if (strLen == -1)
			return -1;
		nameMsg[strLen] = 0;//문자열의 끝을 알리기 위해 설정
		if (strstr(nameMsg, "GAMEOVER")) {
			GAMEOVER = true;
		}
		if (strstr(nameMsg, "SEQUNCE")) {
			char* resultstr;
			if (strstr(nameMsg, "SEQUNCE1")) {
				resultstr = strtok(nameMsg, ":");
				sprintf(seq[0], "%s", resultstr);
				usercnt++;
			}
			else if (strstr(nameMsg, "SEQUNCE2")) {
				resultstr = strtok(nameMsg, ":");
				sprintf(seq[0], "%s", resultstr);
				resultstr = strtok(NULL, " ");
				sprintf(seq[1], "%s", resultstr);
				usercnt++;
			}
			else if (strstr(nameMsg, "SEQUNCE3")) {
				resultstr = strtok(nameMsg, ":");
				sprintf(seq[0], "%s", resultstr);
				resultstr = strtok(NULL, ":");
				sprintf(seq[1], "%s", resultstr);
				resultstr = strtok(NULL, ":");
				sprintf(seq[2], "%s", resultstr);
				usercnt++;
			}
			else if (strstr(nameMsg, "SEQUNCE4")) {
				resultstr = strtok(nameMsg, ":");
				sprintf(seq[0], "%s", resultstr);
				resultstr = strtok(NULL, ":");
				sprintf(seq[1], "%s", resultstr);
				resultstr = strtok(NULL, ":");
				sprintf(seq[2], "%s", resultstr);
				resultstr = strtok(NULL, ":");
				sprintf(seq[3], "%s", resultstr);
				usercnt++;
			}

		}
		if (strstr(nameMsg, "RESORT")) {
			char* resultstr;
			/*for (int i = 0; i < 4; i++) {
			sprintf(seq[i], "\0");
			}*/
			if (strstr(nameMsg, "RESORT1")) {
				resultstr = strtok(nameMsg, ":");
				sprintf(seq[0], "%s", resultstr);
				sprintf(seq[1], "\0");
				nowuser--;
				usercnt--;
			}
			else if (strstr(nameMsg, "RESORT2")) {
				resultstr = strtok(nameMsg, ":");
				sprintf(seq[0], "%s", resultstr);
				resultstr = strtok(NULL, " ");
				sprintf(seq[1], "%s", resultstr);
				sprintf(seq[2], "\0");
				nowuser--;
				usercnt--;
			}
			else if (strstr(nameMsg, "RESORT3")) {
				resultstr = strtok(nameMsg, ":");
				sprintf(seq[0], "%s", resultstr);
				resultstr = strtok(NULL, ":");
				sprintf(seq[1], "%s", resultstr);
				resultstr = strtok(NULL, ":");
				sprintf(seq[2], "%s", resultstr);
				sprintf(seq[3], "%s", "\0");
				nowuser--;
				usercnt--;
			}
		}
		if (strstr(nameMsg, "ALLSCORE")) {
			char* resultstr;
			resultstr = strtok(nameMsg, ":");
			seq_cnt[4][0] = atoi(resultstr);
		}
		if (strstr(nameMsg, "SYSTEMCNT")) {
			char* resultstr;
			if (strstr(nameMsg, seq[0])) {
				resultstr = strtok(nameMsg, ":");
				seq_cnt[0][0] = atoi(resultstr);
			}
			else if (strstr(nameMsg, seq[1])) {
				resultstr = strtok(nameMsg, ":");
				seq_cnt[1][0] = atoi(resultstr);
			}
			else if (strstr(nameMsg, seq[2])) {
				resultstr = strtok(nameMsg, ":");
				seq_cnt[2][0] = atoi(resultstr);
			}
			else if (strstr(nameMsg, seq[3])) {
				resultstr = strtok(nameMsg, ":");
				seq_cnt[3][0] = atoi(resultstr);
			}
		}
		if (strstr(nameMsg, "CRCNT")) {
			char* resultstr;
			resultstr = strtok(nameMsg, ":");
			clearcnt = atoi(resultstr);
		}
		if (strstr(nameMsg, "NEXTROUND")) {
			nextrnd = 1;

		}
		if (ROUND == 1) {


			if (strstr(nameMsg, "LIGHTON")) {
				if (strstr(nameMsg, NAME)) {
					LIGHT = 1;
					PrisonType = 1;

				}
				if (strstr(nameMsg, seq[0])) {
					statustype = 0;
				}
				else if (strstr(nameMsg, seq[1]) && seq[1] != NULL) {
					statustype = 1;
				}
				else if (strstr(nameMsg, seq[2]) && seq[2] != NULL) {
					statustype = 2;
				}
				else {
					statustype = 3;
				}
			}
			if (strstr(nameMsg, "LIGHTOFF")) {
				if (strstr(nameMsg, NAME)) {
					LIGHT = 0;
					PrisonType = 0;

				}
			}
		}
		if (ROUND == 2) {
			if (strstr(nameMsg, "THUNDERON")) {
				thunderType = 1;
				THUNDER = 1;
			}
			if (strstr(nameMsg, "THUNDEROFF")) {
				thunderType = 0;
				THUNDER = 0;

			}
		}
	}
	return 0;
}

void draw_storyboard(void) {

	int i, j, z, x = 16;
	color(7);
	system("mode con:cols=84 lines=43");
	for (z = 0; z < 34; z = z + 14) {
		for (i = 0; i < NEXT_X; i++) {
			bot_org[1][i] = WALL;
		}
		for (i = 0; i < BOT_Y; i++) { //좌우 벽을 만듦  
			bot_org[i][0] = WALL;
			bot_org[i][NEXT_X - 1] = WALL;
		}
		for (j = 0; j < NEXT_X; j++) { //바닥벽을 만듦 
			bot_org[BOT_Y - 1][j] = WALL;
		}
		for (i = 1; i < BOT_Y; i++) {
			for (j = 0; j < NEXT_X; j++) {

				gotoxy(NEXT_X_ADJ + j, i + z);
				switch (bot_org[i][j]) {
				case WALL: //벽모양 
					printf("▩");
					break;

				}
			}
		}
	}
	Sleep(500);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 | (15 << 4));
	gotoxy(NEXT_X_ADJ + 8, 2); printf("■■■■■■");
	gotoxy(NEXT_X_ADJ + 8, 3); printf("■■■■■■");
	gotoxy(NEXT_X_ADJ + 8, 4); printf("■■■■■■");
	gotoxy(NEXT_X_ADJ + 8, 5); printf("■■■■■■");
	gotoxy(NEXT_X_ADJ + 8, 6); printf("■■■■■■");
	gotoxy(NEXT_X_ADJ + 9, 7); printf("■■■■■");
	gotoxy(NEXT_X_ADJ + 15, 2); printf("■■");
	gotoxy(NEXT_X_ADJ + 15, 3); printf("■■■");
	gotoxy(NEXT_X_ADJ + 16, 4); printf("■");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 | (8 << 4));
	gotoxy(NEXT_X_ADJ + 7, 6); printf("■"); gotoxy(NEXT_X_ADJ + 14, 6); printf("■");
	gotoxy(NEXT_X_ADJ + 5, 7); printf("■■■■"); gotoxy(NEXT_X_ADJ + 13, 7); printf("■■");
	gotoxy(NEXT_X_ADJ + 3, 8); printf("■■■■■■■■■■■■");
	gotoxy(NEXT_X_ADJ + 1, 9); printf("■■■■■■■■■■■■■■");
	gotoxy(NEXT_X_ADJ + 1, 10); printf("■■■■■■■■■■■■■■");
	gotoxy(NEXT_X_ADJ + 1, 11); printf("■■■■■■■■■■■■■■");
	gotoxy(NEXT_X_ADJ + 1, 12); printf("■■■■■■■■■■■■■■");
	gotoxy(NEXT_X_ADJ + 18, 3); printf("■");
	gotoxy(NEXT_X_ADJ + 17, 4); printf("■■■"); gotoxy(NEXT_X_ADJ + 16, 5); printf("■■■■■");
	gotoxy(NEXT_X_ADJ + 16, 6); printf("■■■■■■"); gotoxy(NEXT_X_ADJ + 16, 7); printf("■■■■■");
	gotoxy(NEXT_X_ADJ + 16, 8); printf("■■■■"); gotoxy(NEXT_X_ADJ + 16, 9); printf("■■■");
	gotoxy(NEXT_X_ADJ + 16, 10); printf("■■"); gotoxy(NEXT_X_ADJ + 16, 11); printf("■");
	color(7);
	Sleep(500); gotoxy(NEXT_X_ADJ + 28, 6); printf("저벅...."); Sleep(500); gotoxy(NEXT_X_ADJ + 32, 9); printf("저벅....");
	Sleep(500); gotoxy(NEXT_X_ADJ + 28, 6); printf("        "); Sleep(500); gotoxy(NEXT_X_ADJ + 32, 9); printf("        ");
	while (1) {
		Sleep(500); gotoxy(NEXT_X_ADJ + 28, 6); printf("야"); Sleep(500); printf(" 야"); Sleep(1000); printf(" 갔냐??");
		Sleep(2100); gotoxy(NEXT_X_ADJ + 28, 8); printf("땅파자"); Sleep(500);
		break;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 | (8 << 4));
	gotoxy(NEXT_X_ADJ + 1, x); printf("■■■■■■■■■■■■■■■■■■■■■■");
	for (i = 1; i < 10; i++) {
		for (j = 1; j < 24; j = j + 4) {
			gotoxy(NEXT_X_ADJ + j, x + i); printf("■■");
		}
	}
	gotoxy(NEXT_X_ADJ + 1, x + 10); printf("■■■■■■■■■■■■■■■■■■■■■■");

	color(7);
	Sleep(500); gotoxy(NEXT_X_ADJ + 24, x + 3); printf("조금 있다 다시 순찰 돌꺼야");	Sleep(500); gotoxy(NEXT_X_ADJ + 24, x + 5); printf("그때 아무것도 하지마.."); Sleep(500); gotoxy(NEXT_X_ADJ + 24, x + 7); printf("그럼 다 걸려");
	Sleep(500);
	for (i = 0; i < 23; i++) {
		for (j = 0; j < 11; j++) {
			gotoxy(NEXT_X_ADJ + 1 + i, 2 * x - 2 + j);
			switch (prison_org[0][j][i]) {
			case EMPTY: //빈칸모양 
				printf("  ");
				break;
			case 1: //굳은 블럭 모양  
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (7 << 4));
				printf("■");
				color(7);
				break;
			case 2: //움직이고있는 블럭 모양  
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14 | (14 << 4));
				printf("■");
				color(7);
				break;
			}
		}
	}
	Sleep(500); gotoxy(NEXT_X_ADJ + 26, 2 * x + 2); printf("이때 열심히 움직여서"); Sleep(500); gotoxy(NEXT_X_ADJ + 26, 2 * x + 4); printf("땅을 팔수 있어"); Sleep(1000);
	for (i = 0; i < 23; i++) {
		for (j = 0; j < 11; j++) {
			gotoxy(NEXT_X_ADJ + 1 + i, 2 * x - 2 + j);
			switch (prison_org[1][j][i]) {
			case EMPTY: //빈칸모양 
				printf("  ");
				break;
			case 1: //굳은 블럭 모양  
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (7 << 4));
				printf("■");
				color(7);
				break;
			case 2: //움직이고있는 블럭 모양  
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14 | (14 << 4));
				printf("■");
				color(7);
				break;
			}
		}
	}
	Sleep(500); gotoxy(NEXT_X_ADJ + 26, 2 * x + 2); printf("이때 움직이면 다 걸려"); Sleep(500); gotoxy(NEXT_X_ADJ + 26, 2 * x + 4); printf("알겠어??     ");
	Sleep(500); gotoxy(NEXT_X_ADJ + 26, 2 * x + 2); printf("                     "); gotoxy(NEXT_X_ADJ + 26, 2 * x + 4); printf("         ");
	gotoxy(NEXT_X_ADJ + 26, 2 * x + 3); printf("가자 밖으로 !!!!");
	Sleep(1000);

	system("cls");
}

void draw_realending(void) {
	int x = 5, y = 10;
	int i, j, z, count = 0;
	system("cls");
	system("mode con:cols=84 lines=49");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 | (8 << 4));
	gotoxy(11, 1); printf("                                       ");
	gotoxy(7, 2); printf("                                                        ");
	gotoxy(6, 3); printf("                                                            ");
	gotoxy(6, 4); printf("                                                            ");
	gotoxy(5, 5); printf("                                                               ");
	gotoxy(5, 6); printf("                                                               ");
	gotoxy(5, 7); printf("                                                               ");
	gotoxy(4, 8); printf("                                                                   ");
	gotoxy(3, 9); printf("                                                                       ");
	gotoxy(2, 10); printf("                                                                           ");
	gotoxy(3, 11); printf("                                                                         ");
	gotoxy(4, 12); printf("                                                                       ");
	gotoxy(2, 13); printf("                                                                          ");
	gotoxy(2, 14); printf("                                                                           ");
	gotoxy(3, 15); printf("                                                                          ");
	gotoxy(2, 16); printf("                                                                           ");
	gotoxy(3, 17); printf("                                                                        ");
	gotoxy(2, 18); printf("                                                                           ");
	gotoxy(2, 19); printf("                                                                           ");
	gotoxy(3, 20); printf("                                                                         ");
	gotoxy(2, 21); printf("                                                                           ");
	gotoxy(3, 22); printf("                                                                       ");
	gotoxy(4, 23); printf("                                                                      ");
	gotoxy(2, 24); printf("                                                                        ");
	gotoxy(3, 25); printf("                                                                    ");
	gotoxy(4, 26); printf("                                                              ");
	gotoxy(5, 27); printf("                                                                ");
	gotoxy(3, 28); printf("                                                              ");
	gotoxy(5, 29); printf("                                                           ");
	gotoxy(4, 30); printf("                                                              ");
	gotoxy(4, 31); printf("                                                                ");
	gotoxy(3, 32); printf("                                                             ");
	gotoxy(4, 33); printf("                                                        ");
	gotoxy(5, 34); printf("                                                       ");
	gotoxy(8, 35); printf("                                            ");
	gotoxy(9, 36); printf("                                        ");
	gotoxy(11, 37); printf("                                ");
	gotoxy(12, 38); printf("                        ");


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 | (4 << 4));
	gotoxy(x, 3); printf("■■■■");	gotoxy(x, 4); printf("■"); gotoxy(x + 3, 4); printf("■");	gotoxy(x, 5); printf("■"); gotoxy(x + 3, 5); printf("■");
	gotoxy(x, 6); printf("■■■■");	gotoxy(x + 6, 2); printf("■");	gotoxy(x + 6, 3); printf("■");	gotoxy(x + 6, 4); printf("■");	gotoxy(x + 5, 5); printf("■■");
	gotoxy(x + 6, 6); printf("■");	gotoxy(x + 6, 7); printf("■");	gotoxy(x + 6, 8); printf("■");//머
	gotoxy(x + 12, 2); printf("■"); gotoxy(x + 15, 2); printf("■");	gotoxy(x + 11, 3); printf("■■■"); gotoxy(x + 15, 3); printf("■");	gotoxy(x + 15, 4); printf("■"); gotoxy(x + 15, 5); printf("■■");
	gotoxy(x + 11, 5); printf("■■■"); gotoxy(x + 15, 6); printf("■");	gotoxy(x + 11, 6); printf("■"); gotoxy(x + 13, 6); printf("■");
	gotoxy(x + 11, 7); printf("■■■"); gotoxy(x + 15, 7); printf("■");	 gotoxy(x + 15, 8); printf("■");//하
	gotoxy(x + 21, 2); printf("■"); gotoxy(x + 21, 3); printf("■"); gotoxy(x + 21, 4); printf("■■■■■");
	gotoxy(x + 20, 6); printf("■■■■■■■"); gotoxy(x + 23, 7); printf("■"); gotoxy(x + 23, 8); printf("■");//누
	gotoxy(x + 27, 2); printf("■■■■■"); gotoxy(x + 31, 3); printf("■"); gotoxy(x + 31, 4); printf("■"); gotoxy(x + 29, 5); printf("■■■"); gotoxy(x + 29, 6); printf("■"); gotoxy(x + 29, 8); printf("■");

	color(7);
	gotoxy(x + 4, y); printf("■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(x + 4, 1 + y); printf("■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(x + 2, 2 + y); printf("■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(x + 1, 3 + y); printf("■  ■■■■■■■■■■■■■■■■■■■■■■  ■");
	gotoxy(x + 1, 4 + y); printf("■    ■■■■■■■■■■■■■■■■■■■■    ■■");
	gotoxy(x + 2, 5 + y); printf("■    ■■■■■■■■■■■■■■■■■     ■■■■");
	gotoxy(x + 3, 6 + y); printf("■                                      ■■■■■■");
	gotoxy(x + 1, 7 + y); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(x, 8 + y); printf("■      ■■                                        ■■■■■");
	gotoxy(x, 9 + y); printf("■  ■  ■    ■■■              ■■■■          ■■■    ■");
	gotoxy(x, 10 + y); printf("■  ■  ■  ■      ■          ■        ■        ■■■■    ■");
	gotoxy(x, 11 + y); printf("■      ■  ■  ■  ■          ■    ■  ■        ■■■  ■  ■");
	gotoxy(x, 12 + y); printf("■    ■    ■  ■  ■          ■    ■  ■        ■■    ■  ■");
	gotoxy(x + 1, 13 + y); printf("■■      ■      ■          ■    ■  ■        ■    ■    ■");
	gotoxy(x + 1, 14 + y); printf("■          ■■■            ■        ■          ■      ■");
	gotoxy(x + 1, 15 + y); printf("■                  ■■■■    ■■■■            ■    ■");
	gotoxy(x + 1, 16 + y); printf("■            ■    ■■■■                        ■  ■");
	gotoxy(x + 2, 17 + y); printf("■        ■                    ■              ■■■");
	gotoxy(x + 2, 18 + y); printf("■          ■■■■■■■■■■■■            ■");
	gotoxy(x + 3, 19 + y); printf("■          ■              ■    ■        ■");
	gotoxy(x + 4, 20 + y); printf("■        ■            ■              ■");
	gotoxy(x + 5, 21 + y); printf("■■  ■  ■■■■■■    ■    ■■■");
	gotoxy(x + 7, 22 + y); printf("■■                  ■■■");
	gotoxy(x + 9, 23 + y); printf("■■■■■■■■■■");
	gotoxy(x + 8, 24 + y); printf("■  ■    ■      ■  ■");
	gotoxy(x + 7, 25 + y); printf("■  ■      ■■  ■      ■");
	gotoxy(x + 6, 26 + y); printf("■      ■■■    ■          ■");
	gotoxy(x + 5, 27 + y); printf("■      ■  ■               ■■■");
	gotoxy(x + 5, 28 + y); printf("■      ■    ■             ■  ■");

	for (i = 0; i < NEXT_X; i++) {
		bots_org[1][i] = WALL;
	}
	for (i = 0; i < BOT_Y - 4; i++) { //좌우 벽을 만듦  
		bots_org[i][0] = WALL;
		bots_org[i][NEXT_X - 1] = WALL;
	}
	for (j = 0; j < NEXT_X; j++) { //바닥벽을 만듦 
		bots_org[BOT_Y - 5][j] = WALL;
	}
	for (i = 1; i < BOT_Y - 4; i++) {
		for (j = 0; j < NEXT_X; j++) {

			gotoxy(NEXT_X_ADJ + j, i + 38);
			switch (bots_org[i][j]) {
			case WALL: //벽모양 
				printf("▩");
				break;

			}
		}
	}
	gotoxy(5, 40); printf("끝이다 끝이라고 끝이야ㅓㄻ;ㅣㅑㄴ 렁ㄴ미ㅏ; 러ㅏㅣ;ㅇㄴ머 리ㅏ;ㅇㄴㅁ");
	char msg[30];
	sprintf(msg, "ENDGAME");
	int len = *msg;
	SendMsg(msg, len);

	system("cls");
	exit(0);
}
void draw_thunder(void) {
	int y = 2;
	int x = 8;
	int i, j;
	for (i = 0; i < 23; i++) {
		for (j = 0; j < 11; j++) {
			gotoxy(STATUS_X_ADJ + 1 + i, 18 + j); printf("  ");
		}
	}

	if (thunderType == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | (0 << 4));

		gotoxy(STATUS_X_ADJ + 4 + x, 18 + y); printf("■");
		gotoxy(STATUS_X_ADJ + 3 + x, 19 + y); printf("■■");
		gotoxy(STATUS_X_ADJ + 2 + x, 20 + y); printf("■■■");
		gotoxy(STATUS_X_ADJ + 1 + x, 21 + y); printf("■■■■■");
		gotoxy(STATUS_X_ADJ + 2 + x, 22 + y); printf("■■■■■");
		gotoxy(STATUS_X_ADJ + 3 + x, 23 + y); printf("■■■");
		gotoxy(STATUS_X_ADJ + 3 + x, 24 + y); printf("■■");
		gotoxy(STATUS_X_ADJ + 3 + x, 25 + y); printf("■");
		gotoxy(STATUS_X_ADJ + 3 + x, 25 + y); printf("■");
	}
	else if (thunderType == 1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14 | (14 << 4));
		gotoxy(STATUS_X_ADJ + 4 + x, 18 + y); printf("■");
		gotoxy(STATUS_X_ADJ + 3 + x, 19 + y); printf("■■");
		gotoxy(STATUS_X_ADJ + 2 + x, 20 + y); printf("■■■");
		gotoxy(STATUS_X_ADJ + 1 + x, 21 + y); printf("■■■■■");
		gotoxy(STATUS_X_ADJ + 2 + x, 22 + y); printf("■■■■■");
		gotoxy(STATUS_X_ADJ + 3 + x, 23 + y); printf("■■■");
		gotoxy(STATUS_X_ADJ + 3 + x, 24 + y); printf("■■");
		gotoxy(STATUS_X_ADJ + 3 + x, 25 + y); printf("■");
		gotoxy(STATUS_X_ADJ + 3 + x, 25 + y); printf("■");
	}
	color(7);

}
void playlist(void) { //게임 일시정지 함수 
	int i, j;
	int y = 1;
	int x = 15;
	int n = 10;
	int jcntKey = 0;
	system("cls");
	system("mode con:cols=56 lines=24");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 | (8 << 4));
	gotoxy(2, y); printf("■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(2, y + 1); printf("■");
	gotoxy(2, y + 2); printf("■");
	gotoxy(2, y + 3); printf("■");
	gotoxy(2, y + 4); printf("■");
	gotoxy(2, y + 5); printf("■");
	gotoxy(2, y + 6); printf("■■■■■■■■■■■■■■■■■■■■■■■■");

	gotoxy(2, y + 7); printf("■");	gotoxy(2, y + 8); printf("■");	gotoxy(2, y + 9); printf("■");
	gotoxy(2, y + 10); printf("■"); gotoxy(2, y + 11); printf("■"); gotoxy(2, y + 12); printf("■");
	gotoxy(2, y + 13); printf("■"); gotoxy(2, y + 14); printf("■"); gotoxy(2, y + 15); printf("■");
	gotoxy(2, y + 16); printf("■"); gotoxy(2, y + 17); printf("■"); gotoxy(2, y + 18); printf("■");
	gotoxy(2, y + 19); printf("■"); gotoxy(2, y + 20); printf("■"); gotoxy(25, y + 1); printf("■");
	gotoxy(25, y + 2); printf("■"); gotoxy(25, y + 3); printf("■"); gotoxy(25, y + 4); printf("■");
	gotoxy(25, y + 5); printf("■"); gotoxy(25, y + 6); printf("■"); gotoxy(25, y + 7); printf("■");
	gotoxy(25, y + 8); printf("■"); gotoxy(25, y + 9); printf("■"); gotoxy(25, y + 10); printf("■");
	gotoxy(25, y + 11); printf("■"); gotoxy(25, y + 12); printf("■"); gotoxy(25, y + 13); printf("■");
	gotoxy(25, y + 14); printf("■"); gotoxy(25, y + 15); printf("■"); gotoxy(25, y + 16); printf("■");
	gotoxy(25, y + 17); printf("■"); gotoxy(25, y + 18); printf("■"); gotoxy(25, y + 19); printf("■");
	gotoxy(25, y + 20); printf("■"); gotoxy(2, y + 21); printf("■■■■■■■■■■■■■■■■■■■■■■■■");
	color(7);
	gotoxy(3, y + 1); printf("   ■■■                    ■■■");
	gotoxy(3, y + 2); printf("     ■          ■            ■  ");
	gotoxy(3, y + 3); printf("     ■  ■■■      ■■■    ■    ■■■");
	gotoxy(3, y + 4); printf(" ■  ■  ■  ■  ■  ■  ■    ■    ■  ■");
	gotoxy(3, y + 5); printf(" ■■■  ■■■  ■  ■  ■  ■■■  ■  ■");
	gotoxy(4, y + 9); printf("●");
	gotoxy(4, y + 12); printf("●");
	gotoxy(4, y + 15); printf("●");
	gotoxy(4, y + 18); printf("●");


	/*while (1) {


	gotoxy(10, y + 9);  //gets(inputIp);//여기서부터 값 넣으면 됭


	gotoxy(10, y + 12); //gets(inputport);


	gotoxy(10, y + 15); //gets(inputName);


	gotoxy(10, y + 18);// gets(inputName);

	gotoxy(18, 23); printf("WAITING FOR...%2d", n);
	Sleep(1000);

	n--;
	if (n == 0) break;

	}*/

	//화면 지우고 새로 그림 
	draw_join_borad();
	//jcntKey = getch();
	/*
	//키입력시까지 대기
	if (jcntKey == 49) {
	sprintf(IP, "%s", ip_List[0]);
	system("cls");
	system("mode con:cols=84 lines=45");
	reset_main();
	//char jcntKey = 116;
	color(7);
	}
	else if (jcntKey == 50) {
	sprintf(IP, "%s", ip_List[1]);
	system("cls");
	system("mode con:cols=84 lines=45");
	reset_main();
	//char jcntKey = 116;
	color(7);
	}
	else if (jcntKey == 51) {
	sprintf(IP, "%s", ip_List[2]);
	system("cls");
	system("mode con:cols=84 lines=45");
	reset_main();
	//char jcntKey = 116;
	color(7);
	}
	else if (jcntKey == 52) {
	sprintf(IP, "%s", ip_List[3]);
	system("cls");
	system("mode con:cols=84 lines=45");
	reset_main();
	//char jcntKey = 116;
	color(7);
	}
	else if (jcntKey == 53) {
	playlist();
	}
	else {
	system("cls");
	system("mode con:cols=84 lines=45");
	reset_main();
	//char jcntKey = 116;
	color(7);
	}
	*/
	//system("cls");
	//system("mode con:cols=84 lines=45");
	//reset_main();

	//color(7);
} //끝! 
unsigned WINAPI Udpsend(void) {
	//서버부분

	WSADATA wsaData;
	SOCKET hRecvSock;
	SOCKADDR_IN addr;
	int strLen;
	char buf[BUFFER_SIZE] = { '\0', };
	char* result;
	int i = 0;
	int ducnt = 0;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) /* Load Winsock 2.2 DLL */
		ErrorHandling("WSAStartup() error!");

	hRecvSock = socket(PF_INET, SOCK_DGRAM, 0); /*브로드캐스트를 위한 UDP소켓 생성 */
	if (hRecvSock == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(atoi(PORT));	   /* 브로드캐스트 port 설정 */

	if (bind(hRecvSock, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");


	while (1) {
		ducnt = 0;
		strLen = recvfrom(hRecvSock, buf, BUFFER_SIZE, 0, NULL, 0);
		Sleep(300);

		result = strtok(buf, ":");
		for (int j = 0; j < 4; j++) {
			if (strcmp(ip_List[(j % 4)], result) == 0)
				ducnt++;
			break;
		}
		if (ducnt >= 1)
			continue;
		sprintf(ip_List[(i % 4)], "%s", result);
		for (int j = 0; j < 4; j++) {
			if (strcmp(roomList[(j % 4)], result) == 0)
				break;
		}
		result = strtok(NULL, " ");
		sprintf(roomList[(i % 4)], "%s", result);
		i++;
	}
	closesocket(hRecvSock);
	WSACleanup();
}
void draw_thunderstatus(void) {
	int i, j;




	for (i = 0; i < 13; i++) {
		for (j = 0; j < 7; j++) {
			gotoxy(27 + i, 4 + j);
			switch (ThunderStatus[statustype][j][i]) {
			case EMPTY: //빈칸모양 
				printf("  ");
				break;
			case 1: //굳은 블럭 모양  
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (7 << 4));
				printf("■");
				color(7);
				break;
			case 2: //움직이고있는 블럭 모양  
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14 | (14 << 4));
				printf("■");
				color(7);
				break;
			case 3: //움직이고있는 블럭 모양  
				printf("p");
				color(7);
				break;
			case 4: //움직이고있는 블럭 모양  
				printf("1");
				color(7);
				break;
			case 5: //움직이고있는 블럭 모양  
				printf("2");
				color(7);
				break;
			case 6: //움직이고있는 블럭 모양  
				printf("3");
				color(7);
				break;
			case 7: //움직이고있는 블럭 모양  
				printf("4");
				color(7);
				break;

			}
		}
	}
	color(7);
	if (ROUND == 1) {

		gotoxy(28, 6); printf("%d", score[0]);

		gotoxy(31, 6); printf("%d", score[1]);

		gotoxy(34, 6); printf("%d", score[2]);

		gotoxy(37, 6); printf("%d", score[3]);
		score[0] = seq_cnt[0][0]; score[1] = seq_cnt[1][0]; score[2] = seq_cnt[2][0]; score[3] = seq_cnt[3][0];
	}
}
void draw_listmap() {
	int i, j;
	int y = 1;
	int x = 15;
	int n = 10;

	playlist();
	draw_join_borad();

	jcntKey = _getch(); //키입력시까지 대기	
	if (jcntKey == 49) {
		sprintf(IP, "%s", ip_List[0]);
		//system("cls");
		//system("mode con:cols=84 lines=45");
		//reset_main();
		//char jcntKey = 116;
		//color(7);
	}
	else if (jcntKey == 50) {
		sprintf(IP, "%s", ip_List[1]);
		//system("cls");
		//system("mode con:cols=84 lines=45");
		//reset_main();
		//char jcntKey = 116;
		//color(7);
	}
	else if (jcntKey == 51) {
		sprintf(IP, "%s", ip_List[2]);
		//system("cls");
		//system("mode con:cols=84 lines=45");
		//reset_main();
		//char jcntKey = 116;
		//color(7);
	}
	else if (jcntKey == 52) {
		sprintf(IP, "%s", ip_List[3]);
		//system("cls");
		//system("mode con:cols=84 lines=45");
		//reset_main();
		//char jcntKey = 116;
		//color(7);
	}
	else if (jcntKey == 53) {
		draw_listmap();
	}
	else {
		//system("cls");
		//system("mode con:cols=84 lines=45");
		//reset_main();
		//char jcntKey = 116;
		//color(7);
	}
}