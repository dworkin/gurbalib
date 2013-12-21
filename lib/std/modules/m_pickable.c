static string pickable;
static int number_of_pickable_objects;

string is_pickable(void) {
   return pickable;
}

void set_pickable(string pick) {
   pickable = pick;
}
