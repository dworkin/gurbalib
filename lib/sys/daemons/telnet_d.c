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
