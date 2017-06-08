#include <dirent.h>
#include <stdio.h>

int main(int argc, char const *argv[]){
  //printf("%s\n", argv[1]);
  DIR *diretorio;
  struct dirent *dir;
  diretorio = opendir(argv[1]);
  if (diretorio)
  {
    while ((dir = readdir(diretorio)) != NULL)
    {
        if(!strcmp(dir->d_name, argv[2])){
          printf("%s\n", dir->d_name);
        }
    }

    closedir(diretorio);
  }

  return(0);
}
