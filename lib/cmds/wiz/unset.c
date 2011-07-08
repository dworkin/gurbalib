void usage() {
  write("Usage: unset [-h] VAR\n");
  write("Remove an environment varilable VAR.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("See also: set\n");
}

void main(string str) {
  if(!str || str == "") {
    usage();
    return;
  }

  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  this_player()->set_env(str,nil);
}
