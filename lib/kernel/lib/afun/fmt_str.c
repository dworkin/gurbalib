string fmt_str(string str, varargs int dim, int indent_first, int indent_all, 
   int second_indent_len) {
   string *arr;
   string  arg1, p;
   int c, sz, ts;

   if (dim == 0) {
      dim = 78;
   }

   if (second_indent_len) {
      p = pad_string_left(second_indent_len);
   } else {
      p = "    ";
   }

   arg1 = trim_str(str);
   arr = explode(arg1, " ");

   for (c = 0; c < sizeof(arr); c++) {
      if (indent_first && c == 0) {
         arr[c] = "    " + arr[c];
      }

      if (sz + (ts = strlen(arr[c] + second_indent_len)) > dim) {
         arr[c] = "\n" + ((indent_all && c > 0) ? p : "") + arr[c];
      }
      sz += ts + 1;
   }

   return implode(arr, " ");
}
