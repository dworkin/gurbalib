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
   tell_room(nil, "Ding!  The door to the west opens.");
   add_exit("west", elfile);
   remove_item("door");
   add_item("door","The door is open.");
}

void el_leaves() {
   tell_room(nil, "The door to the west closes.");
   remove_exit("west");
   remove_item("door");
   add_item("door","The door is closed.");
}

int press_button(string str) {
   str = lowercase(str);

   if (str == "button") {
      write("You press the button.\n");
      tell_room(this_player(), this_player()->query_Name() + 
         " presses the button.\n");
/* XXX do the work here */
      return 1;
   }
   return 0;
}
