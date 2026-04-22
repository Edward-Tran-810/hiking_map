// Datastructures.cc

#include "datastructures.hh"
#include <random>
#include <cmath>
#include <algorithm>
#include <queue>
#include <unordered_set>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Write any initialization you need here
}

Datastructures::~Datastructures()
{
    clear_all(); // Remove all when object is destroyed
}

// Returns the total number of places stored
int Datastructures::place_count()
{
    return places_.size();
}

void Datastructures::clear_all()
{
    places_.clear();
    areas_.clear();
    clear_ways();
}

// Returns a vector containing IDs of all stored places
std::vector<PlaceID> Datastructures::all_places()
{
    std::vector<PlaceID> ids;

    // Pre-allocate memory for all place IDs to avoid repeated reallocations during push_back
    ids.reserve(places_.size());

    // Iterate through all places and collect their IDs
    for (const auto& [id, place] : places_)
    {
        ids.push_back(id);
    }

    return ids;
}

// Adds a new place to the data structure
// Returns false if the place ID already exists, true otherwise
bool Datastructures::add_place(PlaceID id, const Name& name, PlaceType type, Coord xy)
{
    // Check if place with same ID already exists
    if (places_.find(id) != places_.end())
    {
        return false;
    }

    // Insert new place
    places_[id] = Place(name, type, xy);
    return true;
}

// Returns the name and type of a place by ID
// If not found, returns NO_NAME and NO_TYPE
std::pair<Name, PlaceType> Datastructures::get_place_name_type(PlaceID id)
{
    auto it = places_.find(id);

    // If place exists, return its name and type
    if (it != places_.end())
    {
        return {it->second.name, it->second.type};
    }

    // If place not found, return default values
    return {NO_NAME, PlaceType::NO_TYPE};
}

// Returns the coordinates of a place by ID
// If not found, returns NO_COORD
Coord Datastructures::get_place_coord(PlaceID id)
{
    auto it = places_.find(id);

    // If place exists, return its coordinates
    if (it != places_.end())
    {
        return it->second.coord;
    }

    // If place not found, return default coordinate
    return NO_COORD;
}

// Returns all place IDs sorted alphabetically by their name
std::vector<PlaceID> Datastructures::places_alphabetically()
{
    // Get all place IDs
    std::vector<PlaceID> ids = all_places();

    // Sort IDs based on the name of the corresponding place
    sort(ids.begin(), ids.end(), [this](PlaceID a, PlaceID b) {
        const auto& pa = places_.at(a);
        const auto& pb = places_.at(b);
        return pa.name < pb.name;
    });

    return ids;
}

// Returns all place IDs sorted by their distance from origin (0,0)
// If distances are equal, sort by y-coordinate
std::vector<PlaceID> Datastructures::places_coord_order()
{
    // Get all place IDs
    std::vector<PlaceID> ids = all_places();

    // Sort IDs based on coordinate distance
    sort(ids.begin(), ids.end(), [this](PlaceID a, PlaceID b){
        Coord ca = places_.at(a).coord;
        Coord cb = places_.at(b).coord;

        // Calculate squared distance
        // Convert to datatype long long for preventing int overflow
        long long dist_a = (long long)ca.x * ca.x + (long long)ca.y * ca.y;
        long long dist_b = (long long)cb.x * cb.x + (long long)cb.y * cb.y;

        // Primary sort: distance from origin
        if (dist_a != dist_b)
        {
            return dist_a < dist_b;
        }

        // Secondary sort: y-coordinate
        return ca.y < cb.y;
    });

    return ids;
}

// Finds and returns all place IDs with a given name
std::vector<PlaceID> Datastructures::find_places_name(Name const& name)
{
    std::vector<PlaceID> names;

    // Iterate through all places and match by name
    for (const auto& [id, place] : places_)
    {
        if (place.name == name)
        {
            names.push_back(id);
        }
    }

    return names;
}

// Finds and returns all place IDs with a given type
std::vector<PlaceID> Datastructures::find_places_type(PlaceType type)
{
    std::vector<PlaceID> types;

    // Iterate through all places and match by type
    for (const auto& [id, place] : places_)
    {
        if (place.type == type)
        {
            types.push_back(id);
        }
    }

    return types;
}

// Changes the name of a place with the given ID
// Returns true if the place exists and was updated, false otherwise
bool Datastructures::change_place_name(PlaceID id, const Name& newname)
{
    auto it = places_.find(id);

    // If place exists, update its name
    if (it != places_.end())
    {
        it->second.name = newname;
        return true;
    }

    // If place not found
    return false;
}

// Adds a new area to the data structure
// Returns false if the area ID already exists, true otherwise
bool Datastructures::add_area(AreaID id, const Name& name, std::vector<Coord> coords)
{
    // Check if area with same ID already exists
    if (areas_.find(id) != areas_.end())
    {
        return false;
    }

    // Insert new area
    // std::move transfers ownership of the heap-allocated vector data into the
    // struct instead of copying it - O(1) instead of O(k)
    areas_[id] = Area(name, std::move(coords), NO_AREA, {});
    return true;
}

// Returns the name of an area by ID
// If not found, returns NO_NAME
Name Datastructures::get_area_name(AreaID id)
{
    auto it = areas_.find(id);

    // If area exists, return its name
    if (it != areas_.end())
    {
        return it->second.name;
    }

    return NO_NAME;
}

// Returns the coordinates of an area by ID
// If not found, returns a vector with single item NO_COORD
std::vector<Coord> Datastructures::get_area_coords(AreaID id)
{
    auto it = areas_.find(id);

    // If area exists, return its coordinates
    if (it != areas_.end())
    {
        return it->second.coords;
    }

    return {NO_COORD};
}

// Returns a vector containing IDs of all stored areas
std::vector<AreaID> Datastructures::all_areas()
{
    std::vector<AreaID> ids;

    // Pre-allocate memory for all area IDs to avoid repeated reallocations during push_back
    ids.reserve(areas_.size());

    // Iterate through all places and collect their IDs
    for (auto& [id, area] : areas_)
    {
        ids.push_back(id);
    }

    return ids;
}

// Links an area as a subarea to another area
// Returns false if IDs don't exist or if subarea already has a parent
bool Datastructures::add_subarea_to_area(AreaID id, AreaID parentid)
{
    auto it = areas_.find(id);
    auto parent_it = areas_.find(parentid);

    // If either ID is missing or subarea already belongs elsewhere, return false
    if (it == areas_.end() || parent_it == areas_.end() ||
        it->second.parent != NO_AREA)
    {
        return false;
    }

    // Set parent and add to parent's children list
    it->second.parent = parentid;
    parent_it->second.children.push_back(id);

    return true;
}

// Returns a vector of parent areas in ascending order of hierarchy
// If ID is not found, returns a vector containing NO_AREA
std::vector<AreaID> Datastructures::subarea_in_areas(AreaID id)
{
    auto it = areas_.find(id);

    // If area doesn't exist, return {NO_AREA} vector
    if (it == areas_.end())
    {
        return {NO_AREA};
    }

    std::vector<AreaID> upper_areas;

    // Traverse up the parent chain until the root is reached
    while (it->second.parent != NO_AREA)
    {
        AreaID parent_id = it->second.parent;
        upper_areas.push_back(parent_id);
        it = areas_.find(parent_id); // Move the iterator to the parent
    }

    return upper_areas;
}

// Returns a vector of all direct and indirect areas of a given area
// If ID is not found, returns a vector containing NO_AREA
std::vector<AreaID> Datastructures::all_subareas_in_area(AreaID id)
{
    auto it = areas_.find(id);

    // If area doesn't exist, return {NO_AREA} vector
    if (it == areas_.end())
    {
        return {NO_AREA};
    }

    std::vector<AreaID> subareas;

    for (AreaID child : it->second.children)
    {
        // Add direct child
        subareas.push_back(child);

        // Recursively get all subareas of the child
        std::vector<AreaID> sub = all_subareas_in_area(child);

        // Append them to the result vector
        subareas.insert(subareas.end(), sub.begin(), sub.end());
    }

    return subareas;
}

// Returns a vector of three places (or less) of given type closest to the given coordinate
// in order of increasing distance
std::vector<PlaceID> Datastructures::places_closest_to(Coord xy, PlaceType type)
{
    std::vector<PlaceID> candidates;
    candidates.reserve(places_.size());

    // Collect all matching places
    for (const auto& [id, place] : places_)
    {
        if (type == PlaceType::NO_TYPE || type == place.type)
        {
            candidates.push_back(id);
        }
    }

    // partial_sort: only sort the first 3 elements or less
    size_t k = std::min(candidates.size(), size_t(3));
    std::partial_sort(candidates.begin(), candidates.begin() + k, candidates.end(),
                      [this, xy](PlaceID a, PlaceID b) {
        const Coord& ca = places_.at(a).coord;
        const Coord& cb = places_.at(b).coord;

        // Calculate squared distance
        // Convert to datatype long long for preventing int overflow
        long long da = (long long)(ca.x - xy.x) * (ca.x - xy.x)
                       + (long long)(ca.y - xy.y) * (ca.y - xy.y);
        long long db = (long long)(cb.x - xy.x) * (cb.x - xy.x)
                       + (long long)(cb.y - xy.y) * (cb.y - xy.y);

        if (da != db)
        {
            return da < db;
        }

        return ca.y < cb.y;     // tie-break by y
    });

    // Update the size of candidates vector
    candidates.resize(k);
    return candidates;
}

// Remove the place with the given id and return true if that place exists.
// Otherwise return false.
bool Datastructures::remove_place(PlaceID id)
{
    auto it = places_.find(id);

    // If place doesn't exist, return false
    if (it == places_.end())
    {
        return false;
    }

    // Remove the place by its id
    places_.erase(it->first);
    return true;
}

// Returns the nearest common area in the subarea hierarchy for the areas.
// If given ids does not exist, or if no common area exists, returns NO_AREA.
AreaID Datastructures::common_area_of_subareas(AreaID id1, AreaID id2)
{
    // If either ID doesn't exist, return NO_AREA
    if (areas_.find(id1) == areas_.end() || areas_.find(id2) == areas_.end())
    {
        return NO_AREA;
    }

    // Collect all ancestors of id1 into a set for O(1) average lookup
    std::unordered_set<AreaID> id1_ancestors;
    auto it = areas_.find(id1);

    while (it->second.parent != NO_AREA)
    {
        id1_ancestors.insert(it->second.parent);
        it = areas_.find(it->second.parent);
    }

    // Traverse ancestors of id2, return first one found in id1_ancestors
    it = areas_.find(id2);
    while(it->second.parent != NO_AREA)
    {
        auto parent = it->second.parent;
        // Check if this area exists in id1_ancestors
        if (id1_ancestors.count(parent))
        {
            return parent;
        }

        it = areas_.find(parent);
    }

    return NO_AREA;
}

void Datastructures::clear_ways()
{
    ways_.clear();
    crossroads_.clear();
}

// Returns a vector containing IDs of all stored ways
std::vector<WayID> Datastructures::all_ways()
{
    std::vector<WayID> ids;

    // Pre-allocate memory for all way IDs to avoid repeated reallocations during push_back
    ids.reserve(ways_.size());

     // Iterate through all ways and collect their IDs
    for (const auto& [id, way] : ways_)
    {
        ids.push_back(id);
    }

    return ids;
}

// Adds a new way with given id and coordinates
// Returns true if the way is added successfully, otherwise false
bool Datastructures::add_way(WayID id, std::vector<Coord> coords)
{
    // Check if way already exists
    if (ways_.find(id) != ways_.end())
    {
        return false;
    }

    Distance length = 0;
    for (size_t i = 0; i + 1 < coords.size(); i++)
    {
        long long dx = coords.at(i + 1).x - coords.at(i).x;
        long long dy = coords.at(i + 1).y - coords.at(i).y;
        length += static_cast<Distance>(std::sqrt(dx*dx + dy*dy));
    }

    // Store way data (coordinates)
    ways_[id] = {coords, length};

    // Get endpoints of the way
    Coord front = coords.front(); // starting point
    Coord back  = coords.back();  // ending point

    // Register connections in both directions (undirected graph)
    // From front, can go to back via this way
    crossroads_[front].push_back({id, back});

    // If the way creates a loop, add 1 endpoint only
    if (front != back)
    {
        // From back, can go to front via this way
        crossroads_[back].push_back({id, front});
    }

    return true;
}

// Returns the coordinate vector of the way with given ID.
// If such way doesn’t exist, returns a vector with single item NO_COORD
std::vector<Coord> Datastructures::get_way_coords(WayID id)
{
    auto it = ways_.find(id);

    // Check if this way exists
    if (it == ways_.end())
    {
        return {NO_COORD};
    }

    return it->second.coords;
}

// Returns a list of ways starting from the given coordinate.
// If there is no crossroad in that coordinate, an empty vector is returned.
std::vector<std::pair<WayID, Coord>> Datastructures::ways_from(Coord xy)
{
    auto it = crossroads_.find(xy);

    // Check if there are any crossroads in this coordinate
    if (it == crossroads_.end())
    {
        return {};
    }

    return it->second; // Return vector of ways from this coordinate
}

// Returns any route between the given crossroads using BFS.
// If either coordinate is invalid, returns {NO_COORD, NO_WAY, NO_DISTANCE}.
// If no route exists, returns an empty vector.
std::vector<std::tuple<Coord, WayID, Distance> > Datastructures::route_any(Coord fromxy, Coord toxy)
{
    // Check if both coordinates are valid crossroads
    if (crossroads_.find(fromxy) == crossroads_.end() ||
        crossroads_.find(toxy) == crossroads_.end())
    {
        return {{NO_COORD, NO_WAY, NO_DISTANCE}};
    }

    // Special case: start equals destination
    if (fromxy == toxy)
    {
        return {{fromxy, NO_WAY, 0}};
    }

    // BFS setup:
    // prev maps each coordinate to {way used to reach it, previous coordinate}
    std::unordered_map<Coord, std::pair<WayID, Coord>, CoordHash> prev;
    std::queue<Coord> q;

    // Initialize BFS from starting point
    q.push(fromxy);
    prev[fromxy] = {NO_WAY, NO_COORD};

    bool found = false;

    // Standard BFS loop
    while (!q.empty() && !found)
    {
        Coord curr = q.front();
        q.pop();
        for (const auto& [id, neighbour] : crossroads_.at(curr))
        {
            // Visit only unvisited nodes
            if (prev.find(neighbour) == prev.end())
            {
                // Store how we reached this neighbour
                prev[neighbour] = {id, curr};

                // Stop BFS early if destination is found
                if (neighbour == toxy)
                {
                    found = true;
                    break;
                }

                // Add neighbour to queue for further exploration
                q.push(neighbour);
            }
        }
    }

    // No route found
    if (!found)
    {
        return {};
    }

    // Reconstruct path from destination back to start
    std::vector<std::tuple<Coord, WayID, Distance>> route;

    // Trace back using prev map
    Coord curr = toxy;
    while (curr != fromxy)
    {
        auto [id, prev_coord] = prev.at(curr);
        route.push_back({curr, NO_WAY, 0});     // distance filled in later
        curr = prev_coord;
    }

    route.push_back({fromxy, NO_WAY, 0});

    // Reverse to get route with fromxy -> toxy order
    std::reverse(route.begin(), route.end());

    // Fill in way ID and distances
    Distance cumulative_dist = 0;

    for (size_t i = 0; i + 1 < route.size(); i++)
    {
        Coord end = std::get<0>(route[i + 1]);

        // Way used when leaving ca toward cb
        WayID used_way = prev.at(end).first;
        std::get<1>(route[i]) = used_way;

        cumulative_dist += ways_.at(used_way).way_length;

        // Store cumulative distance at next node
        std::get<2>(route[i + 1]) = cumulative_dist;
    }

    // Start point has distance 0
    std::get<2>(route[0]) = 0;

    return route;
}

bool Datastructures::remove_way(WayID id)
{
    auto it = ways_.find(id);

    // Check if way exists
    if (it == ways_.end())
    {
        return false;
    }

    // Get two endpoints of this way
    Coord front = it->second.coords.front();
    Coord back = it->second.coords.back();

    // Remove way from ways_
    ways_.erase(it);

    // Helper lambda: remove this way from a given endpoint in crossroads_
    auto remove_from_crossroad = [&](Coord endpoint)
    {
        auto cit = crossroads_.find(endpoint);

        if (cit == crossroads_.end())
        {
            return;
        }

        auto& vec = cit->second;

        // Remove the entry where way ID == id
        vec.erase(
            std::remove_if(vec.begin(), vec.end(),
            [&](const std::pair<WayID, Coord>& entry) {
                return entry.first == id;
            }),
            vec.end()
        );

        // If no more ways lead to this endpoint, remove it from crossroads_
        if (vec.empty())
        {
            crossroads_.erase(cit);
        }
    };

    remove_from_crossroad(front);
    remove_from_crossroad(back);

    return true;
}

std::vector<std::tuple<Coord, WayID, Distance> > Datastructures::route_least_crossroads(Coord /*fromxy*/, Coord /*toxy*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<std::tuple<Coord, WayID> > Datastructures::route_with_cycle(Coord /*fromxy*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<std::tuple<Coord, WayID, Distance> > Datastructures::route_shortest_distance(Coord /*fromxy*/, Coord /*toxy*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

Distance Datastructures::trim_ways()
{
    // Replace the line below with your implementation
    throw NotImplemented();
}
