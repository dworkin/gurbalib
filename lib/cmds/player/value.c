void usage() {
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
   lines += ({ "\tbuy, identify, list, listen, look, sell, value" });

   this_player()->more(lines);
}

void main(string str) {
   int chance, roll, value;
   int diff;			/*Difference between roll and chance */
   int dev;			/*Deviation from the actual value */
   object obj;

   if (!str || (str == "")) {
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
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
