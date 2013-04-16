/* 
  Defines for MSSP replies

  Change these defines to alter what is sent in MSSP replies to MUD crawlers.
  XXX show where you can find the MSSP specification and see if there is more
      to do here....
*/

/* Required */
#define MSSP_NAME IMUD_NAME
#define MSSP_PLAYERS (sizeof(players()))
#define MSSP_UPTIME status()[ST_STARTTIME]

/* Generic */
#define MSSP_CODEBASE LIB_NAME + " " + LIB_VERSION + "/" + status()[ST_VERSION]
#define MSSP_PORT LOGIN_PORT /* ports.h */
#define MSSP_CONTACT ADMIN_EMAIL /* local_config.h */

/* Categorization */
#define MSSP_FAMILY "LPMud"
#define MSSP_STATUS "ALPHA" /* "ALPHA", "CLOSED BETA", "OPEN BETA", "LIVE" */
#define MSSP_INTERMUD "I3"

/* Protocols */
#define MSSP_ANSI "1"
#define MSSP_MCCP "0"

/* Commercial */
#define MSSP_PAY_TO_PLAY "0"
#define MSSP_PAY_FOR_PERKS "0"
