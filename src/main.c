#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#include <stdbool.h>


/*
    UTILITY:
    Enum contains singular and
plural processes. For example,
'UPDATE' v. 'UPDATE_ALL'. If a
value is singular, it applies
to only specified packages.
If it is plural, it applies
to every package managed by
SAUR. 
*/
typedef enum Action {
    NONE,
    HELP,
    INSTALL,
    
    REMOVE,
    REMOVE_ALL,
    
    UPDATE,
    /*IMPLIED TO THROW ERRORS FOR
    INFECTED PACKAGES. UPDATING 
    REQUIRES SCANING*/
    UPDATE_ALL,
    FORCE_UPDATE_ALL,

    SCAN,
    SCAN_ALL,
    
    DELETE_SAUR   

} Action;
const int MAXIMUM_ACTIONS=11;
int flagCounter=0;


char charToLower(char c) {
    char* return_char=&c;
    
    int asciiVal=tolower((int)*return_char);
    return (char)asciiVal;   
}

Action genActionEmbeded(const char* flag) {
//        printf("\n%d:%c\n",i,charToLower((*flag)[i]));
    switch(charToLower((*flag))) {
        case 'h':
            return HELP;
        case 's':
            return INSTALL;
        case 'y':
            return UPDATE;
        case 'u':
            return UPDATE_ALL;
        case 'f':
            return FORCE_UPDATE_ALL;
        case 'i':
            return SCAN;
        case 'a':
            return SCAN_ALL;
        case 'r':
            return REMOVE;
        case 'd':
            return REMOVE_ALL;
        default:
            printf(
                "\nError: '%s' is not defined as a flag!\n",
                *flag
            );
            return HELP;
            
    }
}

Action genActionVerbose(const char** flag) {
    if(strcmp(*flag,"--help")==0) {
        return HELP;
    }
 
    if(strcmp(*flag,"--install")==0) {
        return INSTALL;
    }
 
    if(strcmp(*flag,"--uninstall")==0) {
        return REMOVE;
    }
 
    if(strcmp(*flag,"--uninstall-all")==0) {
        return REMOVE_ALL;
    }
 
    if(strcmp(*flag,"--update")==0) {
        return UPDATE;
    }
 
    if(strcmp(*flag,"--update-all")==0) {
        return UPDATE_ALL;
    }
 
    if(strcmp(*flag,"--force-update-all")==0) {
        return FORCE_UPDATE_ALL;
    }
 
    if(strcmp(*flag,"--scan")==0) {
        return FORCE_UPDATE_ALL;
    }

    if(strcmp(*flag,"--scan-all")==0) {
        return FORCE_UPDATE_ALL;
    }
 
    if(strcmp(*flag,"--delete-saur")==0) {
        return DELETE_SAUR;
    }
  
    printf(
        "\nError: '%s' is not defined as a flag!\n",
        *flag
    );
    return HELP;

} 

Action* genActionData(int argc, const char** argv[]) {
    Action* actions=malloc(sizeof(Action)*10);
    flagCounter=0;
    for (int i=1;i<argc;i++) {
        if((*argv)[i][0]=='-') {
            if((*argv)[i][1]!='-') {
                for(int j=1; j<strlen((*argv)[i]);j++) {
                    actions[flagCounter]=genActionEmbeded(
                        &(*argv)[i][j]
                    );

                    flagCounter++;
                }
            } else {
                actions[flagCounter]=genActionVerbose(
                    &(*argv)[i]   
                );     
                flagCounter++;
            }
        }
    }

    return actions;
}

Action* genActionSet(Action* passed) {
    int appendIndex=0;

    for(int i=0; i<flagCounter; i++) {
        for(int j=i+1; j<flagCounter; j++) {
             if(passed[j]==NONE) {
                 continue;
             }
             if(passed[i]==passed[j]) {
                 passed[j]=NONE;
             } 
        }
    }
    return passed;
}

void runActions(Action* actions) {
    for(int i=0; i<flagCounter; i++) {
        if(actions[i]!=NONE) {
            printf("%d",i);

        }
    }    
 
    free(actions);
}

int main(int argc, const char* argv[]) {
    Action* actions=genActionData(argc,&argv);
    actions=genActionSet(actions);
    runActions(actions);        

    return 0;
}

void help() {

}

void install(char** pkg) {

}

void update() {

}

void unistall() {

}

void uninstall_all() {

}

void uninstall_saur() { 

}

