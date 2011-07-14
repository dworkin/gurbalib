void usage() {
  write("Usage: info [-h] OBJ\n");

  write("Get info about the object OBJ.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  object ob;

  if (!str || str == "") {
     usage();
     return;
  }
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }
  // XXX find_object isn't right need another function call that searches
  // for an object in the current environment/player etc...
  // Lots of functions should be using this... status for example...
  ob = find_object(str);
  if (ob) {
     write( "Object_name: " + ob->file_name() + "\n");
  } else {
     write("Unable to find object: " + str + "\n");
  }
}
