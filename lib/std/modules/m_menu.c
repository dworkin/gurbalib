/*
 * A small wrapper module for the menu library.
 * Does some checking on menu data to produce more informative errors
 */
inherit "/sys/lib/menu";

nomask static void do_menu(mixed header, mixed * menu, varargs mixed footer) {
   int item, items, pos, sz;

   argcheck(header && (stringp(header)
      || arrayp(header)), 1, "string or fcall array");
   argcheck(arrayp(menu), 2, "array");
   argcheck(!footer || (stringp(footer)
      || arrayp(footer)), 2, "empty, string or fcall array");

   for (item = 0, items = sizeof(menu); item < items; item++) {
      sz = sizeof(menu[item]);
      if (sz != 4) {
         error("Error in menu item " + item +
            ", expected an array of 4 elements, got " + sz);
      }

      if (!stringp(menu[item][0])) {
         error("Error in menu item " + item + ", string expected in element 0");
      }

      if (!stringp(menu[item][1]) && !arrayp(menu[item][1])) {
         error("Error in menu item " + item +
            ", string or fcall array expected in element 1");
      }

      if (menu[item][2] && (!stringp(menu[item][2]) && 
         !arrayp(menu[item][2]))) {

         error("Error in menu item " + item +
            ", string, fcall array or nil expected in element 2");
      }

      if (!arrayp(menu[item][3])) {
         error("Error in menu item " + item + 
            ", fcall array expected in element 3");
      }

   }
   ::do_menu(header, menu, footer);
}
