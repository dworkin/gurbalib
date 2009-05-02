#include <ports.h>

inherit M_PORT;

void initialize() {
#ifdef SYS_NETWORKING
  open_port("telnet", LOGIN_PORT);
#endif
}

void close_listener() {
  ::close_port();
}

object connection( string ip, int port ) {

  object user;

  console_msg( "New telnet connection from " + ip + ":"+port+"\n" );
  user = clone_object( TELNET_USER_OB );
  return( user );
}

void open(varargs int port) {
}

void close(varargs int force) {
}

void create() {
  initialize();
}
