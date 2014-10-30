/* This file is used by the email_d to pass email to an object */
int newmail, total;
string *index;
string *flags;

static void restore_me(string myfile) {
   write("Calling restore_object on : " + myfile + "\n");
   unguarded("restore_object", myfile);
}

static void save_me(string myfile) {
   write("Calling restore_object on : " + myfile + "\n");
   unguarded("save_object", myfile);
}

int new_email(void) {
   return newmail;
}

