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