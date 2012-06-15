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
#include "CONFIG"

#define SYS_COLOR

#ifndef SYS_PERSIST
#define SYS_PERSIST
#endif

#ifndef WORLD_PERSIST
#define WORLD_PERSIST 0
#endif

#ifndef DUMP_INTERVAL
#define DUMP_INTERVAL 3600
#endif

#ifndef CLEAN_UP_INTERVAL
#define CLEAN_UP_INTERVAL 7200
#endif

#ifndef RESET_INTERVAL
#define RESET_INTERVAL 3600
#endif

#ifndef HEART_BEAT_INTERVAL
#define HEART_BEAT_INTERVAL 2
#endif

#include <mudname.h>

#define LIB_NAME  "GurbaLib"
#define LIB_VERSION "v0.42 devel"

#ifndef ADMIN_EMAIL
#define ADMIN_EMAIL "you@some.place"
#endif

#ifndef LINKDEAD_TIMEOUT
#define LINKDEAD_TIMEOUT 10*60
#endif

#define TRUE  1
#define FALSE 0

#ifndef STARTING_ROOM
#define STARTING_ROOM "/domains/required/rooms/start"
#endif
#define VOID "/domains/required/rooms/void"

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

#define CONNECTION      "/kernel/obj/net/connection"
#define PORT            "/kernel/obj/net/port"

#define M_ACTIONS       "/std/modules/m_actions"
#define M_BLOCKEXITS    "/std/modules/m_block_exits"
#define M_BOARD         "/std/modules/m_board"
#define M_CONNECTION    "/std/modules/m_connection"
#define M_PORT          "/std/modules/m_port"
#define M_FAKE_OBJECT   "/std/modules/m_fake_object"
#define M_GUILD_MASTER  "/std/modules/m_guild_master"
#define M_MESSAGES      "/std/modules/m_messages"
#define M_OPENABLE      "/std/modules/m_openable"
#define M_PICKABLE      "/std/modules/m_pickable"
#define M_READABLE      "/std/modules/m_readable"
#define M_SAVERESTORE   "/std/modules/m_save_restore"
#define M_STORAGE       "/std/modules/m_storage"
#define M_TRIGGERS      "/std/modules/m_triggers"
#define M_UNDROPPABLE   "/std/modules/m_undroppable"
#define M_VENDOR        "/std/modules/m_vendor"
#define M_WANDER        "/std/modules/m_wander"
#define M_WEARABLE      "/std/modules/m_wearable"
#define M_WIELDABLE     "/std/modules/m_wieldable"
#define M_SERIALIZE     "/std/modules/m_serialize"
#define M_MENU          "/std/modules/m_menu"

#define DRIVER          "/kernel/sys/driver"
#define AUTO            "/kernel/lib/auto"

#define ROOM            "/std/room"
#define OBJECT          "/std/object"
#define CONTAINER       "/std/container"
#define BODY            "/std/body"
#define ARMOR           "/std/armor"
#define WEAPON          "/std/weapon"
#define MONSTER         "/std/monster"
#define COINS           "/std/coin"
#define SIGN            "/std/sign"
#define DOOR            "/std/door"
#define SHIELD          "/std/shield"
#define RACE            "/std/race"
#define MONSTER_RACE    "/std/monster_race" 

#define PLAYER          "/sys/lib/player"
#define USER            "/sys/lib/user"

#define USER_OB         "/sys/obj/user/telnet"
#define PLAYER_OB       "/sys/obj/player"
#define TELNET_USER_OB  "/sys/obj/user/telnet"
#define SSH_USER_OB     "/sys/obj/user/ssh"
#define HTTP_USER_OB    "/sys/obj/user/http"
#define FTP_USER_OB     "/sys/obj/user/ftp_command"
#define FTP_DATA_OB     "/sys/obj/user/ftp_data"

#ifndef WIZ_DIR
#define WIZ_DIR "/wiz/"
#endif

#ifndef RACE_DIR
#define RACE_DIR "/domains/required/objects/races/"
#endif

#ifndef DOMAINS_DIR
#define DOMAINS_DIR "/domains/"
#endif

#ifndef MAX_DEPTH
#define MAX_DEPTH       256
#endif

#ifndef MAX_TICKS
#define MAX_TICKS       1000000
#endif

#ifndef DEFAULT_WIDTH
#define DEFAULT_WIDTH 80
#endif
