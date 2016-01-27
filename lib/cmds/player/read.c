inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: read [-h] THING" });
   lines += ({ "" });
   lines += ({ "Allows you to read readable things." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tread sign" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "delete");
   add_also("player", "look");
   add_also("player", "mail");
   add_also("player", "post");
}

static void main(string str) {
   object ob;
   string *lines;

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

   ob = this_environment()->present(str);

   if (ob && ob->is_readable()) {
      if (ob->can_read(this_player())) {
         ob->do_read(this_player());
      } else {
         write("You can't read that.");
      }
   } else {
      ob = this_player()->present(str);
      if (ob && ob->is_readable()) {
         if (ob->can_read(this_player())) {
            ob->do_read(this_player());
         } else {
            write("You can't read that.");
         }
      } else {
         ob = this_environment()->present("board");
         if (ob) {
            if (!str || (str == "")) {
               write("Read what?");
               return;
            }

            if (ob->query_msg_exists(str) == 1) {
               lines = explode(ob->query_message(str), "\n");
               write(implode(lines[..3], "\n"));
               this_player()->more(lines[4..]);
            } else {
               write("No such message.\n");
            }
            return;
         } else {
            write("Read what?");
            return;
         }
      }
   }
}
