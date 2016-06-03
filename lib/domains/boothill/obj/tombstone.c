#include "../domain.h"

inherit "/std/sign";

void setup(void) {
   set_id("tombstone");
   set_short("A tombstone");
   add_ids("stone", "grave", "gravestone");
}

string query_long(void) {
   int x;
   string str;

   x = random(5);
   str = "The tombstone reads:\n\t";
   switch (x) {
      case 0:
         str += "Here lies Fred, with a belly full of lead!\n";
         break;
      case 1:
         str += "Here lies Jake, He got hit over the head with a rake.\n";
         break;
      case 2:
         str += "Here lies Old man Tucker, He couldn't hold his liquor.\n";
         break;
      case 3:
         str += "We don't know this poor feller.\n";
         break;
      case 4:
         str += "Here lies the fine Miss Sally.\n";
         break;
   }
   return str;
}

string query_message(void) {
   return query_long();
}
