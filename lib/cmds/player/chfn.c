void usage() {
  write("Usage: chfn [-h] [real YOURNAME | email EMAIL]\n");
  write("Allows you to change your basic information.\n");
  write("You can set your realname to YOURNAME or your email to EMAIL.\n");
  write("If no info is given show your current information.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  string cmd, what;

  if (str || str == "") {
     write("Email: " + this_player()->query_email_address() + "\n");
     write("Real Name: " + this_player()->query_real_name() + "\n");
     return;
  }

  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }
// XXX figure out why this check isn't working right...
// XXX also make it so the command logs changes... so we can look up old info.
  if( sscanf( str, "%s %s", cmd, what ) != 2 ) {
     usage();
     return;
  }
  if (cmd == "email") {
     this_player()->set_email_address(what);
  } else if (cmd == "real") {
     this_player()->set_real_name(what);
  } else {
     usage();
  }
}

