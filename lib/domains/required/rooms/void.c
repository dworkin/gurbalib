inherit ROOM;

void setup(void) {

   add_area("required");

   set_brief("The void");
   set_long("If you're in here unintentionally, something bugged out. " +
      "Report what you did to the staff.");

   set_exits(([
      "out" : STARTING_ROOM,
   ]));
}
