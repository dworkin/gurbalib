inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: heal [-h] [player]" });
   lines += ({ " " });
   lines += ({ "Allows you to heal a player, if no player is given heal " +
      "yourself." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\theal sirdude" });
   lines += ({ "\theal" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("wiz", "ban");
   add_also("wiz", "forcequit");
   add_also("wiz", "halt");
   add_also("wiz", "muzzle");
   add_also("wiz", "zap");
}

static void main(string str) {
   int max;
   object obj;
   string who;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      obj = this_player();
   } else if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   } else {
      obj = this_environment()->present(str);
      if (!obj) {
         write("heal who?\n");
         return;
      }
   }

   max = obj->query_max_hp();
   obj->set_hp(max);
   max = obj->query_max_end();
   obj->set_end(max);
   max = obj->query_max_mana();
   obj->set_mana(max);

   if (obj->is_player()) {
      obj->set_dead(0);
      who = obj->query_Name();
   } else {
      who = obj->query_id();
   }
   this_player()->query_environment()->tell_room(this_player(),
      this_player()->query_Name() + " waves their hands in odd " +
      "funny gestures.\n" + who + " is completely healed!\n");
   write("You wave your hands and heal " + who + ".\n");
}
