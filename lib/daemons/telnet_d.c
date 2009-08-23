#include <ports.h>


#ifdef SYS_NETWORKING

inherit M_PORT;

void initialize() {
  open_port( "telnet", LOGIN_PORT );
}

void close_listener() {
  ::close_port();
}

#endif

object connection( string ip, int port ) {
  object user;

  if( previous_object() && !require_priv( "system" ) ) {
    error( "Illegal call to connection()" );
  }

  console_msg( "New telnet connection from " + ip + ":"+port+"\n" );
  user = clone_object( TELNET_USER_OB );
  return( user );
}

void open(varargs int port) {
}

void close(varargs int force) {
}

void create() {
#ifdef SYS_NETWORKING
  initialize();
#endif
}

string query_banner() {
  return unguarded( "read_file", "/data/messages/login" );
}

string query_motd() {
  return unguarded( "read_file", "/data/messages/motd" );
}

