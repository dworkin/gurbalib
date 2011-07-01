void usage() {
  write("Usage: translate [-h] WORD\n");
  write("translate WORD into the catfolk language.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("See also: rsay\n");
}

// *Note if more languages are added can make it more complicated to
// support other languages as well...

void main(string str) {
  if( !str || str == "" ) {
    usage();
    return;
  }

  if (sscanf(str, "-%s",str)) {
     usage();
     return();
  }
	
  write(str + "\n");
  write(LANGUAGE_D->english_to_racial("catfolk", str));
}

