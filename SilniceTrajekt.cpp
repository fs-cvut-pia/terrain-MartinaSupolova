#include "SilniceTrajekt.h"
#include <deque>
#include <iostream>

// Konstruktory třídy SilniceTrajekt
SilniceTrajekt::SilniceTrajekt(TerrainMap& m, std::string name_in, Point start_in, Point finish_in) 
    : Path(m, name_in, start_in, finish_in) {}

// Výpočet sklonu mezi dvěma body (x1, y1) a (x2, y2)
float SilniceTrajekt::calculateSlope(Point start, Point end) {
    float distance = sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2));
    float heightDiff = map.alt(end.x, end.y) - map.alt(start.x, start.y);
    return (heightDiff / distance) * 100.0f; // Výpočet sklonu v procentech
}

// Výběr cesty mezi body
bool SilniceTrajekt::find() {
    Matrix<float> distMatrix(256, 256);
    distMatrix.zero();
    
    Matrix<Point> prevMatrix(256, 256);
    std::deque<Point> radaBodu; 
    radaBodu.push_front(start); 
    Point bod;

    while (!radaBodu.empty()) {
        bod = radaBodu.back();    
        
        for (int dx = -1; dx < 2; ++dx) {
            for (int dy = -1; dy < 2; ++dy) {
                if (dst(dx, dy) != 0) { 
                    if (map.validCoords(Point(bod.x + dx, bod.y + dy))) {
                        float newSlope = calculateSlope(bod, Point(bod.x + dx, bod.y + dy));
                        bool isValid = false;

                        if (map.alt(bod.x + dx, bod.y + dy) < 0 || (bod.x + dx == finish.x && bod.y + dy == finish.y)) {
                            isValid = true;
                        } else if (map.alt(bod.x + dx, bod.y + dy) > 0 && newSlope < 6) {
                            isValid = true;
                        }

                        if (isValid && (distMatrix(bod.x, bod.y) + dst(dx, dy) < distMatrix(bod.x + dx, bod.y + dy) || distMatrix(bod.x + dx, bod.y + dy) == 0)) {
                            distMatrix(bod.x + dx, bod.y + dy) = distMatrix(bod.x, bod.y) + dst(dx, dy);
                            prevMatrix(bod.x + dx, bod.y + dy) = bod;
                            radaBodu.push_front(Point(bod.x + dx, bod.y + dy));
                        }
                    }
                }
            }
        }
        radaBodu.pop_back();
    }

    path.push_back(start);  
    path.push_back(finish);  
    Point predBod = prevMatrix(finish);
    while (predBod != start) {
        path.insert(path.begin() + 1, predBod);
        predBod = prevMatrix(predBod);
    }

    return true;
}
