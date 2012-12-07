void usage() {
   string *lines;

   lines = ({ "Usage: emaillist [-h] [admins|players|wizards] [FILE]" });
   lines += ({ "" });
   lines += ({ "Print out an email list of the mud users.
   lines += "{   If FILE is given, write it to that file." });
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
   int i, max;
   object obj;

   names = USER_D->list_all_users();
   max = sizeof(names);
   lines = ({ });

   for(i=0;i<max;i++) {
      obj = get_data_ob(names[i]);

      if (!type || type == "") {
         lines += ({ obj->query_real_name() + "(" + 
            obj->query_name() + ")" +
            obj->query_email_address() });
      } else {
         type = lowercase(type);
         if ((type == "player") || (type == "players")) {
            lines += ({ obj->query_real_name() + "(" + 
               obj->query_name() + ")" +
               obj->query_email_address() });
         } else if ((type == "wiz") || (type == "wizard") || 
            (type == "wizards")) {
            if (query_wizard(obj) {
               lines += ({ obj->query_real_name() + "(" + 
                  obj->query_name() + ")" +
                  obj->query_email_address() });
            }
         } else if ((type == "admin") || (type == "admins")) {
            if (query_admin(obj) {
               lines += ({ obj->query_real_name() + "(" + 
                  obj->query_name() + ")" +
                  obj->query_email_address() });
            }
         }
      }
   }

   max = sizeof(lines);
   for(i=0;i<max;i++) {
      if (!file || file == "") {
         write(lines[i]);
      } else {
         /* XXX how do we write a file? */
      }
   }
}

void main(string str) {
   string type, file;

   if (!str || str == "") {
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (!require_priv("system")) {
      write("You must be admin to do that.");
      return;
   }

/* XXX Do the work here */

   create_list(type, file);

}
