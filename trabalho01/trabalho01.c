//Vinicius Laguna Munchow
//Matricula: 20101860
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIRST_ON_LIST *(void **)listHandler
#define LAST_ON_LIST *(void **)(listHandler + sizeof(void **))
#define PREVIOUS_PERSON (sizeof(char) * 10) + sizeof(int) + sizeof(int)
#define NEXT_PERSON (sizeof(char) * 10) + sizeof(int) + sizeof(int) + sizeof(void **)
#define NAME (sizeof(char) * 10)
#define AGE sizeof(int)
#define NUMBER sizeof(int)
#define LIST_SIZE *(int *)pBuffer
#define OPTION (int *)(pBuffer + sizeof(int))

int memfree(void *pBuffer, void *listHandler) {
    
    if (LIST_SIZE == 0) {
        return 0;
    }

    void *temp = NULL;

    while (FIRST_ON_LIST != NULL) {
        temp = FIRST_ON_LIST;
        FIRST_ON_LIST = *(void **)(temp + NEXT_PERSON);
        free(temp);
    }

    return 0;
}

int remove_person(void *pBuffer, void *listHandler) {

    if (LIST_SIZE == 0) {
        printf("\nAgenda vazia! Preencha-a com alguns registros antes e tente novamente!\n");
        return -1;
    }

    char nameComp[10];
    void *person = FIRST_ON_LIST;
    void *temp = NULL;

    printf("\n-- Digite o nome da pessoa que deseja remover da agenda: ");
    scanf("%s^\n", nameComp);

    while (person != NULL) {

        if ( (strcmp(nameComp, (char *)person)) == 0 ) {

            if (LIST_SIZE == 1) {

                temp = FIRST_ON_LIST;

                free(temp);
                
                FIRST_ON_LIST = NULL;
                LAST_ON_LIST = NULL;
                LIST_SIZE = 0;
                printf("\nNome excluido com sucesso! A agenda esta, agora, vazia.\n");
                return 0;

            } else if ( *(void **)(person + PREVIOUS_PERSON) == NULL ) {

                temp = FIRST_ON_LIST; //aponta para primeira posicao da lista
                FIRST_ON_LIST = *(void **)(temp + NEXT_PERSON);

                free(temp);
                
                *(void **)((FIRST_ON_LIST) + PREVIOUS_PERSON) = NULL;
                LIST_SIZE -= 1;
                printf("\nNome excluido com sucesso!\n");
                return 0;

            } else if ( *(void **)(person + NEXT_PERSON) == NULL ) {

                temp = LAST_ON_LIST;
                LAST_ON_LIST = *(void **)(temp + PREVIOUS_PERSON);

                free(temp);
                
                *(void **)((LAST_ON_LIST) + NEXT_PERSON) = NULL; //seta 'next_person' da nova ultima posiçao da lista como NULL
                LIST_SIZE -= 1;
                printf("\nNome excluido com sucesso!\n");
                return 0;
                
            } else {

                *(void **)(temp + NEXT_PERSON) = *(void **)(person + NEXT_PERSON);
                temp = person;
                person = *(void **)(person + NEXT_PERSON); 
                *(void **)(person + PREVIOUS_PERSON) = *(void **)(temp + PREVIOUS_PERSON);
                
                free(temp);

                LIST_SIZE -= 1;
                printf("\nNome excluido com sucesso!\n");
                return 0;

            }

        } else {
            temp = person; //pega a posicao antes da atualizacao
            person = *(void **)(person + NEXT_PERSON); //pega a prox posicao
        }
    }

    return 0;

}

int add_person(void *pBuffer, void *listHandler){

    //person [(person_size) + prev_person + next_person]
    void *person = malloc(NAME + AGE + NUMBER + sizeof(void **) + sizeof(void **));
    if (!person) {
        printf("Erro ao alocar memoria (person)!\n");
        return -1;
    }
    *(void **)(person + PREVIOUS_PERSON) = NULL;
    *(void **)(person + NEXT_PERSON) = NULL;

    void *aux = NULL;
    
    printf("\n-- Prossiga com as informacoes da pessoa que deseja incluir:\n\n");
	printf("\t Nome: ");
    scanf("%s^\n", (char *)person);
    printf("\t Idade: ");
    scanf("%d", (int *)(person + NAME));
    printf("\t Telefone: ");
    scanf("%d", (int *)(person + NAME + AGE));
    
    if (LIST_SIZE == 0) {

        FIRST_ON_LIST = person;
        LAST_ON_LIST = person;
        LIST_SIZE += 1;
        return 0;

    } else {

        aux = FIRST_ON_LIST;

        while(aux != NULL) {

            if (strcmp((char *)person, (char *)aux) > 0) {

                if (*(void **)(aux + NEXT_PERSON) == NULL) {

                    *(void **)(person + PREVIOUS_PERSON) = aux;
                    *(void **)(aux + NEXT_PERSON) = person;
                    LAST_ON_LIST = person;
                    LIST_SIZE += 1;
                    return 0;

                } else if (strcmp((char *)(*(void **)(aux + NEXT_PERSON)), (char *)person) > 0) {

                    *(void **)(person + PREVIOUS_PERSON) = aux;
                    *(void **)(person + NEXT_PERSON) = *(void **)(aux + NEXT_PERSON);
                    *(void **)(aux + NEXT_PERSON) = person;
                    *(void **)(*(void **)(aux + NEXT_PERSON) + PREVIOUS_PERSON) = person;
                    LIST_SIZE += 1;
                    return 0;

                }

            } else {

            *(void **)(person + PREVIOUS_PERSON) = NULL;
            *(void **)(person + NEXT_PERSON) = aux;
            *(void **)(aux + PREVIOUS_PERSON) = person;
            FIRST_ON_LIST = person;
            LIST_SIZE += 1;
            return 0;

            }

        aux = *(void **)(aux + NEXT_PERSON); //incrementa posicao da lista

        }

    return 0;
    
    }
}

int search_person(void *pBuffer, void *listHandler) {

    if (LIST_SIZE == 0) {
        printf("\nAgenda vazia! Preencha-a com alguns registros antes e tente novamente!\n");
        return -1;
    }

    char nameComp[10];

    void *person = FIRST_ON_LIST;

    printf("\n-- Digite o nome da pessoa que deseja buscar: ");
    scanf("%s^\n", nameComp);

    while (person != NULL) {
        if ((strcmp(nameComp, (char *)person)) == 0) {
            printf("\nNome: %s", (char *)person);
            printf("\nIdade: %i", *(int *)(person + NAME));
            printf("\nTelefone: %i\n", *(int *)(person + NAME + AGE));
            return 0;
        } else {
            person = *(void **)(person + NEXT_PERSON);
        }
    }
    //apenas em caso de nao encontrar nenhum nome
    printf("\nO nome nao existe na agenda! Tente procurar apenas por nomes ja registrados!\n");
    return -1;
}

int list_all(void *pBuffer, void *listHandler){

    if (LIST_SIZE == 0) {
        printf("\nAgenda vazia! Preencha-a com alguns registros antes e tente novamente!\n");
        return -1;
    }

    void *person = FIRST_ON_LIST;

    printf("\n-- LISTA DE PESSOAS REGISTRADAS:\n");

    while (person != NULL) {
        printf("\nNome: %s", (char *)person);
        printf("\nIdade: %i", *(int *)(person + NAME));
        printf("\nTelefone: %i", *(int *)(person + NAME + AGE));
        printf("\n------------------------------\n");
        person = *(void **)(person + NEXT_PERSON);
    }

    return 0;
}

void menu(int *option){
	do {
		printf("\n-- AGENDA DE PESSOAS:\n\n");
		printf("\t 1. Incluir registro\n");
		printf("\t 2. Apagar registro\n");
		printf("\t 3. Buscar por nome\n");
		printf("\t 4. Listar registros\n");
		printf("\t 5. Sair\n");
		printf("\n-- Digite sua escolha: ");
		scanf("%d", option);
	} while (*option <= 0 || *option > 5);
	getchar();
}

int main(int argc, char *argv[]){
    //listHandler = [first_person_on_list + last_person_on_list]
    void *listHandler = malloc(sizeof(void *) + sizeof(void *));
    if (!listHandler){
        printf("Erro ao alocar memoria (listHandler)!\n");
        return -1;
    }
    
    FIRST_ON_LIST = NULL;
    LAST_ON_LIST = NULL;

    //pBuffer = [list_size + op]
    void *pBuffer = malloc(sizeof(int) + sizeof(int));
    if (!pBuffer) {
        printf("Erro ao alocar memoria (pBuffer)!\n");
        return -1;
    }
    LIST_SIZE = 0;

    do {
        *OPTION = 0;
        menu(OPTION);
		switch (*OPTION) {
		case 1:
			add_person(pBuffer, listHandler);
			break;
		case 2:
			remove_person(pBuffer, listHandler);
			break;
		case 3:
            search_person(pBuffer, listHandler);
            break;
        case 4:
			list_all(pBuffer, listHandler);
			break;
		case 5:
            memfree(pBuffer, listHandler);
			break;
		}
	} while (*OPTION != 5);

    free(listHandler);
    free(pBuffer);
    return 0;
}