#include "day6bis.hh"

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
    VIRTUAL_OBSTACLE,
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

typedef struct {
    Position insersetion;
    Position intersected;
    Position origin;
    Direction direction;
} TravelIntersection;

// 

static MapObject char2mapObject(char c) {
    switch(c) {
        case '.': return AIR;
        case '+': return VISITED;
        case '#': return OBSTACLE;
        case 'O': return VIRTUAL_OBSTACLE;
        case '^': return GUARD_UP;
        case 'v': return GUARD_DOWN;
        case '<': return GUARD_LEFT;
        case '>': return GUARD_RIGHT;
        default: return AIR;
    }
}

// 

#pragma GCC diagnostic ignored "-Wunused-function"
static char mapObject2char(MapObject o) {
    switch(o) {
        case AIR: return '.';
        case VISITED: return '+';
        case OBSTACLE: return '#';
        case VIRTUAL_OBSTACLE: return 'O';
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

// 

static Position get2DDirection(const Direction &direction) {
    switch (direction) {
        case UP: return Position(0, 1);
        case DOWN: return Position(0, -1);
        case LEFT: return Position(-1, 0);
        case RIGHT: return Position(1, 0);
        default: return get2DDirection(UP);
    }
}

// 

static pair<Direction, Direction> getOrthogonalDirections(Direction direction) {
    Direction dright = rightRotate(direction);
    Direction dleft = rightRotate(rightRotate(dright));
    return pair(dleft, dright);
}

// 

static Dimension getMapDimension(const Map &m) {
    return Dimension(m.size(), m[0].size());
}

//

static Guard* finGuard(const Map &m) {
    Guard* guard = new Guard();

    MapObject guardObj;

    Dimension mapdim = getMapDimension(m);

    bool found = false;

    for(guard->position.x = 0; guard->position.x < mapdim.width && !found; ++guard->position.x) {
        for(guard->position.y = 0; guard->position.y < mapdim.height && !found; ++guard->position.y) {
            guardObj = m[guard->position.x][guard->position.y];
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

static Position findNextGuardPosition(const Map &m, const Position &position, const Direction &directipon, bool* isOutPtr) {
    bool obstacleFound = false;
    Position result;

    Position d2d = get2DDirection(directipon);
    Dimension mapdim = getMapDimension(m);

    for(
        result.x = position.x, result.y = position.y;
        (
            0 <= result.x && result.x < mapdim.width
            && 0 <= result.y && result.y < mapdim.height
            && !obstacleFound
        );
        result.x += d2d.x, result.y += d2d.y
    ) {
        MapObject obj = m[result.x][result.y];
        obstacleFound = obj == MapObject::OBSTACLE || obj == MapObject::VIRTUAL_OBSTACLE;
    }

    result.x += -(1+obstacleFound)*d2d.x;
    result.y += -(1+obstacleFound)*d2d.y;

    *isOutPtr = !obstacleFound;

    return result;
}

//

static void tickGuard(
    Map &m, Guard* guard,
    bool* isOutPtr,
    map<string, Position>* visitMapPtr = nullptr,
    bool* isLooping = nullptr
) {
    m[guard->position.x][guard->position.y] = AIR;

    Position previousGuardPosition = guard->position;
    guard->position = findNextGuardPosition(m, guard->position, guard->direction, isOutPtr);

    Position posMin = Position(min(previousGuardPosition.x, guard->position.x), min(previousGuardPosition.y, guard->position.y));
    Position posMax = Position(max(previousGuardPosition.x, guard->position.x), max(previousGuardPosition.y, guard->position.y));

    if(visitMapPtr != nullptr) {
        string guardPosKey = "";
        
        guardPosKey.append(to_string(guard->position.x));
        guardPosKey.push_back(';');
        guardPosKey.append(to_string(guard->position.y));

        if((*visitMapPtr).contains(guardPosKey)) {
            Position storedPos = (*visitMapPtr)[guardPosKey];
            if(storedPos.x == previousGuardPosition.x && storedPos.y == previousGuardPosition.y) {
                if(isLooping != nullptr) *isLooping = true;
            }
        }
        else (*visitMapPtr)[guardPosKey] = previousGuardPosition;
    }

    for(int x = posMin.x; x <= posMax.x; ++x) {
        for(int y = posMin.y; y <= posMax.y; ++y) {
            m[x][y] = MapObject::VISITED;
        }
    }

    if(!*isOutPtr) guard->direction = rightRotate(guard->direction);
    m[guard->position.x][guard->position.y] = guard2mapObject(guard);
}

// 

static Map string2map(const string &mapInput) {
    Map m;

    const vector<string> &lines = strings::split(mapInput, "\n");

    Dimension mapdim(lines[0].length(), lines.size());

    for(int i = 0; i < mapdim.width; ++i) m.push_back({});

    int y = 0;
    for(
        auto it = lines.rbegin(), itend = lines.rend();
        it != itend;
        ++it, ++y
    ) {
        const string &line = *it;
        for(int x = 0; x < mapdim.width; ++x) m[x].push_back(char2mapObject(line.at(x)));
    }

    return m;
}

#pragma GCC diagnostic ignored "-Wunused-function"
static string map2string(const Map &m) {
    string result = "";

    Dimension mapdim = getMapDimension(m);

    for(int y = mapdim.height-1; y > -1; --y) {
        for(int x = 0; x < mapdim.width; ++x) {
            result.push_back(mapObject2char(m[x][y]));
        }
        result.push_back('\n');
    }

    result.pop_back();

    return result;
}

// 

static Map copyMap(const Map &m) {
    Map copy;
    
    Dimension mapdim = getMapDimension(m);

    for(int x = 0; x < mapdim.width; ++x) {
        copy.push_back({});

        for(int y = 0; y < mapdim.height; ++y) {
            copy[x].push_back(m[x][y]);
        }
    }

    return copy;
}

// 

static bool testLoopingObstaclePosition(const Map &m, const Position &position, Map* resultMapPtr = nullptr) {
    Map testmap = copyMap(m);
    Dimension testmapdim = getMapDimension(testmap);

    Guard* guard = finGuard(testmap);

    if(
        0 > position.x || position.x > testmapdim.width
        || 0 > position.y || position.y > testmapdim.height
        || (guard->position.x == position.x && guard->position.y == position.y)
    ) {
        *resultMapPtr = testmap;
        return false;
    }

    testmap[position.x][position.y] = VIRTUAL_OBSTACLE;
    
    bool isOut = false;
    bool isLooping = false;

    map<string, Position> visitMap = {};

    while(!isOut && !isLooping) tickGuard(testmap, guard, &isOut, &visitMap, &isLooping);

    if(resultMapPtr != nullptr) *resultMapPtr = testmap;

    return isLooping;
}

// 

#pragma GCC diagnostic ignored "-Wunused-parameter"
Day* day6bis = new Day(
    "6bis",
    "./resources/days/6/input.txt",
    [](const string &input, ostream &logs) -> string {
        Map m = string2map(input);
        Map mapCopy = copyMap(m);
        
        Dimension mapdim = getMapDimension(mapCopy);

        Guard* guard = finGuard(mapCopy);

        bool isOut = false;

        while(!isOut) tickGuard(mapCopy, guard, &isOut);
        cout << map2string(mapCopy) << '\n';

        vector<Position> visitedPositions = {};
        visitedPositions.push_back(guard->position);
        for(int x = 0; x < mapdim.width; ++x) {
            for(int y = 0; y < mapdim.height; ++y) {
                if(mapCopy[x][y] == MapObject::VISITED) visitedPositions.push_back(Position(x, y));
            }
        }

        vector<Position> loopingObstaclePositions = {};

        Map testmap;
        for(const Position &visitedPos : visitedPositions) {
            if(testLoopingObstaclePosition(m, visitedPos, &testmap)) loopingObstaclePositions.push_back(visitedPos);
        }

        return to_string(loopingObstaclePositions.size());
    }
);