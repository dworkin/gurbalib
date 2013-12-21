string format_idle_time(int time) {
   int mins, hrs, days;
   string str;

   mins = time / 60;
   time = time - (mins * 60);

   hrs = mins / 60;
   mins = mins - (hrs * 60);

   days = hrs / 24;
   hrs = hrs - (days * 24);

   str = "";

   if (time > 0) {
      str = " " + time + "s";
   }

   if (mins > 0) {
      str = " " + mins + "m";
   }

   if (hrs > 0) {
      str = " " + hrs + "h";
   }

   if (days > 0) {
      str = " " + days + "d";
   }

   return str;
}
