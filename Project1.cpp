#include<iostream>
#include<cstdlib>
using namespace std;


enum enGameChoice {Stone = 1, Paper = 2, Scissor = 3};

enum enWinner {Player = 1, Computer = 2, Draw = 3};

struct stRoundInfo 
{
	short RoundNumber = 0;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
	
};

struct stGameResults
{
	short GameRound = 0;
	short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string GameWinnerName = "";


};

short RandomNumber(short From, short To)
{
	return rand() % (To - From + 1) + From;
}

string WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player", "Computer", "No Winner" };
	return arrWinnerName[Winner - 1];
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
		return enWinner::Draw;

	switch (RoundInfo.PlayerChoice)
	{
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
			return enWinner::Computer;
		break;

	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissor)
			return enWinner::Computer;
		break;

	case enGameChoice::Scissor:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
			return enWinner::Computer;
		break;

	}

	return enWinner::Player;
}

string ChoiceName(enGameChoice Choice)
{
	string arrChoiceName[3] = {"Stone", "Paper", "Scissor"};
	return arrChoiceName[Choice - 1];
}

void SetWinnerScreenColor(enWinner winner)
{
	switch (winner)
	{
	case enWinner::Player:
		system("color 2F");
		break;

	case enWinner::Computer:
		system("color 4F");
		cout << "\a";
		break;

	case enWinner::Draw:
		system("color 6F");
		break;
	}
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n---------- Round[" << RoundInfo.RoundNumber << "] ----------\n\n";
	cout << "Player   choice: " << ChoiceName(RoundInfo.PlayerChoice) << endl;
	cout << "Computer choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
	cout << "-----------------------------\n";
}

enWinner WhoWonTheGame(short PlayerWinTimes, short ComputerWinTimes)
{
	if (PlayerWinTimes > ComputerWinTimes)
		return enWinner::Player;
	else if (PlayerWinTimes < ComputerWinTimes)
		return enWinner::Computer;
	else
		enWinner::Draw;
}

stGameResults FillGameResults(short HowManyRound, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResults GameResults;
	GameResults.GameRound = HowManyRound;
	GameResults.PlayerWinTimes = PlayerWinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameWinner = WhoWonTheGame(PlayerWinTimes, ComputerWinTimes);
	GameResults.GameWinnerName = WinnerName(GameResults.GameWinner);

	return GameResults;

}

enGameChoice ReadPlayerChoice()
{
	short Choice = 1;
	do
	{
		cout << "\nYour choice: [1]Stone, [2]Paper, [3]Scissor? ";
		cin >> Choice;

	} while (Choice < 1 || Choice > 3);

	return (enGameChoice) Choice;
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);
}

stGameResults PlayGame(short HowManyRound)
{
	stRoundInfo RoundInfo;
	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (int GameRound = 1; GameRound <= HowManyRound; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		PrintRoundResults(RoundInfo);

		if (RoundInfo.Winner == enWinner::Player)
			PlayerWinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;
	}

	return FillGameResults(HowManyRound, PlayerWinTimes, ComputerWinTimes, DrawTimes);
}

string Tabs(short number)
{
	string NumberOfTabs = "";
	for (int i = 0; i < number; i++)
	{
		NumberOfTabs = NumberOfTabs + "\t";
		//cout << NumberOfTabs;
	}
	return NumberOfTabs;
}

void ShowGameOverScreen()
{
	cout << Tabs(2) << "----------------------------------------------------------\n\n";
	cout << Tabs(2) << "                +++ G a m e O v e r +++\n";
	cout << Tabs(2) << "----------------------------------------------------------\n\n";
}

void ShowFinalGameResults(stGameResults GameResults)
{
	cout << Tabs(2) << "_____________________ [Game Results ]_____________________\n\n";
	cout << Tabs(2) << "Game Rounds        : " << GameResults.GameRound << endl;
	cout << Tabs(2) << "Player1 won times  : " << GameResults.PlayerWinTimes << endl;
	cout << Tabs(2) << "Computer won times : " << GameResults.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw times         : " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner       : " << GameResults.GameWinnerName << endl;
	cout << Tabs(2) << "___________________________________________________________\n";

	SetWinnerScreenColor(GameResults.GameWinner);

}

short ReadHowManyRounds()
{
	short GameRound = 1;
	do
	{
		cout << "How many Rounds 1 to 10?" << " ";
		cin >> GameRound;

	} while (GameRound < 1 || GameRound > 10);
	return GameRound;
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char play = 'Y';
	do
	{
		ResetScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());

		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);

		cout << endl << Tabs(3) << "Do you want to play again? Y/N? ";
		cin >> play;

	} while (play == 'y' || play == 'Y');
}

int main()
{
    srand((unsigned)time(NULL));

	StartGame();
    
}
