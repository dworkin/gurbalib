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
}

int check_label(string str) {
   write("You take a peek at the label and it states: Hand wash only.  " +
      "Shake vigiorisly to dry.");
   return 1;
}

int shake_scraf(string str) {
   if (str == "scarf" || str == "bandana") {
      write("You vigiorisly shake the bandana.");
// tell_room XXX
      write("The bandana shifts it's color.");

      set_color("");
      return 1;
   }
   return 0;
}
