// ID: 315233486
// Mail: Eilonashwal30@gmail.com

#ifndef YEAROFPLENTYCARD_HPP
#define YEAROFPLENTYCARD_HPP

#include "DevelopmentCard.hpp"

namespace ariel 
{

    class YearOfPlentyCard : public DevelopmentCard // Inherit from DevelopmentCard
    {
        public:
            YearOfPlentyCard();// Constructor
            ~YearOfPlentyCard() override; // Destructor

            std::string getTypeName() const override{ return "Year of Plenty";}; // Returns the card type name
            int getType() const override { return YEAR_OF_PLENTY; } // Returns the card type (2 for Year of Plenty)
    }; 
}

#endif // YEAROFPLENTYCARD_HPP