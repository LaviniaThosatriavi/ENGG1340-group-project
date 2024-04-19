#include <iostream>
#include <cstdlib>
#include <ctime>
#include <bitset>
#include <vector>
#include <cctype>
using namespace std; 


string toLowerCase(const string& str) {

    string lowerCaseStr = str;
    
    for (char& c : lowerCaseStr) {
        c = tolower(c);
    }
    
    return lowerCaseStr;
}
//convert to lower case

string generateRandomKey() {

    srand(static_cast<unsigned int>(time(nullptr)));
    //seed the random number generator

    vector<string> keys = {"chocolates", "adventures", "reflection", "autombiles"};

    int randomIndex = rand() % 4;
    string randomKey = keys[randomIndex];
    //give random key everytime

    return randomKey; 
}
string generateRandomString(int length) {

    string randomString;
    
    srand(time(nullptr));
    
    for (int i = 0; i < length; i++) {
        char randomChar = rand() % 26 + 97;
        randomString += randomChar;
    }
    
    return randomString;
}
//generate a random string


string encryption(string plainText,string key) {

    string cipher1; 
    //initalize cipher; 

    for (int i = 0; i < plainText.size(); i++) {
    //iterate through each character of the plaintext and key

        string cipherBinary; 
        //initalize cipher character binary

        int textAsciiValue = static_cast<int>(plainText[i]);
        //get the ASCII value of the character for the plainText

        int asciiOffset = islower(textAsciiValue) ? 'a' : 'A';

        string textBinary = bitset<8>(textAsciiValue - asciiOffset).to_string();
        //convert the ASCII value into binary for the plainText

        int keyAsciiValue = static_cast<int>(key[i]);
        //get the ASCII value of the character for the key

        string keyBinary = bitset<8>(keyAsciiValue - asciiOffset).to_string();
        //convert the ASCII value into binary for the key

        for (int j = 0; j < textBinary.size(); j++) {

            int textBinaryInt = static_cast<int>(textBinary[j]) - '0';
            int keyBinaryInt = static_cast<int>(keyBinary[j]) - '0';

            int result = textBinaryInt ^ keyBinaryInt; 
            //perform XOR operation on the binary valye of plaintext and the binary value of key

            string resultString = to_string(result); 
            //convert the operation result into string type

            cipherBinary = cipherBinary + resultString; 
            //add the result in string to the variable cipherBinary

        }

        int cipherAscii = std::stoi(cipherBinary, nullptr, 2);
        //conver the binary value of cipher into ascii value for the cipher
        
        char cipherCharacter = static_cast<char>(cipherAscii + asciiOffset); 
        //conver the ascii value of the cipher into character

        cipher1 += cipherCharacter;

    }

    string cipher2 = toLowerCase(cipher1);

    return cipher2;

}

string decryption(string key, string cipher) {

    string plainText1;
    //initalize plainText

    for (int i = 0; i < cipher.size(); i++) {

        string plainBinary;
        //initalize binary value for the plainText

        int cipherAsciiValue = static_cast<int>(cipher[i]);
        //convert character of cipher into its corresponding ASCII value

        int asciiOffset = islower(cipherAsciiValue) ? 'a' : 'A';
        //determine whether that particular character is in upper or lower case 

        string cipherBinary = bitset<8>(cipherAsciiValue - asciiOffset).to_string();
        //convert ASCII value into binary 

        int keyAsciiValue = static_cast<int>(key[i]);
        //convert character of key into its corresponding ASCII value

        string keyBinary = bitset<8>(keyAsciiValue - asciiOffset).to_string();
        //convert ASCII value of the character of the key into binary 

        for (int j = 0; j < cipherBinary.size(); j++) {

            int cipherBinaryInt = static_cast<int>(cipherBinary[j]) - '0';
            int keyBinaryInt = static_cast<int>(keyBinary[j]) - '0';

            int result = cipherBinaryInt ^ keyBinaryInt;
            //perform XOR operation 

            string resultString = to_string(result);

            plainBinary = plainBinary + resultString;
            //add the computed result to the plainTetxt
   
        }

        int plainAscii = stoi(plainBinary, nullptr, 2);
        //convert the binary value of the characters of the plaintext into ASCII values

        char plainCharacter = static_cast<char>(plainAscii + asciiOffset);
        //convert the ASCII values of the plainText into its corresponding characters

        plainText1 += plainCharacter;
    }

    if (islower(plainText1[0])) {
        plainText1[0] = toupper(plainText1[0]);
    } else {
        plainText1[0] = tolower(plainText1[0]);
    }
    // Flip the case of the first character in the plainText

    string plainText2 = toLowerCase(plainText1);

    return plainText2;
}



void encryptionMain(string originalText,string randomKey) {

    string blue = "\033[34m";
    // ANSI escape code for blue text

    string reset = "\033[0m";
    // ANSI escape code for resetting text color

    string cipher; 

    cipher = encryption(originalText, randomKey);

    cout << "This is the message: "; 
    cout << blue << cipher << reset;
    cout << " Guess the key and decrypt the message!" << "\n";

}