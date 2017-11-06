
#include <iostream>
#include <vector>

using namespace std;

<<<<<<< HEAD
int main ()
{
    int x = 1;

    [&](void)
    {
        x = 2;
    };

    while (x)
    {
        cout << "hello world!" << endl;
        vector<int> age;
        age.push_back(10);
        age.push_back(12);
        age.push_back(15);
        age.push_back(30);
        for (auto i : age)
        {
            cout << i << endl;
        }
        cin >> x;
    }
    
    //getchar ();
=======
void main ()
{
    //need
    cout << "hello world!" << endl;
    getchar ();
>>>>>>> 7f2141b1211cc3349edb05e2f43df7168865dd74
    return 0;
}