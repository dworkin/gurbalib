inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("The bank");
   set_long("You are in the bank.  To the east is a low counter.  The " +
      "counter is covered with heavy iron bars.  On the wall beside " +
      "the counter, a door leads further east");

   add_exit("west","/domains/2.4.5/rooms/narr_alley.c");

   add_item("tree","The branches are very high up.");

   set_objects (([
      "/domains/2.4.5/monsters/bankguard.c" : 1,
   ]));
}

// XXX Need to do door...

