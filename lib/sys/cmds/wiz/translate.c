inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: translate [-h] WORD" });
   lines += ({ " " });
   lines += ({ "translate WORD into various known languages." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\ttranslate hello" });
   lines += ({ "See also:" });

   if (query_wizard(this_player())) {
      lines += ({ "\tbug, chan, echo, echoto, emote, rsay, say, shout, " +
         "ssay, sysmsg, tell, whisper, wizcall, wizlog" });
   }
   if (query_admin(this_player())) {
      lines += ({ "\twall" });
   }

   return lines;
}

private void do_translations(string str) {
   string *race_names, *lines;
   int i, maxi;

   race_names = set_union(RACE_D->query_races(), RACE_D->query_monster_races());
   maxi = sizeof(race_names);
   lines = allocate(maxi);

   for (i = 0; i < maxi; i++) {
      if (!LANGUAGE_D->valid_language(race_names[i])) {
         lines[i] = "" + race_names[i] + ": unknown language.";
         continue;
      }
      lines[i] = "" + race_names[i] + ": '" +
      LANGUAGE_D->english_to_racial(race_names[i], str) + "'.";
   }
   this_player()->more(lines);
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

   do_translations(str);
}

