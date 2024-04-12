#include <iostream>
#include <cstdlib>
#include <ctime>
#include <bitset>
#include <vector>
using namespace std; 

string generateRandomString(int length) {
//function for generating random string with size length 

    string randomString; 
    //initalize random string 

    srand(time(nullptr));
    //random seed is generated based on current time

    for (int i = 0; i < length; i++) {

        int randomType = random() % 2; 
        //classify upper and lowercase

        if (randomType == 0) {
        //lowercase character

            char randomChar = rand() % 26 + 97; 
            //ASCII value for lowercase characters

            randomString += randomChar; 

        } else {

            char randomChar = rand() % 26 + 65; 
            //ASCII value for uppercase characters; 
                
            randomString += randomChar;

        } 

    }

    return randomString; 

}


string encryption(string key) {

    string plainText = generateRandomString(10);
    //import the string from the function generatRandomString as the plainText

    string cipher; 
    //initalize cipher; 

    cout << "This is the plainText: " << generateRandomString(10) << "\n";

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

        cipher += cipherCharacter;

    }

    cout << "This is Cipher: " << cipher << "\n";

    return cipher; 

}

void decryption(string key, string cipher) {
    string plainText;

    for (int i = 0; i < cipher.size(); i++) {
        string plainBinary;

        int cipherAsciiValue = static_cast<int>(cipher[i]);
        int asciiOffset = islower(cipherAsciiValue) ? 'a' : 'A';

        string cipherBinary = bitset<8>(cipherAsciiValue - asciiOffset).to_string();

        int keyAsciiValue = static_cast<int>(key[i]);
        string keyBinary = bitset<8>(keyAsciiValue - asciiOffset).to_string();

        for (int j = 0; j < cipherBinary.size(); j++) {
            int cipherBinaryInt = static_cast<int>(cipherBinary[j]) - '0';
            int keyBinaryInt = static_cast<int>(keyBinary[j]) - '0';

            int result = cipherBinaryInt ^ keyBinaryInt;
            string resultString = to_string(result);

            plainBinary = plainBinary + resultString;
        }

        int plainAscii = std::stoi(plainBinary, nullptr, 2);
        char plainCharacter = static_cast<char>(plainAscii + asciiOffset);

        plainText += plainCharacter;
    }

    // Flip the case of the first character in the plainText
    if (islower(plainText[0])) {
        plainText[0] = toupper(plainText[0]);
    } else {
        plainText[0] = tolower(plainText[0]);
    }

    cout << "This is the plainText: " << plainText << "\n";
}



int main() {

    string cipher; 

    srand(static_cast<unsigned int>(time(nullptr)));
    //seed the random number generator

    vector<string> keys = {"Remarkable", "Innovation", "Technology", "Beneficial", "Continuous", "Intriguing", "Repertoire", "Delectable", "Sufficient", "Vocabulary"};

    int randomIndex = rand() % keys.size();
    string randomKey = keys[randomIndex];
    //give random key everytime

    cout << "This is the random key: " << randomKey << "\n";

    cipher = encryption(randomKey); 

    decryption(randomKey, cipher);

}