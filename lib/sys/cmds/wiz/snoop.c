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
   lines += ({ "See also:" });
   lines += ({ "\tlast, locate, look, mudlist, possess, rwho, where, who" });

   return lines;
}

static void main(string str) {
   int sz, i;
   object *pSnooping;

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
               sz = sizeof(pSnooping);

               for (i = 0; i < sz; i++) {
                  if (pSnooping[i]->query_name() ==
                     this_player()->query_name()) {
                     this_player()->message("He's already snooping you.");
                     return;
                  }
               }
            }
            this_player()->add_snooping(pPlayer);
            pPlayer->add_snoopee(this_player());
         }
      }
   }
}
