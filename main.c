#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "rbt.h"

#define MAX 10

int main() {
    TNoRB *arvore = NULL;

    int opc = -1, flag = 1, n, rn;
    

    do {
        printf("1 - Inserir elemento;\n2 - Remover elemento;\n3 - Ver árvore;\n4 - Sair\n");
        scanf("%d", &opc);

        switch(opc) {
            case 1:
                printf("Elemento a inserir:\n");
                scanf("%d", &n);
                insereNo(&arvore, NULL, &arvore, n);
                break;

            case 2:
                printf("Elemento a remover:\n");
                scanf("%d", &rn);
                removeNo(&arvore, rn);
                break;

            case 3:
                inOrder(arvore);
                break;

            case 4:
                flag = 0;
                break;

            default:
                printf("Opção inválida.\n");
        }

        printf("==========\n");
    } while (flag);

    return 0;
}
