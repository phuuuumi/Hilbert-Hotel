#include <bits/stdc++.h>
using namespace std;

class Room; 

class RoomInfo{
    private:
        int room_number;
        Room* room_type;
        bool occupied;
        public:
            void setRoom(int num, Room* type, bool occ) {
                room_number = num;
                room_type = type;
                occupied = occ;
            }
            int getNumber() const {
                return room_number;
            }

            Room* getTypePtr() const {
                return room_type;
            }

            bool isOccupied() const {
                return occupied;
            }
};

class Room{
    private:
        string room_type;
        int guest;
        map <string,int> bed;
        string bathroom;
        bool living_room;
        double price;
    public:
        void set_data(string ,int ,map <string,int> ,string ,bool ,double );
        void show() const {
            cout << room_type << " "
                 << guest << " "
                << bathroom << " "
                << living_room << " "
                << price << endl;
        }
        string getType() const {
            return room_type;
        }

        double getPrice() const {
            return price;
        }

};

void Room::set_data(string r,int g,map <string,int> b,string bath,bool l,double p){
    room_type = r;
    guest = g;
    bed = b;
    bathroom = bath;
    living_room = l;
    price = p;

}