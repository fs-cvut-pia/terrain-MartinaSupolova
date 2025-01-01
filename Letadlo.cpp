#include "Letadlo.h"

#include <deque>
#include <iostream>

Letadlo::Letadlo(TerrainMap& m, std::string name_in, Point start_in, Point finish_in) : Path(m, name_in,  start_in,  finish_in){};

bool Letadlo::find() {
    
    Matrix<float> distMatrix = Matrix<float>(256, 256);  //matice vzdalenosti
    distMatrix.zero();

    Matrix<Point> prevMatrix = Matrix<Point>(256, 256);  //matice projitych bodu
    
    std::deque<Point> radaBodu; //rada bodu
    radaBodu.push_front(start);  //prida start na zadacek rady bodu
    Point bod;   //aktualni bod
   
   
    while(radaBodu.size() != 0){
       bod = radaBodu.back();    //vybere bod z rady
       
       for(int dx = -1; dx < 2; dx++){  //okolni body souradnice x
            
            for(int dy = -1; dy < 2; dy++){ //okolni body souradnice y
               
               if(dst(dx, dy) != 0){ 
                   
                    if(map.validCoords(Point(bod.x + dx, bod.y +dy)) && (distMatrix(bod.x, bod.y) + dst(dx,dy) < distMatrix(bod.x + dx, bod.y +dy) || distMatrix(bod.x + dx, bod.y +dy) == 0)){
                            
                            //prida bod do vzdalenosti
                            distMatrix(bod.x + dx, bod.y +dy) = distMatrix(bod.x, bod.y) + dst(dx,dy);   

                            //aktualni bod se ulozi do predchoziho bodu
                            prevMatrix(bod.x + dx, bod.y +dy) = bod;   
                           
                           //okolni bod do fronty
                            radaBodu.push_front(Point(bod.x + dx, bod.y + dy));   
                    }
                }
            }
       }
       radaBodu.pop_back(); 
    }

    //ulozeni startu a finishe do path
    path.push_back(start);  
    path.push_back(finish);  
    Point predbod = prevMatrix(finish);
    while(predbod != start){
        path.insert(path.begin() + 1, predbod);
        predbod = prevMatrix(predbod);
    }

    return true;
}