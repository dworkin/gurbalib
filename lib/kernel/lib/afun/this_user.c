static object this_user(void) {
   object ob;

   ob = ::this_user();
   if (ob && ob <- CONNECTION) {
      ob = ob->query_user();
   }
   return ob;
}
