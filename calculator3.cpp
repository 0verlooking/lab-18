#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class Room {
public:
    int number;
    bool is_reserved;

    Room(int n) : number(n), is_reserved(false) {}

    void reserve() {
        is_reserved = true;
    }

    void cancel() {
        is_reserved = false;
    }
};

class Hotel {
public:
    std::vector<std::unique_ptr<Room>> rooms;

    void addRoom(int number) {
        rooms.push_back(std::make_unique<Room>(number));
    }

    void removeRoom(int number) {
        auto it = std::find_if(rooms.begin(), rooms.end(),
        [number](const std::unique_ptr<Room>& room) {
            return room->number == number;
        });

        if (it != rooms.end()) {
            rooms.erase(it);
        }
    }

    Room* findRoom(int number) {
        auto it = std::find_if(rooms.begin(), rooms.end(),
        [number](const std::unique_ptr<Room>& room) {
            return room->number == number;
        });

        return (it != rooms.end()) ? it->get() : nullptr;
    }
};

int main() {
    Hotel hotel;

    hotel.addRoom(101);
    hotel.addRoom(102);
    hotel.addRoom(103);

    Room* room = hotel.findRoom(102);
    if (room != nullptr) {
        room->reserve();
        std::cout << "Room 102 is reserved.\n";
    }

    hotel.removeRoom(101);

    room = hotel.findRoom(101);
    if (room == nullptr) {
        std::cout << "Room 101 is removed from the hotel.\n";
    }

    return 0;
}