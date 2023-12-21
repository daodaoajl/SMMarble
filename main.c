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
      int average;
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
         
         cur_player[i].average = 0;
         
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

void printPlayerStatus(void)//print all player status at the beginning of each turn
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
    

    if (c == 'g')
        printGrades(player);

    return (rand()%MAX_DIE + 1);
}

/*float calcAverageGrade(int player)//calculate average grade of the player
{
     int i;
     int sum = 0;
     float average = 0;
     void* gradePtr = smmdb_getData(LISTNO_NODE, cur_player[player].average);
     
     for (i=0;i<player;i++)
     {
         sum += ;
         anverage= sum/i
     }    //평균 구하기        
}
*/
/*smmGrade_e takeLecture(int player, char *lectureName, int credit) //take the lecture (insert a grade of the player)
{
           
}
*/
//action code when a player stays at a node
void actionNode(int player)
{
    void* boardPtr = smmdb_getData(LISTNO_NODE, cur_player[player].position);
    // int type = smmObj_getNodeType(cur_player[player].position); 
    int type = smmObj_getNodeType(boardPtr);
    char* name = smmObj_getNodeName(boardPtr);
    void* gradePtr;
    enum smmObjGrade grade;
    grade = rand()%MAX_GRADE;// grade random으로 출력 
    
    switch(type)
    {
        //case lecture:
        case SMMMODE_TYPE_LECTURE:
             //현재 에너지가 소요에너지 이상 존재하고 이전에 듣지 않은 강의이면 수강가능 -> AND 연산이 필요 
             if((cur_player[player].energy >= smmObj_getNodeEnergy(boardPtr))&&(/*(이전에 듣지 않은 강의*/1))
             //printGrades 함수 사용-> printGrade(player) 
             {
                int jod;//join or drop
                char jd[3];
                printf("%s, join or drop?\n",name);
                scanf("%s",&jd);
             
                if(strcmp(jd,"join")==0)
                     {jod = 1;} 
                else if(strcmp(jd,"drop")==-1)
                     {jod = 0;}
                else
                {    printf("%s, join or drop?\n",name);
                     scanf("%s",&jd[3]);
                     fflush(stdin);
                }
                        
                if(jod == 1)//join이라고 대답했을 때 
                {
                       cur_player[player].accumCredit += smmObj_getNodeCredit(boardPtr);
                       cur_player[player].energy -= smmObj_getNodeEnergy(boardPtr);
                       //grade generation                       
                       //smmObj_genObject(char* name, smmObjType_e objType, int type, int credit, int energy, smmObjGrade_e grade) 
                       gradePtr = smmObj_genObject(name, smmObjType_grade, 0, smmObj_getNodeCredit(boardPtr), 0,(smmObjGrade_e)grade);
                       smmdb_addTail(LISTNO_OFFSET_GRADE + player, gradePtr);
                       //printf("%s successfully takes the lecture %s with grade %s(average : %f), remained energy : %i", cur_player[player].name, name, grade,/*average*/0,cur_player[player].energy);
                }// energy가 노드의 energy보다 높을 때 실행 
             }
             else
             {
                printf("you are too hungry to take the lecture %s(remained : %i, required: %i\n)",name,smmObj_getNodeEnergy(boardPtr),cur_player[player].energy);
                fflush(stdin);
             }
             break;  
             
        //case restaurant
        case SMMMODE_TYPE_RESTAURNAT:
             
             cur_player[player].energy += smmObj_getNodeEnergy(boardPtr); 
             //식당의 보충 에너지 만큼 플레이어의 현재 에너지 상태가 더해진다. 
             rolldie(player);
             fflush(stdin);
             break;      
        //case laboratory     
        case SMMMODE_TYPE_LABORATORY:
        //-> 실험 중 상태일 때 주사위를 굴리고 성공 기준 값 이상 나오면 실험이 종료 그렇지 않으면 이동하지 못하고 머무름  
             
             if(type == SMMMODE_TYPE_EXPERIMENT)
             {
                       printf("Experiment time! Let's see if you can satisfy proessor (thereshold : 6)\n");
                       
                       int a; 
                       
                       srand((int)time(NULL));
                       a=rand()%6;
                       a=a+1;//a가 1~6까지의 값중 하나가 생성 된다. 
                       //성공 기준값을 3으로 지정하여 do while문 작성  
                       do
                       {
                              printf("-> Experiment result : %i, Fail T_T %s needs more experiment....\n",a,cur_player[player].name);      
                       } 
                       
                       while(a<3);
                              
                       printf("-> Experiment result : %i, success! %s can exit this lab!\n",a,cur_player[player].name);
                       rolldie(player);//실험실에서 나가기 
              }
              else//실험 상태가 아닐경우 그냥 지나감. 
              {
                       printf("This is not experiment time. You can go through this lab.\n");
                       rolldie(player);
              } 
         
        
             break;
             

        case SMMMODE_TYPE_HOME:
             if(rolldie(player))
             {
                 cur_player[player].energy += smmObj_getNodeEnergy(boardPtr); 
                 //지나갈때 보충 에너지 만큼 더해짐 
             }
             break;
        case SMMMODE_TYPE_EXPERIMENT:
             //실험중 상태로 전환되면서 실험실로 이동한다.
             type =  SMMMODE_TYPE_LABORATORY;

             break;
#if 0
        case SMMMODE_TYPE_FOODCHANCE:
             if(type = SMMMODE_TYPE_RESTAURNAT)
             {
              //음식 카드 중 한장을 뽑고 보충된 에너지를 더함.
              food = rand()%MAX_FOOD;     
              printf("node %i : %s, energy %i\n", i, smmObj_getNodeName(boardObj), smmObj_getNodeEnergy(boardObj)); 
              cur_player[player].energy +=  smmObj_getNodeEnergy(boardObj);              
             }
             break;
        case SMMMODE_TYPE_FESTIVAL:
             //축제 카드 중 한 장을 랜덤으로 골라 미션 수행 
              int fest;
              festival = rand()%MAX_FESTIVAL;                   
              printf("%s\n",smmObj_getNodeName(boardObj)); //축제카드 
              scanf("%s\n", &fest);
             break;
#endif
        default:
            break;            
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
        if(type == SMMMODE_TYPE_HOME)
                initEnergy = energy;
        board_nr++;
    }
    fclose(fp);
    
    for (i = 0;i<board_nr;i++)
    {
        void* boardObj = smmdb_getData(LISTNO_NODE, i);
        
        printf("node %i : %s, %i(%s), credit %i, energy %i\n", i, smmObj_getNodeName(boardObj), smmObj_getNodeType(boardObj), smmObj_getTypeName(smmObj_getNodeType(boardObj)), smmObj_getNodeCredit(boardObj), smmObj_getNodeEnergy(boardObj));
    
    //printf("(%s)", smmOhj_getTypeName(SMMMODE_TYPE_LECTURE)); 
    }
    printf("Total number of board nodes : %i\n", board_nr);
    
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
    for (i = 0;i<food_nr;i++)
    {
        void* boardObj = smmdb_getData(LISTNO_FOODCARD, i);
        
        printf("node %i : %s, energy %i\n", i, smmObj_getNodeName(boardObj), smmObj_getNodeEnergy(boardObj));
    
    //printf("(%s)", smmOhj_getTypeName(SMMMODE_TYPE_LECTURE)); 
    }
    printf("Total number of food cards : %i\n", food_nr);
    

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
    for (i = 0;i<festival_nr;i++)
    {
        void* boardObj = smmdb_getData(LISTNO_FESTCARD, i);
        
        printf("node %i : %s\n", i, smmObj_getNodeName(boardObj));
    
    //printf("(%s)", smmOhj_getTypeName(SMMMODE_TYPE_LECTURE)); 
    }
    printf("Total number of festival cards : %i\n", festival_nr);
  
    //game start
    // Sookmyung Marble!! Let's Graduate (total credit : 30)!!
    printf("\n\n\n---------------------------------------------------------------------\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("       Sookmyung Marble!! Let's Graduate (total credit : 30)!!       \n");  
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("---------------------------------------------------------------------\n");
  
    //2. Player configuration ---------------------------------------------------------------------------------

    
    do
    {
        //input player number to player_nr
        printf("\n\ninput player no.:");
        scanf("%d", &player_nr);
        fflush(stdin);
    }
    while ((player_nr<0) || (player_nr > MAX_PLAYER));
    
    cur_player = (player_t*)malloc(player_nr*sizeof(player_t));
    
   
    generatePlayers(player_nr, initEnergy);
    
     
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

