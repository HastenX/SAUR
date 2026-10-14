#include "includes.c"

int main(int argc, const char* argv[]) {
    Node* actionQueue=genActionQueue(argc,argv);

    char** pkgs=genPkgs(argc,argv);
    
    runActions(actionQueue,pkgs); 

    freeQueue(actionQueue);       

    return 0;
}
