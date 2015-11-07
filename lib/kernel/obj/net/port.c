/*
 * GurbaLib port object
 * Inspired by the DGD kernel lib and the Way of the Force kernel
 *
 * March 2009, Aidil@Way of the Force
 */

#include <status.h>
#include <ports.h>

private object user;            /* our user object */
private int port;               /* our port number */
private int blocked;            /* port blocked? */
private string protocol;        /* telnet or tcp */

void set_user(object u) {
   if (previous_program() == M_PORT) {
      user = u;
   }
}

object query_user(void) {
   return user;
}

static void create(void) {
   protocol = nil;
   user = nil;
   blocked = 0;
   port = 0;
}

private void set_protocol(string proto) {
   if (protocol) {
      return;
   } else {
      switch (proto) {
         case "telnet":
         case "tcp":
         case "udp":
            protocol = proto;
            break;
         default:
            error("Unknown protocol");
            break;
      }
   }
}

static void _open(mixed * tls, int p) {
   port = p;

   if (user) {
      user->_F_open(p);
   }
}

void open(int p) {
   _open(DRIVER->new_tls(), p);
}

static void _close(mixed * tls, varargs int force) {
   if (user) {
      catch(user->_F_close(force));
   }
   if (!force) {
      destruct_object(this_object());
   }
}

void close(varargs int force) {
   _close(DRIVER->new_tls(), force);
}

#ifdef SYS_NETWORKING
void open_port(string proto, varargs mixed p) {
   if (previous_object() == user) {
      console_msg("Opening port " + proto + ":" + p + "\n");
      set_protocol(proto);
      if (!intp(p)) {
         ::open_port(proto);
      } else {
         if (p < 1 || p > 65535) {
            error("Bad port " + p + " in open_port()");
         }
         ::open_port(proto, p);
      }
   }
}

static object _connection(mixed * tls, string ip, int port) {
   object ob;

   if (user) {
      ob = user->_F_connection(ip, port);
      return ob;
   } else {
      error("No user set in port object!");
   }
}

object connection(string ip, int port) {
   return _connection(DRIVER->new_tls(), ip, port);
}

int datagram(string str) {
   int len;

   if (previous_object() != user) {
      error("Illegal call to port object");
   }
   if (protocol != "udp" || !port) {
      error("Bad protocol or port not open");
   }
}

static void _datagram_done(mixed * tls) {
}

static void datagram_done(void) {
   _datagram_done(DRIVER->new_tls());
}

static void _receive_error(mixed * tls, string err) {
   console_msg(err + "\n");

   if (user) {
      user->_F_receive_error(err);
   }
}

static void receive_error(string err) {
   _receive_error(DRIVER->new_tls(), err);
}

static void _receive_datagram(mixed * tls, string str, string ip, int p) {
   if (user) {
      user->_F_receive_datagram(ip, p);
   }
}

static void receive_datagram(string str, string ip, int p) {
   _receive_datagram(DRIVER->new_tls(), str, ip, p);
}

void reopen(void) {
   if (previous_program() == DRIVER) {
      console_msg("Reopening port " + protocol + ":" + port + "\n");
      ::open_port(protocol, port);
   } else {
      error("Bad call to reopen");
   }
}
#endif
