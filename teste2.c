
#include <dirent.h>

#include <stdio.h>

#include <string.h>

int main(void)

{

    DIR *d;

    struct dirent *dir;

    d = opendir(".");
    char testando[256];
    if (d)

    {

        while ((dir = readdir(d)) != NULL)

        {

            if(strcmp("teste2.c", dir->d_name)==0){
                printf("\n\n\nteste2.c = %s\n\n", dir->d_name);
                strcpy(testando, dir->d_name);
            }
            printf("%s\n", dir->d_name);

        }

        printf("\n\nminha nova variavel: %s", testando);
        closedir(d);

    }

    return(0);

}
