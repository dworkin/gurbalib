#include <ports.h>

inherit M_PORT;

#ifndef DISABLE_FTP
void initialize(void) {
   open_port("tcp", FTP_PORT);
}

object connection(string ip, int port) {
   object con, session;

   session = clone_object("/sys/daemons/ftp_session");
   con = clone_object("/kernel/obj/net/connection");
   session->set_connection(con);
   return (con);
}

void create(void) {
   initialize();
}
#endif
