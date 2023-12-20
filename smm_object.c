//
//  smm_node.c
//  SMMarble
//
//  Created by Juyeop Kim on 2023/11/05.
//

#include "smm_common.h"
#include "smm_object.h"
#include <string.h>

#define MAX_NODETYPE    7
#define MAX_GRADE       9
#define MAX_NODE        100

static char smmNodeName[SMMMODE_TYPE_MAX][MAX_CHARNAME] = 
{
 "lecture",
 "restautant",
 "lab",
 "home",
 "go to lab",
 "food chance",
 "festival"
};

char* smmObj_getTypeName(int type)
{
 return (char*)smmNodeName[type];    
}

/*typedef enum smmObjType
{
        smmObjType_board = 0;
        smmObjType_card,
        smmObjType_grade
        } smmObjType_e;
        
typedef enum smmObjGrade
{
        smmObjGrade_Ap = 0;
        smmObjGrade_A0,
        smmObjGrade_Am,
        smmObjGrade_Bp,
        smmObjGrade_B0,
        smmObjGrade_Bm,
        smmObjGrade_Cp,
        smmObjGrade_C0,
        smmObjGrade_Cm
        } smmObjGrade_e;
*/
// 1. 구조체 배열 변수 정의 
typedef struct smmObject 
{
       char name[MAX_CHARNAME];
       smmObjType_e objType;
       int  type;
       int  credit;   
       int  energy;  
       smmObjGrade_e grade;
} smmObject_t;


//object generation
void* smmObj_genObject(char* name, smmObjType_e objType, int type, int credit, int energy, smmObjGrade_e grade)
{
    smmObject_t *ptr;
    
    ptr = (smmObject_t*)malloc(sizeof(smmObject_t));
    
    strcpy(ptr->name, name);
    ptr->objType = objType;
    ptr->type = type;
    ptr->credit = credit;
    ptr->energy = energy;
    ptr->grade = grade;
    
    return ptr;
}

//12/20 관련함수 변경 
char* smmObj_getNodeName(void* obj)
{
    smmObject_t* ptr = (smmObject_t*)obj;
    return ptr->name;
}

int smmObj_getNodeType(void* Ptr)
{
    smmObject_t* ptr = (smmObject_t*)Ptr;
    return ptr->type;
}

int smmObj_getNodeCredit(void* Ptr)
{
    smmObject_t* ptr = (smmObject_t*)Ptr;
    return ptr->credit;
}

int smmObj_getNodeEnergy(void* Ptr)
{
    smmObject_t* ptr = (smmObject_t*)Ptr;
    return ptr->energy;    
}

int smmObj_getNodeGrade(void* Ptr)
{
    smmObject_t* ptr = (smmObject_t*)Ptr;
    return ptr->grade;    
}

