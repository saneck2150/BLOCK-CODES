#include <iostream>
#include <string>
#include <bitset>
#include <cstdlib> 
#include <random>

#define NUMB_OF_REDUN_BITS 8 

using namespace std;

// Function reads integers from file and send them as STRING msg


string parityAdd(string dataToEncode)
{
    string dataWithParit = "";
    for (int i = 0; i < dataToEncode.size(); i++)
    {
        dataWithParit += dataToEncode[i];
        for (int j = 0; j < NUMB_OF_REDUN_BITS; j++)
        {
            dataWithParit += '0';
        }
         // Parity bits add
    }
    return dataWithParit;
}

// Function transforms mgs to bits and adds parity bits


string errSimulation(string msgWithParity)
{
    random_device rd;
    mt19937 gen(rd());

    // Define a distribution range for the random numbers
    uniform_int_distribution<int> dis(1, 100);

    // Generate and print a random number
    int randomNumber = dis(gen);

    int errChance = 5; // Err chance to appear

    for (int i = 0; i < msgWithParity.size(); i++)
    {
        if ((randomNumber) <= errChance)
        {
            msgWithParity[i] = (msgWithParity[i] == '0') ? '1' : '0';  // Bit value change
            cout << "Error generated on position " << i+1 << endl;
           
        }
        randomNumber = dis(gen);
    }
    cout << "Msg with error  " << msgWithParity << endl;
    return msgWithParity;
}

// Simulation of an err with bit value change


bool bitCheck(string msgWithParity, int& sumOfFalseMsgs)
{
    for (int i = 0; i < msgWithParity.size(); i += NUMB_OF_REDUN_BITS + 1) 
    {


        for (int j = i+1; j < NUMB_OF_REDUN_BITS + 1 + i; j++)
        {
            if (msgWithParity[j] == '1')
            {
                msgWithParity[j] = '?';
                cout << "Check for err:\t" << msgWithParity << endl;
                cout << "\n";
                cout << "ERROR WAS FOUND ON POSITION " << j+1 << ", RESENDING A MSG" << endl;
                cout << "\n";
                return false;
            }
        }
        
    }
    for (int i = 0; i < msgWithParity.length(); i += NUMB_OF_REDUN_BITS + 1)
    {
        if (msgWithParity[i] == '0')
        {
            sumOfFalseMsgs++;
            cout << endl;
        }
    }

    return true;
}

// Looking for an err in parity bits


string aknolegmentAndRepeate(string msgWithParity, int& iterationNumb, int& sumOfFalseMsgs)
{
    while (!bitCheck(errSimulation(msgWithParity),sumOfFalseMsgs))
    {
        iterationNumb++;
    }
    return msgWithParity;
}

// Send of an msg repeats until it wont have any err

int main()
{
    int iterationNumb = 1;
    string dataToEncode = "1111111111";
    int sumOfIterations = 0;
    int sumOfFalseMsgs = 0;
    double avgIterations = 0;

    for (int i = 0; i < 1000; i++)
    {

        string msgWithParity = parityAdd(dataToEncode);

        cout << "Msg sent:\t" << msgWithParity << endl;

        string pureMsg = aknolegmentAndRepeate(msgWithParity, iterationNumb, sumOfFalseMsgs); // Repeating proces while error appears

        sumOfIterations += iterationNumb;

        cout << "iteration numb:\t" << iterationNumb << endl;

        iterationNumb = 1;
       
        
    }

    avgIterations = (double) sumOfIterations / 1000;

    cout << "sumOfIterations " << sumOfIterations << endl;
    cout << "sumOfFalseMsgs "  << sumOfFalseMsgs << endl;
    cout << "avgIterations "    << avgIterations << endl;
}