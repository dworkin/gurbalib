inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: page [-h] CMD" });
   lines += ({ "Ask your page to do command CMD." });
   lines += ({ "If no page is present, summon one." });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tpage bow" });
   lines += ({ "\tpage wield sword" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
}

static void main(string str) {
   object ob;

   string page;

   if (!alsos) {
      setup_alsos();
   }

   page = this_player()->query_name() + "s page";
   ob = this_player()->query_environment()->present(page);

   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   if (ob) {
      ob->parse(str);
   } else {
      ob = clone_object(DOMAINS_DIR + "/gurba/guilds/fighter/monsters/page.c");
      if (ob) {
         ob->move(this_player()->query_environment());
         ob->set_master(this_player());
         ob->setup();
         this_player()->simple_action("$N $vyell for $p page.");
      } else {
         this_player()->simple_action("$N $vyell for $p page, " +
            "but he can't be yelling loud enough.");
      }
   }
}
