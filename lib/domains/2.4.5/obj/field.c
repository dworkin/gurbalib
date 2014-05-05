#include "../domain.h"

inherit "/std/object";
inherit "/std/modules/m_block_exits";

void setup() {

}

void create(void) {
   ::create();
   set_id("door");
   set_short("A shimmering blue force field");
   set_long("This force field covers the north entrance.");
   add_block("north");
   set_gettable(0);
}

int do_block(object who) {
   if (query_mortal(who)) {
      write("The field zaps you as you try to enter it.\n");
      this_environment()->tell_room(this_player(), 
         this_player()->query_Name() + " gets zapped by the force field.");
      return 1;
   } 
   write("You slip through the force field.\n");
   return 0;
}
