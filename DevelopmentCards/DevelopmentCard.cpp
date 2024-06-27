// ID: 315233486
// Mail: Eilonashwal30@gmail.com

#include "DevelopmentCard.hpp"

namespace ariel 
{

    DevelopmentCard::DevelopmentCard(): used(false) {} // Constructor

    DevelopmentCard::~DevelopmentCard() {} // Destructor

    bool DevelopmentCard::isUsed() const { return used; } // Returns true if the card was used, false otherwise

    void DevelopmentCard::useDevelopmentCard() {this->used = true;} // Set the card as used 
}