//
//  main.c
//  SMMarble
//
//  Created by Juyeop Kim on 2023/11/05.
//

#include <time.h>
#include <string.h>
#include "smm_object.h"//헤더 파일 컴파일 해서 디버깅 
#include "smm_database.h"
#include "smm_common.h"

#define BOARDFILEPATH "marbleBoardConfig.txt"
#define FOODFILEPATH "marbleFoodConfig.txt"
#define FESTFILEPATH "marbleFestivalConfig.txt"

#define MAX_PLAYER                  100

//board configuration parameters
static int board_nr;
static int food_nr;
static int festival_nr;
static int player_nr;

// player 변수를 구조체로 정의 
//typedef struct player
typedef struct player
{
      int energy;
      int position;
      char name[MAX_CHARNAME];    
      int accumCredit;
      int flag_graduate;
}player_t; 

static player_t *cur_player; 

//function prototypes
#if 0
int isGraduated(void); //check if any player is graduated
//void generatePlayers(int n, int initEnergy); //generate a new player
//void printGrades(int player); //print grade history of the player
//void goForward(int player, int step); //make player go "step" steps on the board (check if player is graduated)
//void printPlayerStatus(void); //print all player status at the beginning of each turn
float calcAverageGrade(int player); //calculate average grade of the player
smmGrade_e takeLecture(int player, char *lectureName, int credit); //take the lecture (insert a grade of the player)
void* findGrade(int player, char *lectureName); //find the grade from the player's grade history
//void printGrades(int player); //print all the grade history of the player
#endif

void generatePlayers(int n, int initEnergy) //generate a new player
{
     int i;
     //struct player player[n];
     
     //n time loop     
     for(i=0;i<n;i++)
     {
         //input name
         printf("Input player %i's name : ", i);
         scanf("%s", cur_player[i].name);

         fflush(stdin);
         //구조체로 변경                       
         //set position 
         cur_player[i].position = 0;
          
         //set energy
         cur_player[i].energy = initEnergy;
         
         //set accumCredit
         cur_player[i].accumCredit = 0;
         
         //set flag_graduate
         cur_player[i].flag_graduate = 0; 
         
     }     
}

void printGrades(int player)//print grade history of the player
{
     int i;
     void* gradePtr;
     
     for (i=0;i<smmdb_len(LISTNO_OFFSET_GRADE + player);i++)
     {
         gradePtr = smmdb_getData(LISTNO_OFFSET_GRADE + player, i);
         printf("%s : %s\n", smmObj_getNodeName(gradePtr), smmObj_getNodeGrade(gradePtr));
     }     
}

void printPlayerStatus(void)
{
     int i;
     struct player player[player_nr];
     for(i=0;i<player_nr;i++)
     {                       
        printf("%s : credit %i, energy %i, position %i\n",
                   cur_player[i].name,
                   cur_player[i].accumCredit,
                   cur_player[i].energy,
                   cur_player[i].position);
     }  
}

int rolldie(int player)
{
    char c;
    printf(" Press any key to roll a die (press g to see grade): ");
    c = getchar();
    fflush(stdin);
    
#if 0
    if (c == 'g')
        printGrades(player);
#endif
    
    return (rand()%MAX_DIE + 1);
}


//action code when a player stays at a node
void actionNode(int player)
{
    void* boardPtr = smmdb_getData(LISTNO_NODE, cur_player[player].position);
    // int type = smmObj_getNodeType(cur_player[player].position); 
    int type = smmObj_getNodeType(boardPtr);
    char* name = smmObj_getNodeName(boardPtr);
    void* gradePtr;
    
    switch(type)
    {
        //case lecture:
        case SMMMODE_TYPE_LECTURE:
             //현재 에너지가 소요에너지 이상 존재하고 이전에 듣지 않은 강의이면 수강가능 -> AND 연산이 필요 
             if((cur_player[player].energy >= smmObj_getNodeEnergy(boardPtr))&&(/*(이전에 듣지 않은 강의*/1))
             {
                int jod;//join or drop
                char jd[3];
                printf("%s, join of drop?",name);
                scanf("%s",&jd);
             
                if(strcmp(jd,"join")==0)
                     {jod = 1;}
                else if(strcmp(jd,"drop")==-1)
                     {jod = 0;}
                else
                     {scanf("%s",&jd[3]);}
                        
                if(jod == 1)
                {
                       cur_player[player].accumCredit += smmObj_getNodeCredit(boardPtr);
                       cur_player[player].energy -= smmObj_getNodeEnergy(boardPtr);
                       //grade generation
                       //smmObj_genObject(char* name, smmObjType_e objType, int type, int credit, int energy, smmObjGrade_e grade)
                       gradePtr = smmObj_genObject(name, smmObjType_grade, 0, smmObj_getNodeCredit(boardPtr), 0,/*rand함수로 grade 출력값*/0);
                       smmdb_addTail(LISTNO_OFFSET_GRADE + player, gradePtr);
                }// energy가 노드의 energy보다 높을 때 실행 
             else
                 printf("you are too hungry to take the lecture %s(remained : %i, required: %i)",name,smmObj_getNodeEnergy(boardPtr),cur_player[player].energy);
             }
             break;
#if 0   
        //case restaurant
        case SMMMODE_TYPE_RESTAURNAT:
             
             cur_player[player].energy += smmObj_getNodeEnergy(boardPtr);  
             break;
        //case laboratory     
        case SMMMODE_TYPE_LABORATORY:
        //->
             break;
        case SMMMODE_TYPE_HOME:
             if()
             {
                                 
             }
             break;
        case SMMMODE_TYPE_EXPERIMENT:
             if()
             {
                                 
             }
             break;
        case SMMMODE_TYPE_FOODCHANCE:
             if()
             {
                                 
             }
             break;
        case SMMMODE_TYPE_FESTIVAL:
             if()
             {
                                 
             }
             break;
        default:
            break;
#endif            
}
}


void goForward(int player, int step)
{
     void* boardPtr;
     cur_player[player].position += step;
     boardPtr = smmdb_getData(LISTNO_NODE, cur_player[player].position);
     
     printf("%s go to node %i (name: %s)\n",
                cur_player[player].name, cur_player[player].position,
                smmObj_getNodeName(boardPtr));   
}



int main(int argc, const char * argv[]) {
    
    FILE* fp;
    char name[MAX_CHARNAME];
    int type;
    int credit;
    int energy;
    int i;
    int initEnergy;
    int turn = 0;    
    
    board_nr = 0;
    food_nr = 0;
    festival_nr = 0;
    
    
    srand(time(NULL));
    
    
    //1. import parameters ---------------------------------------------------------------------------------
    //1-1. boardConfig 
    if ((fp = fopen(BOARDFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", BOARDFILEPATH);
        getchar();
        return -1;
    }
    
    printf("Reading board component......\n");
    while ( fscanf(fp, "%s %i %i %i", name, &type, &credit, &energy) == 4 ) //read a node parameter set
    {
        //store the parameter set
        void* boardObj; 
        boardObj = smmObj_genObject(name, smmObjType_board, type, credit, energy, 0);
        smmdb_addTail(LISTNO_NODE, boardObj);
        //void value not ignored as it ought to be ??? -
        //smmObj_genObject를 void형이 아닌 void*로 맞추어서 해결 
        if(type == SMMMODE_TYPE_HOME)
                initEnergy = energy;
        board_nr++;
    }
    fclose(fp);
    printf("Total number of board nodes : %i\n", board_nr);
    
    for (i = 0;i<board_nr;i++)
    {
        void* boardObj = smmdb_getData(LISTNO_NODE, i);
        
        printf("node %i : %s, %i(%s), credit %i, energy %i\n", i, smmObj_getNodeName(boardObj), smmObj_getNodeType(boardObj), smmObj_getTypeName(smmObj_getNodeType(boardObj)), smmObj_getNodeCredit(boardObj), smmObj_getNodeEnergy(boardObj));
    
    //printf("(%s)", smmOhj_getTypeName(SMMMODE_TYPE_LECTURE)); 
    }
    
    
    
    //1-2. food card config 
    if ((fp = fopen(FOODFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FOODFILEPATH);
        return -1;
    }
    
    printf("\n\nReading food card component......\n");
    while (fscanf(fp, "%s %i", name, &energy) == 2) //read a food parameter set
    {
        //store the parameter set
        void* boardObj;
        boardObj = smmObj_genObject(name,0,0,0,energy,0);
        smmdb_addTail(LISTNO_FOODCARD,boardObj);
        food_nr++;    
    
    }
    fclose(fp);
    printf("Total number of food cards : %i\n", food_nr);
    for (i = 0;i<food_nr;i++)
    {
        void* boardObj = smmdb_getData(LISTNO_FOODCARD, i);
        
        printf("node %i : %s, energy %i\n", i, smmObj_getNodeName(boardObj), smmObj_getNodeEnergy(boardObj));
    
    //printf("(%s)", smmOhj_getTypeName(SMMMODE_TYPE_LECTURE)); 
    }
    
    

    //1-3. festival card config 
    if ((fp = fopen(FESTFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FESTFILEPATH);
        return -1;
    }
    
    printf("\n\nReading festival card component......\n");
    while (fscanf(fp, "%s", name) == 1) //read a festival card string
    {
        //store the parameter set
        void* boardObj;
        boardObj = smmObj_genObject(name,0, 0, 0, 0, 0);
        smmdb_addTail(LISTNO_FESTCARD,boardObj);
        festival_nr++;    
    }
    fclose(fp);
    printf("Total number of festival cards : %i\n", festival_nr);
    for (i = 0;i<festival_nr;i++)
    {
        void* boardObj = smmdb_getData(LISTNO_FESTCARD, i);
        
        printf("node %i : %s\n", i, smmObj_getNodeName(boardObj));
    
    //printf("(%s)", smmOhj_getTypeName(SMMMODE_TYPE_LECTURE)); 
    }
  
    //2. Player configuration ---------------------------------------------------------------------------------

    
    do
    {
        //input player number to player_nr
        printf("input player no.:");
        scanf("%d", &player_nr);
        fflush(stdin);
    }
    while ((player_nr<0) || (player_nr > MAX_PLAYER));
    
    cur_player = (player_t*)malloc(player_nr*sizeof(player_t));
    
   
    generatePlayers(player_nr, initEnergy);// -> 함수 실행이 안됨. 
    
     
    //3. SM Marble game starts ---------------------------------------------------------------------------------
    while (1) //is anybody graduated?
    {
        int die_result;
        
        //4-1. initial printing
        printPlayerStatus();
        
        //4-2. die rolling (if not in experiment)
        die_result = rolldie(turn);
        
        //4-3. go forward
        goForward(turn, die_result);

		//4-4. take action at the destination node of the board
        actionNode(turn);
        
        //4-5. next turn
        turn = (turn +1)%player_nr;
    }
    
    free(cur_player);
    system("PAUSE");
    return 0;
}
 //player 이름 입력 전 "[ERROR] smmList() : index is larger than length (len:%i, index:%i)\n" 
