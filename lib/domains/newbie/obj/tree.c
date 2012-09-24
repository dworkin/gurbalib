inherit OBJECT;
inherit M_BLOCKEXITS;

void setup(void) {
   set_id("tree");
   set_long("A large dead tree.  This thing looks ancient.  " +
      "You might be able to break off a branch and use it as a weapon.");
   set_in_room_desc("A large dead tree.");
   add_block("hole");
}

int do_block(object who) {
   if (who->is_completed_quest("NewbieVille")) {
      write("You don't seem to fit through the hole anymore.");
      this_object()->query_environment()->tell_room(this_player(),
         who->query_Name() + " tries to squeeze through the hole but can " +
         "not seem to fit through it.");
      return 1;
   } else {
      write("You wriggle through the hole.");
      return 0;
   }
}
