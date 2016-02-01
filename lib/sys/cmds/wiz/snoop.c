inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: snoop [-h] PLAYER" });
   lines += ({ " " });
   lines += ({ "Snoop on player: PLAYER." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tsnoop sirdude" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "look");
   add_also("player", "who");

   add_also("wiz", "last");
   add_also("wiz", "locate");
   add_also("wiz", "mudlist");
   add_also("wiz", "possess");
   add_also("wiz", "rwho");
   add_also("wiz", "where");
}

int found_snooping(object *pSnooping) {
   int i, sz;

   sz = sizeof(pSnooping);
   for (i = 0; i < sz; i++) {
      if (pSnooping[i]->query_name() ==
         this_player()->query_name()) {

         this_player()->message("They are already snooping you.");
         return 1;
      }
   }
   return 0;
}

static void main(string str) {
   int sz, i;
   object *pSnooping;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      pSnooping = this_player()->query_snooping();

      if (pSnooping && (sizeof(pSnooping) > 0)) {
         this_player()->message("You are snooping:");
         sz = sizeof(pSnooping);
         for (i = 0; i < sz; i++) {
            this_player()->message(capitalize(pSnooping[i]->query_name()));
         }
      } else {
         this_player()->message("You are snooping no one.");
      }

      return;
   }

   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   } else {
      object pPlayer;

      pPlayer = USER_D->find_player(str);

      if (pPlayer == this_player()) {
         this_player()->message("You can't snoop yourself.");
         return;
      }

      if (!pPlayer) {
         this_player()->message("That player isn't here now.");
      } else {
         if (this_player()->is_snooping(pPlayer)) {
            this_player()->remove_snooping(pPlayer);
            pPlayer->remove_snoopee(this_player());
         } else {
            pSnooping = pPlayer->query_snooping();

            if (pSnooping && (sizeof(pSnooping) > 0)) {
               if (found_snooping(pSnooping)) {
                  return;
               }
            }
            this_player()->add_snooping(pPlayer);
            pPlayer->add_snoopee(this_player());
         }
      }
   }
}
