inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: rmuser [-h] USER" });
   lines += ({ "" });
   lines += ({ "Delete the specified user, USER." });
   lines += ({ "If they are a wizard or admin it will prompt you to " +
      "remove their wiz dir." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\trmuser sirdude" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("wiz", "ban");
   add_also("wiz", "forcequit");
   add_also("wiz", "muzzle");
   add_also("wiz", "zap");
}

static void rmuser(string name) {
   USER_D->delete_user(name);
}

void confirm_remove(string str, string name) {
   string dirname;

   switch (lowercase(str[0..0])) {
      case "y":
         rmuser(name);
         write("Ok.");
         dirname = "/wiz/" + name;

         if (file_exists(dirname) == -1) {
            write("You may also want to remove their wiz dir: " + dirname +
               "\n");
         }
         break;
      default:
         write("Aborted.");
         break;
   }
}

static void main(string str) {
   string name;

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

   name = lowercase(str);

   if (this_player()->query_name() == str) {
      write("You may not remove yourself.\n");
      return;
   }

   if (!USER_D->user_exists(str)) {
      write("No such user: " + str + "\n");
      return;
   }

   write("Removing " + name + ", are you sure? (y/n)");
   this_player()->input_to_object(this_object(), "confirm_remove", name);
}
