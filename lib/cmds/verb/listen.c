void usage() {
   write("Usage: listen [-h]\n");
   write("Allows you to hear things you might not normally notice.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
}

string *query_verb_info() {
   return (( { "" } ));
}

int can_listen() {
   return 1;
}

void do_listen() {
   if (!this_environment()->do_listen(this_player()))
      write("You hear nothing special.");
}
