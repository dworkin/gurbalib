/*
   Coded by: Satch@Gurba
   File    : /std/body/size.c
   Date    : 02.26.98

*/

private int actual_size;

int set_size(int size) {
   if (!size) {
      return 0;
   }

   if (size > 6) {
      return 0;
   }

   actual_size = size;
}

int query_size(void) {
   return actual_size;
}

/* convert_size is used to convert the integer actual_size to a string */
string convert_size(void) {
   string desc;

   switch (actual_size) {
      case 1:
         return ("small");
      case 2:
         return ("medium");
      case 3:
         return ("medium/large");
      case 4:
         return ("large");
      case 5:
         return ("extra large");
      case 6:
         return ("any");

      default:
         return ("no size given");
   }
}
