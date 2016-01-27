inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: sell [-h] OBJ" });
   lines += ({ "" });
   lines += ({ "Allows you to sell an object OBJ, " +
      "assuming you are near a shop keeper." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tsell sword" });
   lines += ({ "\tsell helmet" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "buy");
   add_also("player", "extinguish");
   add_also("player", "identify");
   add_also("player", "light");
   add_also("player", "list");
   add_also("player", "listen");
   add_also("player", "look");
   add_also("player", "search");
   add_also("player", "value");

   add_also("wiz", "last");
   add_also("wiz", "locate");
   add_also("wiz", "mudlist");
   add_also("wiz", "possess");
   add_also("wiz", "rwho");
   add_also("wiz", "snoop");
   add_also("wiz", "where");
   add_also("wiz", "who");
}

/* Created by Fudge */

static void main(string str) {
   object obj, *objs;
   int i;

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

   if (this_player()->is_dead()) {
      write("You can not do that when your are not among the living.\n");
      return;
   }

   obj = this_player()->present(str);
   if (obj) {
      /* Found the item */

      objs = this_environment()->query_inventory();
      for (i = 0; i < sizeof(objs); i++) {
         if (objs[i]->is_vendor() == 1) {
            /* Found the shopkeeper */

            if (obj->is_worn()) {
               this_player()->do_remove(obj);
               this_player()->targeted_action(obj->query_remove_message(), nil,
                  obj);
               obj->after_unwear(this_player(), "sell");
            }

            if (obj->is_wielded()) {
               this_player()->do_unwield(obj);
               this_player()->targeted_action(obj->query_unwield_message(),
                  nil, obj);
               obj->after_unwield(this_player(), "sell");
            }

            if (obj->is_undroppable()) {
               this_player()->
                  targeted_action("$N $vare unable to let go of $o.", nil,
                  obj);
               return;
            }

            objs[i]->do_buy(this_player(), obj);
            return;

         }
      }
      write("Sell to who?");
   }
   write("You don't have that.");
}

