int strstr(string search, string what) { 
   string pre; 

   argcheck(search, 1, "string"); 
   argcheck(what, 2, "string"); 

   what = implode(rexplode(what, "%"), "%%"); 

   if (sscanf(search, "%s" + what + "%*s", pre) > 0) { 
      return strlen(pre); 
   } else { 
      return -1; 
   } 
}
