#include <iostream>
#include <vector>
using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void printArr(vector<int> arr) {
    int count = 0;
    for(int i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if(i != arr.size() - 1) {
            cout << " ";
        }
    }

}

void BubbleSort(vector<int> arr) {
    int cnt = 0;
    for(int i = 0; i < arr.size(); i++) {
        for(int j = 0; j < arr.size() - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                cnt++;
                if (cnt == 5) {
                    cout << "Bubble: " << arr[j] << ", " << arr[j + 1] << "; ";
                    printArr(arr);
                    cout << endl;
                    return;
                }
            }
        }


    }
}

void InsertionSort(vector<int> arr) {
    int cnt = 1;
    for (int i = 1; i < arr.size(); i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
        cnt++;
        if(cnt == 5) {
            cout << "Insertion: ";
            printArr(arr);
            cout << endl;
            return;
        }
    }
}

void SelectionSort(vector<int> &arr) {
    int cnt = 0;
    for (int i = 0; i < arr.size() - 1; i++) {
        int min = i;
        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        swap(arr[i], arr[min]);
        cnt++;
        if(cnt == 5) {
            cout << "Selection: "  << arr[i] << "; ";
            printArr(arr);
            cout << endl;
        }
    }
    printArr(arr);
}

int main() {
    vector <int> num;
    int n;
    while (cin >> n) {
        num.push_back(n);
    }
    BubbleSort(num);
    InsertionSort(num);
    SelectionSort(num);

}