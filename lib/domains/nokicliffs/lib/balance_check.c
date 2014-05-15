object *balance_check(object player) {
   object *inv;
   object law_shard, chaos_shard;
   int i, dim;

   inv = player->query_inventory();
   for (i = 0, dim = sizeof(inv); i < dim; i++) {
      if (inv[i]->is_id("lawshard")) {
         law_shard = inv[i];
      }
      if (inv[i]->is_id("chaosshard")) {
         chaos_shard = inv[i];
      }
   }

   inv = ({ law_shard, chaos_shard }) - ({ nil });
   return inv;
}
