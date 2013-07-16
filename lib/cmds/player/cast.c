#define SPELL_DIR "/cmds/spells"
string find_spell(string spellname);

void usage(string str) {
   object target;
   string spellpath;
   string *lines;

   if (str != "") {
      spellpath = find_spell(str);
      if (spellpath) {
	 call_other(spellpath, "usage");
	 return;
      }
   }

   lines = ({ "Usage: cast [-h] [spell [target]]" });
   lines += ({ "" });
   lines += ({ "Allows you to cast a spell.  If you do not give a spell, " +
      " it will list the " });
   lines += ({ "spells you have access to." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tcast missile rat" });
   lines += ({ "See also:" });
   lines += ({ "\tattack, eat, enter, follow, go, pray, quit" });

   this_player()->more(lines);
}

int has_spell(string spellname) {
   string skill;

   if (query_admin(this_player()) || query_wizard(this_player())) {
      return 1;
   }
   if (this_player()->query_skill("spell/" + spellname)) {
      return 1;
   }
   return 0;
}

void list_spells() {
   string *files;
   int i, x;
   string name;

   files = get_dir(SPELL_DIR + "/*.c")[0];

   write("Available spells:\n");
   for (i = sizeof(files) - 1; i >= 0; i--) {
      x = strlen(files[i]) - 3;
      name = files[i][..x];
      if (has_spell(name)) {
	 write("\t" + name + "\n");
      }
   }
}

string find_spell(string spellname) {
   string str;

   str = SPELL_DIR + "/" + spellname;
   if (file_exists(str + ".c")) {
      return str;
   }
   return nil;
}

void cast_spell(string spell, string who) {
   string spellpath;
   object target;

   spellpath = find_spell(spell);

   if (!spellpath || !has_spell(spell)) {
      write("You do not have the spell: " + spell + "\n");
      list_spells();
      return;
   }
   call_other(spellpath, "do_spell", this_player(), who);
}

void main(string str) {
   string spellname, who;

   if (!str || (str == "")) {
      list_spells();
      return;
   }
   if (sscanf(str, "-h %s", str)) {
      usage(str);
      return;
   } else if (sscanf(str, "-%s", str)) {
      usage("");
      return;
   }

   if (sscanf(str, "%s %s", spellname, who) != 2) {
      cast_spell(str, nil);
   } else {
      cast_spell(spellname, who);
   }
}
