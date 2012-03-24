inherit "/std/room";
inherit M_STORAGE;

void setup(void) {
   set_brief("%^MAGENTA%^Storage Room%^RESET%^");
   set_long("There is a storage at one side of the room.");

   set_exits(([
      "south" : "/domains/gurba/town_square"
   ]));

   set_storage_size(10);
   add_item("storage", "The storage is used by the inhabitants of " +
      "Gurba to store some of their items.");
}
