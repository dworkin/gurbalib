inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: pray [-h] [prayer]" });
   lines += ({ "" });
   lines += ({ "Allows you to regain your body...." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tpray for forgiveness" });
   lines += ({ "See also:" });
   lines += ({ "\tattack, cast, eat, enter, follow, go, pray, quit" });

   this_player()->more(lines);
}

static void main(string str) {
   object obj;

   if (!str || (str == "")) {
      write("You pray and feel a shimmering light warm your entire body.");
      this_player()->query_environment()->tell_room(this_player(), 
         this_player()->query_Name() + " prays.\nA shimmering light " +
         "envelopes them.");
   } else if (sscanf(str, "-%s", str)) {
      usage();
      return;
   } else {
      write("You pray: " + str + 
         "\nYou feel a shimmering light warm your entire body.");
      this_player()->query_environment()->tell_room(this_player(), 
         this_player()->query_Name() + " prays: " + str  +
         "\nA shimmering light envelopes them.");
   }

   if (this_player()->is_dead()) {
      this_player()->set_hp(1);
   }
}
