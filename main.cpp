#include "rotatingStone.h"
#include "blockdash.h"
#include "encryption.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{

    string red = "\033[31m";
    // ANSI escape code for red text

    string green = "\033[32m";
    // ANSI escape code for green text

    string blue = "\033[34m";
    // ANSI escape code for blue text

    string reset = "\033[0m";
    // ANSI escape code for resetting text color

    bool player = true;
    bool keyGuess = false;
    int tries = 1;
    char a;
    int keyIndex;
    string playerKey;
    string key = generateRandomKey();
    string cipher = generateRandomString(10);
    string decryptedMessage;
    string keyRiddles[4][3] = {{"chocolates", "Usually sweet, but with a bitter side, I am the dark temptation loved by many.", "On Valentine's Day and Christmas, I am a popular gift, and you can find me in gift shops and supermarkets."}, {"adventures", "In books and movies, I can take you anywhere without leaving your seat.", "I can provide excitement and the unknown, many people long for me, but also fear me."}, {"reflection", "I am your mirror image in the water, but you cannot touch me.", "I can show your true face, but also distort under the light."}, {"autombiles", "I have four wheels, usually travel on roads, and am a basic means of transportation in modern society.", "Whether it's going to work or traveling, you can rely on me for a quick arrival."}};
    string playerDecryption;
    string firstRiddle;
    string secondRiddle;

    for (int i = 0; i < 4; i++)
    {
        if (key == keyRiddles[i][0])
        {
            keyIndex = i;
            // find the random key inside the array
        }
    }

    decryptedMessage = decryption(cipher, key);
    // find the decrypted for comparison

    firstRiddle = keyRiddles[keyIndex][1];
    secondRiddle = keyRiddles[keyIndex][2];
    // determine which riddles to display when guessing the key

    cout << "\n";
    cout << "\r";
    cout << "Once upon a time, in the kingdom of Aragonia, there lived a beautiful princess named Sofia. She had long, flowing hair as black as night, and her eyes shone like the brightest stars in the sky. She was kind, gentle, and loved by all who knew her.\n";
    cout << endl;
    cout << "\r";
    cout << "One day, a wicked sorcerer named Zoltar came to Aragonia, seeking to take over the kingdom and enslave its people. He sent two of his most fearsome monsters to kidnap the princess and clocked her in a invincible cage which can only be unlocked with a magical key.\n";
    cout << endl;
    cout << "\r";
    cout << "When Princess Sofia was taken, the people of Aragonia were filled with despair. They knew that only a brave and courageous prince could save her. So, they sent out a call for a hero to come forth and rescue the princess.\n";
    cout << endl;
    cout << "\r";
    cout << "Prince Alexander, a valiant knight, answered the call. He was determined to save Princess Sofia, no matter what dangers lay ahead. Armed with his sword, shield, and courage, he set out to face the monsters, find the magical key and bring the princess back to her kingdom.\n";
    cout << endl;
    cout << "\r";

    cout << "As he made his way through the dark forest, he came upon the dragon Pyro. Help Prince Alexander kill the dragon by finishing the first game! You have three tries.\n";
    cout << "\n";
    cout << "\r";
    cout << "Enter a to continue\n";

    cin >> a;

    player = blockDashMain();
    // first game

    while (!player && tries < 3)
    {
        cout << "You have failed helping Prince Alexander to rescue the princess, enter a to try again!\n";
        cin >> a;
        player = blockDashMain();
        tries += 1;
    }

    if (tries == 3)
    {
        cout << "You have failed to rescue the Princess!\n";
        cout << "\n";
        cout << "GAME OVER\n";
        system("reset");
        return 0;
    }

    tries = 1;

    cout << "Brilliant! You have successfully helped Prince Alexander to kill the first monster. Here is the first riddle for the magical key: ";
    cout << red << firstRiddle << reset << "\n";
    cout << "\n";
    cout << "But the prince's quest was not yet complete. He still had to face the serpent Viper. Get ready!\n";

    player = rotatingStoneMain();
    // second game

    while (!player && tries < 3)
    {
        cout << "You have failed helping Prince Alexander to rescue the princess, enter a to try again!\n";
        cin >> a;
        player = rotatingStoneMain();
        tries += 1;
    }

    if (tries == 3)
    {
        cout << "You have failed to rescue the Princess!\n";
        cout << "\n";
        system("reset");
        return 0;
    }

    tries = 0;

    cout << "You have helped the Prince killed the second monster! Here is the second riddle for the magical key: ";
    cout << red << secondRiddle << reset << "\n";
    cout << "\n";
    cout << "With both riddle obtained, guess code for the magical code to unlock the invincible cage by decrypting the message! You have three tries.\n";

    encryptionMain(key);
    // display the encrypted message

    while (tries < 3 && !keyGuess)
    {
        cin >> playerKey;
        if (tries == 2)
        {
            // check if all tries have been used

            cout << "You have failed to rescue the Princess!\n";
            cout << "\n";
            cout << "GAME OVER\n";
            return 0;
        }
        else if (playerKey == key)
        {
            // if the user enter the correct key

            cout << "You have successfully find the key, please enter the decrypted message: \n";
            cin >> playerDecryption;
            // the user will need to decrypt the message

            if (playerDecryption == decryptedMessage)
            {
                // if the decrypted message is correct the user win and the loop will be ended

                cout << "You have successfully find the key and decrypted the message! \n";
                keyGuess = true;
            }
            else
            {
                // if the decrypted message is wrong the user will still need to try again

                cout << "You got the decrypted message wrong, almost there! \n";
                tries += 1;
            }
        }
        else
        {

            cout << "Not quite, try again!\n";
            tries += 1;
        }
    }

    cout << "\n";

    cout << "With both monsters defeated, Prince Alexander found Princess Sofia and freed her from her captivity. She was overjoyed to be rescued, and they returned to Aragonia together, where they were greeted with cheers and celebration.\n";

    cout << "\n";

    cout << "Prince Alexander was hailed as a hero, and Princess Sofia fell in love with him. They were married in a grand ceremony, and they ruled the kingdom together with wisdom and kindness. And the people of Aragonia lived in peace and prosperity, knowing that their princess was safe and that they had a brave prince to protect them.\n";

    cout << "\n";

    cout << "GAME OVER\n";
}