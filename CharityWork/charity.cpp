#include <iostream>
#include <string>

class BintyCharity {
private:
    static long long int fundsForNewCharity;
    uint id; // specifier in the chain
    long long int financialLimit;
    long long int balance;
    BintyCharity *next, *prev;
    // TODO: use array
    // or use linked classes
public:
    BintyCharity(long long int _limit, long long int _initialBalance = 0) : financialLimit(_limit), balance(_initialBalance), id(1), next(nullptr), prev(nullptr) {}
    BintyCharity(long long int _limit, long long int _initialBalance, std::string _name, std::string _diseaseType, uint _id = 1) :
            financialLimit(_limit), balance(_initialBalance), id(_id), next(nullptr), prev(nullptr) {}

    void collectFinancialSupport(long long int amount) {
        long long int newBalance = balance + amount;
        // std::cout << "balance = " << balance << ", newBal = " << newBalance << ", limit = " <<  financialLimit << std::endl;
        if(newBalance > financialLimit) {
            balance = financialLimit;
            long long int extra = newBalance - financialLimit;
            if(next != nullptr) {
                next->collectFinancialSupport(extra);
            } else {
                BintyCharity::fundsForNewCharity += extra;
            }
        } else balance = newBalance;

    }

    BintyCharity *find(uint targetId) {
        BintyCharity *c = this;
        while (c != nullptr && c->getID() < targetId) c = c->next;
        while (c != nullptr && c->getID() > targetId) c = c->prev;

        return c;
    }


    long long int getBalance() const {
        return balance;
    }

    void setBalance(long long int _balance) {
        balance = _balance;
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

    BintyCharity *nextCharity(long long int _financialLimit, long long int _initialBalance = 0, std::string _name = "Unknown", std::string _diseaseType = "Unknown") {
        this->next = new BintyCharity(_financialLimit, _initialBalance, _name, _diseaseType, id + 1);
        this->next->prev = this;
        return this->next;
        // std::cout << last->getID() << std::endl;
    }
};
long long int BintyCharity::fundsForNewCharity = 0;

using namespace std;

int main(int argc, char** argv) {
    int n, q;
    string response = "";

    cin >> n >> q;
    long long int limit = 0;
    cin >> limit;
    auto *charityChain = new BintyCharity(limit);
    BintyCharity *curr = charityChain;
    for(int i = 1; i < n; i++) {
        cin >> limit;
        curr = curr->nextCharity(limit);
    }

    // questions
    curr = charityChain;
    for(int i = 0; i < q; i++) {
        int requestType = 0;
        long long int supportAmount = 0L;
        uint targetId;
        cin >> requestType >> targetId;
        curr = curr->find(targetId);

        switch(requestType) {
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