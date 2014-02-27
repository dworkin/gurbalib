inherit "/std/room";

void setup(void) {
   set_short("%^RED%^Fudge's workroom%^RESET%^");
   set_long("The room is splashed with gore.  Piles of limbs in one corner " +
      "and piles of guts in another corner.  In the middle of the room " +
      "is a desk.  On the desk are some grotesque looking tools.");
   set_exits(([
      "out" : "/domains/required/rooms/start", 
      "east" : "/domains/required/rooms/bug_room",
   ]));

   add_item("desk", "The desk is a huge and made of mahogny. " +
      "It's the central piece of furniture of the room, and it is clear " +
      "that Fudge spends a lot of time behind it.");

   add_item("tools", "They are used by grand master Fudge to dissect " +
      "monsters while trying to figure out how strong they are and where " +
      "to place them.");

   add_item("gore", "Youck!");

   add_item("limbs", "The ankle bone is connected to the leg bone. " +
      "It's disgusting.");

   set_objects(
      "/domains/required/objects/chest",
      "/domains/required/monsters/rat", 
      "/domains/required/objects/short_sword", 
      "/domains/required/objects/helmet"
   );
}
