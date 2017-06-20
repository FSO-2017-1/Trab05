#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int contador_resultados = 0;

void ler_arquivo(char local[]){


  FILE *arquivo_alvo = fopen(local, "r");
  char bytes[30];
  //imprime lixo
  fread(bytes, 1, 30, arquivo_alvo);

  //	printf("%s", bytes);


  //imprime só primeira linha
  if(arquivo_alvo == NULL){
    perror("Erro ao abrir arquivo");
  }

  /* fgets(bytes, 30, arquivo_alvo); */
  printf("%s", bytes);


  fclose(arquivo_alvo);
}

void pesquisar_diretorio(char* local, char * arquivo, int max_resultados){
	DIR *diretorio;
    struct dirent *dir;
    diretorio = opendir(local);

	if (diretorio){
		while ((dir = readdir(diretorio)) != NULL) {
			char nome_local[256] = "";
	        strcat(nome_local, local);
			strcat(nome_local, dir->d_name);

			if(!(strcmp(dir->d_name, ".") == 0) && !(strcmp(dir->d_name, "..") == 0)){
				if(dir->d_type == DT_DIR){
					strcat(nome_local, "/");
					pesquisar_diretorio(nome_local, arquivo, max_resultados);
				}else if(strstr(dir->d_name, arquivo) != 0){
//compara a substring de até 4 caracteres, não sei se é o melhor jeito
					if(contador_resultados >= max_resultados){
						return;
					}
					printf("%d. %s --\n", contador_resultados+1, nome_local);
					contador_resultados++;
					ler_arquivo(nome_local);
					printf("\n");
					
				}	
			}
//closedir(diretorio);
		}
		
	}
	
}


int main(int argc, char *argv[]){
	int max_resultados = atoi(argv[3]);
	printf("Resultado do buscador -- '%s' na pasta %s\n", argv[2], argv[1]);
	pesquisar_diretorio(argv[1], argv[2], max_resultados);
	
	return(0);
}
