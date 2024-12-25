#include "header.hpp"

class Resturant {
    public:
        Resturant(string name,string district,string foods,string oppening,string closing,string number_of_tables);
        string get_distric();
        string get_name();
        string get_foods();
        string get_oppening();
        string get_closing();
        string get_number_of_tables();
        map<int,string> get_reserve_chairs();
        void set_chair_reserve(int chair,string time);

    private:
        string name;
        string district;
        string foods;
        string oppening;
        string closing;
        string number_of_tables;
        map<int,string> reserved_chair;
        int reservatoon_id = 1;
};

class User {
    public:
    string get_username();
    string get_password();
    bool is_logged_in();
    void set_username(string usrname);
    void set_password(string password);
    void set_district(string district);
    string get_district();
    void set_reservation(string x,string y);
    map<string,string> get_reservation();
    private:
        string district = "";
        string username;
        string password;
        bool login_status = 0;
        bool is_auser = 0;
        map<string,string> reservation;
};

class System{
    public:
        System(){
            
        }
        void add_resturant(Resturant resturant);
        void add_district(string districts,string neighber);
        void add_user(User user);
        vector<Resturant> get_resturants(); 
        bool repeated_username(string username);
        User * loggin(string username , string password);
        User * get_last_user();
        User * get_lost_login(string username);
        map<string,string> get_districts();
    private:
        vector<Resturant> resturants;
        vector<User> users;
        map<string,string> districts;

};


