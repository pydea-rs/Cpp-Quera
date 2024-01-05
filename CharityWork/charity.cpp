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
	BintyCharity *next, *last;
	// TODO: use array
	// or use linked classes
public:
	BintyCharity(long _limit, long _initialBalance = 0) : name("Unknown"), diseaseType("Unknown"), financialLimit(_limit), balance(_initialBalance), id(1), next(nullptr), last(this) {}
	BintyCharity(long _limit, long _initialBalance, std::string _name, std::string _diseaseType, uint _id = 1) :
		name(_name), diseaseType(_diseaseType), financialLimit(_limit), balance(_initialBalance), id(_id), next(nullptr), last(this) {}

	void collectFinancialSupport(long amount) {
		long newBalance = balance + amount;
		// std::cout << "balance = " << balance << ", newBal = " << newBalance << ", limit = " <<  financialLimit << std::endl;
		if(newBalance > financialLimit) {
			balance = financialLimit;
			long extra = newBalance - financialLimit;
			if(next != nullptr) {
				next->collectFinancialSupport(extra);
			} else {
				BintyCharity::fundsForNewCharity += extra;
			}
		} else balance = newBalance;

	}

	BintyCharity *get(uint _id) {
		BintyCharity *c = this;
		while (c != nullptr && c->getID() != _id) c = c->next;
		return c;
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

	void nextCharity(long _financialLimit, long _initialBalance = 0, std::string _name = "Unknown", std::string _diseaseType = "Unknown") {
		last->next = new BintyCharity(_financialLimit, _initialBalance, _name, _diseaseType, last->getID() + 1);
		last = last->next;
		// std::cout << last->getID() << std::endl;
	}
};
long BintyCharity::fundsForNewCharity = 0;

using namespace std;

int main(int argc, char** argv) {
	int n, q;
	string response = "";

	BintyCharity *charityChain = nullptr;
	cin >> n >> q;

	for(int i = 0; i < n; i++) {
		long limit = 0;
		cin >> limit;
		if(charityChain != nullptr)  {
			charityChain->nextCharity(limit);
		} else {
			charityChain = new BintyCharity(limit);
		}
	}

	// questions
	for(int i = 0; i < q; i++) {
		int requestType = 0;
		cin >> requestType;
		uint targetId;
		BintyCharity *target;
		switch(requestType) {
			case 1:
				int supportAmount;
				cin >> targetId >> supportAmount;
				target = charityChain->get(targetId);
				if(target != nullptr) {
					target->collectFinancialSupport(supportAmount);
				} else
					cout << "Charity with id: "<< targetId << " Not Found!";
				break;
			case 2:
				cin >> targetId;
				target = charityChain->get(targetId);
				if(target != nullptr) {
					response += to_string(target->getBalance()) + "\n";
				} else
					cout << "Charity with id: "<< targetId << " Not Found!";
				break;
			default:
				cout << "Wrong request!";
				break;
		}
	}

	cout << response;
	return 0;
}
