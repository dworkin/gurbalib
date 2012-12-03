void usage() {
   write("Usage: emote [-h] MSG\n");
   write("Send a message MSG to everyone in the room.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("Examples:\n");
   write("\temote does a flip!\n");
   write("\temote beep sirdude\n");
   if (query_wizard(this_player())) {
      write("See also: bug, emote, rsay, say, shout, ssay, tell, translate, " +
         "whisper, wizcall\n");
   } else {
      write("See also: bug, emote, rsay, say, shout, tell, whisper, wizcall\n");
   }
}

void main(string str) {
   if (!str || str == "") {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (!this_player()->is_player() || query_wizard(this_player())) {
      this_player()->query_environment()->tell_room(nil,
	 this_player()->query_Name() + " " + str);
   } else {
      this_player()->query_environment()->tell_room(nil, "-> " +
	 this_player()->query_Name() + " " + str);
   }
}
