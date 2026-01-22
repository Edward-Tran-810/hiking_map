// Datastructures.cc

#include "datastructures.hh"

#include <random>

#include <cmath>

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
    // Write any cleanup you need here
}

int Datastructures::place_count()
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

void Datastructures::clear_all()
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<PlaceID> Datastructures::all_places()
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

bool Datastructures::add_place(PlaceID /*id*/, const Name& /*name*/, PlaceType /*type*/, Coord /*xy*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::pair<Name, PlaceType> Datastructures::get_place_name_type(PlaceID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

Coord Datastructures::get_place_coord(PlaceID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<PlaceID> Datastructures::places_alphabetically()
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<PlaceID> Datastructures::places_coord_order()
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<PlaceID> Datastructures::find_places_name(Name const& /*name*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<PlaceID> Datastructures::find_places_type(PlaceType /*type*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

bool Datastructures::change_place_name(PlaceID /*id*/, const Name& /*newname*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

bool Datastructures::add_area(AreaID /*id*/, const Name &/*name*/, std::vector<Coord> /*coords*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

Name Datastructures::get_area_name(AreaID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<Coord> Datastructures::get_area_coords(AreaID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<AreaID> Datastructures::all_areas()
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

bool Datastructures::add_subarea_to_area(AreaID /*id*/, AreaID /*parentid*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<AreaID> Datastructures::subarea_in_areas(AreaID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<AreaID> Datastructures::all_subareas_in_area(AreaID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<PlaceID> Datastructures::places_closest_to(Coord /*xy*/, PlaceType /*type*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

bool Datastructures::remove_place(PlaceID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

AreaID Datastructures::common_area_of_subareas(AreaID /*id1*/, AreaID /*id2*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

void Datastructures::clear_ways()
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<WayID> Datastructures::all_ways()
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

bool Datastructures::add_way(WayID /*id*/, std::vector<Coord> /*coords*/)
{   
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<Coord> Datastructures::get_way_coords(WayID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<std::pair<WayID, Coord>> Datastructures::ways_from(Coord /*xy*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<std::tuple<Coord, WayID, Distance> > Datastructures::route_any(Coord /*fromxy*/, Coord /*toxy*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

bool Datastructures::remove_way(WayID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
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
