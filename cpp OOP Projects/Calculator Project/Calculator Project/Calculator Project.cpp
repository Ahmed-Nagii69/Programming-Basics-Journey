# include <iostream>
using namespace std;
class clsCalculator {
private:
	int _Result = 0;
	int _Num = 0;
	int _PreviousResult = 0;
	string _LastOper = "Clear";
	bool _IsZero(int n) {
		return (n == 0);
	}
public:
	void Add(int n) {
		_LastOper = "Add";
		_Num = n;
		_Result = _PreviousResult + _Num;
		_PreviousResult = _Result;
	}
	void Substract(int n) {
		_Num = n;
		_Result = _PreviousResult - _Num;
		_PreviousResult = _Result;
		_LastOper = "Substract";

	}
	void Divide(int n) {
		if (_IsZero(n)) {
			_Num = 1;
			_Result = _PreviousResult / _Num;
			_PreviousResult = _Result;
			_LastOper = "Divide";
		}
		else {
			_Num = n;
			_Result = _PreviousResult / _Num;
			_PreviousResult = _Result;
			_LastOper = "Divide";

		}

	}
	void Multiply(int n) {
		_Num = n;
		_Result = _PreviousResult * _Num;
		_PreviousResult = _Result;
		_LastOper = "Multiply";
	}
	void PrintResult() {
		cout << "Result After " << _LastOper << " " << _Num << " Is: " << _Result << endl;
 	}
	void Clear() {
		_Result = 0;
		_PreviousResult = 0;
		_Num = 0;
		_LastOper = "Clear";
	}
};
int main() {

	clsCalculator Calc1;
	Calc1.Add(10);
	Calc1.PrintResult();

	Calc1.Add(100);
	Calc1.PrintResult();

	Calc1.Substract(15);
	Calc1.PrintResult();

	Calc1.Divide(0);
	Calc1.PrintResult();

	Calc1.Clear();
	Calc1.PrintResult();


	return 0;
} 