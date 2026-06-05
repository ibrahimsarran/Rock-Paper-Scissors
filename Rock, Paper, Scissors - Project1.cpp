// Project 1: Rock, Paper, Scissors
#include <iostream>
#include <cstdlib>
#include <ctime> 
using namespace std;

enum enGameChoice { Rock = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short roundNumber = 0;
    enGameChoice playerChoice;
    enGameChoice computerChoice;
    enWinner winner;
    string winnerName = "";
};

struct stGameResult
{
    short gameRounds = 0;
    short playerWonTimes = 0;
    short computerWonTimes = 0;
    short drawTimes = 0;
    enWinner gameWinner;
    string finalWinner = "";

};

short ReadRounds()
{
    short roundNum = 1;

    do
    {
        cout << "How many rounds 1 to 10 ? \n";
        cin >> roundNum;
    } while (roundNum < 1 || roundNum > 10);

    return roundNum;
}

int RandomNumber(int from, int to)
{
    return rand() % (to - from + 1) + from;
}

enGameChoice ReadPlayerChoice()
{
    short playerChoice = 0;
    do
    {
        cout << "\nChoose: [1]: Rock, [2]: Paper, [3]: Scissors. ?" << endl;
        cin >> playerChoice;
    } while (playerChoice < 1 || playerChoice>3);

    return (enGameChoice)playerChoice;
}

enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{

    if (RoundInfo.playerChoice == RoundInfo.computerChoice)
        return enWinner::Draw;

    switch (RoundInfo.playerChoice)
    {
    case enGameChoice::Rock:
        if (RoundInfo.computerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
        break;

    case enGameChoice::Paper:
        if (RoundInfo.computerChoice == enGameChoice::Scissors)
        {
            return enWinner::Computer;
        }
        break;

    case enGameChoice::Scissors:
        if (RoundInfo.computerChoice == enGameChoice::Rock)
        {
            return enWinner::Computer;
        }
        break;
    }
    return enWinner::Player;
}

enWinner WhoWonTheGame(short playerWinTimes, short computerWinTimes)
{
    if (playerWinTimes > computerWinTimes) return enWinner::Player;

    else if (computerWinTimes > playerWinTimes) return enWinner::Computer;

    else return enWinner::Draw;
}

string ChoiceName(enGameChoice Choice)
{
    string arrGameChoices[3] = { "Rock", "Paper", "Scissors" };
    return arrGameChoices[Choice - 1];
}

string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = { "Player1", "Computer", "No Winner (Draw)" };
    return arrWinnerName[Winner - 1];
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "\n____________ Round [" << RoundInfo.roundNumber << "] ____________\n\n";
    cout << "Player1 Choice: " << ChoiceName(RoundInfo.playerChoice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.computerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.winnerName << "]\n";
    cout << "_________________________________________\n" << endl;

}

void SetWinnerScreenColor(enWinner winner)
{
    switch (winner)
    {
    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;

    case enWinner::Player:
        system("color 2F");
        break;

    default:
        system("color 6F");
        break;

    }
}

stGameResult PlayGame(short howManyRounds)
{
    stRoundInfo roundInfo;
    short playerWonTimes = 0, computerWonTimes = 0, drawTimes = 0;
    for (short gameRounds = 1; gameRounds <= howManyRounds; gameRounds++)
    {
        cout << "\nRound [" << gameRounds << "] begins:\n";
        roundInfo.roundNumber = gameRounds;
        roundInfo.playerChoice = ReadPlayerChoice();
        roundInfo.computerChoice = GetComputerChoice();
        roundInfo.winner = WhoWonTheRound(roundInfo);
        roundInfo.winnerName = WinnerName(roundInfo.winner);

        SetWinnerScreenColor(roundInfo.winner);
        // increase winner record

        if (roundInfo.winner == enWinner::Computer)
            computerWonTimes++;

        else if (roundInfo.winner == enWinner::Player)
            playerWonTimes++;

        else if (roundInfo.winner == enWinner::Draw)
            drawTimes++;

        PrintRoundResults(roundInfo);

    }
    return { howManyRounds, playerWonTimes, computerWonTimes, drawTimes, WhoWonTheGame(playerWonTimes, computerWonTimes), WinnerName(WhoWonTheGame(playerWonTimes, computerWonTimes)) };
}

void ShowGameOverScreen()
{
    cout << "\t\t\t------------------------------------\n\n";

    cout << "\t\t\t       +++ G a m e O v e r +++      \n\n";

    cout << "\t\t\t------------------------------------\n  ";
}

void ShowFinalGameResults(stGameResult gameResults)
{
    cout << "\n\t\t------------------[Game Results]------------------\n\n";
    cout << "\t\t Player1 Won Times  : " << gameResults.playerWonTimes << endl;
    cout << "\t\t Computer Won Times : " << gameResults.computerWonTimes << endl;
    cout << "\t\t Draw Times         : " << gameResults.drawTimes << endl;
    cout << "\t\t Final Winner       : " << gameResults.finalWinner << endl;;
    cout << "\n\t\t--------------------------------------------------\n";

    SetWinnerScreenColor(gameResults.gameWinner);
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char playAgain = 'Y';
    do
    {

        ResetScreen();
        stGameResult gameResult = PlayGame(ReadRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(gameResult);

        cout << "Do you want to play again (Y/N) ? ";
        cin >> playAgain;

    } while (playAgain == 'Y' || playAgain == 'y');

}


int main()
{

    srand((unsigned)time(NULL));
    StartGame();

    return 0;
}
