#ifndef SILNICETRAJEKT_H
#define SILNICETRAJEKT_H

#include <iostream>
#include <string>
#include <deque>
#include <vector>       
#include "TerrainMap.h"   
#include "Path.h"         

class SilniceTrajekt : public Path {
public:
    // Konstruktor
    SilniceTrajekt(TerrainMap& m, std::string name_in, Point start_in, Point finish_in);
    
    // Hlavní metoda pro hledání cesty
    bool find();
    
private:
    // Metoda pro výpočet sklonu mezi dvěma body
    float calculateSlope(Point start, Point end);

    // Metoda pro výpočet "náklonu" mezi dvěma sousedními body
    float dst(int dx, int dy) const {
        // Předpokládám, že metoda dst vrací vzdálenost mezi body.
        return std::sqrt(dx * dx + dy * dy);
    }
};

#endif 
