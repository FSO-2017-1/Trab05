#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int contador_resultados = 0;

void ler_arquivo(char* local, char * arquivo, int max_resultados){
	if (contador_resultados == max_resultados) return;
	if (!strstr(local, arquivo)) return;

	FILE* sigD = fopen(local, "r");
	char sig[30];
	fread(sig, 1, 30, sigD);
	contador_resultados++;
	printf("%d. %s --\n", contador_resultados, local);
	printf("\t%s\n",sig);
}

void pesquisar_diretorio(char* local, char * arquivo, int max_resultados){

	DIR *diretorio;
  struct dirent *dir;
  diretorio = opendir(local);

	if (diretorio){
		while ((dir = readdir(diretorio)) != NULL){
			char nome_local[256] = "";
			strcat(nome_local, local);
			strcat(nome_local, dir->d_name);

			if(!(strcmp(dir->d_name, ".") == 0)){
				if(!(strcmp(dir->d_name, "..") == 0)){
					if(dir->d_type == 4){
						strcat(nome_local, "/");
						pesquisar_diretorio(nome_local, arquivo, max_resultados);
					}
					else{
						ler_arquivo(nome_local, arquivo, max_resultados);
					}
				}
			}
		}
		closedir(diretorio);
	}
}


int main(int argc, char *argv[]){
	int max_resultados = atoi(argv[3]);

	if(argc != 4){
			 printf("Use: ./buscador /caminho/que/deseja palavra_de_busca numero_max_de_resultados\n");
			 exit(EXIT_FAILURE);
	}

	printf("\n \nResultado do buscador -- '%s' na pasta %s\n", argv[2], argv[1]);
	pesquisar_diretorio(argv[1], argv[2], max_resultados);

	return(0);
}
