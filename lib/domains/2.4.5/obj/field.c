inherit OBJECT;
inherit M_BLOCKEXITS;

void create(void) {
   ::create();
   set_id("door");
   set_long("This force field covers the north entrance.");
   set_in_room_desc("A shimmering blue force field.");
   add_block("north");
   set_gettable(0);
}

/* Fix this so it works... */

int do_block(object who) {
   if (who->query_level() < 20) {
      write("The field zaps you as you try to enter it.\n");
      this_environment()->tell_room(this_player(), 
         this_player()->query_Name() + " gets zapped by the force field.");
      return 0;
   } 
   write("You slip through the force field.\n");
   return 1;
}
