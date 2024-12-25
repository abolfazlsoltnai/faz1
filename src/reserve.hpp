#include <algorithm>

Resturant * get_resturant_ptr_filter_name(System &ss,string name){
    for (int i = 0 ; i < ss.get_resturants().size();i++)
    {
        if (ss.get_resturants()[i].get_name() == name)
        {
            return &ss.get_resturants()[i];
        }
        
    }
    
}


void set_reservation(System &ss,map<string,string> infs , User *usr){

    string restaurant_name = infs["restaurant_name"];
    Resturant * res = get_resturant_ptr_filter_name(ss,restaurant_name);
    string table_id = infs["table_id"];
    string start_time = infs["start_time"];
    string end_time = infs["end_time"];
    usr->set_reservation(restaurant_name,table_id+"-"+start_time+"-"+end_time);
    res->set_chair_reserve(stoi(table_id),start_time+"-"+end_time);
    cout << "done reservation" << endl;
}



map<string,string> make_command_readble(vector<string> commands){
    map<string,string> z ;
    string c = "" ;
    for (auto  i : commands)
    {
        c += " " + i;
    }
    
    bool name = 0;
    bool chair_num = 0;
    bool come = 0;
    bool go = 0;
    bool food = 0;
    for (auto i : commands)
    {
      
        if (i == "restaurant_name")
        {
            name = 1;
        }
        if (i == "table_id")
        {
            chair_num = 1;
        }
        if (i == "start_time")
        {
            come = 1;
        }
        if (i == "end_time")
        {
            go = 1;
        }
        if (i == "foods")
        {
            food = 1;
        }
        
        
    }
    if(!(name && chair_num && come && go))
    {
        z["valid"] = "0";
        return z;
    }else{
        z["valid"] = "1";
    }
    if(!(food))
    {
        z["food_valid"] = "0";
        return z;
    }else{
        z["food_valid"] = "1";
    }

    string d =  "";
    size_t pos1 = 0;
    size_t pos2 = 0;
    
    pos1 = c.find("restaurant_name");
    pos1 = c.find('"',pos1);
    pos2 = c.find('"',pos1+1);
    d = c.substr(pos1+1,pos2-pos1-1);
    z["restaurant_name"] = d;

    pos1 = c.find("table_id");
    pos1 = c.find('"',pos1);
    pos2 = c.find('"',pos1+1);
    d = c.substr(pos1+1,pos2-pos1-1);    
    z["table_id"] = d;

    pos1 = c.find("start_time");
    pos1 = c.find('"',pos1);
    pos2 = c.find('"',pos1+1);
    d = c.substr(pos1+1,pos2-pos1-1);
    z["start_time"] = d;
    

    pos1 = c.find("end_time");
    pos1 = c.find('"',pos1);
    pos2 = c.find('"',pos1+1);
    d = c.substr(pos1+1,pos2-pos1-1);
    z["end_time"] = d;
    if (food == 1)
    {
        pos1 = c.find("foods");
        pos1 = c.find('"',pos1);
        pos2 = c.find('"',pos1+1);
        d = c.substr(pos1+1,pos2-pos1-1);
        z["foods"] = d;
        
    }else{
        z["foods"] =  "";
    }
    return z;
}

string get_string_like_normal(string x){
    x.erase(0,1);
    x.erase(x.size()-1,1);
    return x;

}

bool compareByName(Resturant& a, Resturant& b) {
    return a.get_name() < b.get_name();
}

vector<Resturant> get_resturent_filter_district(System &ss,string  district){
    vector<Resturant> x ;
    for (auto i : ss.get_resturants())
    {
        if (i.get_distric() == district)
        {
            x.push_back(i);
        }
        
    }

    sort(x.begin(), x.end(), compareByName);
    return x;
    
}



vector<string> splitStringByDelimiter2(const string input, char delimiter) {
    vector<std::string> result;
    stringstream ss(input);
    string item;

    while (std::getline(ss, item, delimiter)) {
        result.push_back(item);
    }

    return result;
}

vector<string> show_resturant_in_district(System &ss,string district){
    vector<string> row;
    vector<Resturant> resturants = ss.get_resturants();
    for(auto &res : resturants){
        if (district == res.get_distric())
        {
            row.push_back(res.get_name());
        }
        
    }
    return row;
}

bool inside_out(vector<string> x,string y){
    bool z = 0;
    for (auto i : x)
    {
        if(i == y){
            z = 1;
        }
    }
    return z;
}

Resturant get_restuarant_filter_name(System ss,string name){
    for (auto i : ss.get_resturants())
    {
        if (i.get_name() == name)
        {
            return i;
        }
        
    }
    return ss.get_resturants()[0];
    
}

map<string,string> get_resturant_give_foods(Resturant r){
    map<string,string> x;
    for (auto i : splitStringByDelimiter2(r.get_foods(),';'))
    {
            x[splitStringByDelimiter2(i,':')[0]] = splitStringByDelimiter2(i,':')[1];
    }
    return x;
    
}
void get_resturant_give_foods_print(Resturant *r){
    for (auto i : splitStringByDelimiter2(r->get_foods(),';'))
    {
            cout << r->get_name();
            cout << i<<endl;
            // cout << splitStringByDelimiter2(i,':')[0];
    }

    
}

bool resturant_has_food(Resturant r,string food){
       map<string,string> foods = get_resturant_give_foods(r);
       for (auto [key,value] : foods)
       {
            if (key == food)
            {
                return 1;
            }
            
       }
       
       return 0;
}

void resturant_list(System &ss,User *usr,vector<string> &future_search,vector<string> &gone_districts,int n = 0){
    
    if (n == 0){
        vector<string> user_neighbor_districts = splitStringByDelimiter2(ss.get_districts()[usr->get_district()],';');
        future_search.insert(future_search.end(),user_neighbor_districts.begin(),user_neighbor_districts.end());
        gone_districts.push_back(usr->get_district());
        n++;
        resturant_list(ss,usr,future_search,gone_districts,n);
    }else{

        for(auto i : future_search){
            if (!inside_out(gone_districts,i))
            {
               gone_districts.push_back(i);
            }
            
        }
        if (gone_districts.size() >= ss.get_districts().size())
        {
            return;
        }
    
        vector<string> copy_from_future;
        for(auto i : future_search){
            copy_from_future.push_back(i);
        }
        future_search.clear();
        for (auto i : copy_from_future)
        {
            for(auto z : splitStringByDelimiter2(ss.get_districts()[i],';')){
                future_search.push_back(z);
            }
        }
        
       if (future_search.empty()) {
         return;
        }
        
        resturant_list(ss,usr,future_search,gone_districts,n);

    }

}

void restaurant_detail(System &ss,string name){
    int i = -1;
    for (int j = 0; j<ss.get_resturants().size();j++)
    {
        if (ss.get_resturants()[j].get_name() == name)
        {
            i = j;
            break;
        }
        
    }
    if (i != -1)
    {
       Resturant x  = ss.get_resturants()[i];
       cout <<  "Name: " << x.get_name() << endl;
       cout << "District: " << x.get_distric() << endl;
       cout << "Time: " << x.get_oppening() << "-" << x.get_closing() << endl;
       cout << "Menu: ";
       map<string,string> foods = get_resturant_give_foods(x);
       for (auto [key,value] : foods)
       {
        cout << key << "(" << value << ")" << ", " ;
       }
       
       cout << endl;
        for (auto  [key,value] : x.get_reserve_chairs())
        {
            cout << key <<": "<<endl;
        }
        

    }else{
        cout << "Not Foundm" << endl;
        return;
    }
    
    
}