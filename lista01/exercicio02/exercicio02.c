//Vinicius Laguna Munchow
//Matricula: 20101860
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *add_semicolon(char *name){ //adiciona ponto e virgula para separar os nomes na string
    int i = strlen(name) + 1;

	name = (char *)realloc(name, sizeof(char) * i + 1);
	if(!name){
			printf("\nErro ao alocar memoria!\n");
        	return NULL;
	}

	name[i - 1] = ';';
	name[i] = '\0';
	return name;
}

char *get_name(char *name, int i){
    do{
		i++;
		name = (char *)realloc(name, sizeof(char) * i + 1);
		if(!name){
			printf("\nErro ao alocar memoria!\n");
        	return NULL;
		}
		name[i - 1] = getchar();
	} while(name[i - 1] != '\n');

	name[i - 1] = '\0';
	return name;
}

char *add_name(char *name){	
    int length = strlen(name);
	printf("\nDigite o nome que deseja inserir: ");
	name = get_name(name, length);
	name = add_semicolon(name);
	return name;
}

char *remove_name(char *name){
	int i = 0;
	char temp[100], temp2[100];

	char *name_comp = (char *)malloc(sizeof(char));
	if (!name_comp) {
        printf("\nErro ao alocar memoria!\n");
        return NULL;
    }

    printf("\nDigite o nome que deseja remover: ");	
	name_comp = get_name(name_comp, i);
	name_comp = add_semicolon(name_comp);
	char *p = strstr(name, name_comp); //guarda o endereço da primeira ocorrencia do nome na string

	if(!p){
		printf("\nNome nao encontrado!\n");
		return NULL;
	} else {
		strcpy(temp, name);
		temp[p - name] = '\0';
		strcpy(temp2, p + strlen(name_comp));
   		strcat(temp, temp2);
    	strcpy(name, temp);
		//o seguinte teste evita erro no caso de dar outra instrução após a remoção de todos os nomes ja existentes
			if (strlen(name) == 0){
				name = (char *)realloc(name, sizeof(char) + 1);
			} else {
				name = (char *)realloc(name, sizeof(char) * strlen(name) + 1);
			}
	}

	printf("\nOperacao de remocao efetuada com sucesso!\n");
	free(name_comp);
	return name;
}

int list_names(char *name){
	int i = 0;

	if(name[0] == '\0'){
		printf("\nNao existem nomes no registro!\n");
		return 1;
	}

	printf("\nNomes registrados: \n");

	while(name[i] != '\0'){

		if(name[i] == ';'){
			printf("\n");
		} else {
			printf("%c", name[i]);
		}
		i++;
	}
	return 0;
}

int menu(void){
	int c = 0;

	do {
		printf("\n-- MENU:\n\n");
		printf("\t 1. Adicionar nome\n");
		printf("\t 2. Remover nome\n");
		printf("\t 3. Listar\n");
		printf("\t 4. Sair\n");
		printf("\n-- Digite sua escolha: ");
		scanf("%d", &c);
	} while (c <= 0 || c > 4);
	getchar();
	return c;
}

int main(int argc, char *argv[]){
    int op=0;

    char *p = (char *)malloc(sizeof(char));
    if (!p) {
        printf("\nErro ao alocar memoria!\n");
        return 1;
    }
    *p = '\0';

    while(op != 4) {
		op = menu();
		switch (op) {
		case 1:
			p = add_name(p);
			break;
		case 2:
			p = remove_name(p);
			break;
		case 3:
			list_names(p);
			break;
		case 4:
			break;
		}
	}

    free(p);
	return 0;
}