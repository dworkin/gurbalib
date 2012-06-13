
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Narrow alley");
   set_long("A narrow alley.  There is a well in the middle.");
   add_item("well", "You look down the well, but see only darkness.  " +
      "There are some iron handles on the inside.");

   add_hidden_exit("down","/domains/2.4.5/rooms/well.c");
}
