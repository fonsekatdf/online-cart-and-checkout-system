#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class PaymentProcessor
{
private:
    stack<string> steps;
    bool paid;

public:
    PaymentProcessor()
    {
        paid = false;
    }

    // push a completed step
    void addStep(string step)
    {
        steps.push(step);
        cout << " [Payment] ✔️ " << step << "\n";
    }

    // pop the most recent step
    bool rollBack()
    {
        if (steps.empty())
        {
            cout << " [Payment] Nothing to roll back.\n";
            return false;
        }

        cout << " [Payment] x Rolling back: " << steps.top() << "\n";
        steps.pop();
        return true;
    }

    // peek at last completed step
    string lastStep() const
    {
        if (steps.empty())
        {
            return "None";
        }

        return steps.top();
    }

    // run full payment flow
    bool processPayment(double amount)
    {
        cout << "\n--- Payment Processing ---\n";

        addStep("Cart verified");
        addStep("Payment address confirmed");
        addStep("Payment method validated");

        if (amount <= 0)
        {
            cout << " [Payment] Invalid amount. Rolling back...\n";
            rollBack();
            rollBack();
            rollBack();
            return false;
        }

        addStep("Card charged Rs." + to_string((int)amount) + ".00");
        addStep("Recipt generated");

        paid = true;
        cout << " [payment] Payment of Rs." << fixed
             << setprecision(2) << amount << " successfully.\n";
        return true;
    }

    // show all steps taken
    void showSteps() const
    {
        if (steps.empty())
        {
            cout << " [Payment] No steps on record.\n";
            return;
        }

        // copy stack to print in order
        stack<string> temp = steps;
        vector<string> history;

        while (!temp.empty())
        {
            history.push_back(temp.top());
            temp.pop();
        }

        cout << "\n Payment History:\n";

        for (int i = (int)history.size() - 1; i >= 0; --i)
        {
            cout << "   " << (history.size() - i) << ". " << history[i] << "\n";
        }
    }

    bool isPaid() const
    {
        return paid;
    }

    bool hasSteps() const
    {
        return !steps.empty();
    }

    void reset()
    {
        while (!steps.empty())
        {
            paid = false;
        }
    }
};
