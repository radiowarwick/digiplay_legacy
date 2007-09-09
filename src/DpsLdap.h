#ifndef DPS_LDAP
#define DPS_LDAP
#include <ldap.h>

typedef LDAP_F( LDAP * )
    (*ldap_init_t)(LDAP_CONST char *host, int port);
typedef LDAP_F( int )
    (*ldap_set_option_t)(LDAP *ld,int option,LDAP_CONST void *invalue);
typedef LDAP_F( int )
    (*ldap_simple_bind_s_t)(LDAP *ld,LDAP_CONST char *who,
            LDAP_CONST char * passwd);
typedef LDAP_F( char * )
    (*ldap_err2string_t)(int err);
typedef LDAP_F( int )
    (*ldap_search_s_t)(LDAP *ld, LDAP_CONST char *base, int scope,
            LDAP_CONST char *filter, char **attrs, int attrsonly,
            LDAPMessage **res);
typedef LDAP_F( int)
    (*ldap_count_entries_t)(LDAP *ld, LDAPMessage *chain);
typedef LDAP_F( LDAPMessage * )
    (*ldap_first_entry_t)(LDAP *ld, LDAPMessage *chain);
typedef LDAP_F( LDAPMessage * )
    (*ldap_next_entry_t)(LDAP *ld, LDAPMessage *chain);
typedef LDAP_F( char * )
    (*ldap_first_attribute_t)(LDAP *ld, LDAPMessage *entry, BerElement **ber);
typedef LDAP_F( char * )
    (*ldap_next_attribute_t)(LDAP *ld, LDAPMessage *entry, BerElement *ber);
typedef LDAP_F( char** )
    (*ldap_get_values_t)(LDAP *ld, LDAPMessage *entry, 
            LDAP_CONST char *target);
typedef LDAP_F( void )
    (*ldap_value_free_t)( char** vals );
typedef LDAP_F( void)
    (*ldap_memfree_t)(void * p);
typedef LDAP_F( int )
    (*ldap_unbind_s_t)(LDAP *ld);
typedef LDAP_F( int )
    (*ldap_msgfree_t)(LDAPMessage *lm);
#endif

