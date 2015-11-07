string ruler(int length) {
   string ruler_str;
   int    counter;

   if (length < 10) {
      length = 10;
   }

   while (counter < length) {
      if (counter == 0) {
         ruler_str = "0";
      } else if (!(counter % 10)) {
         ruler_str += (string)(counter / 10);
      } else if (!(counter % 5)) {
         ruler_str += "+";
      } else if (!(counter % 10)) {
         ruler_str += "" + (counter / 10) + "";
      } else {
         ruler_str += "-";
      }

      counter++;
   }
   ruler_str += ":";
   return ruler_str;
}
