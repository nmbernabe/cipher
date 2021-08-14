//
//  main.cpp
//  cipher
//
//  Created by Niles Bernabe on 8/3/21.
//
//BCDEFGHIJKLMNOPQRSTUVWXYZA
#include <iostream>
#include <algorithm>
#include <string>


void toLowerCase(std::string &plainT) { //changes phrase or word to all upper case
    for (int i = 0; i < plainT.length(); i++) {
        if (plainT[i] >= 'A' && plainT[i] <= 'Z')
            plainT[i] += ('a' - 'A');
    }
}

void toUpperCase(std::string &cipherT) { //changes phrase or word to all lower case
    for (int i = 0; i < cipherT.length(); i++) {
        if (cipherT[i] >= 'a' && cipherT[i] <= 'z')
            cipherT[i] -= ('a' - 'A');
    }
}

void removeSpaces(std::string &plainT) { //removes spaces from phrase
    int count = 0;
    for (int i = 0; i < plainT.length(); i++) {
        if (plainT[i] != ' ')
            plainT[count++] = plainT[i];
        plainT[count] = '\0';
    }
}

void generateKeyTable(std::string key, char keyT[][5]) { //generates key table in the manner specified for playfair j to i substitution
    int count = 0;
    int index = 0;
    int dictionary[25] = {0}; //stores what characters have alreadybeen included in table
    for (int i = 0; i < key.length(); i++) { //fills keytable with key word and removes key characters from dictionary
        if (key[i] - 'A' < 9) {
            if (dictionary[key[i] - 'A'] == 0) {
                keyT[(count / 5)][(count % 5)] = key[i];
                count++;
                
                dictionary[key[i] - 'A'] = 1;
            }
        }
        else {
            if (dictionary[key[i] - 'A' - 1] == 0) {
                keyT[(count / 5)][(count % 5)] = key[i];
                count++;
                
                dictionary[key[i] - 'A' - 1] = 1;
            }
        }
    }
    
    for (int k = 0; k < 25; k++) {
        if (dictionary[k] == 0) {
            index = k;
            break;
        }
    }
    
    for (int i = 0; i < 5; i ++) { //fills in rest of table with the rest of the dictionary
        for (int j = 0; j < 5; j++) {
            if (i == count / 5 && j >= count % 5) {
                if (index < 9) {
                    keyT[i][j] = (char)('A' + index);
                    dictionary[index] = 1;
                }
                else {
                    keyT[i][j] = (char)('A' + index + 1);
                    dictionary[index] = 1;
                }
                for (int k = 24; k >= 0; k--) {
                    if (dictionary[k] == 0) {
                        index = k;
                    }
                }
            }
            else if (i > count / 5) {
                if (index < 9) {
                    keyT[i][j] = (char)('A' + index);
                    dictionary[index] = 1;
                }
                else {
                    keyT[i][j] = (char)('A' + index + 1);
                    dictionary[index] = 1;
                }
                
                for (int k = 24; k >= 0; k--) {
                    if (dictionary[k] == 0) {
                        index = k;
                    }
                }
            }
        }
    }
}

void searchKeyT(char keyT[5][5], char a, char b, int arr[]) { //searches given key table for any given two characters, returns row and column of both characters within table array is [a column, a row, b column, b row]
    if (a == 'j')
        a = 'i';
    else if (b == 'j')
        b = 'i';
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (keyT[i][j] == a) {
                arr[0] = i;
                arr[1] = j;
            }
            else if (keyT[i][j] == b) {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
}

void caesar() { //caesar option
    std::string direction;
    int key;
    char ch;
    std::string plainText;
    std::string cipherText;
    
    std::cout << "Encrypt or Decrypt? "; //multiple inputs accepted
    std::cin >> direction;
    std::cout <<"Enter key: ";
    std::cin >> key; //numerical value that alphabet will be shifted by
    key = key % 26;
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    
    if (direction.compare("Encrypt") == 0 || direction.compare("encrypt") == 0 || direction.compare("e") == 0) {
        std::cout << "Enter plain text: ";
        std::getline(std::cin, plainText);
        toLowerCase(plainText);
        cipherText = plainText;

        //compute cipherText
        
        for (int i = 0; i < plainText.length(); i++) {
            ch = plainText[i];
    
            if (ch >= 'a' && ch <= 'z') {
                ch = ch + key;
                
                if (ch > 'z') {
                    ch = ch - 'z' + 'a' - 1;
                }
                cipherText[i] = ch - ('a' - 'A');
            }
        }
        
        std::cout <<"Cipher Text: ";
        std::cout << cipherText;
        std::cout <<"\n";
    }
    else if (direction.compare("Decrypt") == 0 || direction.compare("decrypt") == 0 || direction.compare("d") == 0) {
        std::cout << "Enter cipher text: ";
        std::getline(std::cin, cipherText);
        toUpperCase(cipherText);
        plainText = cipherText;
        
        //compute plainText;
        for (int i = 0; i < cipherText.length(); i++) {
            ch = cipherText[i];
            
           if (ch >= 'A' && ch <= 'Z') {
                ch = ch - key;
                if (ch < 'A') {
                    ch = ch + 'Z' - 'A' + 1;
                }
                plainText[i] = ch + ('a' - 'A');
            }
        }
        
        std::cout <<"Plain Text: ";
        std::cout << plainText;
        std::cout <<"\n";
    }
    else {
        std::cout <<"Invalid Input.\n";
    }
}

void substitution() {
    std::string direction;
    std::string plainText;
    std::string cipherText;
    char ch;
    std::string key;
    
    std::cout << "Encrypt or Decrypt? "; //multiple variations accepted
    std::cin >> direction;
    std::cout <<"Enter key: ";
    std::cin >> key; //key is an entire 26 character alphabet
    toUpperCase(key);
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    
    if (direction.compare("Encrypt") == 0 || direction.compare("encrypt") == 0 || direction.compare("e") == 0) {
        std::cout <<"Enter plain text: ";
        std::getline(std::cin, plainText);
        toLowerCase(plainText);
        cipherText = plainText;
        
        //compute ciphertext
        for (int i = 0; i < plainText.length(); i++) {
            ch = plainText[i];
            
            if (ch >= 'a' && ch <= 'z') {
                cipherText[i] = key[ch - 'a'];
            }
        }
        
        std::cout <<"Cipher Text: ";
        std::cout << cipherText;
        std::cout <<"\n";
    }
    else if (direction.compare("Decrypt") == 0 || direction.compare("decrypt") == 0 || direction.compare("d") == 0) {
        std::cout <<"Enter cipher text: ";
        std::getline(std::cin, cipherText);
        toUpperCase(cipherText);
        plainText = cipherText;
        
        //compute ciphertext
        for (int i = 0; i < plainText.length(); i++) {
            ch = cipherText[i];
            int index = 0;
            
            if (ch >= 'A' && ch <= 'Z') {
                for (int j = 0; j < key.length(); j++) {
                    if (key[j] == ch) {
                        index = j;
                        break;
                    }
                }
                plainText[i] = 'a' + index;
            }
        }
        
        std::cout <<"Plain Text: ";
        std::cout << plainText;
        std::cout <<"\n";
    }
    else {
        std::cout <<"Invalid Input.\n";
    }
}
void playfair() { //playfair option
    std::string direction;
    std::string key;
    char keyT[5][5];
    int buffer[4];
    std::string plainText;
    std::string cipherText;
    
    std::cout << "Encrypt or Decrypt? "; //multiple variations of input validated
    std::getline(std::cin, direction);
    std::cout <<"Enter key: ";
    std::getline(std::cin, key); //key given with no j can be any word or phrase
    toUpperCase(key);
    key.erase(std::remove(key.begin(), key.end(), ' '), key.end());
    generateKeyTable(key, keyT); //populates key matrix
    
    for (int i = 0; i < 5; i ++) {
        for (int j = 0; j < 5; j++) {
            std::cout <<keyT[i][j];
        }
        std::cout <<"\n";
    }

    
    if (direction.compare("Encrypt") == 0 || direction.compare("encrypt") == 0 || direction.compare("e") == 0) {
        std::cout << "Enter plain text: ";
        std::getline(std::cin, plainText);
        toUpperCase(plainText);
        plainText.erase(std::remove(plainText.begin(), plainText.end(), ' '), plainText.end());
        
        if (plainText.length() % 2 != 0) {
            plainText.push_back('Z');
        }
        cipherText = plainText;
        
        for (int i = 0; i < plainText.length(); i += 2) {
            searchKeyT(keyT, plainText[i], plainText[i + 1], buffer);
            
            if (buffer[0] == buffer[2]) {
                cipherText[i] = keyT[buffer[0]][(buffer[1] + 1) % 5];
                cipherText[i + 1] = keyT[buffer[0]][(buffer[3] + 1) % 5];
            }
            else if (buffer[1] == buffer[3]) {
                cipherText[i] = keyT[(buffer[0] + 1) % 5][buffer[1]];
                cipherText[i + 1] = keyT[(buffer[2] + 1) % 5][buffer[1]];
            }
            else {
                cipherText[i] = keyT[buffer[0]][buffer[3]];
                cipherText[i + 1] = keyT[buffer[2]][buffer[1]];
            }
        }
        
        std::cout <<"Cipher Text: ";
        std::cout << cipherText;
        std::cout <<"\n";
    }
    else if (direction.compare("Decrypt") == 0 || direction.compare("decrypt") == 0 || direction.compare("d") == 0) {
        std::cout << "Enter cipher text: ";
        std::getline(std::cin, cipherText);
        
        plainText = cipherText;
        
        for (int i = 0; i < cipherText.length(); i += 2) {
            searchKeyT(keyT, cipherText[i], cipherText[i + 1], buffer);
            
            if (buffer[0] == buffer[2]) {
                if (buffer[1] - 1 >= 0) {
                    plainText[i] = keyT[buffer[0]][(buffer[1] - 1) % 5];
                }
                else {
                    plainText[i] = keyT[buffer[0]][4];
                }
                if (buffer[3] - 1 >= 0) {
                    plainText[i + 1] = keyT[buffer[2]][(buffer[3] - 1) % 5];
                }
                else {
                    plainText[i + 1] = keyT[buffer[2]][4];
                }
            }
            else if (buffer[1] == buffer[3]) {
                if (buffer[0] - 1 >= 0) {
                    plainText[i] = keyT[(buffer[0] - 1) % 5][buffer[1]];
                }
                else {
                    plainText[i] = keyT[4][buffer[1]];
                }
                if (buffer[2] - 1 >= 0) {
                    plainText[i + 1] = keyT[(buffer[2] - 1) % 5][buffer[1]];
                }
                else {
                    plainText[i + 1] = keyT[4][buffer[1]];
                }
            }
            else {
                
                plainText[i] = keyT[buffer[0]][buffer[3]];
                plainText[i + 1] = keyT[buffer[2]][buffer[1]];
            }
        }
        
        toLowerCase(plainText);
        
        std::cout <<"Plain Text: ";
        std::cout << plainText;
        std::cout <<"\n";
    }
    else {
        std::cout <<"Invalid Input.\n";
    }
}

void vigenere() { //vigenere option
    std::string direction;
    std::string key;
    std::string plainText;
    std::string cipherText;
    
    std::cout << "Encrypt or Decrypt? ";
    std::getline(std::cin, direction); //multiple input options
    std::cout <<"Enter key: ";
    std::getline(std::cin, key); //key given as any word or phrase
    toUpperCase(key);
    key.erase(std::remove(key.begin(), key.end(), ' '), key.end());

    if (direction.compare("Encrypt") == 0 || direction.compare("encrypt") == 0 || direction.compare("e") == 0) {
        std::cout << "Enter plain text: ";
        std::getline(std::cin, plainText);
        plainText.erase(std::remove(plainText.begin(), plainText.end(), ' '), plainText.end());
        toUpperCase(plainText);
        cipherText = plainText;

        //compute cipherText
        int keyInd = 0;
        
        for (int i = 0; i < plainText.length(); i++) {
            char ch = plainText[i];
            cipherText[i] = (ch + key[keyInd] - 2 * 'A') % 26 + 'A'; //shifts cipher text
            keyInd = (keyInd + 1) % key.length();
        }
        
        std::cout <<"Cipher Text: ";
        std::cout << cipherText;
        std::cout <<"\n";
    }
    else if (direction.compare("Decrypt") == 0 || direction.compare("decrypt") == 0 || direction.compare("d") == 0) {
        std::cout << "Enter cipher text: ";
        std::getline(std::cin, cipherText);

        plainText = cipherText;
        
        //compute plainText;
        int keyInd = 0;
        for (int i = 0; i < cipherText.length(); i++) {
            char ch = cipherText[i];
            plainText[i] = (ch - key[keyInd] + 26) % 26 + 'a';
            keyInd = (keyInd + 1) % key.length();
        }
        
        std::cout <<"Plain Text: ";
        std::cout << plainText;
        std::cout <<"\n";
    }
    else {
        std::cout <<"Invalid Input.\n";
    }
}

//plaintext given in lowercase
//ciphertext given in uppercase
int main(int argc, const char * argv[]) { //main loop menu
    int option = 1;
    while (option != 0) {
        std::cout << "Choose cipher: \n";
        std::cout << "  1: Caesar Cipher \n";
        std::cout << "  2: Substitution Cipher \n";
        std::cout << "  3: Playfair Cipher \n";
        std::cout << "  4: Vigenere Cipher \n";
        std::cout << "  0: Quit \n";
        std::cin >> option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        
        do {
            if (option == 1 ) {
                caesar();
            }
            else if (option == 2) {
                substitution();
            }
            else if (option == 3) {
                playfair();
            }
            else if (option == 4) {
                vigenere();
            }
            else if (option == 0) {
                return 0;
            }
            else {
                std::cout <<"Invalid Input.\n";
                break;
            }
        } while (0);
    }
    
    return 0;
}
