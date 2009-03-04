#include <ports.h>
inherit M_CONNECTION;

void initialize( void ) {
  open_port( "tcp", FTP_PORT );
}

object connection( string ip, int port ) {
  object ob;

  ob = clone_object( "/kernel/net/ftp" );
  return( ob );
}