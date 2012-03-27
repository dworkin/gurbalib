inherit ROOM;

void setup(void) {
   add_area("newbie");

   set_brief("%^MAGENTA%^Outside town.%^RESET%^");
   set_long("A small dirt road leads north to a small frontier town.");

   set_exits(([
      "north" : "/domains/boothill/rooms/welcome.c", 
      "south" : "",
   ]));
}
