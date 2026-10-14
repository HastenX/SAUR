// STRING FOR RUNTIME ERRORS
char* failedFlag;

void addNodeLong(Node* startNode, const char* flag) {
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

    char* message=(char*)(malloc(sizeof(char)*(29+strlen(flag))));
    strcat(message,"saur: unrecognized option '");
    strcat(message,flag);
    strcat(message,"'");

    failedFlag=strdup(message);
    free(message);
} 

void addNodeShort(Node* startNode, const char flag) {
    switch(flag) {
        case 'h':
            enqueue(startNode,constructNode(HELP));
            break;
        case 'Q':
            enqueue(startNode,constructNode(QUERY));
            break;
        case 'S':
            enqueue(startNode,constructNode(SYNC));
            enqueue(startNode,constructNode(SCAN));
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
            char* message=(char*)(malloc(sizeof(char)*26));
            strcpy(message,"saur: invalid option '- '");
            message[23]=flag;

            failedFlag=strdup(message);
            free(message);
            break;
    }
}


int getOperations(const char* arg1) {
    int length=strlen(arg1);

    int operations=0;
    for(int i=1;i<length; i++) {
        operations+= 
            arg1[i] == 'h'
            || arg1[i] == 'Q'
            || arg1[i] == 'R'
            || arg1[i] == 'S'
            || arg1[i] == 'T'
            || arg1[i] == 'U'
            || arg1[i] == 'V' ? 
            1:0;
    }

    return operations;
}

char* getErrors(int argc, const char* argv[]) {
    if(argc<2) {
        return "saur: no operation specified (use -h for help)";
    }

    if(argv[1][0]!='-') {
        return "saur: no operation specified (use -h for help)";
    }

    if(argc>2) {
        if(argv[2][0]=='-') {
            return "saur: only one operation may be used at a time";
        }
    }

    if(getOperations(argv[1])>1) {
        return "saur: only one operation may be used at a time";
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
                addNodeShort(head,argv[1][i]);
                if(failedFlag!=NULL) {
                    break;
                }
            }
        } else {
            addNodeLong(head,argv[1]);
        }
    }

    if(failedFlag!=NULL) {
        printf("%s\n",failedFlag);
        free(failedFlag);

        freeQueue(head);
        head=constructNode(QUIT);
    }

    return head;
}
