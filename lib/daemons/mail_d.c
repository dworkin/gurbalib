#define EMAIL_OBJ "/domains/required/objects/email.c"
#define EMAIL_INDEX "/domains/required/objects/email_index.c"
#define DATA_DIR "/daemons/data/email"

/* XXX This is a work in progress, need to convert index to a mapping 
   and flesh it out */

string get_filename(string who) {
   string filen, tmp;
   int x;

   filen = DATA_DIR + "/" + who + "/" + time();
   if (file_exists(filen)) {
      x= 1;
      tmp = filen + x;

      while (file_exists(tmp)) {
         x++;
         tmp = filen + x;
      }
   }
   return filen;
}

string *load_index(string who) {
   object myindex;

   myindex = clone_object(EMAIL_INDEX);
   myindex->restore_me(DATA_DIR + "/" + who + "/index.o");
}

string *save_index(string who, string *index) {
   object myindex;

   myindex->save_me(DATA_DIR + "/" + who + "/index.o");
}

int add_index(string who, object mail, string filename) {
   string *index;
   string line;

   index = load_index(who);

   line = mail->query_from() + ": " + mail->query_subject();
   index += ({ line });

   save_index(who,index);
}

int delete_index(string who, int num) {
   string *index;
   int x, max;

   index = load_index(who);

   max = sizeof(index);
   if (num > max) {
      return 0;
   }

   while (num < max) {
      index[num] = index[num +1];
   }
   index[max] = nil;

   save_index(who,index);
}

int send_email_to_player(string who, object mail) {
   string filename;
   object usr;

   filename = get_filename(who);
   if (mail->save_me(DATA_DIR + "/" + who + "/" + filename)) {
      if (add_index(who,mail,filename)) {

         if (usr = USER_D->find_player(who)) {
            usr->message("You have new email.\n");
         }
         return 1;
      } else {
         return 0;
      }
   } else {
      return 0;
   }
}

object get_email(string who, string file) {
   string filename;
   object email_obj;

   if (this_player()->query_name() != who) {
      write("You do not have permission to that file.\n");
      return nil;
   }

   filename = DATA_DIR + "/" + who + "/" + file;

   if (file_exists(filename)) {
      email_obj = clone_object(EMAIL_OBJ);
      if (email_obj) {
         email_obj->restore_me(filename);
      } else {
         write("ERROR: Failed to load: " + filename + ".\n");
      }
   } else {
      write("No such file.\n");
      return nil;
   }

   return email_obj;
}

int check_new_email(object who) {
   string name;

   name = who->query_name();
}

int test(void) {
   object mail;
   string *lines;

   mail = clone_object(EMAIL_OBJ);

   if (!mail) {
      return 0;
   }

   mail->set_subject("Test");
   mail->set_to("sirdude");
   mail->set_from("sirdude");
   mail->set_date();

   lines = ({ "Hello Sirdude," });
   lines += ({ "" });
   lines += ({ "Welcome to email... :)" });

   mail->set_lines(lines);

   return send_email_to_player("sirdude", mail);
}

void create(void) {
   test();
}
