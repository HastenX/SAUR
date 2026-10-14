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

/*
    Actions are accoiated with 
priority values, where 1 has
the highest priority and 3
has the lowest prioritity.
*/
int getPriotity(Action action) {
    switch(action) {
        case HELP:
            return 1;
        case QUIT:
            return 3;

        case VERSION:
            return 1;

        case QUERY:
            return 2;

        case DEPTEST:
            return 2;
            
        case SYNC:
            return 2;

        case REMOVE:
            return 2;

        case REMOVE_ALL:
            return 2;

        case REMOVE_SAUR:
            return 1;

        case UPGRADE:
            return 2;

        case UPGRADE_ALL:
            return 2;

        case SCAN:
            return 1;

        case SCAN_ALL:
            return 1;
    }
}
