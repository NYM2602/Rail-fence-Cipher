//This is a program to cipher and decipher using the rail-fence cipher
//Rail-fence cipher is a simple shuffeling cipher that chooses a key
//that is the number of rows or rails and arranges the message in a zigzag pattern
//it then takes the letters starting with the first row
//You can choose the key to use for the cipher

#include <iostream>
#include <string>
using namespace std;
//Functions declaration
bool isint(string num);
char* rail_cipher(string txt,int key);
char* rail_decipher(string txt, int key);
//main program
int main()
{
    while (true){
        //print a welcome message and menu
        cout<<"***Welcome to this Rail-Fence ciphering and deciphering program!***"<<endl;
        string choice="`";
        cout<<"A) Cipher"<<endl;
        cout<<"B) Decipher"<<endl;
        cout<<"C) Exit"<<endl;
        cout<<"Please enter your choice: ";
        getline(cin,choice);

        string txt;
        int key;

        if(tolower(choice[0])=='a'){
            //input the original text
            cout<<"Please enter the text you want to be ciphered:"<<endl;
            getline(cin,txt);
            //input the cipher key and validate that it is a number
            while (true){
                cout<<"Please enter the key of the Rail-Fence Cipher that is 2 or more:"<<endl;
                string key_str;
                cin>>key_str;
                cin.get();//prevent error from the newline character
                if (isint(key_str)&&stoi(key_str)>1){
                    key = stoi(key_str);
                    break;
                }
                else{
                    cout<<"This is not a valid number"<<endl;
                }
            }
            cout<<"Here is the ciphered text:"<<endl;
            cout<<rail_cipher(txt,key)<<endl;
        }

        else if (tolower(choice[0])=='b'){
            //input the original text
            cout<<"Please enter the text you want to be deciphered:"<<endl;
            getline(cin,txt);
            //input the cipher key and validate that it is a number
            int key;
            while (true){
                cout<<"Please enter the key of the Rail-Fence Cipher that is 2 or more:"<<endl;
                string key_str;
                cin>>key_str;
                cin.get(); //prevent error from the newline character
                if (isint(key_str)&&stoi(key_str)>1){
                    key = stoi(key_str);
                    break;
                }
                else{
                    cout<<"This is not a valid number"<<endl;
                }
            }
            cout<<"Here is the deciphered text:"<<endl;
            cout<<rail_decipher(txt,key)<<endl;
        }
        else if (tolower(choice[0])=='c'){
            cout<<"Exit"<<endl;
            break;
        }
        else{
            cout<<"This is not a valid choice"<<endl;
        }
    }

}
//function to check if a number is and integer
bool isint(string num){
    int len = num.size();
    for (int i=0;i<len;i++){
        if (isdigit(num[i])==false){
            return false;
        }
    }
    return true;
}
//rail-fence ciphering function
char* rail_cipher(string txt,int key){
    int len = txt.size();
    char first_stage[key][len];
    int cursor = 0, sign = -1;
    for(int i=0;i<len;i++){
        for(int j=0;j<key;j++){
            if (j==cursor){
                first_stage[j][i] = txt[i];
            }
            else if (j!= cursor){
                first_stage[j][i] = '`';
            }
        }
        if (cursor==0 || cursor == key-1){
            sign *= -1;
        }
        cursor += sign;
    }
    int index = 0;
    char* second_stage = new char[len+1];
    for (int j=0;j<key;j++){
        for (int i=0;i<len;i++){
            if (first_stage[j][i] != '`'){
                second_stage[index] = first_stage[j][i];
                index++;
            }
        }
    }
    second_stage[index] = 0;
    return second_stage;
}
//rail-fence deciphering function
char* rail_decipher(string txt, int key){
    int len = txt.size(),cursor=0,index=0;
    int max_gap = (key-2)*2 + 1, big_gap = max_gap, small_gap = 0;
    char first_stage[key][len+max_gap];
    for (int j=0;j<key;j++){
        int flag = 1;
        int i = cursor;
        for (int k=0;k<cursor;k++){
            first_stage[j][k] = '`';
        }
        cursor++;
        while (i<len){
            first_stage[j][i] = txt[index];
            if (flag == 1){
                if (big_gap!=0){
                    for(int k=i+1; k < i+big_gap+1; k++){
                        first_stage[j][k] = '`';
                    }
                    i += big_gap + 1;
                    index++;
                }
            }
            else if (flag == -1){
                if (small_gap!=0){
                    for (int k=i+1; k < i+small_gap+1; k++){
                        first_stage[j][k] = '`';
                    }
                    i += small_gap + 1;
                    index++;
                }
            }
            flag *= -1;


        }
        if (big_gap == 1){
                big_gap--;
            }
            else{
                big_gap -= 2;
            }
            if (small_gap == 0){
                small_gap++;
            }
            else{
                small_gap += 2;
            }
    }

    char* second_stage = new char[len + 1];
    index = 0;
    for (int i=0;i<len;i++){
        for (int j=0;j<key;j++){
            if (first_stage[j][i] != '`'){
                second_stage[index] = first_stage[j][i];
                index++;
                break;
            }
        }
    }
    second_stage[index] = 0;
    return second_stage;
}

