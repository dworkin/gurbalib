inherit ROOM;

void setup(void) {
   set_brief("The weapon shop");
   set_long("This is the weapons shop here you can buy the weapons you " +
      "need for some serious monsterbashing. The shop is run by Grim the " +
      "Armsmaster, an elderly dwarf. Weaponracks are mounted on all walls " +
      "to display his wide range of weaponry.");

   set_exits(([
      "south" : "/domains/gurba/rooms/market2",
   ]));

   add_item("rack", "racks", "weaponracks", "weaponrack",
      "Each of the racks has room for five to seven different weapons.");

   set_objects(([
      "/domains/gurba/vendors/grim" : 1,
   ]));
}

void do_listen(object player) {
   write("You can't really hear anything.");
}
