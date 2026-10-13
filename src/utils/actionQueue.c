

/*
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
    HELP,
    VERSION,
    QUIT,

    QUERY,
    SYNC,
    DEPTEST,
    
    REMOVE,
    REMOVE_ALL,
    
    UPGRADE,
    UPGRADE_ALL,

    SCAN,
    SCAN_ALL,
    
    REMOVE_SAUR   

} Action;

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
    -  Assumes QUIT is never 
    intentionally added to a list.
    -  Will free a node if it has identical
    actions inside list.
 */
void enqueue(Node* startNode, Node* node) {
    if(startNode->action==QUIT) {
        *startNode=*node;
        startNode->next=constructNode(QUIT);

        free(node);
        return;
    }

    Node* target=startNode;
    while(target!=node) {
        if(target->action==node->action ) {
            free(node);
            break;
        }

        // Last node is the node with QUIT Action
        if(target->next->action==QUIT) {
            node->next=target->next;
            target->next=node;
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