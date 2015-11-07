#ifndef PRIVILEGE_DOT_H
#define PRIVILEGE_DOT_H

/* check our caller */

#define DAEMON()  (sscanf(previous_program(), "/daemons/%*s") == 1)
#define KERNEL()  (sscanf(previous_program(), "/kernel/%*s") == 1)
#define SYSTEM()  (sscanf(previous_program(), "/sys/%*s") == 1)
#define ROOT()    (KERNEL() || SYSTEM())
#define CALLOUT() ((previous_program() == AUTO) && \
   (previous_function() == "_F_call_out2"))

/* special privilege flags for users */

#define PLAYER_L 0
#define WIZ_L    1
#define ADMIN_L  2

/* privilege flags */

#define PF_ORPHAN      32
#define PF_NO_ACCESS   64
#define PF_NO_CHECK    128

/* privilege types 0-31 */

#define PT_UNKNOWN      0
#define PT_PREDEF       1
#define PT_DOMAIN       2
#define PT_WIZARD       3
#define PT_PLAYER       4

/*
 * privilege is orphaned, ie, domain, wizard or player
 * no longer exists.
 */
#define PT_DOMAIN_BAD  (PT_DOMAIN | PF_ORPHAN)
#define PT_WIZARD_BAD  (PT_WIZARD | PF_ORPHAN)
#define PT_PLAYER_BAD  (PT_PLAYER | PF_ORPHAN)

#endif
