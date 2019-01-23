#include <ports.h>

private object "connection" connection;

nomask static void connect(string ip, int port) {
   if (!require_priv("network")) {
      error("Permission denied.");
   }
   if (!connection) {
      connection = clone_object(CONNECTION);
      connection->set_user(this_object());
      connection->connect(ip, port);
   }
}

static int send_message(string str) {
   if (connection) {
      return connection->message(str);
   }
}

nomask static int set_mode(int m) {
   if (connection) {
      return connection->set_mode(m);
   }
}

nomask static void disconnect(void) {
   if (!require_priv("network")) {
      error("Permission denied.");
   }
   if (connection) {
      connection->set_mode(MODE_DISCONNECT);
   }
}

void open(varargs int port) {
}

void close(varargs int force) {
}

nomask object "connection" query_connection(void) {
   return connection;
}

nomask void set_connection(object con) {
   connection = con;
   connection->set_user(this_object());
}

static void destructing(void) {
   if (!require_priv("network")) {
      error("Permission denied.");
   }

   if (connection) {
      connection->set_mode(MODE_DISCONNECT);
   }
}
