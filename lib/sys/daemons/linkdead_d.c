static string *linkdead;

void add_linkdead(string str) {
   if (!linkdead) {
      linkdead = ({ });
   }
   linkdead = ({ str });
}

void remove_linkdead(string str) {
   if (!linkdead) {
      linkdead = ({ });
      return;
   }
   linkdead -= ({ str });
}

string *list_linkdead() {
   int i, dim;
   string *lines;

   if (!linkdead) {
      linkdead = ({ });
   }

   lines = ({  });

   for (i = 0, dim = sizeof(linkdead); i < dim; i++) {
      lines += ({ linkdead[i] + " %^BOLD%^%^YELLOW%^[link-dead]%^RESET%^" });
   }

   return lines;
}

