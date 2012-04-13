inherit ROOM;

void setup(void) {
   add_area("boothill");

   set_brief("%^MAGENTA%^Outside town.%^RESET%^");
   set_long("A small dirt road leads north to a small frontier town.");

   set_exits(([
      "north" : "/domains/boothill/rooms/welcome.c", 
      "west" : "/domains/boothill/rooms/outside_town.c",
   ]));
}
