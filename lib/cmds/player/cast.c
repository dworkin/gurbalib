#define SPELL_DIR "/cmds/spells"

void usage() {
  write("Usage: cast [-h] [spell [target]]\n");
  write("Allows you to cast a spell.  If you do not give a spell, it will " +
    "list the spells you have access to.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void list_spells() {
   // XXX Need to do this...
   write("No spells available at this time.\n");
}

string find_spell(string spellname) {
   // XXX Need to figure this out
   return "";
}

void cast_spell(string spell, string who) {
   string spellpath;
   obj target;

   spellpath = find_spell(spellname);

   if (!spellpath) {
      write("You do not have spell: " + spellname + "\n");
      write("Try one of these:\n");
      list_spells();
      return;
  }
  if (who && who != "") {
     target = ????
     if (!target || target->query_environment() != 
        thisplayer()->query_environment()) {
        write("Unable to locate: who\n");
        return;
     }
     call_other(spellpath,main,this_player(), target);
  } else {
     call_other(spellpath,main,this_player(), nil);
  }
}

void main( string str ) {
  string spellname, who;

  if ( !str || str == "" ) {
    list_spells();
    return;
  }
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  if (sscanf( str, "%s %s", spellname, who) != 2) {
     cast_spell(str,nil);
  } else {
     cast_spell(spellname, who);
  }
}

