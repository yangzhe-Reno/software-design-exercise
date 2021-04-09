#include "filesystem.h"

int find_command(char *command){
    char *cmd[] = {"mkdir", "rmdir", "ls", "cd", "pwd", "create", "rm", "reload", "save", "menu", "quit", NULL};

    int i = 0;
    while(cmd[i]){
        if (!strcmp(command, cmd[i])){
            return i; // found command: return index i 
        }
        i++;
    }
    return -1; // not found: return -1
}

int main(int argc, char* argv[], char* env[]){
    int index;

    char line[128], command[16], pathname[64];
    initialize(); //initialize root node of the file system tree

    while(1){
        printf("$ ");
        fgets(line,128,stdin); 
        line[strlen(line)-1] = 0;
        sscanf(line, "%s %s", command, pathname); 
        index = find_command(command);
        switch(index){
            case 0: 
                mkdir(pathname);
                break;
            case 1: 
                rmdir(pathname);
                break;
            case 2: 
                ls(pathname);
                break; 
            case 3:
                cd(pathname);
                break;
            case 4:
                pwd(filesys->cwd);
                printf("\n");
                break;
            case 5:
                create(pathname);
                break;
            case 6:
                rm(pathname);
                break;
/**
            case 7:
                reload(pathname);
                break;
            case 8:
                save(pathname);
                break;
            case 9:
                menu();
                break;
            case 10:
                quit();
                return;
            default: 
                printf("invalid command %s\n", command);
 **/
        }
    }
    return 0;

}