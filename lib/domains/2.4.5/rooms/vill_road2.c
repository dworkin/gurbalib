inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Village road");
   set_long("A long road going east through the village.  There are " +
     "stairs going down.  The road continues to the west.  " +
     "To the north is the shop, and to the south is the adventurers " +
     "guild.  The road runs towards the shore to the east.");

   add_exit("north","/domains/2.4.5/rooms/shop.c");
   add_exit("south","/domains/2.4.5/rooms/adv_guild.c");
   add_exit("east","/domains/2.4.5/rooms/vill_shore.c");
   add_exit("west","/domains/2.4.5/rooms/vill_road1.c");
   add_exit("down","/domains/2.4.5/rooms/station.c");

   set_objects (([
      "/domains/2.4.5/monsters/harry.c": 1,
   ]));
}

// Need to add harry and down???
