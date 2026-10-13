

void editNodeVerbose(Node* startNode, const char* flag) {
    if(strcmp(flag,"--help")==0) {
        enqueue(startNode,constructNode(HELP));
        return;
    }
 
    if(strcmp(flag,"--sync")==0) {
        enqueue(startNode,constructNode(SCAN));
        enqueue(startNode,constructNode(SYNC));
        return;
    }
 
    if(strcmp(flag,"--remove")==0) {
        enqueue(startNode,constructNode(REMOVE));
        return;
    }
 
    if(strcmp(flag,"--uninstall-all")==0) {
        enqueue(startNode,constructNode(REMOVE_ALL));
        return;
    }
 
    if(strcmp(flag,"--upgrade")==0) {
        enqueue(startNode,constructNode(SCAN));
        enqueue(startNode,constructNode(UPGRADE));
        return;
    }
 
    if(strcmp(flag,"--update-all")==0) {
        enqueue(startNode,constructNode(SCAN));
        enqueue(startNode,constructNode(UPGRADE_ALL));
        return;
    }
 
    if(strcmp(flag,"--force-update-all")==0) {
        enqueue(startNode,constructNode(UPGRADE_ALL));
        return;
    }
 
    if(strcmp(flag,"--scan")==0) {
        enqueue(startNode,constructNode(SCAN));
        return;
    }

    if(strcmp(flag,"--scan-all")==0) {
        enqueue(startNode,constructNode(SCAN_ALL));
        return;
    }
 
    if(strcmp(flag,"--remove-saur")==0) {
        enqueue(startNode,constructNode(REMOVE_SAUR));
        return;
    }
  
    printf(
        "Error: '%s' is not defined as a flag!\n",
        flag
    );
    enqueue(startNode,constructNode(HELP));
} 

void editNodeEmbeded(Node* startNode, const char flag) {
    switch(flag) {
        case 'h':
            enqueue(startNode,constructNode(HELP));
            break;
        case 'Q':
            enqueue(startNode,constructNode(QUERY));
            break;
        case 'S':
            enqueue(startNode,constructNode(SCAN));
            enqueue(startNode,constructNode(SYNC));
            enqueue(startNode,constructNode(SYNC));
            break;
        case 'T':
            enqueue(startNode,constructNode(DEPTEST));
            break;
        case 'U':
            enqueue(startNode,constructNode(SCAN));
            enqueue(startNode,constructNode(UPGRADE));
            break;
        case 'V':
            enqueue(startNode,constructNode(VERSION));
            break;
        default:
            printf(
                "error: invalid option '%c'\n",
                flag
            );
            enqueue(startNode,constructNode(HELP));
            break;
    }
}

bool getOperations(const char* arg1) {
    int length=strlen(arg1);

    int operations=0;
    for(int i=1; i<length;i++) {

        int ascii=(int)arg1[i];
        operations+= 
            ascii == (int)'h'
            || ascii == (int)'Q'
            || ascii == (int)'R'
            || ascii == (int)'S'
            || ascii == (int)'T'
            || ascii == (int)'U'
            || ascii == (int)'V' ? 
            1:0;
    }

    return operations;
}

char* getErrors(int argc, const char* argv[]) {
    if(argc<2) {
        return "error: no operation specified (use -h for help)";
    }

    if(argv[1][0]!='-') {
        return "error: no operation specified (use -h for help)";
    }

    int ascii=(int)(argv[1][1]);

    // TODO: COMMENT IF STACK OVERFLOW
    if(getOperations(argv[1])<1) {
        char* str=(char*)(malloc(sizeof(char)*26));
        strcat(str,"error: invalid option '-");
        strcat(str,&argv[1][1]);
        strcat(str,"'");

        return str;
    }

    if(argc>2) {
        if(argv[2][0]=='-'
            || getOperations(argv[1])>1) {
            return "error: only one operation may be used at a time";
        }
    }
    
    return "NONE";
}

Node* genActionQueue(int argc, const char* argv[]) {
    Node* head=constructNode(QUIT);

    char* message=getErrors(argc,argv);

    if(strcmp(message,"NONE")!=0) {
        printf("%s\n",message);
        return head;
    }

    if(argv[1][0]=='-') {
        Action action;
        if(argv[1][1]!='-') {
            for(int i=1; i<strlen(argv[1]);i++) {
                editNodeEmbeded(head,argv[1][i]);

            }
        } else {
            editNodeVerbose(head,argv[1]);

        }
    }

    return head;
}
