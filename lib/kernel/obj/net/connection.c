/*
 * GurbaLib tcp connection object
 * Inspired by the DGD kernel lib and the Way of the Force kernel
 *
 * Feb 2009, Aidil@Way of the Force
 *
 * TODO: Add TLS support when it gets added to the kernel
 *
 */

#include <status.h>
#include <ports.h>

private object user;            /* our user object */
private int mode;               /* connection mode */
private int blocked;            /* connection blocked? */
private string buffer;          /* buffered output string */
private string protocol;        /* telnet or tcp */


void set_user(object u) {
  if(previous_program() == M_CONNECTION) {
    user = u;
  }
}

object query_user() {
  return user;
}

void create() {
  buffer = nil;
  protocol = nil;
  user = nil;
  blocked = 0;
  mode = MODE_ECHO;
}

void set_mode(int m) {
  if (m != mode && m != MODE_NOCHANGE) {
    if (m == MODE_DISCONNECT) {
      destruct_object(this_object());
    } else if (m >= MODE_UNBLOCK) {
      if (m - MODE_UNBLOCK != blocked) {
        block_input(blocked = m - MODE_UNBLOCK);
      }
    } else {
      if (blocked) {
        block_input(blocked = FALSE);
      }
      mode = m;
    }
  }
}

int query_mode() {
  return (blocked) ? MODE_BLOCK : mode;
}

void set_protocol(string proto) {
  if(protocol) {
    return;
  } else {
    switch(proto) {
      case "telnet" :
        protocol = proto;
        set_mode(MODE_UNBLOCK | MODE_ECHO);
        break;
      case "tcp" :
        protocol = proto;
        set_mode(MODE_UNBLOCK | MODE_RAW);
        break;
      default :
        error("Unknown protocol");
        break;
    }
  }
}

static void open() {
  if(user) user->open();
}

static void close(varargs int force) {
  if(user) {
    catch(user->close(force));
  }
  if(force) {
    destruct_object(this_object());
  }
}

#ifdef SYS_NETWORKING
void connect(string ip, int port, varargs string proto) {
  if(previous_object() == user) {
    if(!proto) proto = "tcp";

    set_protocol(proto);

    if(protocol) {
      ::connect(ip,port,proto);
    } 
  }
}
#endif

int message(string str) {
  int len;

  if(previous_object() != user) {
    error("Illegal call to connection object");
  }

  buffer = nil;
  len = send_message(str);
  if (len != strlen(str)) {
    buffer = str[len ..];
    return 0;
  } else {
    return 1;
  }
}

static void message_done() {
  if (buffer) {
    send_message(buffer);
    buffer = nil;
  } else if (user) {
    set_mode(MODE_NOCHANGE);
  }
  if(user) user->message_done();
}

static void receive_error(string err) {
  "/kernel/sys/driver"->message(err);
  if(user) user->receive_error(err);
}

static void receive_message(string str) {
  if(user) {
    user->receive_message(str);
  } else {
    /*
     * Our user is gone, we have no reason to be here either.
     */
    destruct_object(this_object());
  }
}
