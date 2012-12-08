void usage() {
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
   lines += ({ "See also:" });
   lines += ({ "\twho, last" });

   this_player()->more(lines);
}

void create_list(string type, string file) {
   string *names;
   string *lines;
   int i, max, temp;
   object obj;

   names = USER_D->list_all_users();
   max = sizeof(names);
   lines = ({ });

   for(i=0;i<max;i++) {
write("Checking XXX " + names[i] + "\n");
      obj = USER_D->find_player(names[i]);
      if (!obj) {
         temp = 1;
         obj = USER_D->get_data_ob(names[i]);
      }

      if (obj) {
         if (!type || type == "") {
            lines += ({ obj->query_real_name() + "(" + 
               names[i] + ") <" + 
               obj->query_email_address() + ">" });
         } else {
            type = lowercase(type);
            if ((type == "player") || (type == "players")) {
               lines += ({ obj->query_real_name() + "(" + 
                  obj->query_name() + ")" +
                  obj->query_email_address() });
            } else if ((type == "wiz") || (type == "wizard") || 
               (type == "wizards")) {
               if (USER_D->query_wizard(obj)) {
                  lines += ({ obj->query_real_name() + "(" + 
                     obj->query_name() + ")" +
                     obj->query_email_address() });
               }
            } else if ((type == "admin") || (type == "admins")) {
               if (USER_D->query_admin(obj)) {
                  lines += ({ obj->query_real_name() + "(" + 
                     obj->query_name() + ")" +
                     obj->query_email_address() });
               }
            }
         }
         if (temp) {
            temp = 0;
/* XXX           destruct_object(obj); */
         }
      }
   }

   max = sizeof(lines);
   for(i=0;i<max;i++) {
      if (!file || file == "") {
         write(lines[i]);
      } else {
         write_file(file, lines[i]);
      }
   }
}

void main(string str) {
   string type, file;

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (!require_priv("system")) {
      write("You must be admin to do that.");
      return;
   }

   if (sscanf(str, "%s %s", type, file) != 2) {
      type = lowercase(str);
      if ((type == "player")  || (type == "players") ||
         (type == "wiz") || (type == "wizard") || (type == "wizards") ||
         (type == "admin") || (type == "admins")) {
         create_list(type, "");
      } else {
         create_list("",type);
      }
   } else {
      create_list(type, file);
   }
}
