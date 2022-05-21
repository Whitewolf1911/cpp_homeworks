/*

Ali Ihsan Basoglu
1306200089
Date : 17/01/2021
Development Environment: Visual Studio 2019

To run the file you need the change the text.txt in line 30 to whatever file / challenge you have.
Challenge 4 is the as far as i could get

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
    
    vector <char> degisken;
    vector <string> deger;
    int index;
    fstream newfile;
    double sonuc = 0;
    newfile.open("text.txt", ios::in); //dosyayi acma
    if (newfile.is_open()) {   //dosya acikmi kontrolu
        string tp;
        while (getline(newfile, tp)) { //satir satir oku
            tp.erase(remove_if(tp.begin(), tp.end(), isspace), tp.end()); //bosluklari silme
            int i = 0;
            while (i < tp.length()) {
                char c = tp.at(i);
                if (c == '=') {
                    string d = "";
                    c = tp.at(++i);
                    if (c > 64 && c < 91) {

                        
                        vector <char>::iterator it = find(degisken.begin(), degisken.end(), c);

                        if (it != degisken.end())
                            index = distance(degisken.begin(), it);
                        sonuc = stod(deger.at(index));
                        c = tp.at(++i);

                        do {
                            c = tp.at(i);
                            if (c == '+') {
                                c = tp.at(++i);
                                vector <char>::iterator it = find(degisken.begin(), degisken.end(), c);

                                if (it != degisken.end())
                                    index = distance(degisken.begin(), it);
                                sonuc += stod(deger.at(index));

                            }
                            else if (c == '-') {
                                c = tp.at(++i);
                                vector <char>::iterator it = find(degisken.begin(), degisken.end(), c);

                                if (it != degisken.end())
                                    index = distance(degisken.begin(), it);
                                sonuc -= stod(deger.at(index));

                            }
                            else if (c == '*') {
                                c = tp.at(++i);
                                vector <char>::iterator it = find(degisken.begin(), degisken.end(), c);

                                if (it != degisken.end())
                                    index = distance(degisken.begin(), it);
                                sonuc *= stod(deger.at(index));

                            }
                            else if (c == '/') {
                                c = tp.at(++i);
                                vector <char>::iterator it = find(degisken.begin(), degisken.end(), c);

                                if (it != degisken.end())
                                    index = distance(degisken.begin(), it);
                                sonuc /= stod(deger.at(index));

                            } i++;
                        } while (i < tp.length() - 1);

                        ofstream OutFile("challenge.out");                       
                        OutFile << sonuc;                    
                        OutFile.close();
                    }
                    else {
                        while (i < tp.length() - 1) {
                            d += c;
                            c = tp.at(++i);
                        }
                        d += tp.at(i);
                        deger.push_back(d);
                    }
                }
               
                else {
                    degisken.push_back(c);
                }
                i++;
                
            }
           
        }
        newfile.close(); 
    }
}