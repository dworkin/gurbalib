inherit "/std/room";
#define REQDIR "/domains/required"

private string myname(void) {
   string who;

   who = owner_file(file_name());
   if (!who || who == "") {
      who = "ERROR in owner_file:";
   }
   return capitalize(who);
}

void setup(void) {
   set_short(myname() + "'s workroom");
   set_long("The room is littered with all kinds of arcane tools.  " +
      "Your not really sure what all this stuff is but someone looks " +
      "pretty busy.  In the middle of the room, is a large desk with " +
      "various tools on it.");
   set_exits(([
      "out" : STARTING_ROOM,
      "east" : REQDIR + "/rooms/bug_room",
   ]));

   add_item("desk", "The desk is a huge and made of mahogany. " +
      "It's the central piece of furniture of the room, and it is clear that " +
      myname() + " spends a lot of time behind it.");

   add_item("tools", "They are used by " + myname() +
      " to do all kinds of things.");

   set_objects(
      REQDIR + "/monsters/rat", 
      REQDIR + "/objects/chest", 
      REQDIR + "/objects/short_sword", 
      REQDIR + "/objects/helmet"
   );
}
