#include <iostream>
#include <string>


class BintyCharity {
private:
	static BintyCharity **referenceCache;
	static unsigned int cacheSize, cacheStep, cacheIndex, totalCharities;
	static long int fundsForNewCharity;
	unsigned int id; // specifier in the chain
	long int financialLimit;
	long int balance;
	BintyCharity *next, *prev;
	// TODO: use array
	// or use linked classes

	static void cacheThis(BintyCharity *item) {
		BintyCharity::referenceCache[cacheIndex++] = item;
	}
public:
	BintyCharity() {}
	BintyCharity(long int _limit, long int _initialBalance = 0) : financialLimit(_limit), balance(_initialBalance), id(1), next(nullptr), prev(nullptr) {}
	BintyCharity(long int _limit, long int _initialBalance, std::string _name, std::string _diseaseType, unsigned int _id = 1) :
		financialLimit(_limit), balance(_initialBalance), id(_id), next(nullptr), prev(nullptr) {}

	void collectFinancialSupport(long int amount) {
		long int newBalance = balance + amount;
		// std::cout << "balance = " << balance << ", newBal = " << newBalance << ", limit = " <<  financialLimit << std::endl;
		if (newBalance > financialLimit) {
			balance = financialLimit;
			long int extra = newBalance - financialLimit;
			if (next != nullptr) {
				next->collectFinancialSupport(extra);
			}
			else {
				BintyCharity::fundsForNewCharity += extra;
			}
		}
		else balance = newBalance;

	}

	BintyCharity *find(const unsigned int targetId) {
		BintyCharity *c;
		const unsigned int left = (targetId - 1) / BintyCharity::cacheStep;
		if (targetId - BintyCharity::referenceCache[left]->getID() <= BintyCharity::referenceCache[left + 1]->getID() - targetId) {
			c = BintyCharity::referenceCache[left];
			while (c != nullptr && c->getID() < targetId) c = c->next;
		} else {
			c = BintyCharity::referenceCache[left + 1];
			while (c != nullptr && c->getID() > targetId) c = c->prev;
		}

		return c;
	}

	long int getBalance() const {
		return balance;
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

	BintyCharity *nextCharity(long int _financialLimit, long int _initialBalance = 0, std::string _name = "Unknown", std::string _diseaseType = "Unknown") {
		this->next = new BintyCharity(_financialLimit, _initialBalance, _name, _diseaseType, id + 1);
		this->next->prev = this;

		if (!(this->next->getID() % BintyCharity::cacheStep)) {
			cacheThis(this->next);
		}
		return this->next;
		// std::cout << last->getID() << std::endl;
	}

	void endCaching() {
		if (this->id == BintyCharity::totalCharities) // check if this is the last item
			cacheThis(this);
	}

	static void initReferenceCache(unsigned int totalNumberOfItems) {
		BintyCharity::totalCharities = totalNumberOfItems;
		BintyCharity::cacheSize = (totalNumberOfItems / 20);
		BintyCharity::cacheStep = totalNumberOfItems / BintyCharity::cacheSize;
		BintyCharity::cacheSize++;
		BintyCharity::referenceCache = new BintyCharity*[BintyCharity::cacheSize];
	}
};

long int BintyCharity::fundsForNewCharity = 0;
unsigned int BintyCharity::cacheSize = 0, BintyCharity::cacheStep = 0, BintyCharity::cacheIndex = 0, BintyCharity::totalCharities = 0;
BintyCharity **BintyCharity::referenceCache;

using namespace std;

int main() {
	int n, q;
	cin >> n >> q;

	string response = "";

	long int limit = 0;
	cin >> limit;

	BintyCharity::initReferenceCache(n);
	auto *charityChain = new BintyCharity(limit);
	BintyCharity *curr = charityChain;
	for (unsigned int i = 1; i < n; i++) {
		cin >> limit;
		curr = curr->nextCharity(limit);

	}
	curr->endCaching();
	// questions
	curr = charityChain;
	for (int i = 0; i < q; i++) {
		int requestType = 0;
		long int supportAmount = 0L;
		unsigned int targetId;
		cin >> requestType >> targetId;
		curr = curr->find(targetId);

		switch (requestType) {
		case 1:
			cin >> supportAmount;
			curr->collectFinancialSupport(supportAmount);
			break;
		case 2:
			response += to_string(curr->getBalance()) + "\n";
			break;

		default:
			cout << "Wrong request!";
			break;
		}
	}

	cout << response;
	return 0;
}