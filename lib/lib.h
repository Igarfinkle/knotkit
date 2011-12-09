
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <sys/stat.h>
#include <sys/errno.h>

#include <set>
#include <map>
#include <string>
#include <queue>
#include <algorithm>

#include <tr1/functional>
#include <tr1/unordered_map>

/* just need to implement ==, < */
template<class T> bool operator != (const T &a, const T &b) { return ! (a == b); }
template<class T> bool operator <= (const T &a, const T &b) { return (a < b) || (a == b); }
template<class T> bool operator > (const T &a, const T &b) { return ! (a <= b); }
template<class T> bool operator >= (const T &a, const T &b) { return ! (a < b); }

typedef enum copy { COPY, COPY1 } copy;
typedef enum copy2 { COPY2 } copy2;

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

typedef long long int64;
typedef unsigned long long uint64;

typedef size_t hash_t;

inline hash_t hash (bool x) { return (hash_t)x; }
inline hash_t hash (char x) { return (hash_t)x; }
inline hash_t hash (unsigned char x) { return (hash_t)x; }
inline hash_t hash (short x) { return (hash_t)x; }
inline hash_t hash (unsigned short x) { return (hash_t)x; }
inline hash_t hash (int x) { return (hash_t)x; }
inline hash_t hash (unsigned x) { return (hash_t)x; }
inline hash_t hash (long x) { return (hash_t)x; }
inline hash_t hash (unsigned long x) { return (hash_t)x; }

inline hash_t hash (uint64 x) { return (hash_t)((x >> 32) ^ x); }

template<class T>
inline hash_t hash (const T &x)
{
  return x.hash_self ();
}

inline hash_t
hash_combine (hash_t a, hash_t b)
{
  return (a ^ b) * 131;
}

/* uint64 */
static const unsigned uint64_bits = 64;
static const unsigned uint64_bit_mask = 0x3f;

static const unsigned unsigned_bits = 32;
static const unsigned unsigned_bit_mask = 0x1f;

inline unsigned uint64_bitcount (uint64 x) { return __builtin_popcountll (x); }
inline unsigned uint64_ffs (uint64 x) { assert (x != 0); return __builtin_ctzll (x) + 1; }

inline uint64 uint64_bitmask (unsigned i) { assert (i >= 1 && i <= uint64_bits); return ((uint64)1) << (i - 1); }
inline unsigned uint64_fill (unsigned b) { assert (b <= uint64_bits); return ((uint64)1 << b) - 1; }
inline uint64 uint64_bitset (uint64 x, unsigned i) { return x | uint64_bitmask (i); }
inline uint64 uint64_bitclear (uint64 x, unsigned i) { return x & ~uint64_bitmask (i); }
inline uint64 uint64_bittoggle (uint64 x, unsigned i) { return x ^ uint64_bitmask (i); }
inline bool uint64_bittest (uint64 x, unsigned i) { return (bool)(x & uint64_bitmask (i)); }

/* unsigned */
inline unsigned unsigned_bitmask (unsigned i) { assert (i >= 1 && i <= unsigned_bits); return ((unsigned)1) << (i - 1); }
inline unsigned unsigned_fill (unsigned b) { assert (b <= unsigned_bits); return ((unsigned)1 << b) - 1; }

inline unsigned unsigned_discard_bit (unsigned w, unsigned i)
{
  assert (i >= 1 && i <= unsigned_bits);
  return (w & ((((unsigned)1) << (i - 1)) - 1))
    | ((w >> i) << (i - 1));
}

inline unsigned unsigned_bitset (unsigned w, unsigned i) { return w | unsigned_bitmask (i); }
inline unsigned unsigned_bitclear (unsigned w, unsigned i) { return w &~ unsigned_bitmask (i); }
inline bool unsigned_bittest (unsigned w, unsigned i) { return (bool)(w & unsigned_bitmask (i)); }

inline unsigned unsigned_bitcount (unsigned w) { return __builtin_popcount (w); }
inline unsigned unsigned_ffs (unsigned w) { assert (w); return __builtin_ctzl (w) + 1; }

/* pack the bits of z into the zeros of x, where x has n bits. */
unsigned unsigned_pack (unsigned n, unsigned x, unsigned z);

inline bool is_odd (int x) { return x & 1; }
inline bool is_odd (unsigned x) { return x & 1; }

inline bool is_even (int x) { return !is_odd (x); }
inline bool is_even (unsigned x) { return !is_odd (x); }

inline unsigned unsigned_2pow (unsigned e) { return ((unsigned)1) << e; }

class unsigned_const_iter
{
 private:
  unsigned x;
  unsigned b;
  
 public:
  unsigned_const_iter (unsigned x_) : x(x_), b(0) { if (x) b = unsigned_ffs (x); }
  unsigned_const_iter (const unsigned_const_iter &i) : x(i.x), b(i.b) { }
  ~unsigned_const_iter () { }
  
  unsigned_const_iter &operator = (const unsigned_const_iter &i) { x = i.x; b = i.b; return *this; }
  
  unsigned val () const { assert (x); return b; }
  operator bool () { return (bool)x; }
  void operator ++ () { assert (x); x = unsigned_bitclear (x, b); if (x) b = unsigned_ffs (x); }
  void operator ++ (int) { operator ++ (); }
};

inline bool between (unsigned a, unsigned x, unsigned b) { return a <= x && x <= b; }

void stderror (const char *fmt, ...);

int alpha_to_int (char c);

#include <lib/io.h>

#include <lib/show.h>
#include <lib/refcount.h>
#include <lib/pair.h>
#include <lib/maybe.h>
#include <lib/vector.h>
#include <lib/set.h>

class bitset;
template<unsigned B> class ullmanset;

unsigned fact (unsigned n);
unsigned choose (unsigned n, unsigned k);

inline int random_int (int from, int to)
{
  assert (to >= from);
  return from + (random () % (to - from + 1));
}

#include <lib/smallbitset.h>
#include <lib/bitset.h>
#include <lib/ullmanset.h>
#include <lib/setcommon.h>

#include <lib/map_wrapper.h>
#include <lib/map.h>
#include <lib/hashmap.h>
#include <lib/ullmanmap.h>
#include <lib/mapcommon.h>
#include <lib/unionfind.h>
#include <lib/priority_queue.h>
#include <lib/directed_multigraph.h>
