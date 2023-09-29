#include <iostream>
#include <memory>

using namespace std;

class Girl;

class Boy 
{
    public:
        Boy() {
            cout << "boy constructor" << endl;
        }
        void setGirlFriend(shared_ptr<Girl> girl_friend) {
            _girl_friend = girl_friend;
        }
        ~Boy() {
            cout << "boy destructor" << endl;
        }
    private:
        shared_ptr<Girl> _girl_friend;
};


class Girl
{
    public:
        Girl() {
            cout << "girl constructor" << endl;
        }
        void setBoyFriend(shared_ptr<Boy> boy_friend) {
            _boy_friend = boy_friend;
        }
        ~Girl() {
            cout << "girl destructor" << endl;
        }
    private:
        shared_ptr<Boy> _boy_friend;
};

int main() {
    shared_ptr<Girl> spGirl(new Girl());
    shared_ptr<Boy> spBoy(new Boy());
    //spGirl->setBoyFriend(spBoy);
    spBoy->setGirlFriend(spGirl);
    cout << spBoy.use_count() << endl;
    cout << spGirl.use_count() << endl;
}
