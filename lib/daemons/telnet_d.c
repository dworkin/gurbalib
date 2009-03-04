#include <ports.h>
#define DRIVER find_object("/kernel/sys/driver")

inherit M_CONNECTION;

 void initialize() {
#ifdef SYS_NETWORKING
  DRIVER->message( "Opening telnet port...\n" );
  open_port("telnet", LOGIN_PORT);
#endif
 }

object connection( string ip, int port ) {

  object user;

  DRIVER->message( "New connection from " + ip + "\n" );
  user = clone_object( "/std/user" );
  return( user );
}

 void open(varargs int port) {
 }

 void close(varargs int force) {
 }

 void create() {
 initialize();
 }
