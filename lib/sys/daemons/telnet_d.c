#include <ports.h>

#ifdef SYS_NETWORKING

inherit M_PORT;

void initialize(void) {
   open_port("telnet", LOGIN_PORT);
}

void close_listener(void) {
   ::close_port();
}

#endif

object connection(string ip, int port) {
   object user;

   if (previous_object() && !require_priv("system")) {
      error("Illegal call to connection()");
   }

   console_msg("New telnet connection from " + ip + ":" + port + "\n");
   user = clone_object(USER_OB);
   return (user);
}

void open(varargs int port) {
}

void close(varargs int force) {
}

void create(void) {
#ifdef SYS_NETWORKING
   initialize();
#endif
}

string query_banner(void) {

   if (unguarded("file_exists", "/data/messages/login")) {
      return unguarded("read_file", "/data/messages/login");
   } else {
      return "Missing /data/messages/login you may want to reread " +
         "gurbalib/doc/INSTALLING";
   }
}

string query_motd(void) {
   if (unguarded("file_exists", "/data/messages/motd")) {
      return unguarded("read_file", "/data/messages/motd");
   } else {
      return "Missing /data/messages/login you may want to reread " +
         "gurbalib/doc/INSTALLING";
   }
}

/*
 * find telnet commands in input, return results in the form:
 *
 *  ({
 *    ({
 *      character sequence or telnet command,
 *      character sequence or telnet command,
 *      ...
 *    }),
 *    partial telnet command or empty string
 *  })
 */
string *parse_telnet(string str) {
    return parse_string("\
unescaped = /[^\xff]+/ \
escaped = /[^\xff]+\xff\xff/ \
command = /\xff[\x00-\xf9\xff]/ \
command = /\xff\xfa([^\xff]|\xff[^\xf0])*\xff\xf0/ \
command = /\xff[\xfb-\xfe]./ \
partial = /\xff/ \
partial = /\xff\xfa([^\xff]|\xff[^\xf0])*\xff?/ \
partial = /\xff[\xfb-\xfe]/ \
\
Sequence: Commands Data         ? sequence \
Sequence: Commands Data partial ? sequence_partial \
\
Commands: \
Commands: Commands Data command \
\
Data: \
Data: String                    ? telnet_data \
\
String: unescaped \
String: Escaped \
String: String unescaped \
String: String Escaped \
\
Escaped: escaped                ? telnet_escaped", str);
}

static string *sequence(string *parsed) {
    /* no partial telnet command */
    return ({ parsed, "" });
}

static string *sequence_partial(string *parsed) {
    int size;

    /* partial telnet command included */
    size = sizeof(parsed);
    return ({ parsed[.. size - 2], parsed[size - 1] });
}

static string *telnet_data(string *parsed) {
    return ({ implode(parsed, "") });
}

static string *telnet_escaped(string *parsed) {
    string str;

    str = parsed[0];
    return ({ str[.. strlen(str) - 2] });
}
