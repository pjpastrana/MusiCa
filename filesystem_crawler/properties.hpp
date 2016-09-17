#ifndef _PROPERTIES_H_
#define _PROPERTIES_H_

#include <iostream>
#include <string>
#include <rapidjson/document.h>
#include <vector>

using namespace std;
using rapidjson::Document;

class Properties
{
    // TODO: document does not have a copy constructor. Is preventing me having a static instance method to create a singleton
    Document document;

    public:
        Properties(string json_file);
        ~Properties();
        // TODO: how to do get methods with templates
        // template<typename T>
        // void get(string key, T value);
        bool valid_key(string key);
        bool get_bool(string key);
        string get_string(string key);
        int get_int(string key);
        double get_double(string key);
        vector<string> get_string_array(string key);
        vector<int> get_int_array(string key);
        vector<double> get_double_array(string key);

        // static Properties& instance() { return instance_; }
        
        // NOTE: C++11 mandates that the initializer for a local static variable is only run once, even in the presence of concurrency.
        // TODO: how to do singleton
        // static Properties& instance(string json_file);
        // {
        //     static Properties* singleton_instance = new Properties(json_file);
        //     return *singleton_instance;
        // }

};

#endif
