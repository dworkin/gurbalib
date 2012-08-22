/* strcmp, by Aidil@Way of the Force */
nomask static int strcmp(string one, string two) {
   if (one < two) {
      return -1;
   } else if (one > two) {
      return 1;
   } else {
      return 0;
   }
}
