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
    printf("help\n");
}

void version() {
    printf("version\n");
}

void removeSaur() { 
    printf("removeSaur\n");
}

void scanPkg(char** pkgs) {
    printf("scanPkg\n");
}

void scanAllPkg(char** pkgs) {
    printf("scanAllPkg\n");
}

void syncPkg(char** pkgs) {
    printf("syncPkg\n");
}

void queryPkg(char** pkgs) {
    printf("queryPkg\n");    
}

void deptestPkg(char** pkgs) {
    printf("deptestPkg\n");
}

void upgradePkg(char** pkgs) {
    printf("upgradePkg\n");
}

void upgradeAllPkg(char** pkgs) {
    printf("upgradeAllPkg\n");
}

void removePkg(char** pkgs) {
    printf("removePkg\n");
}

void removeAllPkg(char** pkgs) {
    printf("removeAllPkg\n");
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

            case CHANGELOG:
                printf("E");
                break;

            case CASCADE:
                printf("F");
                break;

            case CLEAN:
                printf("G");
                break;
        }
    }   
}