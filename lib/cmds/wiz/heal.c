void usage() {
   write("Usage: heal [-h] [player]\n");
   write("Allows you to heal a player, if no player is given heal yourself.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
}

void main(string str) {
   int max_hp;
   object obj;

   if (str && str != "") {
      obj = this_environment()->present(str);
      if (!obj) {
	 write("heal who?\n");
	 return;
      }
   } else if (sscanf(str, "-%s", str)) {
      usage();
      return;
   } else {
      obj = this_player();
   }

   max_hp = obj->query_max_hp();
   obj->set_hp(max_hp);
   this_player()->query_environment()->tell_room(this_player(),
      this_player()->query_Name() + " waves their hands in odd " +
      "funny gestures.\n" + obj->query_Name() + " is completely healed!\n");
   write("You wave your hands and heal " + obj->query_Name() + ".\n");
}
