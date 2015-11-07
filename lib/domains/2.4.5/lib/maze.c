/* XXX Need to redo movement so it works more like this...
   in newbie and in normal movement...  Right now this is wrong though... */

void goto_the(string location, string dir) {
   object room;
   string error;
     
   event("body_leave", this_player());
   this_player()->query_environment()->tell_room(this_player(), 
      this_player()->query_Name() + " leaves " + dir + ".\n");
   error = catch(this_player()->move(location));

   /* Need to do last exit stuff XXX */

   if (error) {
      if (query_wizard(this_player()) == 1) {
         write("\nConstruction blocks your path.\n" + "Error: " + error + "\n");
         return;
      } else {
         write ("\nConstruction blocks your path.\n");
      }
   }

   call_other(this_player(), "do_look", this_environment());

   room = this_player()->query_environment();
   room->event("body_enter", this_player());
   room->tell_room(this_player(), this_player()->query_Name()  + " enters.\n");
}
