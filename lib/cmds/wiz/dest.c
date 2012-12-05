void usage() {
   string *lines;

   lines = ({ "Usage: dest [-h] OBJ" });
   lines += ({ " " });
   lines += ({ "Destroy object OBJ." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tdest sword" });
   lines += ({ "See also:" });

   if (query_admin(this_player()) {
      lines += ({ "\tcheck, clean, check, rebuild, update, warmboot" });
   } else {
      lines += ({ "\tcheck, clean, check, rebuild, update" });
   }

   this_player()->more(lines);
}

void main(string str) {
   object ob;

   if (!str || str == "") {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   ob = this_player()->query_environment()->present(str);
   if (ob) {
      if (ob->is_player()) {
	 this_player()->simple_action("$N $vtry to dest a player, " +
	    "and $vfail miserably.\n");
      } else {
	 this_player()->simple_action("$N $vtouch the " + ob->query_id() +
	    ", and it disappears.\n");
	 if (ob->query_environment()) {
	    ob->query_environment()->remove_object(ob);
	 }
	 ob->destruct();
      }
   } else if (this_player()->present(str)) {
      ob = this_player()->present(str);
      if (ob) {
	 if (ob->is_player()) {
	    this_player()->simple_action("$N $vtry to dest a player, " +
	       "and $vfail miserably.\n");
	 } else {
            if (ob->is_worn()) {
               this_player()->do_remove(ob);
               this_player()->targetted_action(ob->query_remove_message(),
                  nil, ob);
            }
            if (ob->is_wielded()) {
               this_player()->do_unwield(ob);
               this_player()->targetted_action(ob->query_unwield_message(),
                  nil, ob);
            }
	    this_player()->simple_action("$N $vtouch the " + ob->query_id() +
	       ", and it disappears.\n");
	    if (ob->query_environment()) {
	       ob->query_environment()->remove_object(ob);
	    }
	    ob->destruct();
	 }
      }
   } else {
      write("You can't seem to find the " + str + ".\n");
   }
}
