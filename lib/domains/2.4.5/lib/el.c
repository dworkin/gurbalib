#define elfile "/domains/2.4.5/rooms/elevator.c"

object get_el() {
   object obj;
   obj = find_object(elfile);
   if (!obj) {
      if (obj = compile_object(elfile)) {
         obj->setup();
         obj->setup_mudlib();
      }
   }

   return obj;
}

void el_arrives() {
   this_object()->tell_room(nil, "Ding!  The door to the west opens.");
   this_object()->add_exit("west", elfile);
   this_object()->remove_item("door");
   this_object()->add_item("door","The door is open.");
}

void el_leaves() {
   this_object()->tell_room(nil, "The door to the west closes.");
   this_object()->remove_exit("west");
   this_object()->remove_item("door");
   this_object()->add_item("door","The door is closed.");
}

int press_button(string str) {
   object elev;

   str = lowercase(str);

   if (str == "button") {
      write("You press the button.\n");
      this_object()->tell_room(this_player(), this_player()->query_Name() + 
         " presses the button.\n");
/* XXX do the work here */
      elev = get_el();
      call_other(elev,"set_floor",this_object()->query_floor());
      return 1;
   }
   return 0;
}
