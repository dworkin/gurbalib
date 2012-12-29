#define elfile "/domains/2.4.5/rooms/elevator.c"

object get_el() {
   object obj;
   obj = find_object(elfile);
   if (!obj) {
      catch {
         obj = compile_object(elfile);
         obj->setup();
         obj->setup_mudlib();
      } : {
         write("The elevator is out of service...\n");
/* XXX Do something else here */
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
