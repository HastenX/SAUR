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
    // ENUMS FOR OPERATIONS
    HELP,
    VERSION,

    QUERY,
    SYNC,
    DEPTEST,
    
    REMOVE,
    REMOVE_ALL,
    
    UPGRADE,
    UPGRADE_ALL,

    REMOVE_SAUR, 

    // ENUMS FOR MISC. OPERATIONS
    SCAN,
    SCAN_ALL,  
    QUIT,

    // GENERIC ENUMS FOR OPERATION-OPTIONS:

    // NOTE: FOR ENUM OPERATIONS TO WORK,
    // ALL GENERIC VALUES MUST BE BETWEEN
    // c AND y.
    c,
    d,
    e,
    g,
    i,
    k,
    l,
    m,
    n,
    o,
    p,
    q,
    s,
    t,
    u,
    w,
    y,

    // OPTIONS THAT WILL REPLACE GENERICS:
    CHANGELOG,
    CASCADE,
    CLEAN

    

} Action;

/*
    Actions are accoiated with 
priority values, where 1 has
the highest priority and 3
has the lowest prioritity.
*/
int getPriotity(Action action) {
    switch(action) {
        case SCAN:
            return 1;

        case SCAN_ALL:
            return 1;

        case CHANGELOG:
            return 1;

        case CASCADE:
            return 1;

        case CLEAN:
            return 1;

        case HELP:
            return 2;

        case VERSION:
            return 2;

        case REMOVE_SAUR:
            return 2;

        case QUERY:
            return 2;

        case DEPTEST:
            return 2;
            
        case SYNC:
            return 2;

        case UPGRADE:
            return 2;

        case UPGRADE_ALL:
            return 2;

        case REMOVE:
            return 2;

        case REMOVE_ALL:
            return 2;

        case QUIT:
            return 4;
        
        // ENUM CASE:
        default:
            return 3;
        
    }
}

bool isGeneric(Action action) {
    return action>=c && action<=y;
}

bool isOperation(Action action) {
    return action>=HELP && action<=REMOVE_SAUR;
}
