void usage() {
   write("Usage: heal [-h] [player]\n");
   write("Allows you to heal a player, if no player is given heal yourself.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
}

void main(string str) {
   int max;
   object obj;
   string who;

   if (!str || (str == "")) {
      obj = this_player();
   } else if (sscanf(str, "-%s", str)) {
      usage();
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
      who = obj->query_Name();
   } else {
      who = obj->query_id();
   }
   this_player()->query_environment()->tell_room(this_player(),
      this_player()->query_Name() + " waves their hands in odd " +
      "funny gestures.\n" + who + " is completely healed!\n");
   write("You wave your hands and heal " + who + ".\n");
}
