# hiking26 (Tiraka Project - Hiking Map)
 
A hiking map program built with C++ and Qt for a course assignment. Stores places, areas, and paths, and can find routes between them.
 
## What this project does
 
- Store hiking **places** (firepits, shelters, parking, peaks, bays, areas,
  other) with a unique ID, name, type, and coordinates.
- Store **areas** (regions defined by a polygon), which can be nested inside
  other areas (subareas), and query the area hierarchy.
- Store **ways** (paths/tracks) connecting crossroads, and search **routes**
  between them:
  - any valid route
  - route with the fewest crossroads
  - route containing a cycle
  - shortest-distance route
## Project structure
 
```
tiraka_project.pro
datastructures.hh      # implemented by me
datastructures.cc      # implemented by me
course_code/
  mainprogram.hh/.cc    # provided by the course, not modified
  mainwindow.hh/.cc/.ui # provided by the course, not modified
```
 
(Qt Creator's project view groups these into Headers / Sources / Forms,
but on disk `course_code/` is a single folder next to `datastructures.*`.)
 
Only `datastructures.hh` and `datastructures.cc` were written/modified by
me. Everything under `course_code/` (main program, main window, etc.) is
provided by the course and was not changed, per assignment rules.
 
## What I implemented
 
The public interface of the `Datastructures` class (given by the course)
is fully implemented, covering all grading levels:
 
- **A** - core place/area operations (add, search, sort, etc.)
- **B** - ways, `route_any`, `remove_place`/`remove_way`, area relations
- **C** - `route_least_crossroads`, `route_with_cycle`,
  `route_shortest_distance`
For each operation, `datastructures.hh` contains a comment with the
estimated asymptotic performance and a short rationale, as required by
the assignment.
 
## Data structures used
 
See the comments above each method in `datastructures.hh` for the specific
data structure and performance reasoning behind each operation.
 
## How to build and run
 
**With Qt Creator (GUI):**
Open `tiraka_project.pro` in Qt Creator and click Run. The GUI adds a
command console plus a graphical view of places, areas and ways.
 
**Command-line only (no Qt required):**
```bash
g++ -std=c++20 -o hiking26 datastructures.cc course_code/mainprogram.cc
./hiking26
```
(This builds the text-only version, skipping `course_code/mainwindow.cc`
and the Qt-based GUI files, which require Qt widgets.)
 
Once running (either mode), commands can be typed directly, or loaded from files with:
```
read "[commandfile].txt"
```
 
Type `help` to see all available commands.
 
## Notes
 
- Only `datastructures.hh` / `datastructures.cc` were modified - the public
  interface of `Datastructures` was not changed, per assignment rules.
- Debug output (if any) goes to `cerr`/`qDebug`, not `cout`, so it doesn't
  interfere with `testread`/performance tests.
