void usage() {
  write("Usage: shout [-h] MSG\n");
  write("Send MSG to all players on the mud.  This command should only " +
     " be used SPARINGLY.\n");
  write("Don't abuse it or you'll lose it.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main (string str) {
   int i;
   object *usrs;

   if (!str || str == "") {
      usage();
      return;
   }
   if (sscanf(str, "-%s",str)) {
      usage();
      return;
   }

   if (this_player()->query_muzzle()) {
      write("A magical muzzle has been placed on you, you can not shout.\n");
      this_player()->query_environment()->tell_room( this_player(),
         capitalize(this_player()->query_name()) + " tries to shout but " +
         "the words will not come out.\n" );
      return;
   }

   usrs = players();

   for (i = 0; i < sizeof(usrs); i++) {
      usrs[i]->message("%^RED%^" + "" + 
         capitalize(this_player()->query_name()) + " shouts: %^RESET%^" + 
         str + "\n");
   }
}

