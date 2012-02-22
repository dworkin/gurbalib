void usage() {
  write("Usage: emoteadm -h\n");
  write("Usage: emoteadm show [EMOTE]    show the entrys for EMOTE\n");
  write("\tIf EMOTE is missing show all emotes registered.\n");
  write("Usage: emoteadm del EMOTE     delete the entrys for EMOTE\n");
  write("Usage: emoteadm add NAME [RULE] FORMAT\n");
  write("Add an emote to the emote database.\n");
  write("NAME is the thing players will type for the emote.\n");
  write("RULE if provided is one of the following: LIV|STR|OBJ\n");
  write("It only applies if the target of your emote is of that type.\n");
  write("For emotes without a target, you do not provide a rule.\n");
  write("Format defines what the emote will do.\n");
  write("Example: if you do add blink $N blink.\n");
  write("\tYou will see You blink.\n");
  write("\tEveryone else will see Sirdude blink. (If your name is sirdude)\n");

  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("\t$N\tUpper case name of the player emoting\n");
  write("\t$n\tLower case name of the player emoting\n");
  write("\t$v(verb)\tDefines (verb) as a verb and the parser will " +
     "change output.\n");
  write("\t$T\tUpper case name of target.\n");
  write("\t$t\tLower case name of target.\n");
  write("\t$O\tUpper case name of object.\n");
  write("\t$o\tLower case name of object.\n");
  write("\t$s()\tXXX Need to figure out what this is\n");
  write("\t$p\tPossesive\n");

  write("Examples:\n");
  write("\temoteadm add blink $N blink.\n");
  write("\temoteadm add LIV $N $vblink at $t\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void delete_emote(string str) {
   if ( EMOTE_D->is_emote(str) ) {
      EMOTE_D->remove_emote( str );
      write( "Emote removed.\n" );
    } else {
      write( "No such emote.\n" );
    }
}

void show_emote(string str) {
   string *rules;
   int i;
   string line;

   if (!str || str == "") {
      rules = EMOTE_D->query_emotes( );

      line = "";

      for( i = 0; i < sizeof( rules ); i++ ) {
         line += rules[i] + ", ";
      }
      write(line + "\n");
      write( " \nTotal: " + sizeof(rules) + "\n" );

      return;
   }

   if( EMOTE_D->is_emote( str ) ) {

      rules = EMOTE_D->query_rules( str );

      while( sizeof( rules ) > 0 ) {
         write( rules[0] + " : \"" + EMOTE_D->query_emote( str, rules[0] ) + 
            "\"\n" );
         rules -= ({ rules[0] });
      }
   } else {
      write( "No such emote. \n" );
   }
}

void add_emote(string str) {
   string name, tmp;
   string rule, fmt;

   if ( sscanf(str, "%s %s",name,tmp) != 2 ) {
       usage();
       return;
   }

   if( sscanf( tmp, "%s %s", rule, fmt ) != 2 ) {
      fmt = rule;
      rule = "STR";
   } else if ( uppercase( rule ) != "LIV" &&
	     uppercase( rule ) != "STR" &&
	     uppercase( rule ) != "OBJ" ) {
     fmt = rule + " " + fmt;
     rule = "";
   }

   EMOTE_D->add_emote( name, rule, fmt );
   write( "Emote added.\n" );
}

void main( string str ) {
   string name;
   string fmt;
  
   if( !str || str == "") {
      usage();
      return;
   }
   if (sscanf(str, "-%s",str)) {
      usage();
      return;
   }

   if (str == "show") {
      show_emote("");
      return;
   }

   if( sscanf( str, "%s %s", name, fmt ) != 2 ) {
      usage();
      return;
   }

   if (name == "show") {
      show_emote(fmt);
      return;
   } else if (name == "del" || name == "delete" || name == "rm" || 
      name == "remove") {
      delete_emote(fmt);
      return;
   } else if (name != "add") {
      usage();
      return;
   }
   add_emote(fmt);
}
