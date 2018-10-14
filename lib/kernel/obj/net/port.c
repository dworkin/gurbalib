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
