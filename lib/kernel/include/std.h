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
#define ALIAS_D      "/sys/daemons/alias_d"
#define USER_D       "/sys/daemons/user_d"
#define DOMAIN_D     "/sys/daemons/domain_d"
#define DID_D        "/daemons/did_d"
#define LAST_D       "/daemons/last_d"
#define EVENT_D      "/daemons/event_d"
#define EMOTE_D      "/daemons/emote_d"
#define TELNET_D     "/sys/daemons/telnet_d"
#define FTP_D        "/sys/daemons/ftp_d"
#define COMMAND_D    "/sys/daemons/command_d"
#define SECURE_D     "/kernel/daemons/secure_d"
#define COMPILER_D   "/kernel/daemons/compiler_d"
#define ERROR_D      "/kernel/daemons/error_d"
#define CHANNEL_D    "/daemons/channel_d"
#define TIME_D       "/daemons/time_d"
#define IMUD_D       "/sys/daemons/imud_d"
#define OBJECT_D     "/daemons/object_d"
#define RACE_D       "/daemons/race_d"
#define SKILL_D      "/daemons/skill_d"
#define MONEY_D      "/daemons/money_d"
#define BANISH_D     "/sys/daemons/banish_d"
#define SITEBAN_D    "/daemons/siteban_d"
#define GUILD_D      "/daemons/guild_d"
#define PARSE_D      "/daemons/parse_d"
#define SCHEDULE_D   "/daemons/schedule_d"
#define LOG_D        "/sys/daemons/log_d"
#define QUEST_D      "/daemons/quest_d"

#define CONNECTION      "/kernel/obj/net/connection"
#define PORT            "/kernel/obj/net/port"

#define M_CONNECTION    "/sys/lib/modules/m_connection"
#define M_COMMAND       "/sys/lib/modules/m_command"
#define M_CMDS          "/sys/lib/modules/m_cmds"
#define M_PORT          "/sys/lib/modules/m_port"
#define M_SERIALIZE     "/sys/lib/modules/m_serialize"

#define M_MENU          "/std/modules/m_menu"

#define DRIVER          "/kernel/sys/driver"
#define AUTO            "/kernel/lib/auto"

#define USER_OB         "/sys/obj/user"
#define PLAYER_OB       "/sys/obj/player"

