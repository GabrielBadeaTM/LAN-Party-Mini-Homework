#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Player {
    char * nume;
    char * prenume;
    int puncte;
};
typedef struct Player player;

struct Echipa {
    int nrPlayeri;
    char * numeEchipa;
    player * jucatori;
    float puncteTotal;
};
typedef struct Echipa echipa;

struct nodLista{
    echipa e;
    struct nodLista * next;
};
typedef struct nodLista nod;

struct nodMeci{
    echipa e1;
    echipa e2;
    struct nodMeci * next;
};
typedef struct nodMeci nodM;

struct Coada{
    nodM *f,  *r;
};
typedef struct Coada coada;

struct nodStiva{
    echipa e;
    struct nodStiva * next;
};
typedef struct nodStiva nodS;

struct bstNod{
    echipa e;
    struct bstNod * left, * rigth;
};
typedef struct bstNod bsn;

struct avlNod{
    int height;
    echipa e;
    struct avlNod * left, * rigth;
};
typedef struct avlNod avn;

player readPlayer(FILE * );
echipa readTeam(FILE * );
void delPlayer(player );
void delTeam(echipa );
void plycpy(player * , player );
void echcpy(echipa * , echipa );

nod * createList();
void addElemFS(nod * , FILE * );
void addElem(nod * , echipa );
void removeNextElem(nod * );
void makeList(nod * ,FILE * , int * );
void delList(nod * );

int findN(int );
int getCheckerId(FILE * );
void printTeamNames(nod * , FILE * );
float makeTeamScore(echipa );
void PURGE(nod * , int , int );

coada * createQ();
void enQ(coada * , echipa , echipa );
void deQ(coada * , echipa * , echipa * );
int qEmpty(coada * );
void makeBrackets(nod * , coada * );

void push(nodS ** , echipa );
echipa pop(nodS ** );
int stEmpty(nodS * );
void emptyStack(nodS ** );
void addPoints(echipa * );
void runPreRound(coada * , nodS ** , nodS ** , int , FILE * );
void runAfterRound(coada * , nodS ** , int , FILE * , int * , nod * );
void runTurneu(coada * , nodS ** , nodS ** , FILE * , nod * );

bsn * newNodeBST(echipa );
bsn * insertBst(bsn * , echipa );
void DRS(bsn * , FILE * );
void TOP8(FILE * , nod * , bsn **);
void deleteBstSDR(bsn * );

avn * newNodeAVL(echipa );
int getHeight(avn * );
int balance(avn * );
int maxI(int  , int );
avn * LL(avn * );
avn * RR(avn * );
avn * LR(avn * );
avn * RL(avn * );
avn * insertAvl(avn * , echipa _);
void printLevel(avn * , int , FILE * );
void DRSbstInsAvl (avn ** ,bsn * );
void deleteAvlSDR(avn * );
void LEVEL2(avn ** , bsn * , FILE * );