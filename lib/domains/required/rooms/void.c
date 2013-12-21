inherit "/std/room";

void setup(void) {

   add_area("required");

   set_short("The void");
   set_long("The formless void.");

   set_exits(([
      "out" : STARTING_ROOM,
   ]));
}
