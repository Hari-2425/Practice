if(bookedSeats.containsKey(seatId)) {
            return false;
        }

        bookedSeats.put(seatId, userId);