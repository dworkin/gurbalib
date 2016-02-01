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

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "bug");
   add_also("player", "chan");
   add_also("player", "emote");
   add_also("player", "rsay");
   add_also("player", "say");
   add_also("player", "shout");
   add_also("player", "tell");
   add_also("player", "whisper");
   add_also("player", "wizcall");

   add_also("wiz", "echo");
   add_also("wiz", "echoto");
   add_also("wiz", "ssay");
   add_also("wiz", "sysmsg");
   add_also("wiz", "wizlog");

   add_also("admin", "wall");
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
   if (!alsos) {
      setup_alsos();
   }

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

