inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: locate [-h] PLAYER" });
   lines += ({ " " });
   lines += ({ "Locate player PLAYER through intermud." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tlocate sirdude" });
   lines += ({ "See also:" });
   lines += ({ "\tlast, look, mudlist, possess, rwho, snoop, where, who" });

   return lines;
}

static void main(string str) {

   if (empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   IMUD_D->do_locate(str);
}
