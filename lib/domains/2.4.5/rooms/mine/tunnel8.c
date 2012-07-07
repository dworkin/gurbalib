inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Shaft");
   set_long("In a shaft going straight down.");

   add_exit("up","/domains/2.4.5/rooms/mine/tunnel3.c");
   add_exit("down","/domains/2.4.5/rooms/mine/tunnel9.c");
}
