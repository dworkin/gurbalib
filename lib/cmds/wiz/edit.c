void usage() {
  write("Usage: edit [-h] [FILENAME]\n");
  write("Start up the ed editor and edit a file.\n");
  write("Ed is a line editor, you can only work with one line at a time.\n");
  write("It has two modes command mode and insert mode.\n");
  write("You start in command mode, to enter insert mode you can use " +
     "a or i.\n");
  write("To exit insert mode create a line with just a '.' in it and hit " +
     "return.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("Useful commands:\n"):
  write("\tp\tprint line.\n");
  write("\td\tdelete line.\n");
  write("\tr FILE\tread a file named FILE.\n");
  write("\tw FILE\twrite a file name FILE.\n");
  write("\tq\tquit.\n");
  write("\tQ\tquit, discarding any unsaved work.\n");
  write("\te FILE\tedit a file named FILE.\n");
  write("\t+5\tJump ahead 5 lines.  (you can use other numbers.\n");
  write("\t-5\tJump back 5 lines.  (you can use other numbers.\n");
}

void main( string str ) {
  if( !str || str == "" ) {
    /* Not starting with a file */
    this_player()->edit("");
    this_player()->edit( "file" );
  } else  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  } else {
    this_player()->write( "Starting editor..." );
    this_player()->edit( "e " + str );
    this_player()->edit( "file" );
  }
}

