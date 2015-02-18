int functionp(mixed val) {
   if (typeof(val) == T_OBJECT && val<-"/builtin/function") {
      return 1;
   }
   return 0;
}
