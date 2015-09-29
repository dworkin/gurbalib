inherit "/std/sign";

#define DATAFILE "/data/top_players.txt"

void setup(void) {
   set_id("list","top","top players", "top list", "list of top players");
   set_short("A list of the top players");
   set_gettable(1);
   set_value(5);
   set_weight(1);

   set_message("#query_long");
}

/* XXX conflicts with menu in the room!!! pub2.c */

string query_long() {
   string *lines, stuff;

   lines = ({ "Top Ten Players list" });
   lines += ({ "-------------------------------------------" });

   if (file_exists(DATAFILE)) {
      lines += explode(read_file(DATAFILE), "\n");
   } else {
      lines += ({ "Under construction!" });
   }
   stuff = implode(lines, "\n");

   return stuff;
}

