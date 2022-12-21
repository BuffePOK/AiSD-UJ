#include "pqueue.h"
#include <iostream>
#include <cstdlib>

int main ()
{   
    MyPriorityQueue<int> obj;
    MyPriorityQueue<int> L;
    
    
    std::cout << "Empty " << obj.empty() <<"\n";
    obj.push(1);
    obj.push(3);
    obj.push(7);
    std::cout << "Empty " << obj.empty() <<"\n";

    obj.push(12);
    obj.push(14);
    obj.push(5);
    obj.display();

    L = obj;
    L.display();

    std::cout << "Rozmiar listy to " <<L.size() <<"\n";

    L.pop();
    L.pop();
    L.push(8);
    L.display();

    L.clear();
    

    return 0;
}