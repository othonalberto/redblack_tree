typedef struct TNoRB {
    int chave;
    int cor;
    struct TNoRB *pai;
    struct TNoRB *esq;
    struct TNoRB *dir;
} TNoRB;

void insereNo(TNoRB **arvore, TNoRB *pPai, TNoRB **pMain, int k);

TNoRB *avo(TNoRB *arvore);

TNoRB *tio(TNoRB *arvore);

void rotacaoDireita(TNoRB **no);

void rotacaoEsquerda(TNoRB **no);

void consertaRB(TNoRB **arvore, TNoRB **pMain);

void inOrder(TNoRB *raiz);

void dRotacaoDireita(TNoRB **no);

void dRotacaoEsquerda(TNoRB **no);

void removeNo(TNoRB **arvore, int k);

void nBlackIBlackFRed(TNoRB *aRemover, TNoRB **arvore);

void nBlackIBlackFBlack(TNoRB *aRemover, TNoRB **arvore);

void nBlackIRed(TNoRB *aRemover, TNoRB **arvore);

TNoRB *buscaNo(TNoRB *arvore, int k);

TNoRB *irmao(TNoRB *pai, TNoRB *noAtual);

int filhoEsquerdo(TNoRB *arvore);

TNoRB **maiorEsq(TNoRB **pMaiorEsq);
