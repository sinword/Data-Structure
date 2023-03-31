#include <iostream>
using namespace std;

int rabbit[1000] = {0};

int reproduction(int month) {
    if(rabbit[month] != 0) {
        return rabbit[month];
    }
    else {
        int tmp = reproduction(month - 1) + reproduction(month - 2);
        rabbit[month] = tmp;
        return tmp;
    }
}

int main() {
    int month, t;
    rabbit[0] = 0;
    rabbit[1] = 1;
    rabbit[2] = 1;
    cin >> t;
    for(int i = 0; i < t; i++) {
      cin >> month;
      if(month == 0) {
        cout << "0\n";
      }
      else{
        if(rabbit[month] == 0) {
          reproduction(month);
        }
        cout << rabbit[month] << "\n";
      }
    }
}