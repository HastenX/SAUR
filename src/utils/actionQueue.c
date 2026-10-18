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
        if(nodePriority<targetPriority) {
            Node tempNode=*target;
            *target=*node;
            *node=tempNode;

            target->next=node;
            break;
        } 

        target=target->next;
    }
}

/** deques list and returns Action value. 
    Will not free startNode if n=1.  
*/
Action dequeue(Node* startNode) {
    Node* target=startNode->next;
    Action action;

    if(target!=NULL) {
        action=startNode->action;

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

Node* getOperationNode(Node* startNode) {
    Node* target=startNode;

    while(target->action!=QUIT) {
        if(isOperation(target->action)) {
            return target;
        }
        target=target->next;
    }
    return NULL;
}

Action cSwitch(Action operation) {
    switch(operation) {
        case QUERY:
            return CHANGELOG;
        case REMOVE:
            return CASCADE;
        case SYNC:
            return CLEAN;
        default:
            return operation;
    }
}

// TODO: FULLY IMPLEMENT OVER THE TIMESPAN OF 
// 5 FUCKING YEARS
Action genericSwitch(Action generic, Action operation) {
    switch(generic) {
        case 'c':
            return cSwitch(operation);
            break;
        // case 'd':
        //     enqueue(startNode,constructNode(
        //         dSwitch(operation)
        //     ));
        //     break;
        // case 'e':
        //     enqueue(startNode,constructNode(
        //         eSwitch(operation)
        //     ));
        //     break;
        // case 'g':
        //     enqueue(startNode,constructNode(
        //         gSwitch(operation)
        //     ));
        //     break;
        // case 'i':
        //     enqueue(startNode,constructNode(
        //         iSwitch(operation)
        //     ));
        //     break;
        // case 'k':
        //     enqueue(startNode,constructNode(
        //         kSwitch(operation)
        //     ));
        //     break;
        // case 'l':
        //     enqueue(startNode,constructNode(
        //         lSwitch(operation)
        //     ));
        //     break;
        // case 'm':
        //     enqueue(startNode,constructNode(
        //         mSwitch(operation)
        //     ));
        //     break;
        // case 'n':
        //     enqueue(startNode,constructNode(
        //         nSwitch(operation)
        //     ));
        //     break;
        // case 'o':
        //     enqueue(startNode,constructNode(
        //         oSwitch(operation)
        //     ));
        //     break;
        // case 'p':
        //     enqueue(startNode,constructNode(
        //         pSwitch(operation)
        //     ));
        //     break;
        // case 'q':
        //     enqueue(startNode,constructNode(
        //         qSwitch(operation)
        //     ));
        //     break;
        // case 's':
        //     enqueue(startNode,constructNode(
        //         sSwitch(operation)
        //     ));
        //     break;
        // case 't':
        //     enqueue(startNode,constructNode(
        //         tSwitch(operation)
        //     ));
        //     break;
        // case 'u':
        //     enqueue(startNode,constructNode(
        //         uSwitch(operation)
        //     ));
        //     break;
        // case 'w':
        //     enqueue(startNode,constructNode(
        //         wSwitch(operation)
        //     ));
        //     break;
        // case 'y':
        //     enqueue(startNode,constructNode(
        //         ySwitch(y,operation)
        //     ));
    }
}

void replaceGenericAction(Node* operationNode) {
    Node* target=operationNode->next;
    Action operation=target->action;
    Action option;
    while(target->action!=QUIT) {
        option=genericSwitch(
            dequeue(target),
            operation
        );

        enqueue(operationNode,constructNode(option));
    }
}

// TODO: DETERMINE IF DEPRICATED
// void removeAction(Node* startNode, Action action) {
//     Node* target=startNode;
//     Node* prevTarget=NULL;

//     bool remove=false;
//     while(remove!=true || target!=NULL) {
//         remove=startNode->action==action;

//         prevTarget=target;
//         target=target->next;
//     }

//     if(remove) {
//         if(target==startNode) {
//             dequeue(startNode);
//             return;
//         }
//         if(target->next==NULL) {
//             prevTarget->next=NULL;
//             free(target);

//             return;
//         }
//         prevTarget->next=target->next;
//         free(target);
//     }
// }

