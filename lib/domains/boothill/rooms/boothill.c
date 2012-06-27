inherit ROOM;
#define DIR "/domains/boothill"

void setup(void) {
   add_area("boothill");

   set_brief("Boothill");
   set_long("If your not sure what boothill is, now you know, its a " +
      "cemetary just outside of town.  There are a bunch of cheap " +
      "graves here.  With Odd looking tombstones.  There is also  a " +
      "freshly dug hole, just waiting for the towns next victum.");

   set_exits(([
      "south" : DIR + "/rooms/infront_jail.c", 
      "down" : DIR + "/rooms/hole.c",
   ]));

}

// XXX Need to add room command for this...
void look_at_stone() {
   int x;

   x = random(5);
   switch (x) {
      case 0:
         write("Here lies Fred, with a belly full of lead!\n");
         break;
      case 1:
         write("Here lies Jake, He got hit over the head with a rake.\n");
         break;
      case 2:
         write("Here lies Old man Tucker, He couldn't hold his liquor.\n");
         break;
      case 3:
         write("We don't know this poor feller.\n");
         break;
      case 4:
         write("Here lies the fine Miss Sally.\n");
         break;
   }
}
