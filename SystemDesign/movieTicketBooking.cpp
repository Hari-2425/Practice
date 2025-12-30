// Functional Requirements (few key ones)
// - Browse & Search Movies – Users can view movies by title, genre, language, and showtime.
// - Seat Selection & Booking – Choose seats with real‑time availability and confirm booking.
// - Payment Processing – Support multiple payment methods and handle success/failure.
// - Ticket Management – Generate digital tickets, allow cancellations/refunds.
// - Notifications – Send booking confirmations and reminders.

// ⚙️ Non‑Functional Requirements (few essentials)
// - Performance – Quick response times, especially for seat availability.
// - Scalability – Handle peak loads during blockbuster releases.
// - Security – Encrypt sensitive data, secure payments, role‑based access.
// - Reliability – Prevent double‑booking, ensure consistent transactions.
// - Usability – Simple, intuitive UI across web and mobile.

#include <bits/stdc++.h>
using namespace std;

//Entities - user, movie, seat, ticket, payment
class User{
    string name;
    string Id;
    string phno;
    string email;

    // api endpoint in MovieService
    vector<Movie> SearchMovies(string title, string lang, string genre, string showTime){

    } 

    void BookSeat(Seat seat){
         
    }
};

class Movie{
    string movieId;
    string title;
    string genre;
    unordered_set<string> lang;
    string showTime;
    double price;
    
};

enum seatType{
    first,
    second,
    third
};

class Seat{
    string seatId;
    string type;
    bool available;
};

class Ticket{
    string ticketId;
    double amount;
    string userId;
    Movie bookedMovie;
    Seat bookedSeat;
};

enum paymentType{
    cash,
    online,
    creditCard
};

class Payment{
    string paymentId;
    string UserId;
    double amount;
    string type;
};

int main(){
    return 0;
}
