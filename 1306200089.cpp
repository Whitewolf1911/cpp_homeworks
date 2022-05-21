/*
Ali Ihsan Basoglu
1306200089
Date : 1/12/2020
Development Environment : Visual Studio 2019
*/

#include <iostream>
#include <math.h>
using namespace std;

class Sekiller{
	public:
		void rectangle1(int dimension){
            
            for (int i = 0; i < dimension; i++) {
             
                for (int j = 0; j <= i; j++) {
                    cout << "* ";
                }

                cout << endl;
            }
		
		
		}

        void rectangle2(int dimension) {
            for (int i = 1; i <= dimension; i++) { 

                for (int j = 1; j <= (dimension - i + 1); j++) { 
                    cout << "*";    
                }

                cout << endl;  
            }
        
        }

        void rectangle3(int dimension) {
                       
            int k = 2 * dimension - 2;

            for (int i = 0; i < dimension; i++) {
               
                for (int j = 0; j < k; j++){
                    cout << " ";
                }
       
                k -= 2;
               
                for (int j = 0; j <= i; j++) {
                    
                    cout << "* ";
                }               
                cout << endl;
            }
        }

        void rectangle4(int dimension) {          
            int k = 2 * dimension - 2;
          
            for (int i = 0; i < dimension; i++) {
               
                for (int j = 0; j < k; j++){
                    cout << " ";
                }
               
                k -= 1;
             
                for (int j = 0; j <= i; j++) {                
                    cout << "* ";
                }

                cout << endl;
            }
        
        }

        void rhomb(int dimension) {
            int i, j, k;
            if (dimension > 2 && dimension%2==0) {
                dimension /= 2;
            }
            else if (dimension > 2 && dimension % 2 == 1) {
                dimension += 1;
                dimension /= 2;
            }
            for (i = 1; i <= dimension; i++)

            {

                for (j = 0; j < (dimension - i); j++) {
                    cout << " ";
                }                   

                for (j = 1; j <= i; j++) {
                    cout << "*";
                }

                for (k = 1; k < i; k++) {
                    cout << "*";
                }
                cout << endl;

            }

            for (i = dimension - 1; i >= 1; i--)

            {

                for (j = 0; j < (dimension - i); j++){
                    cout << " ";
                }

                for (j = 1; j <= i; j++){
                    cout << "*";
                }

                for (k = 1; k < i; k++){
                    cout << "*";
                }

                cout << endl;

            }
            cout << endl;
        
        }

        void circle(int yaricap)
        {            
            float uzaklik;
            if (yaricap > 2 && yaricap % 2 == 0) {
                yaricap /= 2;
            }
            else if (yaricap > 2 && yaricap % 2 == 1) {
                yaricap += 1;
                yaricap /= 2;
            }
            for (int i = 0; i <= 2 * yaricap; i++) {
               
                for (int j = 0; j <= 2 * yaricap; j++) {
                    uzaklik = sqrt((i - yaricap) * (i - yaricap) + (j - yaricap) * (j - yaricap));
                                     
                    if (uzaklik > yaricap - 0.5 && uzaklik < yaricap + 0.5)
                        cout << "*";
                    else
                        cout << " ";
                }
                cout << endl;
            }

        }


};


int main()
{
    int option = 0;
    int dimension = 0;

    Sekiller sekilObjesi;
    while (true) {

        cout << "ENTER YOUR CHOICE" << endl;
        cout << "1. Rectangle1" << endl;
        cout << "2. Rectangle2" << endl;
        cout << "3. Rectangle3" << endl;
        cout << "4. Rectangle4" << endl;
        cout << "5. Rhomb" << endl;
        cout << "6. Circle" << endl;
        cout << "7. Close Application" << endl;

        cin >> option;
        if (option == 7) {
            exit(0);
        }
        cout << "Enter the dimension you want " << endl;
        cin >> dimension;
        cout << "\n";

        switch (option)
        {
        case 1:
            sekilObjesi.rectangle1(dimension);
            break;
        case 2:
            sekilObjesi.rectangle2(dimension);
            break;
        case 3:
            sekilObjesi.rectangle3(dimension);
            break;
        case 4:
            sekilObjesi.rectangle4(dimension);
            break;
        case 5:
            sekilObjesi.rhomb(dimension);
            break;
        case 6:
            sekilObjesi.circle(dimension);
            break;
        }

    }
}