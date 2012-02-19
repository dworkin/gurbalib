void usage() {
  write("Usage: addemote [-h] NAME [RULE] FORMAT\n");
  write("Add an emote to the emote database.\n");
  write("Name is the thing players will type for the emote.\n");
  write("Rule if provided is one of the following: LIV|STR|OBJ\n");
  write("It only applies if the target of your emote is of that type.\n");
  write("For emotes without a target, you do not provide a rule.\n");
  write("Format defines what the emote will do.\n");
  write("Example: if you do addemote blink $N blink.\n");
  write("\tYou will see You blink.\n");
  write("\t everyone else will see Sirdude blink. (If your name is sirdude)\n");

// XXX Need to flesh out help here.... what are the special symbols...

  write("Examples:\n");
  write("\taddemote blink $N blink.\n");
  write("\taddemote LIV $N $vblink at $t\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

// XXX Need to mabye combine this will showemote and rmemote

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
