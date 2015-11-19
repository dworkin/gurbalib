/*
 * Gurbalib port module
 *
 * This must be inherited by anything that wants to listen
 * on a port or use udp.
 *
 * udp is currently not implemented by the port object.
 *
 * Aidil @ Way of the Force
 *
 */

private object "port" port_object;
private int port_number;

/* For use by the object inheriting us */
nomask static void open_port(string proto, varargs mixed port) {
   /* 
    *
    * there is no privilege network in the default setup, through
    * one could conceivably create one. However, this does mean
    * we don't want a wizard called network, or a domain for that
    * matter.
    *
    */
   if (!require_priv("network")) {
      error("Permission denied.");
   }
   if (port_object) {
      if (intp(port)) {
         console_msg("Port already open: " + proto + ":" + (string)port + "\n");
      } else {
         console_msg("Port already open: " + proto + ":*\n");
      }
   } else {
      port_object = clone_object(PORT);
      port_object->set_user(this_object());
      port_object->open_port(proto, port);
   }
}

nomask static void close_port(void) {
   if (!require_priv("network")) {
      error("Permission denied.");
   }
   if (port_object) {
      destruct_object(port_object);
   }
}

nomask static int send_datagram(string str) {
   if (port_object) {
      return port_object->datagram(str);
   }
}


/* For use by the port object only */

nomask object _F_connection(string ip, int port) {
   if ((object "port") previous_object() == port_object) {
      return call_other(this_object(), "connection", ip, port);
   }
}

nomask void _F_open(varargs int port) {
   if ((object "port") previous_object() == port_object) {
      port_number = port;
      call_other(this_object(), "open", port);
   }
}

nomask void _F_close(varargs int force) {
   if ((object "port") previous_object() == port_object) {
      call_other(this_object(), "close", force);
   }
}


/* Public functions */

nomask object "port" query_port_object(void) {
   return port_object;
}

nomask int query_port_number(void) {
   return port_number;
}
