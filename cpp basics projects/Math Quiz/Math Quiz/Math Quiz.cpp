# include <iostream>
# include <cstdlib>
using namespace std;
int random_number(int from, int to) {
	return rand() % (to - from + 1) + from;
}
int read_number(string message) {
	int num;
	cout << message;
	cin >> num;
	while (cin.fail() || num <= 0) {
		cout << "Invalid Input! Please Try Again: ";
		cin >> num;
	}
	return num;
}
enum en_question_level { easy = 1, med = 2, hard = 3, mix = 4 };
enum en_operation_type {add=1, sub = 2, mul = 3, division = 4, mixed = 5};
struct st_question_info {
	en_question_level question_level;
	en_operation_type question_operation;
	int question_part1;
	int question_part2;
	char oper;
	int question_number = 0;
	int question_ans = 0;
	int user_ans;
};
struct st_quiz_info {
	int questions_number = 0;
	string questions_level;
	string op_type;
	int n_correct = 0;
	int n_wrong = 0;
	string status;
};
en_operation_type read_operation_type() {
	int oper;
	cout << "Please Enter The Operation Type: \n";
	cout << "[1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mixed: ";
	oper = read_number("");
	return en_operation_type(oper);
}
en_question_level read_question_level() {
	int level;
	cout << "Please Enter The Question Level: \n";
	cout << "[1] Easy, [2] Med, [3] Hard, [4] Mix: ";
	level = read_number("");
	return en_question_level(level);
}
string get_level_name(en_question_level level) {
	string types[] = { "Easy", "Med", "Hard", "Mix" };
	return types [level- 1];
}
string get_operation_type_name(en_operation_type operation) {
	switch (operation) {
	case add: return "Add";
	case sub: return "Sub";
	case mul: return "Mul";
	case division: return "Div";
	case mixed: return "Mixed";
	default: return "Unknown";
	}
}
char get_operation(en_operation_type operation) {
	char operations[] = { '+', '-', '*', '/' };
	switch (operation)
	{
	case add:
		return '+';
	case sub:
		return '-';
	case mul:
		return '*';
	case division:
		return '/';
	case mixed:
		return operations[random_number(0, 3)];
	default:
		break;
	}
}
int get_question_parts(st_question_info info) {
	if (info.question_level == en_question_level::easy)
		return random_number(1, 10);
	else if(info.question_level == en_question_level::med)
		return random_number(100, 200);

	else if(info.question_level == en_question_level::hard)
		return random_number(200, 500);

	else if(info.question_level == en_question_level::mix)
		return random_number(1, 500);
}
int question_calculation(st_question_info info) {
	switch (info.oper) {
	case '+': return info.question_part1 + info.question_part2;
	case '-': return info.question_part1 - info.question_part2;
	case '*': return info.question_part1 * info.question_part2;
	case '/': return info.question_part1 / info.question_part2;
	default: return 0;
	}
}

st_quiz_info game(int n) {
	int correct = 0, wrong = 0;
	st_question_info question_info;
		question_info.question_level = read_question_level();
		question_info.question_operation = read_operation_type();
	for (int i = 1; i <= n; i++) {
		question_info.question_number = i;
		question_info.oper = get_operation(question_info.question_operation);
		question_info.question_part1 = get_question_parts(question_info);
		question_info.question_part2 = get_question_parts(question_info);
		question_info.question_ans = question_calculation(question_info);
		cout << "_________ Question [" << i << "/" << n << "] _____________\n";
		cout << question_info.question_part1 << " " << question_info.oper << " " <<
		question_info.question_part2 << endl;
		question_info.user_ans = read_number("");
		if (question_info.question_ans == question_info.user_ans) {
			correct++;
			cout << "Correct Answer :)\n";
			system("color 2F");
		}
		else {
			wrong++;
			cout << "Wrong Answer :(" << endl << "\a";
			system("color 4F");
			cout << "The Rigth Answer Is: " << question_info.question_ans << endl;
		}
		cout << "____________\n";
	}
	st_quiz_info quiz_info;
	quiz_info.n_correct = correct;
	quiz_info.n_wrong = wrong;
	quiz_info.op_type = get_operation_type_name(question_info.question_operation);
	quiz_info.questions_level = get_level_name(question_info.question_level);
	quiz_info.questions_number = n;
	if (correct >= wrong)
		quiz_info.status = "Winnner";
	else
		quiz_info.status = "Opps! Try Again.";
	return quiz_info;
}
void print_quiz_result(st_quiz_info info) {
	cout << "\n========== ++ Quiz Result Summary ++ ==========\n";
	cout << "Total Questions   : " << info.questions_number << endl;
	cout << "Difficulty Level  : " << info.questions_level << endl;
	cout << "Operation Type    : " << info.op_type << endl;
	cout << "Correct Answers   : " << info.n_correct << endl;
	cout << "Wrong Answers     : " << info.n_wrong << endl;
	cout << "Final Status      : " << info.status << endl;
	cout << "==================================\n";

}
void start_game() {
	char play_again = 'y';
	do {
		system("cls");
		st_quiz_info results = game(read_number("Enter The Number Of Questions: "));
		print_quiz_result(results);
		cout << "Do You Need Play More (Y/N): ";
		cin >> play_again;
	} while (play_again == 'Y', play_again == 'y');
}
int main() {

	srand(time(0));


	start_game();


	return 0;
}