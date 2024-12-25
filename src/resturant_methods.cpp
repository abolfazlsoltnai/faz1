#include "classes.hpp"

Resturant::Resturant(string _name,string _district,string _foods,string _oppening,string _closing,string _number_of_tables){
    name = _name ;
    district = _district;
    foods  = _foods;
    oppening = _oppening;
    closing = _closing;
    number_of_tables = _number_of_tables;
    for (int i = 1; i <= stoi(number_of_tables); i++)
    {
        reserved_chair[i] = "";
    }
    
}
void Resturant::set_chair_reserve(int chair,string time){
    reserved_chair[chair] = time;
}
string Resturant::get_oppening(){
    return oppening;
}
string Resturant::get_closing(){
    return closing;
}
string Resturant::get_number_of_tables(){
    return number_of_tables;
}

map<int,string> Resturant::get_reserve_chairs(){
    return reserved_chair;
}
