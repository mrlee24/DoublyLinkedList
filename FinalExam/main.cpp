#include <iostream>
#include <vector>
#include "MyCircularLinkedList.cpp"
using namespace std;

int main(int argc, const char * argv[]) {
    int temp[] = {1, 2, 3, 4};
    MyCircularList<int> myList(temp);
    MyCircularListIterator<int> it = myList.iterator();
    vector<int> vec = myList.toVector();
    cout << "To Vector " << endl;
    for(int i = 0; i < vec.size(); i++) {
        cout << vec[i] << endl;
    }

    int value = myList.head();
    cout << "Head: " << value << endl;
    cout << "Original List: " << endl;
    myList.print(myList, 5);

    cout << "Cloned List: " << endl;
    MyCircularList<int> clone = myList.copy();
    clone.print(clone, 4);
    
    int temp2[] = {5, 6, 7, 8};
    MyCircularList<int> myList2(temp2);
    //myList2.print(myList2, 5);
    cout << "Concat List: " << endl;
    myList.concat(myList2);
    myList.print(myList, 16);

    int new_value = it.next();
    cout << "Next node: " << new_value << endl;
    new_value = it.next();
    cout << "Next node: " << new_value << endl;
    new_value = it.previous();
    cout << "Previous node: " << new_value << endl;
    new_value = it.previous();
    cout << "Previous node: " << new_value << endl;

    try {
        cout << "Previous = " << it.previous() << endl;
        cout << " and I continue here" << endl;
    }
    catch (MyLLInvalidAccessException e) {
        cout << "Exception code = " << e.getCode() << endl;
        cout << e.getMessage() << endl;
    }
    
    it.set(100);
    it.next();
    it.next();

    cout << "Next: " << it.next() <<endl;
    cout << "Go to the beginning" << endl;
    it.goToBegin();
    
    //myList.print(myList, 8);
    
    new_value = it.next();
    cout << "Next node: " << new_value << endl;
    try {
        cout << "Previous = " << it.previous() << endl;
        cout << " and I continue here" << endl;
    }
    catch (MyLLInvalidAccessException e) {
        cout << "Exception code = " << e.getCode() << endl;
        cout << e.getMessage() << endl;
    }

    new_value = it.next();
    cout << "Next node: " << new_value << endl;
    new_value = it.next();
    cout << "Next node: " << new_value << endl;
    return 0;
}
