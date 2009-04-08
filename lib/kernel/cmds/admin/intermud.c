#include <ports.h>

#define grammar "whitespace=/[ 	]/ "+\
                "command=/restart/ "+\
                "command=/status/  "+\
                "command=/stop/ "+\
                "command=/start/ "+\
                "command=/enable/ "+\
                "command=/disable/ "+\
                "arg=/[a-zA-Z0-9]/ "+\
                "arguments: command "+\
                "arguments: command arg"\

void display_usage() {
  "/cmds/player/help"->main( "intermud" );
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
      break;
    case 2    :
      r = "loaded and online";
      break;
  }
  write( "I3 status: " + r );
}
                
void main( string str ) {
  mixed * args;
  string error;

  if( !str ) {
    display_usage();
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
    display_usage();
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
        IMUD_D->close( 0 );
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
  }
}
