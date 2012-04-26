inherit ARMOR;

string get_color() {

   switch(random(5)) {
      case 0:
	return "red";
      case 1:
        return "blue";
      case 2:
        return "white";
      case 3:
        return "black";
      default:
        return "orange";
   }
}

int set_color(string str) {
   if (!str || str == "") 
      str = get_color();

   set_in_room_desc("A " + str + " bandana.");
   set_long("This " + str + " bandana, looks pretty stylish.  It has " +
      "a small label attached to it.");
}

void setup(void) {

   set_id("bandana", "scarf");
   set_color("");

   set_gettable(1);
   set_slot("apparel");
   set_wear_message("$N $vput $o on.");
   set_remove_message("$N $vtake off $o.");

   add_object_command("shake","do_shake");
// XXX Need to add call to check_label....
}

int check_label(string str) {
   write("You take a peek at the label and it states: Hand wash only.  " +
      "Shake vigiorisly to dry.");
   this_player()->query_environment()->tell_room(this_player(),
      this_player()->query_Name() + " takes a peek at a label on their " +
      "bandana.\n");
   return 1;
}

int do_shake(string str) {
   if (str == "scarf" || str == "bandana") {
      write("You vigiorisly shake the bandana.");
      this_player()->query_environment()->tell_room(this_player(),
         this_player()->query_Name() + "vigiorisly shakes a colorful " +
         "bandana.\n");
      write("The bandana shifts it's color.");

      set_color("");
      return 1;
   }
   return 0;
}
