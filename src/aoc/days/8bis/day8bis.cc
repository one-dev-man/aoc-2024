#include "day8bis.hh"

// 

#define MAPOBJ_AIR '.'
#define MAPOBJ_ANTINODE '#'

typedef vector<vector<char>> Map;

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    int width;
    int height;
} Dimension;

// 

static Dimension getMapdim(const Map &map) {
    return Dimension(map.size(), map[0].size());
}

// 

static bool isAntenna(char obj) {
    return (('a' <= obj) && (obj <= 'z')) || (('A' <= obj) && (obj <= 'Z')) || (('0' <= obj) && (obj <= '9'));
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
        for(int x = 0; x < mapdim.width; ++x) map[x].push_back(line.at(x));
    }

    return map;
}

static string map2string(const Map &map) {
    string result = "";

    Dimension mapdim = getMapdim(map);

    for(int y = mapdim.height-1; y > -1; --y) {
        for(int x = 0; x < mapdim.width; ++x) {
            result.push_back(map[x][y]);
        }
        result.push_back('\n');
    }

    result.pop_back();

    return result;
}

// 

static Map copyMap(const Map &m) {
    Map copy;
    
    Dimension mapdim = getMapdim(m);

    for(int x = 0; x < mapdim.width; ++x) {
        copy.push_back({});

        for(int y = 0; y < mapdim.height; ++y) {
            copy[x].push_back(m[x][y]);
        }
    }

    return copy;
}

// 

#pragma GCC diagnostic ignored "-Wunused-parameter"
Day* day8bis = new Day(
    "8bis",
    "./resources/days/8/input.txt",
    [](const string &input, ostream &logs) -> string {
        Map m = string2map(input);
        Map mapCopy = copyMap(m);
        const Dimension mapdim = getMapdim(mapCopy);

        map<char, vector<Position>> antennasFreqMap = {};
        for(int x = 0; x < mapdim.width; ++x) {
            for(int y = 0; y < mapdim.width; ++y) {
                char freq = mapCopy[x][y];
                if(isAntenna(freq)) antennasFreqMap[freq].push_back(Position(x, y));
            }
        }

        logs << map2string(mapCopy) << '\n';

        vector<Position> antinodesPositions = {};

        for(const pair<char, vector<Position>> antennasFreqEntry : antennasFreqMap) {
            const vector<Position> antennasPositions = antennasFreqEntry.second;

            for(const Position &a1pos : antennasPositions) {
                for(const Position &a2pos : antennasPositions) {
                    if(a1pos.x != a2pos.x && a1pos.y != a2pos.y) {
                        Position dvect = Position(a2pos.x - a1pos.x, a2pos.y - a1pos.y);

                        for(
                            Position antinodePos = Position(a2pos.x, a2pos.y);
                            (
                                0 <= antinodePos.x && antinodePos.x < mapdim.width
                                && 0 <= antinodePos.y && antinodePos.y < mapdim.height
                            );
                            antinodePos.x += dvect.x, antinodePos.y += dvect.y
                        ) {
                            char obj = mapCopy[antinodePos.x][antinodePos.y];

                            const size_t findResult = collections::find<Position>(
                                antinodesPositions,
                                antinodePos,
                                [](Position p1, Position p2) -> bool {
                                    return p1.x == p2.x && p1.y == p2.y;
                                }
                            );
                            if(findResult == collections::nindex) {
                                if(!isAntenna(obj)) mapCopy[antinodePos.x][antinodePos.y] = MAPOBJ_ANTINODE;
                                antinodesPositions.push_back(antinodePos);
                            }
                        }
                    }
                }
            }
        }

        logs << "//////////////////////////////////////////////////////////" << '\n';
        logs << map2string(mapCopy) << '\n';

        return to_string(antinodesPositions.size());
    }
);