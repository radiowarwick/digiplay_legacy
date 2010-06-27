#ifndef DPS_LDAP
#define DPS_LDAP
#include <ldap.h>

typedef LDAP * (*ldap_init_t)
    (LDAP_CONST char *host, int port);
typedef int (*ldap_set_option_t)
    (LDAP *ld,int option,LDAP_CONST void *invalue);
typedef int (*ldap_simple_bind_s_t)
    (LDAP *ld,LDAP_CONST char *who, LDAP_CONST char * passwd);
typedef char * (*ldap_err2string_t)
    (int err);
typedef int (*ldap_search_s_t)
    (LDAP *ld, LDAP_CONST char *base, int scope, LDAP_CONST char *filter,
     char **attrs, int attrsonly, LDAPMessage **res);
typedef int (*ldap_count_entries_t)
    (LDAP *ld, LDAPMessage *chain);
typedef LDAPMessage * (*ldap_first_entry_t)
    (LDAP *ld, LDAPMessage *chain);
typedef LDAPMessage * (*ldap_next_entry_t)
    (LDAP *ld, LDAPMessage *chain);
typedef char * (*ldap_first_attribute_t)
    (LDAP *ld, LDAPMessage *entry, BerElement **ber);
typedef char * (*ldap_next_attribute_t)
    (LDAP *ld, LDAPMessage *entry, BerElement *ber);
typedef char** (*ldap_get_values_t)
    (LDAP *ld, LDAPMessage *entry, LDAP_CONST char *target);
typedef void (*ldap_value_free_t)
    ( char** vals );
typedef void (*ldap_memfree_t)
    (void * p);
typedef int (*ldap_unbind_s_t)
    (LDAP *ld);
typedef int (*ldap_msgfree_t)
    (LDAPMessage *lm);
#endif

