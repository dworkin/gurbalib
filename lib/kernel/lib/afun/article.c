string article(string name) {
   argcheck(name, 1, "string");

   if ((strlen(name) > 3 && lowercase(name[0..3]) == "hour") ||
      (strlen(name) > 4 && lowercase(name[0..4]) == "honor") ||
      (strlen(name) > 5 && lowercase(name[0..5]) == "honour")) {
      return ("an");
   }

   switch (name[0]) {
      case 'a':
      case 'e':
      case 'i':
      case 'o':
      case 'u':
	 return ("an");
      default:
	 return ("a");
   }

   return nil;
}
