inherit ROOM;

void setup(void) {
   add_area("Gurba");
   set_brief("%^CYAN%^Gelmir Road%^RESET%^");
   set_long("To the north is the entrance to the Fighters Guild. A short " +
      "distance to the west is the town square, but you can't see if " +
      "anything is going on there.");
   set_exits(([
      "north" : "/domains/gurba/guilds/fighter/entrance",
      "west" : "/domains/gurba/rooms/gelmir2",
   ]));

   add_item("road", "path", "floor", "street", "The further you get from " +
      "the town square, the poorer the condition of the road. Here there " +
      "are some rather big holes in the stonework, and it could use some " +
      "maintainance.");
   add_item("guild", "fighters guild", "fighters", "guild hall", "hall",
      "The building doesn't look much different from the other houses in " +
      "this area, except for it beeing a lot bigger. It's made of red " +
      "brick, and it looks a bit faded.");
}
