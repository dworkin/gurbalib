/*
 * check for 1.4 with network extensions, or 1.2/1.3 with network
 * package
 */
#if defined(__NETWORK_EXTENSIONS__) || defined(__NETWORK_PACKAGE__)
#ifndef SYS_NETWORKING
#define SYS_NETWORKING
#endif
#endif

#include "AUTO"

#include "/kernel/include/local_config.h"

#define LIB_NAME  "GurbaLib"
#define LIB_VERSION "v0.50"

#define TRUE  1
#define FALSE 0

#define LANGUAGE_D   "/daemons/language_d"
#define ANSI_D       "/daemons/ansi_d"
#define ALIAS_D      "/daemons/alias_d"
#define USER_D       "/sys/daemons/user_d"
#define DID_D        "/daemons/did_d"
#define LAST_D       "/daemons/last_d"
#define EVENT_D      "/daemons/event_d"
#define EMOTE_D      "/daemons/emote_d"
#define TELNET_D     "/daemons/telnet_d"
#define FTP_D        "/daemons/ftp_d"
#define SECURE_D     "/kernel/daemons/secure_d"
#define COMPILER_D   "/kernel/daemons/compiler_d"
#define ERROR_D      "/kernel/daemons/error_d"
#define CHANNEL_D    "/daemons/channel_d"
#define TIME_D       "/daemons/time_d"
#define IMUD_D       "/daemons/imud_d"
#define OBJECT_D     "/daemons/object_d"
#define RACE_D       "/daemons/race_d"
#define SKILL_D      "/daemons/skill_d"
#define MONEY_D      "/daemons/money_d"
#define BANISH_D     "/daemons/banish_d"
#define SITEBAN_D    "/daemons/siteban_d"
#define GUILD_D      "/daemons/guild_d"
#define PARSE_D      "/daemons/parse_d"
#define SCHEDULE_D   "/daemons/schedule_d"
#define LOG_D        "/sys/daemons/logd"
#define CMD_ERROR_D  "/daemons/cmd_error_d"
#define QUEST_D      "/daemons/quest_d"

#define CONNECTION      "/kernel/obj/net/connection"
#define PORT            "/kernel/obj/net/port"

#define M_CONNECTION    "/std/modules/m_connection"
#define M_PORT          "/std/modules/m_port"
#define M_SERIALIZE     "/std/modules/m_serialize"
#define M_MENU          "/std/modules/m_menu"

#define DRIVER          "/kernel/sys/driver"
#define AUTO            "/kernel/lib/auto"

#define PLAYER          "/sys/lib/player"
#define USER            "/sys/lib/user"

#define USER_OB         "/sys/obj/user/telnet"
#define PLAYER_OB       "/sys/obj/player"
#define TELNET_USER_OB  "/sys/obj/user/telnet"

