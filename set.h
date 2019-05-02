
#ifndef SET_INCLUDED
#define SET_INCLUDED    1

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cmath>


class set 
{
   size_t set_size;
   double max_load_factor;
   std::vector< std::list< std::string >> buckets;

public:
   // Number of buckets cannot be zero. 
   
   set( size_t num_buckets = 4, double max_load_factor = 3.0 ) 
      : set_size{ 0 },
        max_load_factor{ max_load_factor },
        buckets{ std::vector< std::list< std::string >> ( num_buckets ) }
   {
      if( num_buckets == 0 )
         throw std::runtime_error( "number of buckets cannot be zero" ); 
   }

   set( const set& s ) = default; 
   set& operator = ( const set& s ) = default; 
   ~set() = default; 

   set(std::initializer_list<std::string > init )
      :set( ) 
   {
      for( const auto& s : init )
         insert(s);
   }

   bool contains( const std::string& s ) const;

   bool simp_insert( const std::string& s );
      // Returns true if the insertion took place.
      // simp_insert is called 'simple', because it does not rehash.

   bool insert( const std::string& s );
      // Returns true if the insertion took place.

   bool remove( const std::string& s );
      // Returns true if s was present.

   size_t size() const
   {
      return set_size;
   }

   bool isempty() const
   {
      return set_size == 0;
   }

   double loadfactor() const 
   {
      return static_cast<double> ( set_size ) / buckets. size( ); 
         // C-style casts of form (double) set_size are deprecated. 
   }

   double standarddev() const 
   {
      double sum = 0.0;
      double lf = loadfactor();

      for ( const auto& l : buckets ) 
      {
	  double dif = l.size() - lf;
          sum += dif*dif;
      }

      return sqrt( sum / buckets.size() );
   }

   void clear();
     
   void rehash( size_t newbucketsize );
      // Is this a const operation? Somewhat.
 
   std::ostream& print( std::ostream& out ) const; 
   std::ostream& printstatistics( std::ostream& out ) const;

   // You should not use the following functions, but they are needed in 
   // main, because we want to see all elements and we 
   // have no iterators. Iterators could
   // be defined as pairs consisting of 
   //    std::vector< std::list< std::string >> :: const_iterator
   //    std::list< std::string > :: const_iterator

   size_t getnrbuckets( ) const  
   {
      return buckets. size( ); 
   }

   const std::list< std::string > & getbucket( size_t i ) 
   {
      return buckets[i];
   }
};


inline std::ostream& operator << ( std::ostream& out, const set& s ) 
{
   return s.print( out );
}


bool equal( const std::string& s1, const std::string& s2 );
size_t hash( const std::string& s );

#endif


