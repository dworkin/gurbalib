#include <type.h>

#undef DEBUG_PARSE

mapping verbs;
string *names;
string grammar;
object last_obj;

void rescan_verbs( void );

void create( void ) {
  int i;

  verbs = ([ ]);
  rescan_verbs();
}

string *query_verbs( void ) {
  return( names );
}

int is_verb( string verb ) {
  if( member_array( verb, map_indices( verbs ) ) != -1 )
    return( 1 );
  return( 0 );
}

object query_verb_object( string verb ) {

  return( verbs[verb] );
}

string query_grammar( void ) {
  return( grammar );
}

mixed parse( string str ) {
  mixed *result;
  string function;
  mixed returned;
  int i;

  last_obj = nil;

  result = parse_string( grammar, str );

#ifdef DEBUG_PARSE
  write( "result: " + dump_value( result, ([ ]) ) );
#endif

  if( !result )
    return( 0 );

  function = "";
  if( sizeof( result ) > 1 ) {
    for( i = 0; i < sizeof( result ); i ++ ) {
      switch( typeof( result[i] ) ) {
      case T_STRING:
	/*	if( i == 0 ) */
	  function += lowercase(result[i]) + " ";
	  /*	else
		function += "str "; */
	break;
      case T_OBJECT:
	if( result[i]->is_living() )

	  function += "liv ";
	else
	  function += "obj ";
	break;
      }
    }
    function = implode( explode( function, " " ), "_" );
  } else {
    function = result[0];
  }
  
#ifdef DEBUG_PARSE
  write( "Function : 'can_" + function + "' in object " + verbs[result[0]] ); 
#endif

  switch( sizeof( result ) ) {
  case 1:
    returned = call_other( verbs[result[0]], "can_" + function );
    break;
  case 2:
    returned = call_other( verbs[result[0]], "can_" + function, 
			   result[1] );
    break;
  case 3:
    returned = call_other( verbs[result[0]], "can_" + function, 
			   result[1], result[2] );
    break;
  case 4:
    returned = call_other( verbs[result[0]], "can_" + function, 
			   result[1], result[2], result[3] );
    break;
  case 5:
    returned = call_other( verbs[result[0]], "can_" + function, 
			   result[1], result[2], result[3], result[4] );
    break;
  }

  if( returned == 1 ) {
#ifdef DEBUG_PARSE
      write( "calling : " + "do_" + function ); 
#endif
      switch( sizeof( result ) ) {
      case 1:
	returned = call_other( verbs[result[0]], "do_" + function );
	break;
      case 2:
	returned = call_other( verbs[result[0]], "do_" + function, 
			       result[1] );
	break;
      case 3:
	returned = call_other( verbs[result[0]], "do_" + function, 
			       result[1], result[2] );
	break;
      case 4:
	returned = call_other( verbs[result[0]], "do_" + function, 
			       result[1], result[2], result[3] );
	break;
      case 5:
	returned = call_other( verbs[result[0]], "do_" + function, 
			       result[1], result[2], result[3], result[4] );
	break;
      }
  }
  
  if( !returned ) {
    returned = 1;
  }
  return( returned );
}

void rescan_verbs( void ) {
  mixed *list;
  string verb;
  int i;
  mixed info;

  list = get_dir( "/cmds/verb/*.c" );
  names = list[0];

  for( i = 0; i < sizeof( names ); i++ ) {
    names[i] = names[i][.. (strlen( names[i] )-3)];
    verb = "/cmds/verb/" + names[i];
    verbs[names[i]] = verb;
  }

  grammar = "whitespace = / / word = /[a-z]+/ number = /[0-9]+/ ";

  for( i = 0; i < sizeof( names ); i++ ) {
    write( "Scanning " + names[i] + "(" + verbs[names[i]] + ")" );
  
    info = call_other( verbs[names[i]], "query_verb_info" );

    write( "Verb info: " + dump_value( info, ([]) ) );

    if( sizeof( info ) > 0 ) {
      /* Rules and aliases */
      int j;

      for( j = 0; j < sizeof( info ); j++ ) {
	string *words;
	int k;

	grammar += "Sentence: '" + names[i] + "' ";

	words = explode( info[j], " " );
	for( k = 0; k < sizeof( words ); k++ ) {

	  switch( words[k] ) {
	  case "OBJ":
	    grammar += "OBJ ";
	    break;
	  case "OBJA":
	    grammar += "OBJA ";
	    break;
	  case "OBJI":
	    grammar += "OBJI ";
	    break;
	  case "OBJE":
	    grammar += "OBJE ";
	    break;
	  case "OBJC":
	    grammar += "OBJC ";
	    break;
	  case "LIV":
	    grammar += "LIV ";
	    break;
	  default:
	    grammar += "'" + words[k] + "' ";
	  }
	}
      }
    }
  }
  grammar = grammar + "OBJ: Object ? find_direct_object \
OBJA: Object ? construct_obj_packet \
OBJI: Object ? find_inv_object \
OBJE: Object ? find_environment_object \
OBJC: Object ? find_container_object \
LIV: Object ? find_living_object \
Object: Article_List Adjective_List Noun Obj_Index \
Article: 'the' \
Article: 'a' \
Article: 'an' \
Article: 'any' \
Article: 'my' \
Article: 'in' \
Article: 'at' \
Article: 'on' \
Article: 'from' \
Article: \
Article_List: Article ? group_results \
Adjectives: word Adjectives \
Adjectives: \
Adjective_List: Adjectives ? group_results \
Preposition: word \
Preposition: \
Preposition_List: Preposition ? group_results \
Noun: word \
words: word ? group_results \
Index: number \
Index: \
Obj_Index: Index ? define_obj_index \
";

}

static mixed *construct_obj_packet(mixed *mpTree)
{
  string res;
  int i;

#ifdef DEBUG_PARSE
  write( "construct_obj_packet(" 
	 + dump_value( mpTree[0], ([ ])) + ","
	 + dump_value( mpTree[1], ([ ])) + ","
	 + dump_value( mpTree[2], ([ ])) + ","
	 + dump_value( mpTree[3], ([ ])) + ")\n" ); 
#endif

  res = "";

  for( i = 0; i < sizeof( mpTree[1] ); i++ )
    res += mpTree[1][i] + " ";

  res += mpTree[2];

  return ({ res });
}

static mixed *find_container_object( mixed *mpTree ) {
  object ob;

#ifdef DEBUG_PARSE
  write( "find_container_object(" 
	 + dump_value( mpTree[0], ([ ])) + ","
	 + dump_value( mpTree[1], ([ ])) + ","
	 + dump_value( mpTree[2], ([ ])) + ","
	 + dump_value( mpTree[3], ([ ])) + ")\n" );
#endif

  if( !last_obj ) {
    write( "Parse error: Tell Fudge!\n" );
    return( nil );
  }

  if( sizeof( mpTree[1] ) > 0 ) {
    ob = last_obj->find_adjs_object_num( mpTree[1], mpTree[2], mpTree[3] );
  } else {
    ob = last_obj->find_object_num( mpTree[2], mpTree[3] );
  }
  if( !ob ) {
    return nil;
  }
  
  last_obj = ob;
  return( ({ ob }) );

}

static mixed *find_living_object( mixed *mpTree ) {
  object ob;

#ifdef DEBUG_PARSE
  write( "find_living_object(" 
	 + dump_value( mpTree[0], ([ ])) + ","
	 + dump_value( mpTree[1], ([ ])) + ","
	 + dump_value( mpTree[2], ([ ])) + ","
	 + dump_value( mpTree[3], ([ ])) + ")\n" ); 
#endif
  
  if( sizeof( mpTree[1] ) > 0 ) {
    ob = this_environment()->find_adjs_object_num( mpTree[1], mpTree[2], mpTree[3] );
  } else {
    ob = this_environment()->find_object_num( mpTree[2], mpTree[3] );
  }
  
  if( ob ) {
    if( ob->is_living() ) {
      last_obj = ob;
      return( ({ ob }) );
    }
  }

  return( nil );

}

static mixed *find_direct_object( mixed *mpTree ) {
  object ob;
  
#ifdef DEBUG_PARSE
  write( "find_direct_object(" 
	 + dump_value( mpTree[0], ([ ])) + ","
	 + dump_value( mpTree[1], ([ ])) + ","
	 + dump_value( mpTree[2], ([ ])) + ","
	 + dump_value( mpTree[3], ([ ])) + ")\n" ); 
#endif
  
  if( sizeof( mpTree[1] ) > 0 ) {
    /* With adjective */
    ob = this_environment()->find_adjs_object_num( mpTree[1], mpTree[2], mpTree[3] );
    if( !ob ) {
      ob = this_player()->find_adjs_object_num( mpTree[1], mpTree[2], mpTree[3] );
      if( !ob ) {
	return nil;
      }
    }
  } else {
    ob = this_environment()->find_object_num( mpTree[2], mpTree[3] );
    if( !ob ) {
      ob = this_player()->find_object_num( mpTree[2], mpTree[3] );
      if( !ob ) {
	return nil;
      }
    }
  }
  
  if( ob->is_living() ) {
    return( nil );
  }

  last_obj = ob;
  return( ({ ob }) );
}

static mixed *find_inv_object( mixed *mpTree ) {
  object ob;
  
#ifdef DEBUG_PARSE
  write( "find_inv_object(" 
	 + dump_value( mpTree[0], ([ ])) + ","
	 + dump_value( mpTree[1], ([ ])) + ","
	 + dump_value( mpTree[2], ([ ])) + ","
	 + dump_value( mpTree[3], ([ ])) + ")\n" ); 
#endif
  
  if( sizeof( mpTree[1] ) > 0 ) {
    /* With adjective */
    ob = this_player()->find_adjs_object_num( mpTree[1], mpTree[2], mpTree[3] );
  } else {
    /* Without adjective */
    ob = this_player()->find_object_num( mpTree[2], mpTree[3] );
  }
  if( !ob ) {
    return nil;
  }

  last_obj = ob;
  return( ({ ob }) );
}

static mixed *find_environment_object( mixed *mpTree ) {
  object ob;
  
#ifdef DEBUG_PARSE
  write( "find_environment_object(" 
	 + dump_value( mpTree[0], ([ ])) + ","
	 + dump_value( mpTree[1], ([ ])) + ","
	 + dump_value( mpTree[2], ([ ])) + ","
	 + dump_value( mpTree[3], ([ ])) + ")\n" ); 
#endif

  if( sizeof( mpTree[1] ) > 0 ) {
    ob = this_environment()->find_adjs_object_num( mpTree[1], mpTree[2], mpTree[3] );
  } else {
    ob = this_environment()->find_object_num( mpTree[2], mpTree[3] );
  }
  if( !ob ) {
    return nil;
  }

  last_obj = ob;
  return( ({ ob }) );
}

static mixed *define_obj_index( mixed *mpTree ) {
  if( !mpTree || !sizeof( mpTree ) )
    return( ({ 1 }) );
  else
    return( ({ (int) mpTree[0] }) );
}

static mixed *group_results( mixed *mpTree ) {
  return( ({ mpTree }) );
}

static mixed *fix_order(mixed *mpTree) {
  mixed obj;
  int i;
  #ifdef DEBUG_PARSE
    write("fix_order("
       + dump_value( mpTree[0], ([ ])) + ","
       + dump_value( mpTree[1], ([ ])) + ","
       + dump_value( mpTree[2], ([ ])) + ","
       + dump_value( mpTree[3], ([ ])) + ","
       + dump_value( mpTree[4], ([ ])) + ","
       + dump_value( mpTree[5], ([ ])) + ","
       + dump_value( mpTree[6], ([ ])) + ")\n" );
      #endif
    last_obj = mpTree[6];
      obj = find_container_object(mpTree[1..4]);
      if(typeof(obj) == T_ARRAY)
              mpTree = ({mpTree[0]})+obj+({mpTree[5],mpTree[6]});
      else
              mpTree = ({mpTree[0],mpTree[3]})+mpTree[5..6];
      return mpTree;
}

