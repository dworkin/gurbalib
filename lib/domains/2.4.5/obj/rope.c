inherit OBJECT;
string tied_to;
object tied_to_obj;

void setup(void) {
   set_id("rope");
   set_adj("old");
   set_long("You see nothing special about the rope.");
   set_gettable(1);

   set_value(15);
   set_weight(10);
}

string query_in_room_desc() {
   if (tied_to)
      return "An old rope tied to " + tied_to;
   return "An old rope";
}
