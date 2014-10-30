inherit M_COMMAND;

void usage(void) {
   string *lines;

   lines = ({ "Usage: tell [-h] WHO WHAT" });
   lines += ({ "" });
   lines += ({ "Send a message WHAT to WHO.  IF you want to tell someone on "
      });
   lines += ({ "another mud a message, you use user@MUD.  If there are spaces "
      });
   lines += ({ "in the mudname you need to surround the whole thing in \"'s."
      });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\ttell sirdude You have a large nose." });
   lines += ({ "\ttell guest Hi how are you?" });
   lines += ({ "\ttell \"sirdude@Dead Souls Dev\" Hi how are you?" });
   lines += ({ "See also:" });
   if (query_wizard(this_player())) {
      lines += ({ "\tbug, chan, echo, echoto, emote, rsay, shout, ssay, say, " +
         "sysmsg, translate, whisper, wizcall" });
   } else {
      lines += ({ "\tbug, chan, emote, rsay, say, shout, whisper, " + 
         "wizcall" });
   }

   if (query_admin(this_player())) {
      lines += ({ "\twall" });
   }

   this_player()->more(lines);
}

static void main(string who) {
   object usr;
   string what, where;

   if (empty_str(who)) {
      usage();
      return;
   }

   if (sscanf(who, "-%s", who)) {
      usage();
      return;
   }

   if (sscanf(who, "\"%s\" %s", who, what) != 2) {
      sscanf(who, "%s %s", who, what);
   }

   if (!what || (what == "")) {
      write("Tell " + who + " what?\n");
      return;
   }

   if (sscanf(who, "%s@%s", who, where) == 2) {
      /* intermud tell */
      IMUD_D->do_tell(who, where, what);
      this_player()->message("You tell %^PLAYER%^" + capitalize(who) + "@" +
         where + "%^RESET%^: %^TELL_TO%^" + what + "%^RESET%^\n", 1);
   } else {
      who = lowercase(who);
      usr = USER_D->find_player(who);
      if (usr && (!usr->query_ignored(this_player()->query_name())
            || query_wizard(this_player()))) {
         usr->message("%^PLAYER%^" + this_player()->query_Name() +
            "%^RESET%^%^TELL_FROM%^ tells you: " + what + "%^RESET%^\n", 1);
         usr->set_last_tell(lowercase(this_player()->query_name()));
         this_player()->message("You tell " + "%^PLAYER%^" + capitalize(who) +
            "%^RESET%^: %^TELL_TO%^" + what + "%^RESET%^\n", 1);
      } else {
         write("You can't seem to reach " + who + ".\n");
      }
   }
}
