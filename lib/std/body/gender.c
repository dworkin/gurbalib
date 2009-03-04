/*
   NOTES:
   This file should use string...not int.

   Why? Because it's more readable? 

   can we change this without screwin somthin up?

   I would guess so, since if you don't have a gender specified, you are made male. 

   Satch
*/

int  gender;

void create() { }

void set_gender( int gen )
{
   gender = gen;
}

int query_gender( void )
{
   return( gender );
}

string query_gender_string( void )
{
   switch( gender )
   {
      case 1 : return("male");
      case 2 : return("female");

      default: return("Unable to determine gender");
      }
   }

string query_gender_pronoun( void )
{
   switch( gender )
   {
      case 1 : return("he");
      case 2 : return("she");

      default: return("it");
      }
   }

string query_gender_possessive( void )
{
   switch( gender )
   {
      case 1 : return("his");
      case 2 : return("hers");

      default: return("its");
      }
   }

string query_gender_reflexive( void )
{
   switch( gender )
   {
      case 1 : return("himself");
      case 2 : return("herself");

      default: return("itself");
      }
   }
