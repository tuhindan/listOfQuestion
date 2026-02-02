// Confluent screening round

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class FunctionRegister {
    private:
        unordered_map<string, vector<string>> ump;
        unordered_map<string, vector<string>> vmp;
        
        string concatStr(vector<string> arg_list, int index) {
            string res = "";
            for (int i = 0 ; i < index ; i++) {
                res.append(arg_list[i]);
            }
            return res;
        }
        
        void concatVector(vector<string> &to, vector<string> &from ) {
            for(auto &s :  from) {
                to.push_back(s);
            }
        }
        
        int findArgIndexForVardiac(vector<string> &arg_list) {
            int count  = 0;
            for(int i = arg_list.size() - 1; i > 0 ; i--) {
                if(arg_list[i] == arg_list[i-1]) {
                    count++;
                } else
                    break;
            }
            
            return arg_list.size() - count;
        }
    
    public:
        void registerFunc(string func_name, vector<string> arg_list , bool isVariadic) {
            string key = concatStr(arg_list,arg_list.size());

            if(isVariadic) {
                auto it = vmp.find(key);
                if(it == vmp.end()) {
                    vmp[key] = {func_name};
                } else {
                    it->second.push_back(func_name);
                }
            } else {
                auto it = ump.find(key);
                if(it == ump.end()) {
                    ump[key] = {func_name};
                } else {
                    it->second.push_back(func_name);
                }
            }
        }
        
        vector<string> getFunc(vector<string> arg_list) {
            vector<string> res;
            string key = concatStr(arg_list, arg_list.size());
            
            auto it = ump.find(key);
            if(it != ump.end())
                concatVector(res, it->second);
                
            int pos = findArgIndexForVardiac(arg_list);
            // cout<<"pos : "<<pos<<endl;
            key = concatStr(arg_list, pos);
            it = vmp.find(key);
            if(it != vmp.end())
                concatVector(res, it->second);
            for(int i = pos ; i < arg_list.size() ; i++) {
                key.append(arg_list[i]);
                it = vmp.find(key);
                if(it != vmp.end())
                    concatVector(res, it->second);
            }
            
            return res;
        }
};

void printVector(vector<string> v) {
    for(auto &s : v) 
        cout<<s<<" ";
    cout<<endl;
}

int main()
{
    FunctionRegister functionRegister;
    
    functionRegister.registerFunc("func1" , {"bool", "integer", "integer"}, false);
    functionRegister.registerFunc("func2" , {"bool", "integer"}, false);
    functionRegister.registerFunc("func3" , {"bool"}, false);
    functionRegister.registerFunc("func4" , {}, false);
    
    functionRegister.registerFunc("func11" , {"bool", "integer", "integer"}, true);
    functionRegister.registerFunc("func12" , {"bool", "integer"}, true);
    functionRegister.registerFunc("func13" , {"bool"}, true);
    functionRegister.registerFunc("func5" , {}, true);
    
    
    printVector(functionRegister.getFunc({"bool", "integer", "integer"}));
    printVector(functionRegister.getFunc({"bool"}));
    printVector(functionRegister.getFunc({}));
    

    return 0;
}
