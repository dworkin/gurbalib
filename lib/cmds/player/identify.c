void usage() {
   string *lines;

   lines = ({ "Usage: identify [-h] OBJ" });
   lines += ({ "Closely inspect an object OBJ to see if there is any " +
      "addition information." });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tidentify sword" });
   lines += ({ "\tidentify helmet" });
   lines += ({ "See also: buy, list, look, retrieve, sell, store, value" });

   this_player()->more(lines);
}

void main(string str) {
   object obj;
   object *wielded;

   if (!str || str == "") {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   obj = this_player()->present(lowercase(str));
   if (!obj) {
      write("Maybe you should get one first?");
      return;
   }

   if (obj->query_detailed_desc()) {
      write(obj->query_detailed_desc());
   } else {
      write("You discover nothing special");
   }
}
