#include <iostream>
#include <string>

class BintyCharity {
private:
	static long int fundsForNewCharities;
	unsigned int id; // specifier in the chain
	long int financialLimit;
	long int balance;

public:
	BintyCharity() {}
	BintyCharity(int _id, long int _limit, long int _initialBalance = 0) : financialLimit(_limit), balance(_initialBalance), id(_id) {}
	BintyCharity(unsigned int _id, long int _limit, long int _initialBalance, std::string _name, std::string _diseaseType) :
		financialLimit(_limit), balance(_initialBalance), id(_id) {}

	long int collectFinancialSupport(long int amount) {
		long int newBalance = balance + amount;
		// std::cout << "balance = " << balance << ", newBal = " << newBalance << ", limit = " <<  financialLimit << std::endl;
		long int extra = newBalance - financialLimit;
		if(extra > 0) {
			balance = financialLimit;
			return extra; // this is returned to be used on next charity
		}
		balance = newBalance;
		return 0L;
	}

	long int getBalance() const {
		return balance;

	}
    static void collectFundsForNewCharities(long int amount) {
        BintyCharity::fundsForNewCharities += amount;
    }
	void setBalance(long int _balance) {
		balance = _balance;
	}

	long int getFinancialLimit() const {
		return financialLimit;
	}

	void setFinancialLimit(long int _limit) {
		financialLimit = _limit;
	}
	void setID(unsigned int _id) {
		id = _id;
	}

	unsigned int getID() const {
		return id;
	}

};
long int BintyCharity::fundsForNewCharities = 0;

using namespace std;

int main() {
	int n, q;
	string responses = "";

	cin >> n >> q;
	auto **charities = new BintyCharity*[n];
	long int limit;
	for(int i = 0; i < n; i++) {
		cin >> limit;
		charities[i] = new BintyCharity(i + 1, limit);
	}

	// questions
	for(int i = 0; i < q; i++) {
		int requestType = 0;
		cin >> requestType;
		unsigned int targetId;
		long int supportAmount;
		switch(requestType) {
			case 1:
				cin >> targetId >> supportAmount;
                targetId--; // charity indexes started from 1
				while(targetId < n && (supportAmount = charities[targetId++]->collectFinancialSupport(supportAmount)) > 0);

                if(targetId >= n)
                    BintyCharity::collectFundsForNewCharities(supportAmount);
				break;
			case 2:
				cin >> targetId;
				responses += to_string(charities[targetId - 1]->getBalance()) + "\n";
				break;
			default:
				cout << "Wrong request!";
				break;
		}
	}

	cout << responses;
	return 0;
}
