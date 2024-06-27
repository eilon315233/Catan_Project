// ID: 315233486
// Mail: Eilonashwal30@gmail.com

#ifndef MONOPOLYCARD_HPP
#define MONOPOLYCARD_HPP

#include "DevelopmentCard.hpp"

namespace ariel 
{

    class MonopolyCard : public DevelopmentCard  // MonopolyCard class inherits from DevelopmentCard
    {
        public:
            MonopolyCard(); // Constructor
            ~MonopolyCard() override; // Destructor

            string getTypeName() const override{ return "Monopoly";}; // Returns the card type name
            int getType() const override { return MONOPOLY; } // Returns the card type (3 for Monopoly)
    };

}

#endif // MONOPOLYCARD_HPP