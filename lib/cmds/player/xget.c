void main( string arg ) {
   object ob;
   object *inv;
   int i;
   object *objs;
   

   if( !arg || arg == "" ) {
      write( "Get what?\n" );
      return;
   }
  
   if( arg == "all" ) {
      inv = this_environment()->query_inventory();
      for( i=0; i < sizeof( inv ); i++ ) {
         if( inv[i]->is_gettable() ) {
            if( inv[i]->move( this_player() ) ) {
               this_player()->targetted_action( "$N $vpick up $o.", nil, inv[i] );
            } 
            else {
               this_player()->targetted_action( "$N $vtry to pick up $o, but $vfail.", nil, inv[i] ); 
            }
         } 
         else {
            if( !inv[i]->is_player() ) {
               this_player()->targetted_action( "$N $vare unable to get $o.", nil, inv[i] ); 
            }
         }
      } 
      return;
   }   
  
   ob = this_environment()->present( arg );
   if( !ob ) {  
      /* Hmm. Not a real object. Maybe it's a fake one. */

      /* Check the players inventory */
      objs = this_player()->query_inventory();
      for( i = 0; i < sizeof( objs ); i++ ) {
         if( objs[i]->query_items() ) {
            if( member_array( arg, objs[i]->query_items() ) != -1 ) {
               /* Found a fake object */
               this_player()->targetted_action( "$N $vare unable to get the "+arg+".", nil, ob ); 
               return;
            }
         }
      }
      /* Check if it's in the room */
      if( member_array( arg, this_environment()->query_items() ) != -1 ) {
         /* Found a fake object */
         this_player()->targetted_action( "$N $vare unable to get the "+arg+".", nil, ob ); 
         return;
      }
      /* Check the rooms inventory */
      objs = this_environment()->query_inventory();
      for( i = 0; i < sizeof( objs ); i++ ) {
         if( objs[i]->query_items() ) {
            if( member_array( arg, objs[i]->query_items() ) != -1 ) {
               /* Found a fake object */
               this_player()->targetted_action( "$N $vare unable to get the "+arg+".", nil, ob ); 
               return;
            }
         }
      }
     
      /* There is nothing at all like that here to try to get */
      write( "You can't seem to find the " + arg + ".\n" );
      return;
   }
    
   else {
      /* try to get a real item */
      if( ob->is_gettable() ) {
         if( ob->move( this_player() ) ) {
            this_player()->targetted_action( "$N $vpick up $o.", nil, ob );
         } 
         else {
            this_player()->targetted_action( "$N $vtry to pick up $o, but $vfail.", nil, ob ); 
         }
      } 
      else {
         this_player()->targetted_action( "$N $vare unable to get $o.", nil, ob ); 
      }
   }
}
