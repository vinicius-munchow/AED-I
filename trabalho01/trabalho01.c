//Vinicius Laguna Munchow
//Matricula: 20101860
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int memfree(void *pBuffer, void *listHandler) {
    
    if (*(int *)pBuffer == 0) {
        return 0;
    }

    while (*(void **)(listHandler) != NULL) {
        void *temp = malloc(sizeof(void **));
        temp = *(void **)(listHandler);
        *(void **)(listHandler) = *(void **)(temp + (sizeof(char) * 10 + sizeof(int) + sizeof(int) + sizeof(void **)));
        free(temp);
    }

    return 0;
}

int remove_person(void *pBuffer, void *listHandler) {

    if (*(int *)pBuffer == 0) {
        printf("\nAgenda vazia! Preencha-a com alguns registros antes e tente novamente!\n");
        return -1;
    }

    char nameComp[10];

    void *person = malloc(sizeof(void **)); 
    person = *(void **)(listHandler); //'first_person_on_list'

    void *temp = malloc(sizeof(void **)); 
    *(void **)temp = NULL;

    if (!person || !temp) {
        printf("Erro ao alocar memoria!\n");
        return -1;
    }

    printf("\n-- Digite o nome da pessoa que deseja remover da agenda: ");
    scanf("%s^\n", nameComp);

    while (person != NULL) {
        if ((strcmp(nameComp, (char *)person)) == 0) {

            if (*(int *)pBuffer == 1) {

                temp = *(void **)listHandler;
                free(temp);
                *(void **)listHandler = NULL;
                *(void **)(listHandler + sizeof(void **)) = NULL;
                *(int *)pBuffer = 0;
                printf("\nNome excluido com sucesso! A agenda esta, agora, vazia.\n");
                return 0;

            } else if ( *(void **)(person + sizeof(char) * 10 + sizeof(int) + sizeof(int)) == NULL ) {

                temp = *(void **)listHandler; //aponta para primeira posicao da lista
                *(void **)listHandler = *(void **)(temp + sizeof(char) * 10 + sizeof(int) + sizeof(int) +sizeof(void **));
                free(temp);
                *(void **)(listHandler + sizeof(char) * 10 + sizeof(int) + sizeof(int)) = NULL;
                *(int *)pBuffer -= 1;
                printf("\nNome excluido com sucesso!\n");
                return 0;

            } else {

                //[temp->prox] = [person->prox], ou seja, pula a posicao do nome a ser removido
                *(void **)(temp + sizeof(char) * 10 + sizeof(int) + sizeof(int) +sizeof(void **)) = *(void **)(person + sizeof(char) * 10 + sizeof(int) + sizeof(int) + sizeof(void **));
                //atualiza a posicao de temp
                temp = person;
                //person = [person->prox]
                person = *(void **)(person + (sizeof(char) * 10 + sizeof(int) + sizeof(int) + sizeof(void **)));
                //[person->prev] = [temp->prev], ou seja, pula a posicao do nome a ser removido 
                *(void **)(person + sizeof(char) * 10 + sizeof(int) + sizeof(int)) = *(void **)(temp + sizeof(char) * 10 + sizeof(int) + sizeof(int));
                
                free(temp);

                *(int *)pBuffer -= 1;

                printf("\nNome excluido com sucesso!\n");

                return 0;
            }

        } else { //if-else -> strcmp != 0
            temp = person; //pega a posicao antes da atualizacao
            person = *(void **)(person + (sizeof(char) * 10 + sizeof(int) + sizeof(int) + sizeof(void **))); //pega a prox posicao
        } //if-else -> strcmp != 0
    } //while

    return 0;

}

int add_person(void *pBuffer, void *listHandler){

    //person [(person_size) + prev_person + next_person]
    void *person = malloc((sizeof(char) * 10) + sizeof(int) + sizeof(int) + sizeof(void **) + sizeof(void **));
    *(void **)(person + ((sizeof(char) * 10) + sizeof(int) + sizeof(int))) = NULL;
    *(void **)(person + ((sizeof(char) * 10) + sizeof(int) + sizeof(int) + sizeof(void **))) = NULL;

    void *aux = malloc(sizeof(void **)); 
    *(void **)aux = NULL;
    
    if (!person || !aux) {
        printf("Erro ao alocar memoria!\n");
        return -1;
    }

    printf("\n-- Prossiga com as informacoes da pessoa que deseja incluir:\n\n");
	printf("\t Nome: ");
    scanf("%s^\n", (char *)person);
    printf("\t Idade: ");
    scanf("%i", &*(int *)(person + (sizeof(char) * 10)));
    printf("\t Telefone: ");
    scanf("%i", &*(int *)(person + (sizeof(char) * 10) + sizeof(int)));     
    
    if (*(int *)pBuffer == 0) {
        *(void **)listHandler = person; //primeira pessoa da lista
        *(void **)(listHandler + sizeof(void **)) = person; //ultima pessoa da lista
        
        *(int *)pBuffer += 1;
        return 0;
    }

    aux = *(void **)(listHandler + sizeof(void **)); //armazena a ultima ocorrencia da lista

    *(void **)(person + ((sizeof(char) * 10) + sizeof(int) + sizeof(int))) = aux; //'prev_person' apontará para o ultimo end. antigo
    *(void **)(aux + ((sizeof(char) * 10) + sizeof(int) + sizeof(int) + sizeof(void **))) = person; //'next_person'de aux apontará para person
    *(void **)(listHandler + sizeof(void **)) = person; //'last_person_on_list' apontará para o novo endereço

    *(int *)pBuffer += 1;

    return 0;
}

int search_person(void *pBuffer, void *listHandler) {

    if (*(int *)pBuffer == 0) {
        printf("\nAgenda vazia! Preencha-a com alguns registros antes e tente novamente!\n");
        return -1;
    }

    char nameComp[10];

    void *person = malloc(sizeof(void **));
    person = *(void **)(listHandler); //'first_person_on_list'

    if (!person) {
        printf("Erro ao alocar memoria!\n");
        return -1;
    }

    printf("\n-- Digite o nome da pessoa que deseja buscar: ");
    scanf("%s^\n", nameComp);

    while (person != NULL) {
        if ((strcmp(nameComp, (char *)person)) == 0) {
            printf("\nNome: %s", (char *)person);
            printf("\nIdade: %i", *(int *)(person + (sizeof(char) * 10)));
            printf("\nTelefone: %i\n", *(int *)(person + (sizeof(char) * 10) + sizeof(int)));
            return 0;
        } else {
            person = *(void **)(person + (sizeof(char) * 10 + sizeof(int) + sizeof(int) + sizeof(void **))); //'next_person'
        }
    }
    //apenas em caso de nao encontrar nenhum nome
    printf("\nO nome nao existe na agenda! Tente procurar apenas por nomes ja registrados!\n");
    return -1;
}

int list_all(void *pBuffer, void *listHandler){

    if (*(int *)pBuffer == 0) {
        printf("\nAgenda vazia! Preencha-a com alguns registros antes e tente novamente!\n");
        return -1;
    }

    void *person = malloc(sizeof(void **)); 
    person = *(void **)(listHandler); //'first_person_on_list'
        
    if (!person) {
        printf("Erro ao alocar memoria!\n");
        return -1;
    }

    printf("\n-- LISTA DE PESSOAS REGISTRADAS:\n");

    while (person != NULL) {
        printf("\nNome: %s", (char *)person);
        printf("\nIdade: %i", *(int *)(person + (sizeof(char) * 10)));
        printf("\nTelefone: %i", *(int *)(person + (sizeof(char) * 10) + sizeof(int)));
        printf("\n------------------------------\n");
        person = *(void **)(person + (sizeof(char) * 10 + sizeof(int) + sizeof(int) + sizeof(void **))); //'next_person'
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
		scanf("%d", &*(int *)(pBuffer + sizeof(int)));
	} while (*(int *)(pBuffer + sizeof(int)) <= 0 || *(int *)(pBuffer + sizeof(int)) > 5);
	getchar();
	return pBuffer;
}

int main(int argc, char *argv[]){
    //listHandler = [first_person_on_list + last_person_on_list]
    void *listHandler = malloc(sizeof(void **) + sizeof(void **));
    *(void **)listHandler = NULL;

    //pBuffer = [list_length + op]
    void *pBuffer = malloc(sizeof(int) + sizeof(int));
    *(int *)pBuffer = 0;
    *(int *)(pBuffer + sizeof(int)) = 0;

    if (!pBuffer || !listHandler) {
        printf("Erro ao alocar memoria!\n");
        return -1;
    }

    do {
        pBuffer = menu(pBuffer);
		switch (*(int *)(pBuffer + sizeof(int))) {
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
	} while (*(int *)(pBuffer + sizeof(int)) != 5);

    free(listHandler);
    free(pBuffer);
    return 0;
}