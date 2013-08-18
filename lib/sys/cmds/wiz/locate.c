void usage() {
   string *lines;

   lines = ({ "Usage: locate [-h] PLAYER" });
   lines += ({ " " });
   lines += ({ "Locate player PLAYER." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tlocate sirdude" });
   lines += ({ "See also:" });
   lines += ({ "\tlast, look, mudlist, possess, rwho, snoop, where, who" });

   this_player()->more(lines);
}

void main(string str) {
   if (!query_wizard(this_player())) {
      write("You must be a wizard to do that.\n");
      return;
   }

   if (!str || (str == "")) {
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   IMUD_D->do_locate(str);
}
