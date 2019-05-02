/*
 * set.cpp
 *
 *  Created on: Mar 18, 2019
 *      Author: benja
 */

#include "set.h"
//load factor==num of strings/num of buckets

// From previous task:

bool equal( const std::string& s1, const std::string& s2 ){
    if(s1.length() != s2.length())
        return false;
    for (size_t i=0; i < s1.length(); i++) 
    {
        if(tolower(s1[i] != tolower(s2[i])))
            return false;
    }
    return true;
}

// Must be new written:
// It is important that equal and hash agree. That means:
//    If equal(s1,s2) then hash(s1) == hash(s2).

size_t hash( const std::string& st )
{
    std::string s = st;
    size_t sum = 0, pow = 31;

    for (size_t i=0, k=1; i<s.size(); k++, i++)
    {
        s[i] = tolower(s[i]); //making case insensitive
    }
    //calculating for the hash function: s[0]*31^(n-1)+s[1]*31^(n-2)+...
    for (size_t i = 0, b = 1; i < s.size(); i++, b++)
    {
        pow = 31;
        size_t num = s.size() - b;
        if (num == 0)
            pow = 1;
        else
            for (size_t t = 1; t < num; t++)
            {
                pow = pow * pow;
            }
        sum = sum + s[i] * pow;
    }
    return sum;
}


bool set::contains( const std::string& s ) const
{
    size_t a = hash(s) % buckets.size();
    for(auto it = buckets[a].begin(); it!= buckets[a].end(); it++)
    {
        if (equal (*it, s))
            return true;
    }
    return false;
}


bool set::simp_insert( const std::string& s )
{
    if (set::contains(s))
        return false;
    size_t a = hash(s) % buckets.size();
    buckets[a].push_back(s);
    set_size++;
    return true;
}


bool set::insert( const std::string& s )
{
    if (set::simp_insert(s))
    {
        size_t a = loadfactor();
        if (a > max_load_factor)
        {
            rehash(buckets.size()*2);
        }
        return true;
    }
    else
        return false;
}

void set::rehash( size_t newbucketsize )
{
    if (newbucketsize < 4)
        newbucketsize = 4;
    std::vector< std::list< std::string >> newbuckets = std::vector< std::list< std::string >> (newbucketsize);

    for (size_t i = 0; i < buckets.size(); i++)
    {
        for (auto it = buckets[i].begin(); it != buckets[i].end(); it++)
        {
            size_t a = hash(*it) % newbuckets.size();
            newbuckets[a].push_back(*it);
        }
    }

    buckets = newbuckets;
}

bool set::remove( const std::string& s )
{
    if(!set::contains(s))
        return false;
    size_t a = hash(s) % buckets.size();
    auto it = buckets[a].begin();
    while (it != buckets[a].end())
    {
        if (*it == s)
            break ;
        it++;
    }
    buckets[a].erase(it);
    set_size--;
    return true;
}

void set::clear( )
{
   for (size_t i = 0; i < buckets.size(); i++)
    buckets[i].clear();
}

std::ostream& set::print( std::ostream& out ) const
{
    size_t i=0;
    for (auto it = buckets.begin(); it!=buckets.end(); i++, it++)
    {
        out<<"bucket["<<i<<"]\t";
        out << "{";
        for (auto a = buckets[i].begin(); a!= buckets[i].end(); a++)
            out << *a << " ";
        out << "}"<< std::endl;
    }
    //out << "St.dev = " << standarddev() << std::endl;
    return out;
}


std::ostream& set::printstatistics( std::ostream& out ) const
{
    std::cout << "set size =            " << size( ) << "\n";
    std::cout << "load factor =         " << loadfactor( ) << " ( max = " << max_load_factor << " )\n";
    std::cout << "standard deviation =  " << standarddev( ) << "\n";
    return out;
}


