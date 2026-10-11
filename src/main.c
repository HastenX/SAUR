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

const int MAXIMUM_ACTIONS=50;
int flagCounter=0;


char charToLower(char c) {
    char* return_char=&c;
    
    int asciiVal=tolower((int)*return_char);
    return (char)asciiVal;   
}

Action genActionEmbeded(const char flag) {
    switch(charToLower(flag)) {
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
                "Error: '%c' is not defined as a flag!\n",
                flag
            );
            return HELP;
            
    }
}

Action genActionVerbose(const char* flag) {
    if(strcmp(flag,"--help")==0) {
        return HELP;
    }
 
    if(strcmp(flag,"--install")==0) {
        return INSTALL;
    }
 
    if(strcmp(flag,"--uninstall")==0) {
        return REMOVE;
    }
 
    if(strcmp(flag,"--uninstall-all")==0) {
        return REMOVE_ALL;
    }
 
    if(strcmp(flag,"--update")==0) {
        return UPDATE;
    }
 
    if(strcmp(flag,"--update-all")==0) {
        return UPDATE_ALL;
    }
 
    if(strcmp(flag,"--force-update-all")==0) {
        return FORCE_UPDATE_ALL;
    }
 
    if(strcmp(flag,"--scan")==0) {
        return FORCE_UPDATE_ALL;
    }

    if(strcmp(flag,"--scan-all")==0) {
        return FORCE_UPDATE_ALL;
    }
 
    if(strcmp(flag,"--delete-saur")==0) {
        return DELETE_SAUR;
    }
  
    printf(
        "Error: '%s' is not defined as a flag!\n",
        flag
    );
    return HELP;

} 

Action* genActionData(int argc, const char* argv[]) {
    Action* actions=malloc(sizeof(Action)*MAXIMUM_ACTIONS);
    flagCounter=0;

    for (int i=1;i<argc;i++) {
        
        if(argv[i][0]=='-') {
        
            if(argv[i][1]!='-') {
        
                for(int j=1; j<strlen(argv[i]);j++) {
                    actions[flagCounter]=genActionEmbeded(
                        argv[i][j]
                    );

                    flagCounter++;
                }
            } else {
        
                actions[flagCounter]=genActionVerbose(
                    argv[i]   
                );     
                flagCounter++;
            }
        }
    }

    return actions;
}

char** genPkgs(int argc,const char* argv[]) {
    char** pkgs=calloc(argc,sizeof(char));
    int pkgNum=0;

    for(int i=1; i<argc; i++) {
        if(argv[i][0]!='-') {

            pkgs[i]=strdup(argv[i]);
            pkgNum++;
        }
    }
}

bool skipHelp=false;
void help() {

}

bool skipScan=false;
void scan(char** pkgs) {

}

bool skipScanALl=false;
void scanAll(char** pkgs) {

}

bool skipInstall=false;
void install(char** pkgs) {

}

bool skipUpdate=false;
void update(char** pkgs) {

}

bool skipUpdateAll=false;
void updateAll(char** pkgs) {

}

bool skipForceUpdateAll=false;
void forceUpdateAll(char** pkgs) {

}

bool skipUninstall=false;
void unistall(char** pkgs) {

}

bool skipUninstallAll=false;
void uninstallAll(char** pkgs) {

}

void uninstallSaur() { 

}

void runActions(Action* actions,char** pkgs) {
    for(int i=0; i<flagCounter; i++) {
        if(actions[i]!=NONE) {
            switch(actions[i]) {
                case HELP:
                    help();
                    break;

                case INSTALL:
                    scan(pkgs);
                    install(pkgs);
                    break;

                case UPDATE:
                    scan(pkgs);
                    update(pkgs);
                    break;

                case UPDATE_ALL:
                    scanAll(pkgs);
                    updateAll(pkgs);
                    break;

                case FORCE_UPDATE_ALL:
                    forceUpdateAll(pkgs);
                    break;

                case SCAN:
                    scan(pkgs);
                    break;

                case SCAN_ALL:
                    scanAll(pkgs);
                    break;

                case REMOVE:
                    unistall(pkgs);
                    break;

                case REMOVE_ALL:
                    uninstallAll(pkgs);
                    break;

                case DELETE_SAUR:
                    uninstallSaur();
                    break;
            }
        }
    }    
}

int main(int argc, const char* argv[]) {
    Action* actions=genActionData(argc,argv);

    char** pkgs=genPkgs(argc,argv);
    
    runActions(actions,pkgs); 

    free(actions);       

    return 0;
}

