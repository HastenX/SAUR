#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#include <stdbool.h>

#include "utils/includes.c"

char** genPkgs(int argc,const char* argv[]) {
    if(argc<3) {
        char** strArray=(char**)calloc(1,sizeof(char)*4);
        strArray[0]="NONE";
        return strArray;
    }

    char** pkgs=calloc(argc-2,sizeof(char));
    for(int i=2; i<argc; i++) {
        if(argv[i][0]!='-') {

            pkgs[i-2]=strdup(argv[i]);
        }
    }
    return pkgs;

}

void help() {

}

void version() {

}

void removeSaur() { 

}

void scanPkg(char** pkgs) {

}

void scanAllPkg(char** pkgs) {

}

void syncPkg(char** pkgs) {
    
}

void queryPkg(char** pkgs) {

}

void deptestPkg(char** pkgs) {

}

void upgradePkg(char** pkgs) {

}

void upgradeAllPkg(char** pkgs) {

}

void removePkg(char** pkgs) {

}

void removeAllPkg(char** pkgs) {

}

void runActions(Node* startNode,char** pkgs) {
    while(startNode->action!=QUIT) {
        switch(dequeue(startNode)) {
            case HELP:
                help();
                break;

            case VERSION:
                version();
                break;

            case QUERY:
                queryPkg(pkgs);
                break;

            case DEPTEST:
                deptestPkg(pkgs);
                break;
                
            case SYNC:
                syncPkg(pkgs);
                break;

            case REMOVE:
                removePkg(pkgs);
                break;

            case REMOVE_ALL:
                removeAllPkg(pkgs);
                break;

            case REMOVE_SAUR:
                removeSaur();
                break;

            case UPGRADE:
                upgradePkg(pkgs);
                break;

            case UPGRADE_ALL:
                upgradeAllPkg(pkgs);
                break;

            case SCAN:
                scanPkg(pkgs);
                break;

            case SCAN_ALL:
                scanAllPkg(pkgs);
                break;
        }
    }   
}

int main(int argc, const char* argv[]) {
    Node* actionQueue=genActionQueue(argc,argv);

    char** pkgs=genPkgs(argc,argv);
    
    runActions(actionQueue,pkgs); 

    freeQueue(actionQueue);       

    return 0;
}
