string horizontal_rule(object "/sys/obj/player" player, string str) {
   int width, i;
   string retval;

   width = this_player()->query_width();

   for (retval = "", i = 0; i < width; i += strlen(str) ) {
      retval += str;
   }

   return retval;
}

