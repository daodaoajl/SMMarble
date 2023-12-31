//
//  smm_object.h
//  SMMarble object
//
//  Created by Juyeop Kim on 2023/11/05.
//

#ifndef smm_object_h
#define smm_object_h

#define SMMMODE_TYPE_LECTURE            0
#define SMMMODE_TYPE_RESTAURNAT         1
#define SMMMODE_TYPE_LABORATORY         2
#define SMMMODE_TYPE_HOME               3
#define SMMMODE_TYPE_EXPERIMENT         4
#define SMMMODE_TYPE_FOODCHANCE         5
#define SMMMODE_TYPE_FESTIVAL           6

#define SMMMODE_TYPE_MAX                7

#define MAX_GRADE       9
#define MAX_NODE        100
#define MAX_FOOD        14

//������ ���ڿ� 


typedef enum smmObjType
{
        smmObjType_board = 0,
        smmObjType_card,
        smmObjType_grade
        }smmObjType_e;
        
typedef enum smmObjGrade
{
        smmObjGrade_Ap = 0,
        smmObjGrade_A0,
        smmObjGrade_Am,
        smmObjGrade_Bp,
        smmObjGrade_B0,
        smmObjGrade_Bm,
        smmObjGrade_Cp,
        smmObjGrade_C0,
        smmObjGrade_Cm
        }smmObjGrade_e;

/* node type :
    lecture,
    restaurant,
    laboratory,
    home,
    experiment,
    foodChance,
    festival
*/


/* grade :
    A+,
    A0,
    A-,
    B+,
    B0,
    B-,
    C+,
    C0,
    C-
*/



//object generation
void* smmObj_genObject(char* name, smmObjType_e objType, int type, int credit, int energy, smmObjGrade_e grade);

//member retrieving
char* smmObj_getNodeName(void* obj);//int node_nr -> void* obj ���� ������(12/18) 
int smmObj_getNodeType(void* Ptr);
int smmObj_getNodeCredit(void* Ptr);
int smmObj_getNodeEnergy(void* Ptr);
int smmObj_getNodeGrade(void* Ptr);

//element to string

char* smmObj_getTypeName(int type);


#endif /*smm_object_h*/
