void usage() {
   write("Usage: I [-h] MSG\n");
   write("Allows a wizard to tell other wizards what they have been upto.\n");
   write("Use it to explain what you have been working on.\n");
   write("All wizards will see whats been recorded since they last logged " +
      "in.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
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

   DID_D->add_entry(str);
}
