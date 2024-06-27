// ID: 315233486
// Mail: Eilonashwal30@gmail.com

#ifndef VICTORYPOINTCARD_HPP
#define VICTORYPOINTCARD_HPP

#include "DevelopmentCard.hpp"

namespace ariel 
{

    class VictoryPointCard : public DevelopmentCard // Inherit from DevelopmentCard
    {
        public:
            VictoryPointCard(); // Constructor
            ~VictoryPointCard() override; // Destructor

            std::string getTypeName() const override{ return "Victory Point";}; // Returns the card type name
            int getType() const override { return VICTORY_POINT; } // Returns the card type (1 for Victory Point)
    };
}

#endif // VICTORYPOINTCARD_HPP