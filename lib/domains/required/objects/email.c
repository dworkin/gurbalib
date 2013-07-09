/* This file is used by the email_d to pass email to an object */
string to, from, subject, date;
string *lines;

static void restore_me(string myfile) {
   write("Calling restore_object on : " + myfile + "\n");
   unguarded("restore_object", myfile);
}

static void save_me(string myfile) {
   write("Calling restore_object on : " + myfile + "\n");
   unguarded("save_object", myfile);
}

int is_email(string name) {
   if (!date) {
      return 0;
   } else {
      return 1;
   }
}

