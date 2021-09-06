//Vinicius Laguna Munchow
//Matricula: 20101860
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[10];
    int age;
    int phone;
} Person;

Person person[10];

int *add_person(void *pBuffer){

    if(*(int *)pBuffer < 10) {
        printf("\n-- Prossiga com as informacoes da pessoa que deseja incluir:\n\n");
        printf("\t Nome: ");
        scanf("%s", person[*(int *)pBuffer].name);
        printf("\t Idade: ");
        scanf("%i", &person[*(int *)pBuffer].age);
        printf("\t Telefone: ");
        scanf("%i", &person[*(int *)pBuffer].phone);
        *(int *)pBuffer = *(int *)pBuffer + 1;
        return pBuffer;
    } else {
        printf("Lista cheia!");
        return NULL;
    }
}

int list_all(void *pBuffer){

    if (*(int *)pBuffer != 0){
        printf("\n-- LISTA DE PESSOAS REGISTRADAS:\n");
        for(*(int *)(pBuffer + sizeof(int) + sizeof(char)) = 0;
         *(int *)(pBuffer + sizeof(int) + sizeof(char)) < *(int *)pBuffer;
          *(int *)(pBuffer + sizeof(int) + sizeof(char)) = *(int *)(pBuffer + sizeof(int) + sizeof(char)) + 1) {
            printf("\nREGISTRO %i: \n", *(int *)(pBuffer + sizeof(int) + sizeof(char)) + 1);
            printf("\nNome: %s", person[*(int *)(pBuffer + sizeof(int) + sizeof(char))].name);
            printf("\nIdade: %i", person[*(int *)(pBuffer + sizeof(int) + sizeof(char))].age);
            printf("\nTelefone: %i\n", person[*(int *)(pBuffer + sizeof(int) + sizeof(char))].phone);
        }
    } else {
        printf("\nAgenda vazia! Preencha-a com alguns registros antes e tente novamente!\n");
        return -1;
    }

    return 0;
}

int *menu(void *pBuffer){

	do {
		printf("\n-- AGENDA DE PESSOAS:\n\n");
		printf("\t 1. Incluir registro\n");
		printf("\t 2. Apagar registro\n");
		printf("\t 3. Buscar por nome\n");
		printf("\t 4. Listar registros\n");
		printf("\t 5. Sair\n");
		printf("\n-- Digite sua escolha: ");
		scanf("%d", &*(int *)(pBuffer + sizeof(int) + sizeof(char)));
	} while (*(int *)(pBuffer + sizeof(int) + sizeof(char)) <= 0 || 
    *(int *)(pBuffer + sizeof(int) + sizeof(char)) > 5);

	getchar();

	return pBuffer;
}


int main(int argc, char *argv[]){

    void *pBuffer = malloc((sizeof(int) * 2) + sizeof(char));
    if (!pBuffer) {
        printf("\nErro ao alocar memoria!\n");
        return -1;
    }
    //pBuffer = [tamanhoLista, stringCompara, contadores]
    *(int *)pBuffer = 0;
    *(char *)(pBuffer + sizeof(int)) = 'f';
    *(int *)(pBuffer + sizeof(int) + sizeof(char)) = 0;
    

    do {
		pBuffer = menu(pBuffer);
		switch (*(int *)(pBuffer + sizeof(int) + sizeof(char))) {
		case 1:
			pBuffer = add_person(pBuffer);
			break;
        case 4:
			list_all(pBuffer);
			break;
		case 5:
			break;
		}
	} while(*(int *)(pBuffer + sizeof(int) + sizeof(char)) != 5);

    free(pBuffer);
	return 0;
}