inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: value [-h] OBJ" });
   lines += ({ "" });
   lines += ({ "Evaluate the specified object and print out what you " +
         "think it is worth." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tvalue sword" });
   lines += ({ "\tvalue helmet" });
   lines += ({ "See also:" });
   lines += ({ "\tbuy, extinguish, identify, light, list, listen, look, " +
      "search, sell " });

   if (query_wizard(this_player())) {
      lines += ({ "\tlast, locate, mudlist, possess, rwho, snoop, where, who"
         });
   }

   return lines;
}

static void main(string str) {
   int chance, roll, value;
   int diff;                    /*Difference between roll and chance */
   int dev;                     /*Deviation from the actual value */
   object obj;

   if (empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   str = lowercase(str);

   obj = this_player()->present(str);
   if (!obj)
      obj = this_environment()->present(str);

   if (!obj) {
      write("You don't see " + str + " here.");
      return;
   }

   if (!obj->is_living() && obj->query_value()) {

      chance = this_player()->query_skill("value");
      roll = random(5000);
      if (roll > chance) {
         diff = roll - chance;
         dev = random(diff);
         if (random(2) == 1) {
            value = obj->query_value() * (1 + (diff / 100));
         } else {
            value = obj->query_value() + (1 - (diff / 100));
         }
      } else {
         value = obj->query_value();
      }
      write("You estimate that the value is about " + value +
         " gold pieces.\n");
   } else {
      write("You can't evaluate that.");
   }
}
