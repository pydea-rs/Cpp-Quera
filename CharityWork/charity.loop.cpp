#include <iostream>
#include <string>

class BintyCharity {
private:
	static long fundsForNewCharity;
	uint id; // specifier in the chain
	long financialLimit;
	std::string name;
	std::string diseaseType;
	long balance;

public:
	BintyCharity() {}
	BintyCharity(int _id, long _limit, long _initialBalance = 0) : name("Unknown"), diseaseType("Unknown"), financialLimit(_limit), balance(_initialBalance), id(_id) {}
	BintyCharity(uint _id, long _limit, long _initialBalance, std::string _name, std::string _diseaseType) :
		name(_name), diseaseType(_diseaseType), financialLimit(_limit), balance(_initialBalance), id(_id) {}

	long collectFinancialSupport(long amount) {
		long newBalance = balance + amount;
		// std::cout << "balance = " << balance << ", newBal = " << newBalance << ", limit = " <<  financialLimit << std::endl;
		long extra = newBalance - financialLimit;
		if(extra > 0) {
			balance = financialLimit;
			return extra; // this is returned to be used on next charity
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
	void setID(uint _id) {
		id = _id;
	}

	uint getID() const {
		return id;
	}

};
long BintyCharity::fundsForNewCharity = 0;

using namespace std;

int main(int argc, char** argv) {
	int n, q, resIndex = -1;
	BintyCharity *charities = new BintyCharity[n];
	long *responses = new long[n];

	cin >> n >> q;
	long limit;
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

		switch(requestType) {
			case 1:
				long supportAmount;
				cin >> targetId >> supportAmount;
				while((supportAmount = charities[targetId - 1].collectFinancialSupport(supportAmount)) > 0)
					targetId++;
				break;
			case 2:
				cin >> targetId;
				responses[++resIndex] = charities[targetId - 1].getBalance();
				break;
			default:
				cout << "Wrong request!";
				break;
		}
	}

	for(; resIndex >= 0; resIndex--)
		cout << responses[resIndex] << endl;
	return 0;
}
