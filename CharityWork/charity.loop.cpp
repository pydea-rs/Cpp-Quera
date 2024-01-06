#include <iostream>
#include <string>

class BintyCharity {
private:
	static long long int fundsForNewCharities;
	uint id; // specifier in the chain
	long long int financialLimit;
	std::string name;
	std::string diseaseType;
	long long int balance;

public:
	BintyCharity() {}
	BintyCharity(int _id, long long int _limit, long long int _initialBalance = 0) : name("Unknown"), diseaseType("Unknown"), financialLimit(_limit), balance(_initialBalance), id(_id) {}
	BintyCharity(uint _id, long long int _limit, long long int _initialBalance, std::string _name, std::string _diseaseType) :
		name(_name), diseaseType(_diseaseType), financialLimit(_limit), balance(_initialBalance), id(_id) {}

	long long int collectFinancialSupport(long long int amount) {
		long long int newBalance = balance + amount;
		// std::cout << "balance = " << balance << ", newBal = " << newBalance << ", limit = " <<  financialLimit << std::endl;
		long long int extra = newBalance - financialLimit;
		if(extra > 0) {
			balance = financialLimit;
			return extra; // this is returned to be used on next charity
		}
		balance = newBalance;
		return 0L;
	}

	long long int getBalance() const {
		return balance;

	}
    static void collectFundsForNewCharities(long long int amount) {
        BintyCharity::fundsForNewCharities += amount;
    }
	void setBalance(long long int _balance) {
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

	long long int getFinancialLimit() const {
		return financialLimit;
	}

	void setFinancialLimit(long long int _limit) {
		financialLimit = _limit;
	}
	void setID(uint _id) {
		id = _id;
	}

	uint getID() const {
		return id;
	}

};
long long int BintyCharity::fundsForNewCharities = 0;

using namespace std;

int main(int argc, char** argv) {
	int n, q;
	auto *charities = new BintyCharity[n];
	string responses = "";

	cin >> n >> q;
	long long int limit;
	for(int i = 0; i < n; i++) {
		charities[i].setID(i + 1);
		cin >> limit;
		charities[i].setFinancialLimit(limit);
	}

	// questions
	for(int i = 0; i < q; i++) {
		int requestType = 0;
		cin >> requestType;
		uint targetId;
		long long int supportAmount;
		switch(requestType) {
			case 1:
				cin >> targetId >> supportAmount;
                targetId--; // charity indexes started from 1
				while(targetId < n && (supportAmount = charities[targetId++].collectFinancialSupport(supportAmount)) > 0);

                if(targetId >= n)
                    BintyCharity::collectFundsForNewCharities(supportAmount);
				break;
			case 2:
				cin >> targetId;
				responses += to_string(charities[targetId - 1].getBalance()) + "\n";
				break;
			default:
				cout << "Wrong request!";
				break;
		}
	}

	cout << responses;
	return 0;
}
