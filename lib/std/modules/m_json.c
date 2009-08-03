/*
 * JSON message generator and parser module
 * This module was created as part of a framework to support
 * 'railsgame', a modular web based mud server (gurbalib acts as
 * gameserver component in the railsgame framework)
 *
 * By Aidil of Way of the Force, august 2009
 *
 * This code is in the public domain.
 *
 *
 * USAGE:
 *
 * string save_json(mapping data) 
 * 
 *   Turn 'mapping' into a JSON message
 *   Note that the mapping must contain a service and action key with appropriate
 *   (string) values. The return value is the JSON message. An error will be thrown
 *   if the mapping cannot be converted to a json message
 *
 * mapping restore_json(string message)
 *
 *   Return a mapping containing the parsed JSON message
 *   an error will be thrown if the message is not a valid json message
 *
 */

#include <type.h>

#undef DEBUG_JSON

#define GRAMMAR "whitespace=/[ 	]*/\n\
                 beginmsg=/{/\n\
                 endmsg=/}/\n\
                 kvsep=/:/\n\
                 pairsep=/,/\n\
                 string=/\"([^\\\\\"\n]*(\\\\.)*)*\"/\n\
                 int=/[0-9]+/\n\
                 msg : beginmsg pairs endmsg\n\
                 pairs : pair\n\
                 pairs : pairs pairsep pair\n\
                 pair : key kvsep value ? wrap_kvpair\n\
                 key : ustring\n\
                 value: ustring\n\
                 value: int\n\
                 ustring: string ? unquote_string"


string save_json(mapping data) {
  string service;
  string action;
  string result;
  string * keys;
  int count;
  int size;

  if(!data) {
    error("Empty mapping?");
  }

  service = data["service"];
  action  = data["action"];

  if(!service) {
    error("Service is a required field");
  }

  if(!action) {
    error("Action is a required field");
  }

  keys = map_indices(data);

  keys -= ({ "service", "action" });

  result = "{\"service\" : \""+service+"\", \"action\" : \""+action+"\"";
  for( count = 0, size = sizeof( keys ); count < size; count++ ) {
    result += ", \""+keys[count]+"\" : ";
    switch( typeof( data[keys[count]] ) ) {
      case T_STRING :
        result += "\""+data[keys[count]]+"\"";
        break;
      case T_INT :
        result += data[keys[count]];
        break;
      default : 
        error( "Bad data for json message: "+dump_value( data[keys[count]] ) );
        break;
    }
  }
  result += "}";
  return result;
}

mapping restore_json( string message ) {
  int count;
  int size;
  mapping result;
  mixed * parse_tree;

  result = ([ ]);

  parse_tree = parse_string(GRAMMAR,message);

  if( !parse_tree ) {
    error( "Bad message format" );
  }

  for( count = 0, size = sizeof( parse_tree ); count < size; count++ ) {
    if( arrayp( parse_tree[count] ) ) {
      result[parse_tree[count][0]] = parse_tree[count][1];
#ifdef DEBUG_JSON
      write( "Setting " + parse_tree[count][0] + " to " + parse_tree[count][1] );
    } else {
      write( dump_value( parse_tree[count] ) );
#endif
    }
  }

  return result;
}

mixed * wrap_kvpair( mixed * data ) {
  return ({ ({ data[0] , data[2] }) });
}

mixed * unquote_string( mixed * data ) {
  return ({ data[0][1..strlen(data[0])-2] });
}

