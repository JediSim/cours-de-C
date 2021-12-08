#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include "minishell.h"


int getcmd(char* CMD_LINE, char** CMD_ELEMS){

    // On recupere le premier morceau de la commande
    char* cmd = strtok(CMD_LINE,"\n ");
    int i = 0;
    // On place chaque partie de la commande dans CMD_ELEMS
    while (cmd != NULL){
        CMD_ELEMS[i] = cmd;
        cmd = strtok(NULL,"\n ");
        i++;
    }
    CMD_ELEMS[i] = "";
    return 0;
}

int eqcmd(char* cmd, char* value){
    // compare si deux String sont égal
    if (strcmp(cmd,value) == 0){
        return 1;
    }else{
        return 0;
    }
}

void action_quit(){
    // appeller sys_exit avec EXIT_SUCCESS en paramètres
    _Exit(EXIT_SUCCESS);
}

void action_pwd(){
    char path[SIZE_BUFFER];
    getcwd(path,sizeof(path));
    printf(">>> %s\n",path);
}

void action_cd(char* path){
    if (chdir(path)){
        printf("Error message: %s\n",strerror(errno));
    }else{
        printf(">>> %s\n",path);
    }
}

void action_ls(){
    struct stat fileStat;
    char path[SIZE_BUFFER];
    getcwd(path,sizeof(path));
    DIR *dir = opendir(path);
    struct dirent *dirent = readdir(dir);
    for(;(dirent != NULL); dirent = readdir(dir)){
        if (stat(dirent->d_name,&fileStat) != -1){
            // protection pour le proprietaire
            printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
            printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
            printf((fileStat.st_mode & S_IWUSR) ? "x" : "-");

            // protection pour les groupes
            printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
            printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
            printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");

            // protection pour les utilisateurs
            printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
            printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
            printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");

            printf("    ");

            // taille en octet
            printf("%lu",fileStat.st_size);

            printf("    ");

            // nombre de block alloué
            printf("%lu",fileStat.st_blocks);

            printf("    ");

            // no d'innode
            printf("%lu",fileStat.st_ino);

            printf("    ");

            printf("%s\n",dirent->d_name);

        }else{
            printf("Error message: %s\n",strerror(errno));
        }
    }
    
}

void action_exec(char *exe, char **cmd){
    pid_t pid = fork();
    if (pid == -1){
        //error
        printf("%sError message: %s\n%s",KRED,strerror(errno),KNRM);

    }else if (pid == 0){
        //, On est dans le processus fils
        execv(exe, cmd);
    }else{
        // On est dans le processus père
    }
}

int main()
{   
    char PREVDIR[SIZE_BUFFER];
    char* CMD_ELEMS[SIZE_BUFFER];
    char CMD_LINE[SIZE_BUFFER];

    int QUIT = 0;
    while (!QUIT) {
        // On affiche le prompt
        printf("%s\n>%s",KGRN,KNRM);
        // On recupère l'entrée
        if(!fgets(CMD_LINE,SIZE_BUFFER,stdin)){QUIT=1;continue;};
        // On recupere la commande et ses paramètres
        getcmd(CMD_LINE,CMD_ELEMS);
        if (eqcmd(CMD_ELEMS[0],"exit")){
            // pour utiliser l'appelle systeme sys_exit
            action_quit();
        }else if (eqcmd(CMD_ELEMS[0],"pwd")){
            action_pwd();
        }else if (eqcmd(CMD_ELEMS[0],"cd")){
            if (eqcmd(CMD_ELEMS[1], "~") || eqcmd(CMD_ELEMS[1], "")){
                getcwd(PREVDIR,sizeof(PREVDIR));

                action_cd(HOME);
            }else if(eqcmd(CMD_ELEMS[1], "-")){
                action_cd(PREVDIR);
            }else{
                getcwd(PREVDIR,sizeof(PREVDIR));

                action_cd(CMD_ELEMS[1]);
            }
        }else if(eqcmd(CMD_ELEMS[0],"ls")){
            action_ls();
        }else if(eqcmd(CMD_ELEMS[0],"exec")){
            action_exec(CMD_ELEMS[1], CMD_ELEMS+2);
        }
        else{
            // a transformer en action_ERROR()
            printf("Commande invalide\n");
        }
    }
    return 0;
}
