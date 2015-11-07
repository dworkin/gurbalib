object *players(void) {
   int i, sz;
   object *p;
   object *u;
   object player;

   u = users();
   p = ( { } );

   sz = sizeof(u);
   for (i = 0; i < sz; i++) {
      if (player = u[i]->query_player()) {
         if (player->query_Name()) {
            p += ( { player } );
         }
      }
   }
   return p;
}
