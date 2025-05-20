#include "ants.h"

int main() {
    Anthill Small_hill(4, 3); 
    Small_hill.set_room_capacity(0, 3);
    Small_hill.set_room_capacity(1, 1);
    Small_hill.set_room_capacity(2, 1);
    Small_hill.set_room_capacity(3, 3);

    Small_hill.add_tunnels(0,1);
    Small_hill.add_tunnels(0,2);
    Small_hill.add_tunnels(1,4);
    Small_hill.add_tunnels(2,4);
    


    Anthill Big_hill(16, 50);
    Big_hill.set_room_capacity(0, 50);
    Big_hill.set_room_capacity(1, 1);
    Big_hill.set_room_capacity(2, 1);
    Big_hill.set_room_capacity(3, 1);
    Big_hill.set_room_capacity(4, 1);
    Big_hill.set_room_capacity(5, 1);
    Big_hill.set_room_capacity(6, 1);
    Big_hill.set_room_capacity(7, 1);
    Big_hill.set_room_capacity(8, 1);
    Big_hill.set_room_capacity(9, 1);
    Big_hill.set_room_capacity(10, 1);
    Big_hill.set_room_capacity(11, 1);
    Big_hill.set_room_capacity(12, 1);
    Big_hill.set_room_capacity(13, 1);
    Big_hill.set_room_capacity(14, 1);
    Big_hill.set_room_capacity(15, 50);

    Big_hill.add_tunnels(1,2);
    Big_hill.add_tunnels(2,3);
    Big_hill.add_tunnels(3,4);
    Big_hill.add_tunnels(4,15);
    Big_hill.add_tunnels(0,1);
    Big_hill.add_tunnels(2,5);
    Big_hill.add_tunnels(5,4);
    Big_hill.add_tunnels(13,15);
    Big_hill.add_tunnels(8,12);
    Big_hill.add_tunnels(12,13);
    Big_hill.add_tunnels(6,7);
    Big_hill.add_tunnels(7,9);
    Big_hill.add_tunnels(9,14);
    Big_hill.add_tunnels(14,15);
    Big_hill.add_tunnels(7,10);
    Big_hill.add_tunnels(10,14);
    Big_hill.add_tunnels(1,6);
    Big_hill.add_tunnels(6,8);
    Big_hill.add_tunnels(8,11);
    Big_hill.add_tunnels(11,13);
}

