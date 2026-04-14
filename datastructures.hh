// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <source_location>
#include <unordered_map>

// Types for IDs
using PlaceID = long long int;
using AreaID = long long int;
using Name = std::string;
using WayID = std::string;

// Return values for cases where required thing was not found
PlaceID const NO_PLACE = -1;
AreaID const NO_AREA = -1;
WayID const NO_WAY = "!!No way!!";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

// Enumeration for different place types
// !!Note since this is a C++11 "scoped enumeration", you'll have to refer to
// individual values as PlaceType::SHELTER etc.
enum class PlaceType { OTHER=0, FIREPIT, SHELTER, PARKING, PEAK, BAY, AREA, NO_TYPE };

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Duration is unknown
Distance const NO_DISTANCE = NO_VALUE;



// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    explicit NotImplemented(std::string const msg = "",
                            const std::source_location location = std::source_location::current())
        : msg_{}
    {
        std::string funcname = location.function_name();
        if (auto namestart = funcname.find_last_of(':'); namestart != std::string::npos)
        { funcname.erase(0, namestart+1); }
        if (auto nameend = funcname.find_first_of('('); nameend != std::string::npos)
        { funcname.erase(nameend, std::string::npos); }
        msg_ = (!msg.empty() ? msg+" in " : "")+funcname+"()";
    }
    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};

// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate: Returns size of unordered_map in constant time.
    int place_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Clears all elements from all unordered maps, which requires destroying each stored element.
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Iterates once over all n entries to collect IDs into the vector.
    std::vector<PlaceID> all_places();

    // Estimate of performance: O(1) average
    // Short rationale for estimate: One hash table lookup to check for duplicates and one
    // insertion, both O(1) average for unordered_map.
    bool add_place(PlaceID id, Name const& name, PlaceType type, Coord xy);

    // Estimate of performance: O(1) average
    // Short rationale for estimate: Single unordered_map lookup by ID.
    std::pair<Name, PlaceType> get_place_name_type(PlaceID id);

    // Estimate of performance: O(1) average
    // Short rationale for estimate:  Single unordered_map lookup by ID.
    Coord get_place_coord(PlaceID id);

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: Collecting all IDs is O(n). Sorting is O(n log n),
    // each comparator call performs two O(1) average hash lookups, so sorting
    // remains O(n log n) overall.
    std::vector<PlaceID> places_alphabetically();

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: Same as places_alphabetically().
    std::vector<PlaceID> places_coord_order();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Scanning all n places linearly to find all places having the same name.
    std::vector<PlaceID> find_places_name(Name const& name);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Same as find_places_name().
    std::vector<PlaceID> find_places_type(PlaceType type);

    // Estimate of performance: O(1) average
    // Short rationale for estimate: Single unordered_map lookup and in-place string assignment,
    // both O(1) average.
    bool change_place_name(PlaceID id, Name const& newname);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(k) average, where k = number of boundary coordinates
    // Short rationale for estimate: One hash map lookup and one insertion are O(1) average.
    // coords is passed by value then moved into the struct in O(1).
    bool add_area(AreaID id, Name const& name, std::vector<Coord> coords);

    // Estimate of performance: O(1) average
    // Short rationale for estimate: Single unordered_map lookup by ID.
    Name get_area_name(AreaID id);

    // Estimate of performance: O(k), where k = number of boundary coordinates
    // Short rationale for estimate: unordered_map lookup is O(1) average,
    // returning the coordinate vector copies k elements.
    std::vector<Coord> get_area_coords(AreaID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Iterates once over all n entries in the areas map
    // to collect their IDs into the vector.
    std::vector<AreaID> all_areas();

    // Estimate of performance: O(1) average
    // Short rationale for estimate: Two unordered_map lookups and one vector push_back,
    // all O(1) average.
    bool add_subarea_to_area(AreaID id, AreaID parentid);

    // Estimate of performance: O(d), where d = depth of the area in the hierarchy
    // Short rationale for estimate: Traverses the parent chain from the given area to
    // the root. Each step performs one O(1) average hash map lookup.
    // d is typically much smaller than total number of areas n.
    std::vector<AreaID> subarea_in_areas(AreaID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(s), where s = total number of subareas (direct + indirect)
    // Short rationale for estimate: Each node in the subtree is visited exactly once
    // via DFS recursion, each visit performs one O(1) average hash map lookup.
    std::vector<AreaID> all_subareas_in_area(AreaID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Scanning all n places to collect candidates is O(n).
    // partial_sort with k = 3 is O(n log 3) = O(n). Each comparator call performs
    // two O(1) average hash lookups via places_.at(). Total is O(n).
    std::vector<PlaceID> places_closest_to(Coord xy, PlaceType type);

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_place(PlaceID id);

    // Estimate of performance:
    // Short rationale for estimate:
    AreaID common_area_of_subareas(AreaID id1, AreaID id2);

    // Estimate of performance:
    // Short rationale for estimate:
    void clear_ways();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<WayID> all_ways();

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_way(WayID id, std::vector<Coord> coords);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<Coord> get_way_coords(WayID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::pair<WayID, Coord>> ways_from(Coord xy);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::tuple<Coord, WayID, Distance>> route_any(Coord fromxy, Coord toxy);

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_way(WayID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::tuple<Coord, WayID, Distance>> route_least_crossroads(Coord fromxy, Coord toxy);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::tuple<Coord, WayID>> route_with_cycle(Coord fromxy);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::tuple<Coord, WayID, Distance>> route_shortest_distance(Coord fromxy, Coord toxy);

    // The operation below is a bonus operation (a little more challenging and probably requires googling for an algorithm)

    // Estimate of performance:
    // Short rationale for estimate:
    Distance trim_ways();

private:
    struct Place {
        Name name;
        PlaceType type;
        Coord coord;
    };

    std::unordered_map<PlaceID, Place> places_;

    struct Area {
        Name name;
        std::vector<Coord> coords;

        AreaID parent;
        std::vector<AreaID> children;
    };

    std::unordered_map<AreaID, Area> areas_;
};

#endif // DATASTRUCTURES_HH
