// Project 1: Rock, Paper, Scissors
#include <cstdlib>
#include <iostream>
using namespace std;

enum enGameChoice { Rock = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short roundNumber = 0;
    enGameChoice playerChoice = enGameChoice::Rock;
    enGameChoice computerChoice = enGameChoice::Rock;
    enWinner roundWinner = enWinner::Draw;
};

struct stGameResult
{
    short gameRounds = 0;
    short playerWonTimes = 0;
    short computerWonTimes = 0;
    short DrawTimes = 0;
    string finalWinner = "";
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
    cout << "\t\t\t------------------------------------\n\n";

    cout << "\t\t\t       +++ G a m e O v e r +++      \n\n";

    cout << "\t\t\t------------------------------------\n  ";
}

void showFinalGameResults(stGameResult gameResults)
{
    cout << "\n\t\t------------------[Game Results]------------------\n\n";
    cout << "\t\tplayerWonTimes   : " << gameResults.playerWonTimes << endl;
    cout << "\t\tcomputerWonTimes : " << gameResults.computerWonTimes << endl;
    cout << "\t\tDrawTimes        : " << gameResults.DrawTimes << endl;
    cout << "\t\tfinalWinner      : " << gameResults.finalWinner << endl;;
    cout << "\n\t\t--------------------------------------------------\n";
}

bool resetScreen()
{
    char yesNo = 'a';
    cout << "Do you want to play again? ";
    cin >> yesNo;
    if (yesNo == 'Y' || yesNo == 'y')
    {
        system("color 0F");
        system("cls");
        return true;
    }
    else
        return false;

}

void startGame()
{
    short roundNum = readRounds();
    stGameResult result;
    stRoundInfo roundInfo;
    for (int i = 1; i <= roundNum; i++)
    {

        roundInfo.playerChoice = readPlayerChoice();
        roundInfo.computerChoice = getComputerChoice(1, 3);
        roundInfo.roundNumber = i;
        roundInfo.roundWinner = whoWonTheRound(roundInfo);

        cout << "\n----------Round[" << roundInfo.roundNumber << "]--------------\n\n";
        cout << "Player1  Choice : " << choiceName(roundInfo.playerChoice) << endl;
        cout << "Computer Choice : " << choiceName(roundInfo.computerChoice) << endl;
        cout << "Round Winner    : [" << winnerName(roundInfo.roundWinner) << "]" << endl;
        cout << "\n----------------------------------\n\n";

        if (roundInfo.roundWinner == enWinner::Computer)
            result.computerWonTimes++;

        else if (roundInfo.roundWinner == enWinner::Player)
            result.playerWonTimes++;

        else if (roundInfo.roundWinner == enWinner::Draw)
            result.DrawTimes++;



    }

    showGameOverScreen();
    if (result.computerWonTimes > result.playerWonTimes)
        result.finalWinner = winnerName(enWinner::Computer);

    else if (result.computerWonTimes < result.playerWonTimes)
        result.finalWinner = winnerName(enWinner::Player);

    else
        result.finalWinner = winnerName(enWinner::Draw);

    showFinalGameResults(result);

    while (resetScreen());
    {
        startGame();
    }





}


int main()
{

    srand((unsigned)time(NULL));
    startGame();

    return 0;
}
