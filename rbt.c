#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "rbt.h"

#define BLACK 0
#define RED 1

void insereNo(TNoRB **arvore, TNoRB *pPai, TNoRB **pMain, int k) {
    assert(arvore);

    if (*arvore == NULL) {
        *arvore = (TNoRB*)malloc(sizeof(TNoRB));
        if (*arvore == NULL) return;

        (*arvore)->chave = k;
        (*arvore)->cor = RED;

        (*arvore)->esq = NULL;
        (*arvore)->dir = NULL;
        (*arvore)->pai = pPai;
    } else {

        if (k < (*arvore)->chave) {
            insereNo(&((*arvore)->esq), *arvore, pMain, k);
            consertaRB(&((*arvore)->esq), pMain);
        } else if (k > (*arvore)->chave) {
            insereNo(&((*arvore)->dir), *arvore, pMain, k);
            consertaRB(&((*arvore)->dir), pMain);
        }
    }
    
    if (*arvore == *pMain)
            (*arvore)->cor = BLACK;

}

TNoRB *avo(TNoRB *arvore) {
    if ((arvore != NULL) && (arvore->pai != NULL))
            return (arvore->pai)->pai;
    else
        return NULL;
}

TNoRB *tio(TNoRB *arvore) {
    TNoRB *nAvo = avo(arvore);
    if (nAvo == NULL) return NULL;

    if (arvore->pai == nAvo->esq)
        return nAvo->dir;
    else
        return nAvo->esq;

}

void rotacaoDireita(TNoRB **no) {
    assert(no);

    if (*no == NULL) return;

    TNoRB *aux = *no;
    *no = aux->esq;
    aux->esq = (*no)->dir;
    (*no)->dir = aux;

    (*no)->pai = aux->pai;
    if(aux->dir != NULL)
        (aux->dir)->pai = aux;

    aux->pai = *no;

    aux->cor = RED;
    (*no)->cor = BLACK;

}

void rotacaoEsquerda(TNoRB **no) {
    assert(no);

    if (*no == NULL) return;

    TNoRB *aux = *no;
    *no = aux->dir;
    aux->dir = (*no)->esq;
    (*no)->esq = aux;

    (*no)->pai = aux->pai;
    if (aux->esq != NULL)
        (aux->esq)->pai = aux;

    aux->pai = *no;
 
    aux->cor = RED;
    (*no)->cor = BLACK;
}

void consertaRB(TNoRB **arvore, TNoRB **pMain) {
    assert(arvore);

    TNoRB *nAvo = NULL;
    TNoRB *nTio = NULL;

    if((*arvore)->pai != NULL) {
        if((*arvore)->pai->cor == BLACK) return;

        if((*arvore)->cor == RED) {
            nTio = tio(*arvore); 
            if (nTio != NULL && nTio->cor == RED) {
                nAvo = avo(*arvore);
                (*arvore)->pai->cor = BLACK;
                nTio->cor = BLACK;
                if (nAvo->pai != NULL) {
                    nAvo->cor = RED;
                } 
            } else {
                nAvo = avo(*arvore);
                if (nAvo != NULL) {
                    if ((*arvore)->pai == nAvo->esq) { // filho esquerdo
                        if ((*arvore) == (nAvo->esq)->esq) {
                            if (nAvo->pai != NULL) {
                                if ((nAvo->pai)->esq == nAvo)
                                    rotacaoDireita(&((nAvo->pai)->esq));
                                else
                                    rotacaoDireita(&((nAvo->pai)->dir));
                            } else {
                                rotacaoDireita(pMain);
                            }


                       } else {
                           if (nAvo->pai != NULL) {
                               if ((nAvo->pai)->esq == nAvo) {
                                    dRotacaoDireita(&((nAvo->pai)->esq));
                               } else
                                   dRotacaoDireita(&((nAvo->pai)->dir));
                           } else { 
                                dRotacaoDireita(pMain);
                           }
                      }
                   } else { 
                       if ((*arvore) == ((nAvo->dir)->dir)) {
                           if (nAvo->pai != NULL) {
                               if (((nAvo->pai)->esq) == nAvo) {
                                    rotacaoEsquerda(&((nAvo->pai)->esq));
                               } else
                                   rotacaoEsquerda(&((nAvo->pai)->dir));
                           } else {
                                rotacaoEsquerda(pMain);
                           }

                       } else {
                           if (nAvo->pai != NULL) {
                               if((nAvo->pai)->esq == nAvo) {
                                    dRotacaoEsquerda(&((nAvo->pai)->esq));
                               } else {
                                   dRotacaoEsquerda(&((nAvo->pai)->dir));
                               }
                           } else {
                                    dRotacaoEsquerda(pMain);
                           }
                       }
                }
                }
            }
        }
    }
}
    

void inOrder(TNoRB *raiz) {
    if (raiz == NULL) return;

    inOrder(raiz->esq);
    printf("Mora: %p\nChave: %d, Cor: %d\nPai: %p\nEsq: %p\nDir: %p\n\n", raiz, raiz->chave, raiz->cor, raiz->pai, raiz->esq, raiz->dir);
    inOrder(raiz->dir);
}

void dRotacaoEsquerda(TNoRB **no) {
    assert(no);

    rotacaoDireita(&((*no)->dir));
    rotacaoEsquerda(no);

}

void dRotacaoDireita(TNoRB **no) {
    assert(no);

    rotacaoEsquerda(&((*no)->esq));
    rotacaoDireita(no);
}

void removeNo(TNoRB **arvore, int k){
    assert(arvore);

    if((*arvore) == NULL) return;

    TNoRB *aRemover = *arvore;

    aRemover = buscaNo(aRemover, k);

    if(aRemover == NULL) return;

    if(aRemover->dir == NULL && aRemover->esq == NULL){
        if(aRemover->pai == NULL){
            free(aRemover);
            *arvore = NULL;
            return;
        } else {
            if(aRemover->cor == RED && aRemover->dir == NULL && aRemover->esq == NULL){
                if(filhoEsquerdo(aRemover) == 1){
                    free(aRemover);
                    aRemover->pai->esq = NULL;
                } else {
                    free(aRemover);
                    aRemover->pai->dir = NULL;
                }
                return;
            } else {
                TNoRB *nIrmao = irmao(aRemover->pai,aRemover);
                    if(nIrmao == NULL) return;

                if(aRemover->cor == BLACK && nIrmao->cor == BLACK){
                    if(nIrmao->dir == NULL && nIrmao->esq == NULL){
                        nBlackIBlackFBlack(aRemover, arvore);
                        return;
                    } else if(nIrmao->esq->cor == BLACK && nIrmao->dir->cor == BLACK){
                        nBlackIBlackFBlack(aRemover, arvore);
                        return;
                    }
                    else if(nIrmao->dir->cor == BLACK && nIrmao->esq == NULL){
                        nBlackIBlackFBlack(aRemover, arvore);
                        return;
                    }
                    else if(nIrmao->esq->cor == BLACK && nIrmao->dir == NULL){
                        nBlackIBlackFBlack(aRemover, arvore);
                        return;
                    }
                } else if(aRemover->cor == BLACK && nIrmao->cor == BLACK && (nIrmao->esq->cor == RED || nIrmao->dir->cor == RED)){
                    if(nIrmao->esq != NULL){
                        nBlackIBlackFRed(aRemover, arvore);
                        return;
                    } else if (nIrmao->dir != NULL){
                        nBlackIBlackFRed(aRemover, arvore);
                        return;
                    }
                } else if(aRemover->cor == BLACK && nIrmao->cor == RED){
                    nBlackIRed(aRemover, arvore);
                }
            }

            return;
        }
    } else if (aRemover->dir == NULL || aRemover->esq == NULL){
        if(aRemover->dir != NULL){
            aRemover->chave = aRemover->dir->chave;
            free(aRemover->dir);
            aRemover->dir = NULL;
        } else {
            aRemover->chave = aRemover->esq->chave;
            free(aRemover->esq);
            aRemover->esq = NULL;
        }
    } else {
        TNoRB **nSubstituto = maiorEsq(&(aRemover->esq));
        TNoRB *auxSubstituto = *nSubstituto;

        aRemover->chave = (*nSubstituto)->chave;
        (*nSubstituto)->pai->esq = (*nSubstituto)->esq;


        if(aRemover->cor == RED){
            if(aRemover->esq == NULL && aRemover == aRemover->pai->esq && (aRemover->dir->dir != NULL || aRemover->dir->esq != NULL)){
                if(aRemover->dir->dir != NULL){
                    rotacaoDireita(&(aRemover->esq));
                    rotacaoEsquerda(&aRemover);
                }
                if(aRemover->dir->esq != NULL){
                    rotacaoDireita(&(aRemover->dir));
                    rotacaoEsquerda(&aRemover);
                }
            } else if(aRemover->esq == NULL && aRemover == aRemover->pai->dir && (aRemover->esq->dir != NULL || aRemover->esq->esq != NULL)){
                if(aRemover->esq->dir != NULL){
                    rotacaoEsquerda(&(aRemover->esq));
                    rotacaoDireita(&aRemover);
                }
                if(aRemover->esq->esq != NULL){
                    rotacaoEsquerda(&(aRemover->esq));
                    rotacaoDireita(&aRemover);
                }
            }

            aRemover->cor = BLACK;
            if(aRemover->esq != NULL)
                aRemover->esq->cor = RED;
            if(aRemover->dir != NULL)
                aRemover->dir->cor = RED;
        }
        free(auxSubstituto);
    }
}

void nBlackIBlackFRed(TNoRB *aRemover, TNoRB **arvore){
    assert(arvore);

    TNoRB *paiARemover = aRemover->pai;

    if(filhoEsquerdo(aRemover) == 1){
        free(aRemover);
        aRemover->pai->esq = NULL;
    } else {
        free(aRemover);
        aRemover->pai->dir = NULL;
    }

    if(paiARemover->esq == NULL){
        if(paiARemover->pai == NULL){
            if((paiARemover->dir)->dir == NULL){
                rotacaoDireita(&((*arvore)->dir));
            }
            rotacaoEsquerda(arvore);
        } 
        else {
            if((paiARemover->dir)->dir == NULL){
                rotacaoDireita(&(paiARemover->dir));
            }
            rotacaoEsquerda(&paiARemover);
        }
    } 
    else {
        if(paiARemover->pai == NULL){
            if((paiARemover->esq)->esq == NULL){
                rotacaoEsquerda(&((*arvore)->esq));
            }
            rotacaoDireita(arvore);
        } else {
            if((paiARemover->dir)->dir == NULL){
                rotacaoEsquerda(&(paiARemover->esq));
            }
            rotacaoDireita(&paiARemover);
        }
    }
    return;
}

void nBlackIBlackFBlack(TNoRB *aRemover, TNoRB **arvore){
    assert(arvore);

    TNoRB *paiARemover = aRemover->pai;
    TNoRB *nIrmao = irmao(paiARemover, aRemover);

    nBlackIRed(aRemover, arvore);

    paiARemover->cor = BLACK;
    nIrmao->cor = RED;
}

void nBlackIRed(TNoRB *aRemover, TNoRB **arvore){
    assert(arvore);

    TNoRB *paiARemover = aRemover->pai;

    nBlackIBlackFRed(aRemover,arvore);

    paiARemover->cor = BLACK;
    if(paiARemover->esq != NULL)
        (paiARemover->esq)->cor = RED;
    if(paiARemover->dir != NULL)
        (paiARemover->dir)->cor = RED;
}

TNoRB *buscaNo(TNoRB *arvore, int k){
    if (arvore == NULL) return NULL;

    if (arvore->chave == k) return arvore;

    if (k < arvore->chave)
        return buscaNo(arvore->esq, k);
    else
        return buscaNo(arvore->dir, k);
}

TNoRB *irmao(TNoRB *pai, TNoRB *noAtual){
    if(pai == NULL) return NULL;

    if(pai->dir->chave == noAtual->chave)
        return pai->esq;
    else
        return pai->dir;
}

int filhoEsquerdo(TNoRB *arvore){
    if(arvore->pai->esq == arvore)
        return 1;
    else
        return 0;
}

TNoRB **maiorEsq(TNoRB **pMaiorEsq){
    assert(pMaiorEsq);
    
    if (*pMaiorEsq == NULL) return NULL;

    if ((*pMaiorEsq)->dir == NULL)
        return pMaiorEsq;
    else
        return maiorEsq(&((*pMaiorEsq)->dir));
}
