# include <iostream>
# include <cstdlib>
using namespace std;
enum en_winner {player = 1, computer = 2, draw = 3};
enum en_game_choices {rock = 1, paper = 2, scissor = 3};
int read_n(string message) {
	int n = 0;
	cout << message;
	cin >> n;
	while (cin.fail() || n <= 0) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Wrong Input! Please Try Again: ";
		cin >> n;
	}
	return n;
}
int random_number(int from, int to) {
	return rand() % (to - from + 1) + from;
}
struct st_round_info {
	int round_number = 0;
	en_game_choices player_choice;
	en_game_choices computer_choice;
	en_winner round_winner;
};
struct st_game_info {
	int game_rounds = 0;
	int player_wins = 0;
	int computer_wins = 0;
	int draw_times = 0;
	en_winner final_winner;
};
en_game_choices read_player_choice() {
	int n;
	cout << "Please Enter Your Coice: \n";
	cout << "[1] Rock\n";
	cout << "[2] Paper\n";
	cout << "[3] Scissor\n";
	n = read_n("");
	return en_game_choices(n);
}
en_game_choices get_computer_choice() {
	return en_game_choices(random_number(1, 3));
}
en_winner round_winner(st_round_info r) {
	if (r.computer_choice == r.player_choice)
		return en_winner::draw;

	if (r.computer_choice == en_game_choices::paper) {
		if (r.player_choice == en_game_choices::rock)
			return en_winner::computer;
		else 
			return en_winner::player;
	}
	else if (r.computer_choice == en_game_choices::rock) {
		if (r.player_choice == en_game_choices::scissor)
			return en_winner::computer;
		else 
			return en_winner::player;
	}
	else if (r.computer_choice == en_game_choices::scissor) {
		if (r.player_choice == en_game_choices::paper)
			return en_winner::computer;
		else
			return en_winner::player;
	}

	return en_winner::draw;
}
en_winner final_game_winner(st_game_info info) {
	if (info.computer_wins > info.player_wins)
		return en_winner::computer;
	else if(info.computer_wins < info.player_wins)
		return en_winner::player;
	else
		return en_winner::draw;

}
string get_winner_name(en_winner winner) {
	if (winner == en_winner::computer)
		return "[Computer]";
	else if (winner == en_winner::player)
		return "[Player]";
	else 
		return "[No Winner]";
}
string get_choice_name(int n) {
	switch (n)
	{
	case 1:
		return "Rock";
	case 2:
		return "Paper";
	case 3:
		return "Scissor";
	default:
		break;
	}
}
void print_round_info(st_round_info round){
	cout << "__________________ Round[" << round.round_number << "] __________________\n\n";
	cout << "Player Choice: " << get_choice_name(round.player_choice) << endl;
	cout << "Computer Choice: " << get_choice_name(round.computer_choice) << endl;
	cout << "Winner Name: " << get_winner_name(round.round_winner) << endl;
	cout << "_________________________________________________________________________\n";
	}
st_game_info play_game() {
	int computer_wins = 0, player_wins = 0, draws = 0;
	int n = read_n("Enter The Number Of Rounds: ");
	st_round_info round_info;
	for (int i = 1; i <= n; i++) {
		round_info.round_number = i;
		round_info.computer_choice = get_computer_choice();
		round_info.player_choice = read_player_choice();
		round_info.round_winner = round_winner(round_info);
		print_round_info(round_info);
	if (round_info.round_winner == en_winner::player) {
		player_wins++;
		system("color 2F");
	}
	else if (round_info.round_winner == en_winner::computer) {
		computer_wins++;
		cout << "\a";
		system("color 4F");
	}
	else {
		draws++;
		system("color 1F");
	}
	}
	st_game_info game_info;
	game_info.computer_wins = computer_wins;
	game_info.player_wins = player_wins;
	game_info.draw_times = draws;
	game_info.game_rounds = round_info.round_number;
	game_info.final_winner = final_game_winner(game_info);
	return game_info;
}
void print_game_result(st_game_info game_info) {
	cout << "\n\n____________________ 🎮 Game Over 🎮 _________________________\n\n";
	cout << "Rounds Total Number: " << game_info.game_rounds << endl;
	cout << "Player Total Wins: " << game_info.player_wins << endl;
	cout << "Computer Total Wins: " << game_info.computer_wins << endl;
	cout << "Draws Total Number: " << game_info.draw_times << endl;
	cout << "Final Winner: " << get_winner_name(game_info.final_winner) << endl;
	cout << "\n\n______________________________________________________________\n\n";
}
void game() {
	char play_again = 'Y';
	do {
		system("cls");
		st_game_info results = play_game();
		print_game_result(results);
		cout << "\nDo you want to play again? (Y/N): ";
		cin >> play_again;
	} while (play_again == 'Y' || play_again == 'y');
}
int main() {
	srand(time(0));
	game();





	return 0;
}