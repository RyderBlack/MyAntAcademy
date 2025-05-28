#include <iostream>
#include "ants.h"

int main() {

    Anthill ant_0 (4,2);
    ant_0.set_room_capacity(0,2);
    ant_0.set_room_capacity(1,1);
    ant_0.set_room_capacity(2,1);
    ant_0.set_room_capacity(3,2);

    ant_0.add_tunnels(0,1);
    ant_0.add_tunnels(0,2);
    ant_0.add_tunnels(1,3);
    ant_0.add_tunnels(2,3);

//-----------------------------------------------------

    Anthill ant_1(4, 5);
    ant_1.set_room_capacity(0,5);
    ant_1.set_room_capacity(1,1);
    ant_1.set_room_capacity(2,1);
    ant_1.set_room_capacity(3,5);

    ant_1.add_tunnels(0,1);
    ant_1.add_tunnels(1,2);
    ant_1.add_tunnels(2,3);


//------------------------------------------------

    Anthill ant_2(4,5);

    ant_2.set_room_capacity(0,5);
    ant_2.set_room_capacity(1,1);
    ant_2.set_room_capacity(2,1);
    ant_2.set_room_capacity(3,5);

    ant_2.add_tunnels(0,1);
    ant_2.add_tunnels(1,2);
    ant_2.add_tunnels(2,3);
    ant_2.add_tunnels(0,3);

//---------------------------------------------------------

    Anthill ant_3(6,5);

    ant_3.set_room_capacity(0,5);
    ant_3.set_room_capacity(1,1);
    ant_3.set_room_capacity(2,1);
    ant_3.set_room_capacity(3,1);
    ant_3.set_room_capacity(4,1);
    ant_3.set_room_capacity(5,5);

    ant_3.add_tunnels(0,1);
    ant_3.add_tunnels(1,2);
    ant_3.add_tunnels(4,5);
    ant_3.add_tunnels(1,4);
    ant_3.add_tunnels(2,3);


//---------------------------------------------

    Anthill ant_4(8,10);

    ant_4.set_room_capacity(0,10);
    ant_4.set_room_capacity(1,2);
    ant_4.set_room_capacity(2,1);
    ant_4.set_room_capacity(3,1);
    ant_4.set_room_capacity(4,2);
    ant_4.set_room_capacity(5,2);
    ant_4.set_room_capacity(6,1);
    ant_4.set_room_capacity(7,10);

    ant_4.add_tunnels(3,4);
    ant_4.add_tunnels(0,1);
    ant_4.add_tunnels(1,2);
    ant_4.add_tunnels(2,4);
    ant_4.add_tunnels(4,5);
    ant_4.add_tunnels(5,7);
    ant_4.add_tunnels(4,6);
    ant_4.add_tunnels(6,7);
    ant_4.add_tunnels(1,3);

// -----------------------------------------------------------------
    Anthill ant_5(16, 50);
    ant_5.set_room_capacity(0, 50);
    ant_5.set_room_capacity(1, 8);
    ant_5.set_room_capacity(2, 4);
    ant_5.set_room_capacity(3, 2);
    ant_5.set_room_capacity(4, 4);
    ant_5.set_room_capacity(5, 2);
    ant_5.set_room_capacity(6, 4);
    ant_5.set_room_capacity(7, 2);
    ant_5.set_room_capacity(8, 5);
    ant_5.set_room_capacity(9, 1);
    ant_5.set_room_capacity(10, 1);
    ant_5.set_room_capacity(11, 1);
    ant_5.set_room_capacity(12, 1);
    ant_5.set_room_capacity(13, 4);
    ant_5.set_room_capacity(14, 12);
    ant_5.set_room_capacity(15, 50);

    ant_5.add_tunnels(0, 1);
    ant_5.add_tunnels(1, 2);
    ant_5.add_tunnels(2, 3);
    ant_5.add_tunnels(3, 4);
    ant_5.add_tunnels(4, 15);
    ant_5.add_tunnels(1, 6);
    ant_5.add_tunnels(6, 8);
    ant_5.add_tunnels(8, 12);
    ant_5.add_tunnels(12, 13);
    ant_5.add_tunnels(13, 15);
    ant_5.add_tunnels(2, 5);
    ant_5.add_tunnels(5, 4);
    ant_5.add_tunnels(6, 7);
    ant_5.add_tunnels(7, 10);
    ant_5.add_tunnels(10, 14);
    ant_5.add_tunnels(14, 15);
    ant_5.add_tunnels(3, 9);
    ant_5.add_tunnels(9, 11);
    ant_5.add_tunnels(11, 15);

//--------------------------------------------------------------------
    Anthill King_hill(23,100);

    King_hill.set_room_capacity(0,100);
    King_hill.set_room_capacity(1,50);
    King_hill.set_room_capacity(2,50);
    King_hill.set_room_capacity(3,50);
    King_hill.set_room_capacity(4,1);
    King_hill.set_room_capacity(5,1);
    King_hill.set_room_capacity(6,3);
    King_hill.set_room_capacity(7,3);
    King_hill.set_room_capacity(8,7);
    King_hill.set_room_capacity(9,5);
    King_hill.set_room_capacity(10,5);
    King_hill.set_room_capacity(11,3);
    King_hill.set_room_capacity(12,3);
    King_hill.set_room_capacity(13,10);
    King_hill.set_room_capacity(14,20);
    King_hill.set_room_capacity(15,1);
    King_hill.set_room_capacity(16,1);
    King_hill.set_room_capacity(17,30);
    King_hill.set_room_capacity(18,10);
    King_hill.set_room_capacity(19,5);
    King_hill.set_room_capacity(20,5);
    King_hill.set_room_capacity(21,30);
    King_hill.set_room_capacity(22,100);

    King_hill.add_tunnels(0,1);
    King_hill.add_tunnels(1,2);
    King_hill.add_tunnels(2,3);
    King_hill.add_tunnels(3,4);
    King_hill.add_tunnels(4,5);
    King_hill.add_tunnels(5,22);
    King_hill.add_tunnels(0,6);
    King_hill.add_tunnels(6,7);
    King_hill.add_tunnels(7,8);
    King_hill.add_tunnels(8,9);
    King_hill.add_tunnels(9,10);
    King_hill.add_tunnels(10,22);
    King_hill.add_tunnels(0,11);
    King_hill.add_tunnels(11,12);
    King_hill.add_tunnels(12,13);
    King_hill.add_tunnels(13,14);
    King_hill.add_tunnels(14,15);
    King_hill.add_tunnels(15,22);
    King_hill.add_tunnels(0,16);
    King_hill.add_tunnels(16,17);
    King_hill.add_tunnels(17,18);
    King_hill.add_tunnels(18,19);
    King_hill.add_tunnels(19,20);
    King_hill.add_tunnels(20,22);
    King_hill.add_tunnels(21,3);
    King_hill.add_tunnels(21,8);
    King_hill.add_tunnels(21,13);
    King_hill.add_tunnels(21,18);


    //std::cout << " Simulation de small hill :\n" ;
    //Small_hill.simulate_bfs();
    //std::cout << " Simulation de big hill :\n";
    //Big_hill.simulate_bfs();
    std::cout << "Simulation de King hill :\n";
    King_hill.simulate_bfs();

    return 0;
}