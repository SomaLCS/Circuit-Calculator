#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


void SetFormula(string& formula)
{
    formula.clear();

    cout << "Enter circuit formula: " ;
    cin >> formula;
    cout << endl;
}

void GenerateFormula(string& formula)
{
    string Decimal = ".0" ;

    srand(time(0));

    formula.clear(); // clear any preoccupied formula to generate new formula

    int TotalResistor = 3 + ( rand() % 6 ) ; // Total resistors ranged from 3 to 8
    int Parallel = 0;
    char Sign[2] = {'+', '/'};

    for(int i = 0; i < TotalResistor ; i++)
    {
        formula += to_string(1 + (rand() % 100 )) ;     //generate number between 1 to 100
        formula += Decimal ;                            //add .0 to every resistance

        char x = Sign[rand() % 2] ;                     //gives off either 1 or 0

        if(x == '/')
        {
            Parallel++;
        }

        if(Parallel <= 2)   // ensure parallel circuit is no more than 3
        {
            formula += x ;
        }

        else
        {
            formula += '+';
            Parallel = 0;
        }


    }

    formula.resize(formula.size() - 1);

}

void DisplayFormula(string& formula)
{
    if(formula == "0")
    {
        cout << "No formula! Please generate a formula first. \n" << endl;
    }

    else cout << "Circuit formula is " << formula << "\n" << endl;
}

double CalculateFormula(string& formula)
{
    signed PlusSign = count (formula.begin(), formula.end(), '+'); //count the number of '+' signs

    string StoreSign[PlusSign + 1];

    for(int x = 0; x <= PlusSign ; x++)
    {
            StoreSign[x] = formula.substr(0, formula.find('+')); //copy till the first '+' sign to substring
            formula.erase(0, formula.find('+') + 1); //erase original stored values
    }

    vector <double> Parallel;
    double Temp = 0;
    double Total = 0;

    for (int y = 0; y <= PlusSign; y++)
    {
        if (StoreSign[y].find('/') != string::npos) //solving circuit in parallel / *npos* is used to check any matches
        {
            signed DivideSign = count (StoreSign[y].begin(), StoreSign[y].end(), '/' ); //count the number of '/' signs

                for (int z = 0; z <= DivideSign; z++)
                {
                    Parallel.push_back(stod(StoreSign[y].substr(0, StoreSign[y].find('/'))));
                    StoreSign[y].erase (0, StoreSign[y].find('/') + 1);
                }

                for (int j = 0; j<= DivideSign; j++) //convert to 1/R and sum up
                    Temp += (1/Parallel[j]);

            Total += (1/Temp); //sum of total parallel resistance

        }

        else //convert numerical characters to double then sum up
            Total += stod(StoreSign[y]);

        Parallel.clear(); //remove all the data stored in vector

        Temp = 0; //initialize temp to zero
    }

    return Total;
}


void PlayQuiz(string& formula)
{
    double Answer = 0;
    int Correct = 0;

    cout << "Quiz is selected." << endl;

    for(int i = 1; i <= 5; i++)
    {
        GenerateFormula(formula);
        cout << "Circuit " << i << " formula is " << formula << endl;
        cout << "Enter circuit " << i << " total resistance: ";
        cin >> Answer;

        cout << endl;

        double Value = CalculateFormula(formula);

        if(fabs(Value - Answer) < 0.1f)     //compare double value as there is decimal point
        {
            Correct++;                      //if satisfy then correct answer increase
        }

    }

    cout << "Your mark for this quiz is " << Correct << "/5 \n" << endl;

    formula = "0";
}

int main()
{
    int choice;
    string formula = "0";

    cout << "***Welcome to Total Resistance Calculator Program***" << endl;
    cout << "1. Enter circuit formula." << endl;
    cout << "2. Generate circuit randomly." << endl;
    cout << "3. Show circuit formula." << endl;
    cout << "4. Calculate total resistance." << endl;
    cout << "5. Play a quiz." << endl;

    do
    {
        cout << "Your choice [1-5] : " ;
        cin >> choice;

        switch(choice)
        {
            case 1 :
                SetFormula(formula);
                break;

            case 2 :
                GenerateFormula(formula);
                cout << "Random circuit is generated. \n" << endl;
                break;

            case 3 :
                DisplayFormula(formula);
                break;

            case 4 :
                cout << "Circuit total resistance is " <<  fixed << setprecision(1) << CalculateFormula(formula) << " ohm. \n"<< endl;
                break;

            case 5 :
                PlayQuiz(formula);
                break;

            default :
                cout << "Invalid input!" << endl;
                cout << "Program will be terminated." << endl;
                choice = -1;

        }
    }while(choice!= -1);

    cout << endl;

}
