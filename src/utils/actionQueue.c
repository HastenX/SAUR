typedef struct Node {
    Action action;
    struct Node* next;
} Node;

Node* constructNode(Action action) {
    Node* node=(Node*)malloc(sizeof(Node));
    node->action=action;

    return node;
}

/** -  Appends node to startNode
    if node added doesn't have 
    an action already inside linked 
    list. 
    -  Will free a node if it has identical
    actions inside list.
 */
void enqueue(Node* startNode, Node* node) {
    int nodePriority=getPriotity(node->action);

    Node* target=startNode;
    while(target!=node) {
        int targetPriority=getPriotity(startNode->action);
        if(target->action==node->action ) {
            free(node);
            break;
        }

        // Last node is the node with QUIT Action
        if(targetPriority>nodePriority) {
            Node tempNode=*startNode;

            *startNode=*node;
            *node=tempNode;

            startNode->next=node;
            break;
        } 

        target=target->next;
    }
}

/** deques list and returns Action value. 
    Will not free startNode if n=1.  
*/
Action dequeue(Node* startNode) {
    Action action=startNode->action;
    Node* target=startNode->next;

    if(target!=NULL) {
        startNode->action=target->action;
        startNode->next=target->next;

        free(target);
    }

    return action;
}

/**frees all nodes for linkedQueue. Includes start Node.*/
void freeQueue(Node* startNode) {
    Node* target=startNode;
    Node* nextTarget;

    while(target!=NULL) {
        nextTarget=target->next;
        free(target);
        target=nextTarget;
    }
}

bool hasAction(Node* startNode, Action action) {
    bool hasAction=false;
    Node* target=startNode;

    while(!hasAction && target->action!=QUIT) {
        hasAction=target->action==action;
    }
    return hasAction
}

void help();

void version();

void removeSaur();

void scanPkg(char** pkgs);

void scanAllPkg(char** pkgs);

void syncPkg(char** pkgs);

void queryPkg(char** pkgs);

void deptestPkg(char** pkgs);

void upgradePkg(char** pkgs);

void upgradeAllPkg(char** pkgs);

void removePkg(char** pkgs);

void removeAllPkg(char** pkgs);

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