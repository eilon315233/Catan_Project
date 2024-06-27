// ID: 315233486
// Mail: Eilonashwal30@gmail.com

#ifndef ROADBUILDINGCARD_HPP
#define ROADBUILDINGCARD_HPP

#include "DevelopmentCard.hpp"

namespace ariel 
{

    class RoadBuildingCard : public DevelopmentCard // RoadBuildingCard class inherits from DevelopmentCard
    {
        public:
            RoadBuildingCard(); // Constructor
            ~RoadBuildingCard() override; // Destructor

            string getTypeName() const override{ return "RoadBuilding";}; // Returns the card type name
            int getType() const override { return ROAD_BUILDING; } // Returns the card type (1 for RoadBuilding)
    };
}

#endif // ROADBUILDINGCARD_HPP