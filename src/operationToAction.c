char* addNodeLong(Node* startNode, const char* flag) {
    char* failedFlag="NONE";
    if(strcmp(flag,"--help")==0) {
        enqueue(startNode,constructNode(HELP));
        return failedFlag;
    }
 
    if(strcmp(flag,"--sync")==0) {
        enqueue(startNode,constructNode(SCAN));
        enqueue(startNode,constructNode(SYNC));
        return failedFlag;
    }
 
    if(strcmp(flag,"--remove")==0) {
        enqueue(startNode,constructNode(REMOVE));
        return failedFlag;
    }
 
    if(strcmp(flag,"--uninstall-all")==0) {
        enqueue(startNode,constructNode(REMOVE_ALL));
        return failedFlag;
    }
 
    if(strcmp(flag,"--upgrade")==0) {
        enqueue(startNode,constructNode(SCAN));
        enqueue(startNode,constructNode(UPGRADE));
        return failedFlag;
    }
 
    if(strcmp(flag,"--update-all")==0) {
        enqueue(startNode,constructNode(SCAN));
        enqueue(startNode,constructNode(UPGRADE_ALL));
        return failedFlag;
    }
 
    if(strcmp(flag,"--force-update-all")==0) {
        enqueue(startNode,constructNode(UPGRADE_ALL));
        return failedFlag;
    }
 
    if(strcmp(flag,"--scan")==0) {
        enqueue(startNode,constructNode(SCAN));
        return failedFlag;
    }

    if(strcmp(flag,"--scan-all")==0) {
        enqueue(startNode,constructNode(SCAN_ALL));
        return failedFlag;
    }
 
    if(strcmp(flag,"--remove-saur")==0) {
        enqueue(startNode,constructNode(REMOVE_SAUR));
        return failedFlag;
    }

    char* message=(char*)(malloc(sizeof(char)*(29+strlen(flag))));
    strcat(message,"saur: unrecognized option '");
    strcat(message,flag);
    strcat(message,"'");

    failedFlag=strdup(message);
    free(message);

    return failedFlag;
} 

char* addNodeShort(Node* startNode, const char flag) {
    char* failedFlag="NONE";
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
        case 'R':
            enqueue(startNode,constructNode(SCAN));
            enqueue(startNode,constructNode(REMOVE));
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
        // GENERIC CASES
        case 'c':
            enqueue(startNode,constructNode(c));
            break;
        case 'd':
            enqueue(startNode,constructNode(d));
            break;
        case 'e':
            enqueue(startNode,constructNode(e));
            break;
        case 'g':
            enqueue(startNode,constructNode(g));
            break;
        case 'i':
            enqueue(startNode,constructNode(i));
            break;
        case 'k':
            enqueue(startNode,constructNode(k));
            break;
        case 'l':
            enqueue(startNode,constructNode(l));
            break;
        case 'm':
            enqueue(startNode,constructNode(m));
            break;
        case 'n':
            enqueue(startNode,constructNode(n));
            break;
        case 'o':
            enqueue(startNode,constructNode(o));
            break;
        case 'p':
            enqueue(startNode,constructNode(p));
            break;
        case 'q':
            enqueue(startNode,constructNode(q));
            break;
        case 's':
            enqueue(startNode,constructNode(s));
            break;
        case 't':
            enqueue(startNode,constructNode(t));
            break;
        case 'u':
            enqueue(startNode,constructNode(u));
            break;
        case 'w':
            enqueue(startNode,constructNode(w));
            break;
        case 'y':
            enqueue(startNode,constructNode(y));
            break;
        default:
            char* message=(char*)(malloc(sizeof(char)*26));
            strcpy(message,"saur: invalid option '- '");
            message[23]=flag;

            failedFlag=strdup(message);
            free(message);
            break;
    }
    return failedFlag;
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
        if(argv[1][1]!='-') {
            for(int i=1; i<strlen(argv[1]);i++) {
                message=addNodeShort(head,argv[1][i]);
                if(message!=NULL) {
                    break;
                }
            }
        } else {
            message=addNodeLong(head,argv[1]);
        }
    }

    if(message!="NONE") {
        printf("%s\n",message);
        free(message);

        freeQueue(head);
        head=constructNode(QUIT);
    }

    replaceGenericAction(
        getOperationNode(head)
    );

    return head;
}
