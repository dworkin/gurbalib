inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: translate [-h] WORD" });
   lines += ({ " " });
   lines += ({ "translate WORD into the catfolk language." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tXXX I'm broken get a wiz to fix me..." });
   lines += ({ "See also:" });
   lines += ({ "\tbug, chan, echo, echoto, emote, rsay, shout, ssay, say, " +
    "sysmsg, tell, whisper, wizcall" });

   if (query_admin(this_player())) {
      lines += ({ "\twall" });
   }

   this_player()->more(lines);
}

/* XXX THis needs work, shouldn't only do catfolk... */

private int known_lang(string language) {
   return LANGUAGE_D->language_has_dictionary(language);
}

private string get_trans(string lang, string str) {
   return LANGUAGE_D->english_to_racial(lang, str);
}

private void do_translations(string str) {
   string *race_names;
   string *lines;
   int     i, dim;

   race_names = set_union(RACE_D->query_races(),
    RACE_D->query_monster_races());
   lines = allocate(sizeof(race_names));

   for (i = 0, dim = sizeof(race_names); i < dim; i++) {
      if (!known_lang(race_names[i])) {
	 lines[i] = "" + race_names[i] + ": unknown language.";
	 continue;
      }
      lines[i] = "" + race_names[i] + ": '" +
      get_trans(race_names[i], str) + "'.";
   }
   this_player()->more(lines);
}

static void main(string str) {
   if (empty_str(str)) {
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   do_translations(str);
}

