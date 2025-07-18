#include "lanPartyLib.h"

//functia care citeste din fisier datele despre un player;
player readPlayer(FILE * fs){
    player p;

    //citeste nume;
    char text[50];
    fscanf(fs,"%s",text);
    p.nume = malloc(sizeof(char) * (strlen(text) + 1));
    strcpy(p.nume,text);

    //citeste prenume;
    fscanf(fs,"%s",text);
    p.prenume = malloc(sizeof(char) * (strlen(text) + 1));
    strcpy(p.prenume,text);

    //citeste puncte;
    fscanf(fs,"%d", &(p.puncte));

    return p;
}

//functia care citeste din fisier datele despre o ehipa;
echipa readTeam(FILE * fs){
    echipa e;
    //citeste nr playeri din echipa
    fscanf(fs, "%d", &(e.nrPlayeri));
    fgetc(fs);

    //citeste nume echipa
    char text[100];
    fgets(text,100,fs);
    text[strlen(text)-2] = '\0';
    if(text[strlen(text) - 1] == ' ') text[strlen(text) - 1] = '\0'; //unele echipe aveau un spatiu la final, asa ca l-am sters;
    e.numeEchipa = malloc(sizeof(char) * (strlen(text) + 1));
    strcpy(e.numeEchipa,text);

    //vector dinamic pt playerii din echipa
    e.jucatori = malloc(e.nrPlayeri * sizeof(player));
    for(int i = 0; i < e.nrPlayeri; i++){
        e.jucatori[i] = readPlayer(fs);
    }

    //calculam punctajul echipei
    e.puncteTotal = makeTeamScore(e);
    return e;
}

//creeaza o lista
nod * createList(){
   nod * head = malloc(sizeof(nod));
   head->next = NULL;
   return head;
}

//adauga in lista o echipa citita din fisier;
void addElemFS(nod * _head, FILE * fs){
    nod * ptr = malloc(sizeof(nod));
    ptr->next = _head->next;
    _head->next = ptr;
    ptr->e = readTeam(fs);
}

//adauga in lista o echipa data ca parametru;
void addElem(nod * _head, echipa _e){
    nod * ptr = malloc(sizeof(nod));
    ptr->next = _head->next;
    _head->next = ptr;
    echcpy(&(ptr->e), _e);
}

//sterge elementul urmator din lista dupa pointerul dat ca parametru
void removeNextElem(nod * ptr){
    if(ptr->next != NULL){
        nod * aux = ptr->next;
        ptr->next = ptr->next->next;
        delTeam(aux->e);
        free(aux);
    }
}

//sterge lista cu totul;
void delList(nod * h){
    while(h->next != NULL){
        removeNextElem(h);
    }
    free(h);
}

//creeaza lista ceruta in problema si inchide fisierul din care se citesc datele;
void makeList(nod * h ,FILE * fs, int * _numarEchipe){
    fscanf(fs,"%d",_numarEchipe);
    for(int i = 0; i < *_numarEchipe; i++){
        addElemFS(h,fs);
    }
    fclose(fs);
}

//afiseaza in fisier numele echipelor;
void printTeamNames(nod * h, FILE * fs){
    h = h->next;
    while(h != NULL){
        fprintf(fs,"%s\n",h->e.numeEchipa);
        h = h->next;
    }
}

//calculeaza si returneaza punctajul echipei;
float makeTeamScore(echipa e){
    float score = 0;
    for(int i = 0; i < e.nrPlayeri; i++){
        score += e.jucatori[i].puncte;
    }
    score/=e.nrPlayeri;
    return score;
}

//gaseste numarul n maxim ca putere a lui 2 mai mica decat nr de jucatori;
int findN(int nrEchipe){
    int n = 1;
    while(n <= nrEchipe){
        n*=2;
    }
    n/=2;
    return n;
}

//elibereaza spatiul alocat pentru un player;
void delPlayer(player p){
    if(p.nume != NULL) free(p.nume);
    if(p.prenume != NULL) free(p.prenume);
}

//elibereaza spatiul alocat pentru o echipa;
void delTeam(echipa e){
    for(int i=0; i< e.nrPlayeri; i++){
        delPlayer(e.jucatori[i]);
    }
    free(e.jucatori);
    free(e.numeEchipa);
}

//sterge din lista echipele cu cel mai mic scor pana raman doar n; mai multe explicatii in readme;
void PURGE(nod * h, int n, int nrEchipe){
    while(nrEchipe > n){
        nod * ptr = h->next;
        nod * ptrDel = h;
        nod * ptrAux = h;

        float pctMin = ptr->e.puncteTotal;

        while(ptr != NULL){
            if(ptr->e.puncteTotal < pctMin){
                pctMin = ptr->e.puncteTotal;
                ptrAux = ptrDel;
            }
            ptr = ptr->next;
            ptrDel = ptrDel->next;
        }

        removeNextElem(ptrAux);
        nrEchipe--;
    }
}

//calculeaza cerinta curenta;
int getCheckerId(FILE * fs){
    int s = 0;
    int x;
    while(!feof(fs)){
        fscanf(fs,"%d",&x);
        s+=x;
    }
    fclose(fs);
    return s;
}

//copiaza profund o structura player in alta;
void plycpy(player * pDest, player pData) {
    //copiaza punctele
    (*pDest).puncte = pData.puncte;

    //copiaza numele
    (*pDest).nume = malloc(sizeof(char)*(strlen(pData.nume) + 1));
    strcpy((*pDest).nume, pData.nume);

    //copiaza prenumele;
    (*pDest).prenume = malloc(sizeof(char)*(strlen(pData.prenume) + 1));
    strcpy((*pDest).prenume, pData.prenume);
}

//copiaza profund o structura echipa in alta; // stiu, bun nume :)
void echcpy(echipa * eDest, echipa eData){
    //copiaza numarul de playeri
    (*eDest).nrPlayeri = eData.nrPlayeri;

    //copiaza punctele totale;
    (*eDest).puncteTotal = eData.puncteTotal;

    //copiaza numele echipei;
    (*eDest).numeEchipa = malloc(sizeof(char)*(strlen(eData.numeEchipa) + 1));
    strcpy((*eDest).numeEchipa, eData.numeEchipa);

    //copiaza toate datele despre fiecare player;
    (*eDest).jucatori = malloc(sizeof(player)*eData.nrPlayeri);
    for (int i = 0; i < eData.nrPlayeri; i++) {
        plycpy(&((*eDest).jucatori[i]), eData.jucatori[i]);
    }
}

//creeaza o coada;
coada * createQ(){
    coada * q;
    q = malloc(sizeof(coada));
    q->f = NULL;
    q->r = NULL;
    return q;
}

void enQ(coada * q, echipa _e1, echipa _e2){
    nodM * newNodPtr = malloc(sizeof(nodM));
    newNodPtr->next = NULL;
    echcpy(&(newNodPtr->e1),_e1);
    echcpy(&(newNodPtr->e2),_e2);

    if(q->f == NULL){
        q->f = newNodPtr;
        q->r = newNodPtr;
    } else {
        q->r->next = newNodPtr;
        q->r = newNodPtr;
    }
}

void deQ(coada * q, echipa * _ec1, echipa * _ec2){
    if(!qEmpty(q)){
        echcpy(&(*_ec1),q->f->e1);
        echcpy(&(*_ec2 ),q->f->e2);
        nodM * aux = q->f;
        q->f = q->f->next;
        delTeam(aux->e1);
        delTeam(aux->e2);
        free(aux);
        if(q->f==NULL) q->r = NULL;
    }
}

//returneaza 1 daca coada e goala;
int qEmpty(coada * q){
    return (q->f == NULL ? 1 : 0);
}

//goleste lista si pune toate valorile din ea in coada;
void makeBrackets(nod * h, coada * q){

    nod * ptr = h->next;
    while(ptr != NULL){
        enQ(q, ptr->e, ptr->next->e);
        ptr = ptr->next->next;
        removeNextElem(h);
        removeNextElem(h);
    }
}

void push(nodS ** t, echipa e){
    nodS * newNodPtr = malloc(sizeof(nodS));
    echcpy(&(newNodPtr->e),e);
    newNodPtr->next = NULL;

    if (*t == NULL) {
        *t = newNodPtr;
    } else {
        newNodPtr->next = *t;
        *t = newNodPtr;
    }
}

echipa pop(nodS ** t){
    if(!stEmpty(*t)){
        nodS * auxNod = (*t);
        echipa auxVal;
        echcpy(&(auxVal),(*t)->e);

        (*t) = (*t)->next;
        delTeam(auxNod->e);
        free(auxNod);
        return auxVal;
    }
}

//returneaza 1 daca stiva e goala;
int stEmpty(nodS * t){
    return(t==NULL?1:0);
}

//adauga cate un punct la fiecare jucator; Recalculeaza punctele echipei;
void addPoints(echipa * e){
    for(int i =0; i< (*e).nrPlayeri; i++){
        (*e).jucatori[i].puncte += 1;
    }
    (*e).puncteTotal = makeTeamScore(*e);
}

//afiseaza cine cu cine se bate, decide castigatorul;
//adauga puncte invingatorilor si pune echipele in stivele corespunzatoare;
void runPreRound(coada * q, nodS ** _winT, nodS ** _losT, int roundNr, FILE * fs){
    echipa e1, e2;

    fprintf(fs,"--- ROUND NO:%d\n",roundNr);
    while(!qEmpty(q)){
        deQ(q,&e1,&e2);
        fprintf(fs,"%-32s - %32s\n",e1.numeEchipa,e2.numeEchipa);

        if(e1.puncteTotal > e2.puncteTotal){
            addPoints(&e1);
            push(_winT, e1);
            push(_losT, e2);
        }else if(e1.puncteTotal <= e2.puncteTotal){
            addPoints(&e2);
            push(_winT, e2);
            push(_losT, e1);
        }

        delTeam(e1);
        delTeam(e2);
    }
    fprintf(fs,"\n");
}

//goleste stiva;
void emptyStack(nodS ** t){
    while(!stEmpty(*t)){
        nodS * auxNod = (*t);
        (*t) = (*t)->next;
        delTeam(auxNod->e);
        free(auxNod);
    }
}

//pune echipele in coada de meciuri, face noua lista cu ultimii 8 si afiseaza clasamentul;
//mai multe explicatii in readme;
void runAfterRound(coada * q, nodS ** _winT, int roundNr, FILE * fs, int * _remaining, nod * h){
    int last8 = (*_remaining == 16)?1:0;
    *_remaining = 0;
    echipa e1 , e2;
    int t = 0;
    fprintf(fs,"WINNERS OF ROUND NO:%d\n",roundNr);
    while(!stEmpty(*_winT)){
        (*_remaining)++;
        switch(t){
            case 0:
                e1 = pop(_winT);
                fprintf(fs,"%-32s  -  %.2f\n",e1.numeEchipa,e1.puncteTotal);
                t = 1; break;
            case 1:
                e2 = pop(_winT);
                fprintf(fs,"%-32s  -  %.2f\n",e2.numeEchipa,e2.puncteTotal);
                enQ(q, e1, e2);
                if(last8){
                    addElem(h,e1);
                    addElem(h,e2);
                }
                delTeam(e1);
                delTeam(e2);
                t = 0; break;
        }
    }

    if(*_remaining == 1) delTeam(e1); 
    else fprintf(fs,"\n");
}

//executa operatiile necesare pentru efectuarea cerintei 3 folosind functiile descrise mai sus;
void runTurneu(coada * q, nodS ** _winT, nodS ** _losT, FILE * _fs, nod * h){
    int runda = 1, remaining = 100;
    while(remaining > 1){
        runPreRound(q,_winT,_losT,runda,_fs);
        emptyStack(_losT);
        runAfterRound(q,_winT,runda,_fs,&remaining, h);
        //emptyStack(_winT);
        runda++;
    }
    free(q);
}

//creeaza un nod bst;
bsn * newNodeBST(echipa _e){
    bsn * newN = malloc(sizeof(bsn));
    echcpy(&(newN->e),_e);
    newN->left = NULL;
    newN->rigth = NULL;
    return newN;
}

bsn * insertBst(bsn * root, echipa _e){
    //daca e null adauga nod;
    if(root == NULL) return newNodeBST(_e);

    //adauga nod conform criteriului;
    if(_e.puncteTotal < (root->e).puncteTotal){
        root->left = insertBst(root->left,_e);
    } else if (_e.puncteTotal > (root->e).puncteTotal){
        root->rigth = insertBst(root->rigth,_e);
    } else { //au accelasi scor
        if(strcmp(_e.numeEchipa,(root->e).numeEchipa) < 0){
            root->left = insertBst(root->left,_e);
        } else {
            root->rigth = insertBst(root->rigth,_e);
        }
    }
    return root;
}

//parcurge un arbore bst in ordine descrescatoare si il afiseaza sub forma ceruta;
void DRS (bsn * root, FILE * fs){
    if(root != NULL){
        DRS(root->rigth, fs);
        fprintf(fs, "%-32s  -  %.2f\n",root->e.numeEchipa,root->e.puncteTotal);
        DRS(root->left, fs);
    }
}

//afiseaza ultimele 8 echipe in ordine descrescatoare, sterge lista;
void TOP8(FILE * fs, nod * h, bsn ** root){
    nod * ptr = h->next;
    while(ptr != NULL){
        *root = insertBst(*root,ptr->e);
        ptr = ptr->next;
    }
    delList(h);
    fprintf(fs,"\nTOP 8 TEAMS:\n");
    DRS(*root, fs);
}

//sterge arborele bst;
void deleteBstSDR(bsn * root){
    if(root != NULL){
        deleteBstSDR(root->left);
        deleteBstSDR(root->rigth);
        delTeam(root->e);
        free(root);
    }
}

//creeaza un nod avl;
avn * newNodeAVL(echipa _e){
    avn * newN = malloc(sizeof(avn));
    echcpy(&(newN->e),_e);
    newN->left = NULL;
    newN->rigth = NULL;
    newN->height = 0;
    return newN;
}

//returneaza inaltimea nodului
int getHeight(avn * _nod){
    if(_nod == NULL) return -1;
    else return _nod->height;
}

//returneaza factorul de echilibru al nodului
int balance(avn * _nod){
    if(_nod == NULL) return 0;
    else return getHeight(_nod->left) - getHeight(_nod->rigth);
}

//functia max;
int maxI(int i , int j){
    return (i>j)?i:j;
}

//rotatii:
avn * LL(avn * z){
    avn * y = z->left;
    avn * t = y->rigth;

    y->rigth = z;
    z->left = t;

    z->height = maxI(getHeight(z->left),getHeight(z->rigth)) + 1;
    y->height = maxI(getHeight(y->left),getHeight(y->rigth)) + 1;

    return y;
}

avn * RR(avn * z){
    avn * y = z->rigth;
    avn * t = y->left;

    y->left = z;
    z->rigth = t;
    
    z->height = maxI(getHeight(z->left),getHeight(z->rigth)) + 1;
    y->height = maxI(getHeight(y->left),getHeight(y->rigth)) + 1;

    return y;
}

avn * LR(avn * z){
    z->left = RR(z->left);
    return LL(z);
}

avn * RL(avn * z){
    z->rigth = LL(z->rigth);
    return RR(z);
}

//functia de inserare in avl;
avn * insertAvl(avn * root, echipa _e){
    //daca e null adauga nod;
    if(root == NULL) return newNodeAVL(_e);

    //adauga un nod conform criteriului;
    if(_e.puncteTotal < (root->e).puncteTotal){
        root->left = insertAvl(root->left,_e);
    } else if (_e.puncteTotal > (root->e).puncteTotal){
        root->rigth = insertAvl(root->rigth,_e);
    } else if (_e.puncteTotal == (root->e).puncteTotal){
        if(strcmp(_e.numeEchipa,(root->e).numeEchipa) < 0){
            root->left = insertAvl(root->left,_e);
        } else {
            root->rigth = insertAvl(root->rigth,_e);
        }
    }
    else return root;

    //recalculeaza inaltimea si factorul de echilibru;
    root->height = 1 + maxI(getHeight(root->left),getHeight(root->rigth));
    int k = balance(root);

    //rotatiile necesare in functie de puncte si de nume;
    if( (k < -1) && 
           ( (root->rigth != NULL && _e.puncteTotal < (root->rigth->e).puncteTotal) ||
             (root->rigth != NULL && (_e.puncteTotal == (root->rigth->e).puncteTotal) && strcmp(_e.numeEchipa, (root->rigth->e).numeEchipa) < 0) ) )
    {
        return RL(root);
    }
    if( (k < -1) && 
           ( (root->rigth != NULL && _e.puncteTotal > (root->rigth->e).puncteTotal) ||
             (root->rigth != NULL && (_e.puncteTotal == (root->rigth->e).puncteTotal) && strcmp(_e.numeEchipa, (root->rigth->e).numeEchipa) > 0) ) )
    {
        return RR(root);
    }
    if( (k > 1) && 
            ( (root->left != NULL && _e.puncteTotal < (root->left->e).puncteTotal) ||
              (root->left != NULL && (_e.puncteTotal == (root->left->e).puncteTotal) && strcmp(_e.numeEchipa, (root->left->e).numeEchipa) < 0) ) )
    {
        return LL(root);
    }
    if( (k > 1) && 
            ( (root->left != NULL && _e.puncteTotal > (root->left->e).puncteTotal) ||
              (root->left != NULL && (_e.puncteTotal == (root->left->e).puncteTotal) && strcmp(_e.numeEchipa, (root->left->e).numeEchipa) > 0) ) )
    {
        return LR(root);
    }
    
    return root;
}

//afiseaza numele echipelor de pe nivelul dat ca parametru dintr-un arvore avl;
void printLevel(avn * root, int level, FILE * fs){
    if (root == NULL) return;
    if (level == 0) fprintf(fs,"%s\n", root->e.numeEchipa);
    else if (level > 0) {
        printLevel(root->rigth, level-1, fs);
        printLevel(root->left, level-1, fs);
    }
}

//insereaza intr-un avbore avl echipele dintr-un arbore bst parcurs in ordine descrescatoare;
void DRSbstInsAvl (avn ** _aRoot,bsn * _bRoot){
    if(_bRoot != NULL){
        DRSbstInsAvl(_aRoot,_bRoot->rigth);
        *_aRoot = insertAvl(*_aRoot,_bRoot->e);
        DRSbstInsAvl(_aRoot,_bRoot->left);
    }
}

//sterge un arbore avl;
void deleteAvlSDR(avn * root){
    if(root != NULL){
        deleteAvlSDR(root->left);
        deleteAvlSDR(root->rigth);
        delTeam(root->e);
        free(root);
    }
}

//creeaza arborele avl cerut si afiseaza echipele de pe nivelul 2;
//elibereaza memoria folosita pentru arbori;
void LEVEL2(avn ** _aRoot, bsn * _bRoot, FILE * fs){
    DRSbstInsAvl(_aRoot,_bRoot);
    fprintf(fs,"\nTHE LEVEL 2 TEAMS ARE:\n");
    printLevel(*_aRoot, 2 ,fs);

    deleteBstSDR(_bRoot);
    deleteAvlSDR(*_aRoot);
}