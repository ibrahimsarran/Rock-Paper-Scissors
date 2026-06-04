// Project 1: Rock, Paper, Scissors

#include <cstdlib>
#include <iostream>
using namespace std;

enum enGameChoice{Rock = 1, Paper = 2, Scissors = 3};
enum enWinner{ Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short roundNumber = 0;
    enGameChoice playerChoice;
    enGameChoice computerChoice;
    string roundWinner;
};

struct stGameResult
{
    short gameRounds;
    short playerWonTimes;
    short computerWonTimes;
    short DrawTimes;
    enWinner finalWinner;
};

short readRounds()
{
    short roundNum = 0;

    do
    {
        cout << "How many rounds 1 to 10 ? \n";
        cin >> roundNum;
    } while (roundNum < 1 || roundNum>10);

    return roundNum;
}

enGameChoice readPlayerChoice()
{
    short playerChoice = 0;
    do
    {
        cout << "\nChoose: [1]: Rock, [2]: Paper, [3]: Scissors. ?" << endl;
        cin >> playerChoice;
    } while (playerChoice < 1 || playerChoice>3);

    return (enGameChoice)playerChoice;
}

enGameChoice getComputerChoice(int from, int to)
{
    short computerChoice = 0;

    computerChoice = rand() % (to - from + 1) + from;

    return (enGameChoice)computerChoice;
}


enWinner whoWonTheRound(stRoundInfo roundInfo)
{

    if (roundInfo.playerChoice == roundInfo.computerChoice)
    {
        system("color 6F");
        return enWinner::Draw;
    }

    switch (roundInfo.computerChoice)
    {
    case enGameChoice::Rock:
        if (roundInfo.playerChoice == enGameChoice::Scissors)
        {
            system("color 4F");
            cout << "\a";
            return enWinner::Computer;
           
        }
        break;
        

    case enGameChoice::Paper:
        if (roundInfo.playerChoice == enGameChoice::Rock)
        {
            system("color 4F");
            cout << "\a";
            return enWinner::Computer;
        }
        break;
       

    case enGameChoice::Scissors:
        if (roundInfo.playerChoice == enGameChoice::Paper)
        {
            system("color 4F");
            cout << "\a";
            return enWinner::Computer;
        }
        break;
        

        
    }
    system("color 2F");
    return enWinner::Player;

    
}

string choiceName(enGameChoice choice)
{
    switch (choice)
    {
    case enGameChoice::Rock:
        return "Rock";
        break;

    case enGameChoice::Paper:
        return "Paper";
        break;

    case enGameChoice::Scissors:
        return "Scissors";
        break;
    }


}
string winnerName(enWinner winner)
{
    switch (winner)
    {
    case enWinner::Computer:
        return "Computer";
        break;

    case enWinner::Player:
        return "PLayer";
        break;

    case enWinner::Draw:
        return "No Winner";
        break;
    }

    
}

void showGameOverScreen()
{
    cout << "\t";
}
void showFinalGameResults(stGameResult gameResults)
{

}

void resetGame()
{
    system("color 0F");
    system("cls");
}

void startGame()
{
    short roundNum = readRounds();
    stRoundInfo roundInfo;
    cout << "\n----------Round[" << roundInfo.roundNumber << "]--------------\n\n";
    for (int i = 1; i <= roundNum; i++)
    {
        
        roundInfo.playerChoice = readPlayerChoice();
        roundInfo.computerChoice = getComputerChoice(1, 3);
        roundInfo.roundNumber = i;
        roundInfo.roundWinner = winnerName(whoWonTheRound(roundInfo));

        
        cout << "Player1  Choice : " << choiceName(roundInfo.playerChoice)   << endl;
        cout << "Computer Choice : " << choiceName(roundInfo.computerChoice) << endl;
        cout << "Round Winner    : [" << roundInfo.roundWinner    <<"]" << endl;
        cout << "\n----------------------------------";
        
    }
    resetGame();

}



int main()
{

    srand((unsigned)time(NULL));
    startGame();

    return 0;
}
