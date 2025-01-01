#include "Silnice.h"

#include <deque>
#include <iostream>


Silnice::Silnice(TerrainMap& m, std::string name_in, Point start_in, Point finish_in) : Path(m, name_in,  start_in,  finish_in){};

bool Silnice::find() {
   
    Matrix<float> distMatrix = Matrix<float>(256, 256);  
    distMatrix.zero();
    Matrix<Point> prevMatrix = Matrix<Point>(256, 256);  
    std::deque<Point> radaBodu; 
    radaBodu.push_front(start);  
    Point bod;  
   
    while(radaBodu.size() != 0){
       bod = radaBodu.back();    
       
       for(int dx = -1; dx < 2; dx++){  
           
            for(int dy = -1; dy < 2; dy++){
                
                if(dst(dx, dy) != 0){ 
                    
                    if(map.validCoords(Point(bod.x + dx, bod.y +dy)) && (distMatrix(bod.x, bod.y) + dst(dx,dy) < distMatrix(bod.x + dx, bod.y +dy) || distMatrix(bod.x + dx, bod.y +dy) == 0)){
                        
                        if((map.alt(bod.x + dx, bod.y +dy) > 0 &&  abs(map.alt(bod.x + dx, bod.y +dy) - map.alt(bod)) < 60)|| (bod.x + dx == finish.x && bod.y + dy == finish.y)){
                            distMatrix(bod.x + dx, bod.y +dy) = distMatrix(bod.x, bod.y) + dst(dx,dy);  
                            prevMatrix(bod.x + dx, bod.y +dy) = bod;   
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
    while(predBod != start){
        path.insert(path.begin() + 1, predBod);
        predBod = prevMatrix(predBod);
    }

    return true;
}