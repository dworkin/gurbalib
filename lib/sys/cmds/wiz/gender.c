inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: gender [-h] [male|female|neuter]" });
   lines += ({ " " });
   lines += ({ "Allows you to set your gender." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tgender male" });
   lines += ({ "See also:" });
   lines += ({ "\ttitle" });

   this_player()->more(lines);
}

static void main(string str) {

   if (!str || (str == "")) {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (lowercase(str) == "female") {
      this_player()->set_gender("female");
      write("You are now female.\n");
      this_player()->save_me();
   } else if (lowercase(str) == "male") {
      this_player()->set_gender("male");
      write("You are now male.\n");
      this_player()->save_me();
   } else if (lowercase(str) == "neuter") {
      this_player()->set_gender("neuter");
      write("You are now neuter.\n");
      this_player()->save_me();
   } else {
      write("Please use \"male\", \"female\" or \"neuter\" as an argument.\n");
   }
}
