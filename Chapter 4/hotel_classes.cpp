class Guest {
public:
	Guest();
	Guest(const char *name);
	void programLevel(int level);

private:
	string m_name;
	int m_level;
};

class Room {
public:
    Room();
    Room(const char *number);
    void type(int type);
private:
    string m_number;
    int m_type;    
};

class Reservation {
public:
	Reservation();
	Guest *getGuest(int guestIndex);
	Room *getRoom(int roomIndex);
	int guestCount();
	int roomCount();
};

Reservation *LoadReservation(const char *reservationKey);