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
//유형의 문자열 

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
void smmObj_genNode(char* name, int type, int credit, int energy);

//member retrieving
char* smmObj_getNodeName(int node_nr);
int smmObj_getNodeType(int node_nr);

//element to string

char *smmObj_getTypeName();


#endif /* smm_object_h */
