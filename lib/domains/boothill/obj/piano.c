inherit OBJECT;

void setup(void) {
   set_id("piano");
   set_long("A pretty beat up bar piano.  This thing looks like " +
      "it has seen better days.  It seems to beckon you to play it.");
   set_in_room_desc("A rough looking piano.");

// XXX why doesn't this work?
   add_object_command("play","do_play");
}

int do_play(string str) {
   int x;

   if (str == "piano") {
      x = random(5);
      switch(x) {
         case 0:
            write("You play a little ditty.");
            this_environment()->tell_room(this_player(), 
               this_player()->query_Name() + " plays a little ditty.");
            break;
         case 1:
            write("You stroke the keys with love.");
            this_environment()->tell_room(this_player(), 
               this_player()->query_Name() + " plays a sweet little number.");
            break;
         case 2:
            write("You bring it home.");
            this_environment()->tell_room(this_player(), 
               this_player()->query_Name() + " stuns you with their " + 
               "rendition of chopin.");
            break;
         default:
            write("You work the keyboard like it was your best friend.");
            this_environment()->tell_room(this_player(), 
               this_player()->query_Name() + " plays an old country song.");
            break;
      }
   }
   return 0;
}
