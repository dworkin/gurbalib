void usage() {
  write("Usage: addemote [-h] NAME RULE FORMAT\n");
  write("Add an emote to the emote database.\n");

// XXX Need to flesh out help here.... what is RULE, what is FORMAT?

  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}


void main( string str ) {
  string name;
  string fmt;
  string rule;
  if( sscanf( str, "%s %s", name, fmt ) != 2 ) {
    usage();
    return;
  }
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  if( sscanf( fmt, "%s %s", rule, fmt ) != 2 ) {
    fmt = rule;
    rule = "STR";
  } else if( uppercase( rule ) != "LIV" &&
	     uppercase( rule ) != "STR" &&
	     uppercase( rule ) != "OBJ" ) {
    fmt = rule + " " + fmt;
    rule = "";
  }

  EMOTE_D->add_emote( name, rule, fmt );
  write( "Emote added.\n" );
}
