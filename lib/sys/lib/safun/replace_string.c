string replace_string(string str, string old, string newstr) {
   int d, olen, slen, i;
   string done;

   argcheck(str, 1, "string");
   argcheck(old, 2, "string");
   argcheck(newstr, 3, "string");

   olen = strlen(old) -1;
   slen = strlen(str);

   d = 0;
   done = "";
   for (i = 0; i < slen; i++) {

      if (slen > (i + olen)) {
         /* Still not reached the end of the string */
         if (str[i..(i + olen)] == old) {
            /*Found an occurance of the old string */
            done += newstr;
            d += strlen(newstr);
            i += olen;
         } else {
            done += " ";
            done[d] = str[i];
            d++;
         }
      } else {
         done += str[i..];
         return done;
      }
   }

   return done;
}
