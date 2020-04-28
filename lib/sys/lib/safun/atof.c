float atof(string str) {
   float n;

   if (sscanf(str, "%f", n) > 0) {
     return n;
   }
     return 0.0;
}
