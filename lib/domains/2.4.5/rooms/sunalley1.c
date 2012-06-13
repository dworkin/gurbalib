inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Sun alley");
   set_long("Sun alley runs east-west.");

   add_exit("east","/domains/2.4.5/rooms/eastroad3.c");
   add_exit("west","/domains/2.4.5/rooms/sunalley2.c");
}
