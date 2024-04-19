#include <string>
using namespace std; 

string toLowerCase(const std::string& str);
string generateRandomString(int length);
string generateRandomKey(); 
string encryption(string originalText,string key); 
string decryption(string key, string cipher); 
void encryptionMain(string randomKey); 
