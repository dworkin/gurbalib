#include <ports.h>

#define grammar "whitespace=/[ 	]/ "+\
                "command=/restart/ "+\
                "command=/status/  "+\
                "command=/stop/ "+\
                "command=/start/ "+\
                "command=/enable/ "+\
                "command=/disable/ "+\
                "command=/switch/ "+\
                "command=/default/ "+\
                "arg=/[a-zA-Z0-9*]*/ "+\
                "arguments: command "+\
                "arguments: command arg"\

void usage() {
  write("Usage: intermud [-h] <command> [arg]\n");
  write("An interface to the intermud connection service.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("Valid commands:\n" +
    "  - status\n" +
    "    Shows information on the current intermud connection\n" +
    "  - stop\n" +
    "    Stops the current connection and unloads the intermud service\n" +
    "  - start\n" +
    "    Loads the intermud service and starts a connection (if enabled)\n" +
    "  - enable\n" +
    "    Enables intermud 3 connections\n" +
    "  - disable\n" +
    "    Disables intermud 3 connections\n" +
    "  - default [name]\n" +
    "    Displays the default router (and sets it if name is provided\n"
  );
}

static int check_istat() {
  if(!find_object(IMUD_D)) {
    return 0;
  } else {
    return 1 + IMUD_D->query_connected();
  }
}

void display_istat() {
  int s;
  string r;

  s = check_istat();

  switch(s) {
    case 0    : 
      r = "not loaded";
      break;
    case 1    :
      r = "loaded and offline\n";
      if(IMUD_D->query_enabled()) {
        r += "I3 is enabled";
      } else {
        r += "I3 is disabled";
      }
      r += "Default router: " + IMUD_D->query_default_router();
      break;
    case 2    :
      r = "loaded and online";
      r += "\nConnected to "+IMUD_D->query_current_router_name()+" ("+IMUD_D->query_current_router_ip()+")";
      break;
  }
  write( "I3 status: " + r );
}
                
void main( string str ) {
  mixed * args;
  string error;

  if( !require_priv( "system" ) ) {
    write("You must be admin to do that.");
    return;
  }

  if( !str ) {
    usage();
    return;
  }

  if( error = catch( args = parse_string( grammar, str ) ) ) {
    int pos;

    if( sscanf( error, "Bad token at offset %d", pos ) == 1 ) {
      write( "Invalid character " + str[pos..pos] + " at position " + pos + "." );
      return;
    } else {
      rethrow();
    }
  }

  if( !args ) {
    usage();
    return;
  }

  switch( args[0] ) {
    case "restart" :
      if( !find_object(IMUD_D) ) {
        write("IMUD_D is not loaded");
      } else if( !IMUD_D->query_enabled()) {
        write("IMUD_D is not enabled");
      } else {
        if( IMUD_D->query_connection() ) {
          IMUD_D->query_connection()->set_mode( MODE_DISCONNECT );
        }
      }
      break;
    case "status" :
      display_istat();
      break;
    case "enable" :
      IMUD_D->enable_i3();
      display_istat();
      break;
    case "disable" :
      if( !find_object(IMUD_D) ) {
        write("IMUD_D is not loaded");
      } else {
        IMUD_D->disable_i3();
        display_istat();
      }
      break;
    case "start" :
      if(find_object(IMUD_D)) {
        write("Already active");
      } else {
        call_other(IMUD_D,"???");
        write("IMUD_D loaded and starting");
      }
      break;
    case "stop" :
      if(!find_object(IMUD_D)) {
        write("IMUD_D is not active");
      } else {
        destruct_object(find_object(IMUD_D));
        write("IMUD_D unloaded");
      }
      break;
    case "switch" :
      if(!find_object(IMUD_D)) {
        write("IMUD_D is not active");
      } else {
        IMUD_D->switch_router();
      }
      break;
    case "default" :
      if(!find_object(IMUD_D)) {
        write("IMUD_D is not active");
      } else {
        if(sizeof(args) > 1) {
          IMUD_D->set_default_router(args[1]);
        }
        write("Default router: "+IMUD_D->query_default_router());
      }
      break;
  }
}
