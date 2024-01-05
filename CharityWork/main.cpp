#include <iostream>

class BintyCharity {
private:
	long financialLimit;
	std::string name;
    std::string diseaseType;
    long financialLimit;
    long balance;
	    
public:
	BintyCharity(std::string _name, std::string _diseaseType, long _limit, long initialBalance = 0) :
		name(_name), diseaseType(_diseaseType), financialLimit(_limit), balance(initialBalance) }{
			
		}
		
	long collectFinancialSupport(long amount) {
		long newBalance = balance + amount;
		if(newBalance > financialLimit) {
			balance = financialLimit;
			return newBalance - financialLimit;
		}
	}
		
};
int main(int argc, char** argv) {
	return 0;
}