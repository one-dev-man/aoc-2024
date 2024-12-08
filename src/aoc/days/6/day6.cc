#include "day6.hh"

// 

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef enum {
    AIR,
    VISITED,
    OBSTACLE,
    GUARD_UP,
    GUARD_DOWN,
    GUARD_LEFT,
    GUARD_RIGHT
} MapObject;

typedef vector<vector<MapObject>> Map;

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    int width;
    int height;
} Dimension;

typedef struct {
    Position position;
    Direction direction;
} Guard;

// 

static MapObject char2mapObject(char c) {
    switch(c) {
        case '.': return AIR;
        case '+': return VISITED;
        case '#': return OBSTACLE;
        case '^': return GUARD_UP;
        case 'v': return GUARD_DOWN;
        case '<': return GUARD_LEFT;
        case '>': return GUARD_RIGHT;
        default: return AIR;
    }
}

// 

static char mapObject2char(MapObject o) {
    switch(o) {
        case AIR: return '.';
        case VISITED: return '+';
        case OBSTACLE: return '#';
        case GUARD_UP: return '^';
        case GUARD_DOWN: return 'v';
        case GUARD_LEFT: return '<';
        case GUARD_RIGHT: return '>';
        default: return '.';
    }
}

// 

static bool isGuardObject(MapObject o) {
    return o == GUARD_UP || o == GUARD_DOWN || o == GUARD_LEFT || o == GUARD_RIGHT;
}

// 

static MapObject guard2mapObject(const Guard* guard) {
    switch(guard->direction) {
        case UP: return GUARD_UP;
        case DOWN: return GUARD_DOWN;
        case LEFT: return GUARD_LEFT;
        case RIGHT: return GUARD_RIGHT;
        default: return GUARD_UP;
    }
}

// 

static Direction rightRotate(const Direction &direction) {
    switch (direction) {
        case UP: return RIGHT;
        case RIGHT: return DOWN;
        case DOWN: return LEFT;
        case LEFT: return UP;
        default: return UP;
    }
}

static Position get2DDirection(const Direction &direction) {
    switch (direction) {
        case UP: return Position(0, 1);
        case DOWN: return Position(0, -1);
        case LEFT: return Position(-1, 0);
        case RIGHT: return Position(1, 0);
        default: return get2DDirection(UP);
    }
}

static Dimension getMapDimension(const Map &map) {
    return Dimension(map.size(), map[0].size());
}

//

static Guard* finGuard(const Map &map) {
    Guard* guard = new Guard();

    MapObject guardObj;

    Dimension mapdim = getMapDimension(map);

    bool found = false;

    for(guard->position.x = 0; guard->position.x < mapdim.width && !found; ++guard->position.x) {
        for(guard->position.y = 0; guard->position.y < mapdim.height && !found; ++guard->position.y) {
            guardObj = map[guard->position.x][guard->position.y];
            found = isGuardObject(guardObj);
        }
    }

    guard->position.x--;
    guard->position.y--;

    if(found) {
        switch(guardObj) {
            case GUARD_UP: guard->direction = UP; break;
            case GUARD_DOWN: guard->direction = DOWN; break;
            case GUARD_LEFT: guard->direction = LEFT; break;
            case GUARD_RIGHT: guard->direction = RIGHT; break;
            default: break;
        }

        return guard;
    }
    return nullptr;
}

//

static Position findNextGuardPosition(const Map &map, const Position &position, const Direction &directipon, bool* isOutPtr) {
    bool obstacleFound = false;
    Position result;

    Position d2d = get2DDirection(directipon);
    Dimension mapdim = getMapDimension(map);

    for(
        result.x = position.x, result.y = position.y;
        (
            0 <= result.x && result.x < mapdim.width
            && 0 <= result.y && result.y < mapdim.height
            && !obstacleFound
        );
        result.x += d2d.x, result.y += d2d.y
    ) {
        obstacleFound = map[result.x][result.y] == MapObject::OBSTACLE;
    }

    result.x += -(1+obstacleFound)*d2d.x;
    result.y += -(1+obstacleFound)*d2d.y;

    *isOutPtr = !obstacleFound;

    return result;
}

//

static void tickGuard(Map &map, Guard* guard, bool* isOutPtr) {
    map[guard->position.x][guard->position.y] = AIR;

    Position previousGuardPosition = guard->position;
    guard->position = findNextGuardPosition(map, guard->position, guard->direction, isOutPtr);

    Position posMin = Position(min(previousGuardPosition.x, guard->position.x), min(previousGuardPosition.y, guard->position.y));
    Position posMax = Position(max(previousGuardPosition.x, guard->position.x), max(previousGuardPosition.y, guard->position.y));

    for(int x = posMin.x; x <= posMax.x; ++x) {
        for(int y = posMin.y; y <= posMax.y; ++y) {
            map[x][y] = MapObject::VISITED;
        }
    }

    if(!*isOutPtr) guard->direction = rightRotate(guard->direction);
    map[guard->position.x][guard->position.y] = guard2mapObject(guard);
}

// 

static Map string2map(const string &mapInput) {
    Map map;

    const vector<string> &lines = strings::split(mapInput, "\n");

    Dimension mapdim(lines[0].length(), lines.size());

    for(int i = 0; i < mapdim.width; ++i) map.push_back({});

    int y = 0;
    for(
        auto it = lines.rbegin(), itend = lines.rend();
        it != itend;
        ++it, ++y
    ) {
        const string &line = *it;
        for(int x = 0; x < mapdim.width; ++x) map[x].push_back(char2mapObject(line.at(x)));
    }

    return map;
}

static string map2string(const Map &map) {
    string result = "";

    Dimension mapdim = getMapDimension(map);

    for(int y = mapdim.height-1; y > -1; --y) {
        for(int x = 0; x < mapdim.width; ++x) {
            result.push_back(mapObject2char(map[x][y]));
        }
        result.push_back('\n');
    }

    result.pop_back();

    return result;
}

// 

#pragma GCC diagnostic ignored "-Wunused-parameter"
Day* day6 = new Day(
    "6",
    "./resources/days/6/input.txt",
    [](const string &input, ostream &logs) -> string {
        Map map = string2map(input);

        Guard* guard = finGuard(map);

        bool isOut = false;
        while(!isOut) {
            tickGuard(map, guard, &isOut);
        }
        
        size_t visitedCaseCount = 1;
        for(const vector<MapObject> &line : map) {
            visitedCaseCount += collections::count<MapObject>(line, MapObject::VISITED);
        }

        cout << map2string(map) << '\n';

        delete guard;
        return to_string(visitedCaseCount);
    }
);