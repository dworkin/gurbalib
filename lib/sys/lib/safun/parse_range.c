int *parse_range(string str) {
   string  left_str, right_str, tmp_str, tmp2_str, flag_str;
   mixed  *tmp_arr, tmp2_arr;
   int    *ret_arr, *parsed_arr;
   int     left_nr, right_nr, tmp_nr, nr, nr2, nr3, flag;

   if (sscanf(str, "-%s", tmp_str)) {
      str = "1" + str;
   }

   while (str[strlen(str) - 1] == '-') {
      str = str[0..strlen(str) - 2];
   }

   while (sscanf(str, "%s--%s", left_str, right_str)) {
      str = left_str + "-" + right_str;
   }

   while (str[0] == ',') {
      str = str[1..strlen(str)-1];
   }

   while (str[strlen(str)-1] == ',') {
      str = str[0..strlen(str)-2];
   }

   for (nr = 0; nr < strlen(str); nr++) {
      if (str[nr] == ' ') {
         str[nr] = ',';
      }
   }

   while (sscanf(str, "%s,,%s", left_str, right_str)) {
      str = left_str + "," + right_str;
   }

   parsed_arr = ({ });
   ret_arr = ({ });

   while (sscanf(str, "%s-%s", left_str, right_str) == 2) {
      tmp_arr = explode(left_str + ",", ",");

      if (!sscanf(tmp_arr[sizeof(tmp_arr) - 1], "%d", left_nr)) {
         return nil;
      }

      tmp_arr = explode(right_str + ",", ",");

      if (!sscanf(tmp_arr[0], "%d", right_nr)) {
         return nil;
      }

      if (right_nr < left_nr) {
         tmp_nr = left_nr;
         left_nr = right_nr;
         right_nr = tmp_nr;
      }

      for (nr = left_nr; nr <= right_nr; nr++) {
         parsed_arr += ({ nr });
      }

      str = left_str + "," + right_str;
   }

   tmp2_arr = explode(str + ",", ",");

   nr2 = sizeof(tmp2_arr);
   for (nr = 0; nr < nr2; nr++) {
      if (!intp(tmp2_arr[nr])) {
         sscanf(tmp2_arr[nr], "%d", nr3);
      }
      parsed_arr += ({ nr3 });
   }

   return set_remove_repeats(parsed_arr);
}

