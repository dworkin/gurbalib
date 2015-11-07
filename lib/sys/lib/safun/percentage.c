int percentage(mixed part, mixed total) {
   if (total == 0) {
      return 0;
   }
   return (int)((float) part * 100.0 / (float) total);
}

