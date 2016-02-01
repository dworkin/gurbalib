inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: emaillist [-h] [admins|players|wizards] [FILE]" });
   lines += ({ "" });
   lines += ({ "Print out an email list of the mud users." });
   lines += ({ "If FILE is given, write it to that file." });
   lines += ({ "If admins, players or wizards are specified only " +
      "include those users." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\temaillist" });
   lines += ({ "\temaillist wizards" });
   lines += ({ "\temaillist wizards /tmp/email.txt" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "who");
   add_also("player", "last");
}

void create_list(string type, string file) {
   string line, *names;
   int i, max;

   names = USER_D->list_all_users();
   max = sizeof(names);

   if (type == "wiz") {
      type = "wizards";
   }
   if (type == "wizard") {
      type = "wizards";
   }
   if (type == "admin") {
      type = "admins";
   }

   for (i = 0; i < max; i++) {
      if (query_guest(names[i])) {
         /* Skip this account it's special */
      } else {
         line = USER_D->get_email_info(this_player(), names[i], type);
         if (line && (line != "")) {
            if (!file || (file == "")) {
               write(line);
            } else {
               write_file(file, line);
            }
         }
      }
   }
}

static void main(string str) {
   string type, file;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      create_list("", "");
      return;
   }

   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(str, "%s %s", type, file) > 0) {
      type = lowercase(type);
   } else {
      type = lowercase(str);
   }
   if ((type == "player")  || (type == "players") ||
      (type == "wiz") || (type == "wizard") || (type == "wizards") ||
      (type == "admin") || (type == "admins")) {
      create_list(type, "");
   } else {
      write("Invalid list type.\n");
   }
}
