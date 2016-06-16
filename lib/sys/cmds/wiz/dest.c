inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: dest [-h] OBJ" });
   lines += ({ " " });
   lines += ({ "Destroy object OBJ." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tdest sword" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("wiz", "check");
   add_also("wiz", "clean");
   add_also("wiz", "clone");
   add_also("wiz", "eval");
   add_also("wiz", "graph");
   add_also("wiz", "rebuild");
   add_also("wiz", "update");

   add_also("admin", "checkmud");
   add_also("admin", "warmboot");
}

static void main(string str) {
   object ob;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
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
         if (ob->is_living() && ob == this_player()->get_target(ob)) {
            ob->halt_fight();
            this_player()->halt_fight();
         }
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
               this_player()->targeted_action(ob->query_remove_message(),
                  nil, ob);
               ob->after_unwear(this_player(), "dest");
            }
            if (ob->is_wielded()) {
               this_player()->do_unwield(ob);
               this_player()->targeted_action(ob->query_unwield_message(),
                  nil, ob);
               ob->after_unwield(this_player(), "dest");
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
