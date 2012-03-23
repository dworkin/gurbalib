void usage() {
   write("Usage: emote [-h] MSG\n");
   write("Send a message MSG to everyone in the room.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("Example:\n");
   write("\t If you type \"emote does a flip\" the output will look like " +
      "this:\n");
   write("\t PLAYER does a flip\n");
   if (query_wizard(this_player())) {
      write("See also: say ssay tell whisper\n");
   } else {
      write("See also: say tell whisper\n");
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
