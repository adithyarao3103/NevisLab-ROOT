// 01-Jun-2023 WGS:
// Definitions of structures for STL+ROOT testing.

#include <vector>
#include <map>

// Some typedefs for practice in making things easier. If this doesn't
// look "easy", ask which looks simpler: map2D_vt (for 'map2D value type'),
//  or std::pair<std::tuple<int,int>, double>
typedef std::map<int,double>      vMap_t;
typedef vMap_t::value_type        vMap_vt;
typedef std::tuple<int,int>       axes_t;
typedef std::map< axes_t, double> map2D_t;
typedef map2D_t::value_type       map2D_vt;
