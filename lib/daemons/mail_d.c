#define EMAIL_OBJ "/domains/required/objects/email.c"
#define EMAIL_INDEX "/domains/required/objects/email_index.c"
#define DATA_DIR "/daemons/data/email"

object get_mail(string who, string file) {
   string filename;
   object email_obj;

   if (this_player()->query_name() != who) {
      write("You do not have permission to that file.\n");
      return nil;
   }

   filename = DATA_DIR + "/" + who + "/" + file;

   if (file_exists(filename)) {
      email_obj = clone_object(EMAIL_OBJ);
      email_obj->restore_me(filename);
   } else {
      write("No such file.\n");
      return nil;
   }

   return email_obj;
}

string get_filename(string who) {
   string filen;

   filen = DATA_DIR + "/" + who + "/" + time();
   while (file_exists(filen)) {
     filen += "1";
   }
   return (filen);
}

int add_index(string who, object mail, string filename) {
}

int delete_index(string who, int index) {
}

string *get_index(string who) {
}

int write_mail(string who, object mail) {
   string filename;

   filename = get_filename(who);
   if (mail->save_me(DATA_DIR + "/" + who + "/" + filename)) {
      if (add_index(who,mail,filename)) {
         return 1;
      } else {
         return 0;
      }
   } else {
      return 0;
   }
}

