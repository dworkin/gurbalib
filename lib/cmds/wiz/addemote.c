void main( string str ) {
  string name;
  string fmt;
  string rule;
  if( sscanf( str, "%s %s", name, fmt ) != 2 ) {
    write( "Useage: addemote <name> <RULE> <format>\n" );
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
