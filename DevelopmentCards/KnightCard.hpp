// ID: 315233486
// Mail: Eilonashwal30@gmail.com

#ifndef KNIGHTCARD_HPP
#define KNIGHTCARD_HPP

#include "DevelopmentCard.hpp"

namespace ariel 
{
    class KnightCard : public DevelopmentCard // KnightCard class inherits from DevelopmentCard
    {
        public:
            KnightCard(); // Constructor
            ~KnightCard() override; // Destructor

            string getTypeName() const override{ return "Knight";}; // Returns the card type name 
            int getType() const override { return KNIGHT; } // Returns the card type (0 for Knight)
    };
}

#endif // KNIGHTCARD_HPP