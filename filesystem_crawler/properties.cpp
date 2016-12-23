#include "properties.hpp"
#include "utils.hpp"

Properties::Properties(string json_file)
{
    string json_content = utils::read_from_file(json_file);
    document.Parse(json_content.c_str());
    if(document.Parse(json_content.c_str()).HasParseError())
    {
        cerr << "ERROR: parsing "<< json_file << endl;
        return;
    }
    if(!document.IsObject() )
    {
        cerr << "ERROR: " << json_file << "is not a valid json." << endl;
        return;
    }
}

Properties::~Properties()
{}

bool Properties::valid_key(string key)
{
    bool valid = true;
    if(!document.HasMember(key.c_str()))
    {
        cerr << "ERROR: no key named " << key << endl;
        valid = false;
    }
    return valid;
}

bool Properties::get_bool(string key)
{
    const char* ckey = key.c_str();
    bool value = false;
    if(valid_key(key) && document[ckey].IsBool())
    {
        value = document[ckey].GetBool();
    }
    return value;
}

string Properties::get_string(string key)
{
    const char* ckey = key.c_str();
    string value;
    if(valid_key(key) && document[ckey].IsString())
    {
        value = document[ckey].GetString();
    }
    return value;
}

int Properties::get_int(string key)
{
    const char* ckey = key.c_str();
    int value = -1;
    if(valid_key(key) && document[ckey].IsNumber() && document[ckey].IsInt())
    {
        value = document[ckey].GetInt();
    }
    return value;
}

double Properties::get_double(string key)
{
    const char* ckey = key.c_str();
    double value = -1.0;
    if(valid_key(key) && document[ckey].IsNumber() && document[ckey].IsDouble())
    {
        value = document[ckey].GetDouble();
    }
    return value;
}

vector<string> Properties::get_string_array(string key)
{
    const char* ckey = key.c_str();
    vector<string> string_array;
    if(valid_key(key) && document[ckey].IsArray())
    {
        for (auto& v : document[ckey].GetArray())
            string_array.push_back(v.GetString());
    }
    return string_array;
}


vector<int> Properties::get_int_array(string key)
{
    const char* ckey = key.c_str();
    vector<int> int_array;
    if(valid_key(key) && document[ckey].IsArray())
    {
        for (auto& v : document[ckey].GetArray())
            int_array.push_back(v.GetInt());
    }
    return int_array;
}

vector<double> Properties::get_double_array(string key)
{
    const char* ckey = key.c_str();
    vector<double> double_array;
    if(valid_key(key) && document[ckey].IsArray())
    {
        for (auto& v : document[ckey].GetArray())
            double_array.push_back(v.GetDouble());
    }
    return double_array;
}
