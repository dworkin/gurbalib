inherit ROOM;
#define REQDIR "/domains/required"

private string myname() {
   return capitalize(owner_file(file_name()));
}

void setup(void) {
   set_brief(myname() + "'s workroom");
   set_long("The room is littered with all kinds of arcane tools.  " +
      "Your not really sure what all this stuff is but someone looks " +
      "pretty busy.");
   set_exits(([
      "out" : STARTING_ROOM,
      "east" : REQDIR + "/rooms/bug_room",
   ]));

   add_item("desk", "The desk is a huge and made of mahogny. " +
      "It's the central piece of furniture of the room, and it is clear that " +
      myname() + " spends a lot of time behind it.");

   add_item("tools", "They are used by " + myname() +
      " to do all kinds of things.");

   set_objects(([
      REQDIR + "/monsters/rat" : 1, 
      REQDIR + "/objects/chest" : 1, 
      REQDIR + "/objects/weapons/short_sword" : 1, 
      REQDIR + "/objects/armor/buckler" : 1,
   ]));
}
