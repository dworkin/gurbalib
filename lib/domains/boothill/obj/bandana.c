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

void setup(void) {
   string color;

   color = get_color();
   set_id("bandana", "scarf");
   set_in_room_desc("A " + color + " bandana.");
   set_long("It looks pretty stylish.");
   set_gettable(1);
   set_slot("apparell");
   set_wear_message("$N $vput $o on.");
   set_remove_message("$N $vtake off $o.");
}
