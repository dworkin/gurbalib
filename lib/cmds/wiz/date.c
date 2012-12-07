void usage() {
   string *lines;

   lines = ({ "Usage: date [-h]" });
   lines += ({ " " });
   lines += ({ "Show the real world time and date." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tdate" });
   lines += ({ "See also:" });
   lines += ({ "\ttime, status" });

   this_player()->more(lines);
}

void main(string str) {
   if (str && str != "") {
      usage();
      return;
   }
   write(ctime(time()) + "\n");
}
