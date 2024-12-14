# SpadesApp

HIGH-Level CONCEPTUAL VIEW:
- randomly generate a deck of 52 cards
- create users (each is initialized with an emptylist aka 'their hand')
- disperse 13 cards to the users
- [betting pink slips]
= Game Begins:
- each user selects three cards in their deck to starting with RIGHT [LEFT, ACROSS, RIGHT] and this will become their selectedCards attribute value
- remove the selectedCards from the users deck
- add the selectedCards to the user depending on the configuration of the current turn (aka LEFT, ACROSS, RIGHT)
- find the 2 of Clubs by searching through each user's deck
- Now the turn will go to the user to the left of the person who has the 2 of Clubs




LOW-LEVEL VIEW:
- find the 2 of clubs and then send a request to the user that is considered to their 'left' and then wait for a response from that user (add timer)
- process that response: take their card choice and lay it on the 'pile', send update of current game state to all users
- repeat this process until: [enter edge case]




class User {

    private:
        int deck[13];
        int selectedCards[3];


}


