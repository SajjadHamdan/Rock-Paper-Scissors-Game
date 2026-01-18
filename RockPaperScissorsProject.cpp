#include <iostream>
#include<string>
#include<cmath>
#include<cstdlib>
using namespace std;

enum enGamChoese { Stone = 1, Paper = 2, Scissor = 3 };
enum enWinnwe { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short NumberOfRound = 0;
	enGamChoese PlayChoese;
	enGamChoese ComputerChoese;
	string RoundName;
	enWinnwe RoundWinner;

};

struct stGameREsult
{
	short GameRound = 0;
	short PlayerWoinnTime = 0;
	short ComputerWinnweTimes = 0;
	short DrawTimes = 0;
	enWinnwe GameWiner;
	string WinnerName;

};

short ReadHowManyRound()
{
	short HowManyRound;

	do
	{
		cout << "How Many Round you want Play? 1 to 10 : ";
		cin >> HowManyRound;

	} while (HowManyRound < 1 || HowManyRound>10);

	return HowManyRound;

}

int RandomNumber(int From, int To)
{
	int RandomNumber = rand() % (To - From + 1) + From;

	return RandomNumber;
}

enGamChoese ReadPlayerChoese()
{
	short ReadChpese;
	do
	{
		cout << "\nChoes [1]:Stone, [2]:Paper, [3]:Scissor? : ";
		cin >> ReadChpese;

	} while (ReadChpese < 1 || ReadChpese>3);

	return (enGamChoese)ReadChpese;
}

enGamChoese GetComputerChoese()
{
	return (enGamChoese)RandomNumber(1, 3);
}

string WinnerName(enWinnwe winnerName)
{
	string arryWinner[3] = { "Player", "Copmuter", "No Winner" };

	return arryWinner[winnerName - 1];
}

string ChoiseNamer(enGamChoese GameChoise)
{
	string arrChoise[3] = { "Stone", "Paper", "Scissor" };

	return arrChoise[GameChoise - 1];
}


void SetSecreenColor(enWinnwe winner)
{
	switch (winner)
	{
	case enWinnwe::Player:
		system("color 2F");
		break;
	case enWinnwe::Computer:
		system("color 4F");
		cout << "\a";
		break;
	case enWinnwe::Draw:
		system("color 6F");
		break;
	}
}

enWinnwe WhoRoundWinner(stRoundInfo RoundInfo)
{
	if (RoundInfo.ComputerChoese == RoundInfo.PlayChoese)
		return enWinnwe::Draw;


	switch (RoundInfo.PlayChoese)
	{
	case enGamChoese::Paper:
		if (RoundInfo.ComputerChoese == enGamChoese::Scissor)
			return enWinnwe::Computer;

	case enGamChoese::Stone:
		if (RoundInfo.ComputerChoese == enGamChoese::Paper)
			return enWinnwe::Computer;

	case enGamChoese::Scissor:
		if (RoundInfo.ComputerChoese == enGamChoese::Stone)
			return enWinnwe::Computer;
	}

	return enWinnwe::Player;

}

enWinnwe WhoWinnerTheGame(stGameREsult GameResult)
{
	if (GameResult.PlayerWoinnTime > GameResult.ComputerWinnweTimes)
		return enWinnwe::Player;

	else if (GameResult.ComputerWinnweTimes > GameResult.PlayerWoinnTime)
		return enWinnwe::Computer;

	else
		return enWinnwe::Draw;
}

void PrintRoundResult(stRoundInfo RoundInfo)
{
	cout << "\n\n_________________[Round " << RoundInfo.NumberOfRound << "]________________\n";
	cout << "Player Choice   :" << ChoiseNamer(RoundInfo.PlayChoese) << endl;
	cout << "Computer Choice :" << ChoiseNamer(RoundInfo.ComputerChoese) << endl;
	cout << "Round Winner    :[" << RoundInfo.RoundName << "]" << endl;
	cout << "_________________________________________\n\n";

	SetSecreenColor(RoundInfo.RoundWinner);
}

stGameREsult FillGameResult(short NumberOfRound, short PlayerWinnerTimes, short ComputerWinnerTimes, short DrweTimes)
{
	stGameREsult GameResult;

	GameResult.GameRound = NumberOfRound;
	GameResult.PlayerWoinnTime = PlayerWinnerTimes;
	GameResult.ComputerWinnweTimes = ComputerWinnerTimes;
	GameResult.DrawTimes = DrweTimes;
	GameResult.GameWiner = WhoWinnerTheGame(GameResult);
	GameResult.WinnerName = WinnerName(GameResult.GameWiner);

	SetSecreenColor(GameResult.GameWiner);

	return GameResult;

}

string Tap(short NumberTap)
{
	string T = "";

	for (int i = 1; i <= NumberTap; i++)
	{
		T = T + "\t";
		cout << T;
	}
	return T;

}

void PrintGamrResult(stGameREsult GameResult)
{
	cout << Tap(2) << "________________[Game Result]____________________\n";
	cout << Tap(2) << "Game Round            :" << GameResult.GameRound << endl;
	cout << Tap(2) << "Player Winner Times     :" << GameResult.PlayerWoinnTime << endl;
	cout << Tap(2) << "Computer Winner Timrs :" << GameResult.ComputerWinnweTimes << endl;
	cout << Tap(2) << "Draw Times            :" << GameResult.DrawTimes << endl;
	cout << Tap(2) << "Winner Game Name      :" << GameResult.WinnerName << endl;
	cout << Tap(2) << "__________________________________________________\n";
}

void ShowGameOver()
{
	cout << Tap(2) << "_________________________________________________\n\n";
	cout << Tap(2) << "             +++ G a m e O v e r +++\n\n";
	cout << Tap(2) << "_________________________________________________\n\n";
}

stGameREsult PlayGame(short ROundNumber)
{
	stRoundInfo RoundInfo;
	short PlayerWinnerTimes = 0, ComputerWinnerTimes = 0, DrawTimes = 0;
	for (short NumberRound = 1; NumberRound <= ROundNumber; NumberRound++)
	{
		RoundInfo.NumberOfRound = NumberRound;
		RoundInfo.PlayChoese = ReadPlayerChoese();
		RoundInfo.ComputerChoese = GetComputerChoese();
		RoundInfo.RoundWinner = WhoRoundWinner(RoundInfo);
		RoundInfo.RoundName = WinnerName(RoundInfo.RoundWinner);

		PrintRoundResult(RoundInfo);

		if (RoundInfo.RoundWinner == enWinnwe::Player)
			PlayerWinnerTimes++;
		if (RoundInfo.RoundWinner == enWinnwe::Computer)
			ComputerWinnerTimes++;
		if (RoundInfo.RoundWinner == enWinnwe::Draw)
			DrawTimes++;

	}


	return FillGameResult(ROundNumber, PlayerWinnerTimes, ComputerWinnerTimes, DrawTimes);
}

void SetSecreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgin = 'Y';
	do
	{
		SetSecreen();
		stGameREsult Gameresult = PlayGame(ReadHowManyRound());
		ShowGameOver();
		PrintGamrResult(Gameresult);

		cout << Tap(2) << "Do you want play agin ?  Y/N ";
		cin >> PlayAgin;

	} while (PlayAgin == 'y' || PlayAgin == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}

