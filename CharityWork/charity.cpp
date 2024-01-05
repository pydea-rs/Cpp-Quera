#include <iostream>

class BintyCharity {
private:
	long financialLimit;
	std::string name;
    std::string diseaseType;
    long balance;

	// TODO: use array
	// or use linked classes
public:
	BintyCharity(std::string _name, std::string _diseaseType, long _limit, long initialBalance = 0) :
		name(_name), diseaseType(_diseaseType), financialLimit(_limit), balance(initialBalance) {}

	long collectFinancialSupport(long amount) {
		long newBalance = balance + amount;
		if(newBalance > financialLimit) {
			balance = financialLimit;
			return newBalance - financialLimit;
		}
		balance = newBalance;
		return 0L;
	}

	long getBalance() const {
		return balance;
	}

	void setBalance(long _balance) {
		balance = _balance;
	}

	std::string getName() const {
		return name;
	}

	void setName(std::string _name) {
		name = _name;
	}

	std::string getDiseaseType() const {
		return diseaseType;
	}

	void setDiseaseType(std::string _type) {
		diseaseType = _type;
	}

	long getFinancialLimit() const {
		return financialLimit;
	}

	void setFinancialLimit(long _limit) {
		financialLimit = _limit;
	}
};

int main(int argc, char** argv) {
	return 0;
}
