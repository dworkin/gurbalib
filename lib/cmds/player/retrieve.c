void usage() {
   string *lines;

   lines = ({ "Usage: retrieve [-h] OBJ" });
   lines += ({ "" });
   lines += ({ "Allows you to retrieve an object OBJ, from storage." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tretrieve sword" });
   lines += ({ "\tretrieve helmet" });
   lines += ({ "See also:" });
   lines += ({ "\tbuy, identify, list, look, sell, store, value" });

   this_player()->more(lines);
}

void main(string str) {

   if (!str || str == "") {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (!this_environment()->is_storage()) {
      this_player()->write("Perhaps you should try retrieving your item from " +
	 "a storage location?\n");
      return;
   }

   this_environment()->borrow_object(str);
}
