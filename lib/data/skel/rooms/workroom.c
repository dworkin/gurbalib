inherit ROOM;

private string myname() {
   return capitalize(owner_file(file_name()));
}

void setup(void) {
   set_brief(myname() + "'s workroom");
   set_long("The room is littered with all kinds of arcane tools.  " +
      "Your not really sure what all this stuff is but someone looks " +
      "pretty busy.");
   set_exits(([
      "out" : "/domains/required/rooms/start", 
      "east" : "/domains/required/rooms/bug_room",
   ]));

   add_item("desk", "The desk is a huge and made of mahogny. " +
      "It's the central piece of furniture of the room, and it is clear that " +
      myname() + " spends a lot of time behind it.");

   add_item("tools", "They are used by " + myname() +
      " to do all kinds of things.");

   set_objects(([
      "/domains/required/objects/chest" : 1, 
      "/domains/required/monsters/rat" : 1, 
      "/domains/required/objects/weapons/short_sword" : 1, 
      "/domains/required/objects/armor/buckler" : 1,
   ]));
}
