void usage() {
   string *lines;

   lines = ({ "Usage: last [-h] [player]" });
   liens += ({ " " });
   lines += ({ "Find out when a player was last logged in." });
   lines += ({ "If no player is given show last for everyone." });
   liens += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tlast" });
   lines += ({ "\tlast sirdude" });
   lines += ({ "See also:" });
   lines += ({ "\tlocate, look, rwho, snoop, where, who" });

   this_player()->more(lines);
}

void main(string str) {
   string msg;

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (!require_priv("system")) {
      write("Access denied");
      return;
   }

   if (str != "") {
      msg = LAST_D->query_entry(lowercase(str));
   } else {
      msg = LAST_D->query_list();
   }
   write(msg);
}
