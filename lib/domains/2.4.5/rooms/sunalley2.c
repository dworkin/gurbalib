inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Sun alley");
   set_long("Sun alley runs east from here.");

   add_exit("east","/domains/2.4.5/rooms/sunalley1.c");
}
