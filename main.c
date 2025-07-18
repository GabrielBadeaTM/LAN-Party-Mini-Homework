#include "lanPartyLib.h"

int main (int argc, char* argv[]) {
    
    FILE * fs1 = fopen(argv[1],"r");
    FILE * fs2 = fopen(argv[2],"r");
    FILE * fs3 = fopen(argv[3],"w");

    int checker = getCheckerId(fs1);
    
    nod * h = createList();
    coada * q;
    nodS * winT = NULL, * losT = NULL;
    bsn * BSTroot = NULL;
    avn * AVLroot = NULL;

    int numarEchipe;
    makeList(h,fs2,&numarEchipe);

    switch (checker){
        case 1:
            printTeamNames(h, fs3);
            delList(h);
            break;   
        case 2:
            PURGE(h,findN(numarEchipe),numarEchipe);
            printTeamNames(h, fs3);
            delList(h);
            break;
        case 3:
            PURGE(h,findN(numarEchipe),numarEchipe);
            printTeamNames(h, fs3);
            fprintf(fs3,"\n");
 
            q = createQ();
            makeBrackets(h,q);
            runTurneu(q,&winT,&losT,fs3,h);
            
            delList(h);
            break;
        case 4:
            PURGE(h,findN(numarEchipe),numarEchipe);
            printTeamNames(h, fs3);
            fprintf(fs3,"\n");

            q = createQ();
            makeBrackets(h,q);
            runTurneu(q,&winT,&losT,fs3,h);

            TOP8(fs3,h,&BSTroot);
            deleteBstSDR(BSTroot);
            break;
        case 5:
            PURGE(h,findN(numarEchipe),numarEchipe);
            printTeamNames(h, fs3);
            fprintf(fs3,"\n");

            q = createQ();
            makeBrackets(h,q);
            runTurneu(q,&winT,&losT,fs3,h);

            TOP8(fs3,h,&BSTroot);
            LEVEL2(&AVLroot,BSTroot, fs3);
            break;
    }
           
    fclose(fs3);
    return 0;
}