// ID: 315233486
// Mail: Eilonashwal30@gmail.com

#ifndef DEVELOPMENTCARD_HPP
#define DEVELOPMENTCARD_HPP

#define KNIGHT 0
#define VICTORY_POINT 1
#define ROAD_BUILDING 2
#define MONOPOLY 3
#define YEAR_OF_PLENTY 4

#include <string>

using namespace std;

namespace ariel 
{

    class DevelopmentCard 
    {
        private:
            bool used; // true if the card was used, false otherwise

        public:
            DevelopmentCard(); // Constructor
            virtual ~DevelopmentCard(); // Destructor
            
            bool isUsed() const; // Returns true if the card was used, false otherwise
            void useDevelopmentCard(); // Set the card as used

            virtual string getTypeName()const = 0; // Returns the name of the card
            virtual int getType() const = 0; // Returns the type of the card (Knight, Victory Point, Road Building, Monopoly, Year of Plenty)
    };

}

#endif