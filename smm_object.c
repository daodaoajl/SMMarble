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

static char smmNodeName[SMMMODE_TYPE_MAX][]
{
 "lecture"
 "restautant"
 "lab"
 "home"
 "go to lab"
 "food chance"
 "festival"
};

char smmObj_getTypeName(int Type)
{
 return smmNodeName[type];    
}
#if 0
//11/30 -> 기존 배열의 구조체 화 
static char smmObj_name[MAX_NODE][MAX_CHARNAME];
static int smmObj_type[MAX_NODE];
static int smmObj_credit[MAX_NODE];
static int smmObj_energy[MAX_NODE];
static int smmObj_noNode=0;
#endif
//컴파일 되지 않음

// 1. 구조체 배열 변수 정의 
struct smmObject 
{
       char name[MAX_CHARNAME];
       int  type;
       int  credit;   
       int  energy;  
};
//

//2. 구조체 배열 변수 정의
struct smmObject smm_node[MAX_NODE];
 



//object generation
void smmObj_genNode(char* name, int type, int credit, int energy)
{
    #if 0 
    strcpy(smmObj_name[smmObj_noNode], name);
    smmObj_type[smmObj_noNode] = type;
    smmObj_credit[smmObj_noNode] = credit;
    smmObj_energy[smmObj_noNode] = energy;
    
    smmObj_noNode++;
    #endif
    //구조체 변경 
    strcpy(smm_node[smmObj_noNode].name, name);
}

char* smmObj_getNodeName(int node_nr)
{
    return smmObj_name[smmObj_noNode];
}

int smmObj_getNodeType(int node_nr)
{
    return smmObj_type[node_nr];
}

#if 0


//member retrieving



//element to string
char* smmObj_getNodeName(smmNode_e type)
{
    return smmNodeName[type];
}

char* smmObj_getGradeName(smmGrade_e grade)
{
    return smmGradeName[grade];
}

#endif
