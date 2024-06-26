#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Funcția pentru a genera o carte aleatoare
int getRandomCard() {
    return rand() % 13 + 1;  // Valori posibile: 1-13 (A, 2-10, J, Q, K)
}

// Funcția pentru a calcula valoarea unei mâini de cărți
int calculateHandValue(const vector<int>& hand) {
    int sum = 0;
    int numAces = 0;

    for (int card : hand) {
        if (card == 1) {
            sum += 11;  // Asul
            numAces++;
        } else if (card >= 11) {
            sum += 10;  // Fetele (J, Q, K)
        } else {
            sum += card;  // Carte numerică
        }
    }

    // Reducem valoarea asurilor, dacă depășim 21
    while (sum > 21 && numAces > 0) {
        sum -= 10;
        numAces--;
    }

    return sum;
}

// Funcția pentru a curăța consola pe oricare sistem de operare
void clearConsole() {
#ifdef _WIN32
    system("cls");  // Pentru Windows
#else
    system("clear");  // Pentru Linux/Unix
#endif
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));  // Inițializăm generatorul de numere aleatoare

    int playerWins = 0;
    int dealerWins = 0;

    while (true) {
        vector<int> playerHand;
        vector<int> dealerHand;

        // Începem jocul prin dându-le două cărți jucătorului și dealer-ului
        playerHand.push_back(getRandomCard());
        playerHand.push_back(getRandomCard());

        dealerHand.push_back(getRandomCard());
        dealerHand.push_back(getRandomCard());

        clearConsole();  // Curățăm consola înainte de începerea unei noi runde

        cout << "Bun venit la jocul de Blackjack!" << endl;

        while (true) {
            cout << "\nMana ta: ";
            for (int card : playerHand) {
                cout << card << " ";
            }
            cout << "Valoare mana: " << calculateHandValue(playerHand) << endl;

            // Verificăm dacă jucătorul a depășit 21
            if (calculateHandValue(playerHand) > 21) {
                cout << "Ai depasit 21! Ai pierdut!" << endl;
                dealerWins++;
                break;
            }

            // Jucătorul decide dacă să mai ia o carte sau să se oprească
            cout << "Vrei să iei o carte suplimentara? (da/nu): ";
            string choice;
            cin >> choice;

            if (choice != "da") {
                break;
            }

            // Jucătorul ia o carte suplimentară
            playerHand.push_back(getRandomCard());
        }

        // Dealer-ul ia cărți până când valoarea mâinii sale este cel puțin 17
        while (calculateHandValue(dealerHand) < 17) {
            dealerHand.push_back(getRandomCard());
        }

        cout << "\nMana dealer-ului: ";
        for (int card : dealerHand) {
            cout << card << " ";
        }
        cout << "Valoare mana: " << calculateHandValue(dealerHand) << endl;

        // Determinăm câștigătorul
        int playerValue = calculateHandValue(playerHand);
        int dealerValue = calculateHandValue(dealerHand);

        if (playerValue > 21) {
            cout << "Dealer-ul castiga! Ai depasit 21." << endl;
            dealerWins++;
        } else if (dealerValue > 21) {
            cout << "Tu castigi! Dealer-ul a depasit 21." << endl;
            playerWins++;
        } else if (playerValue > dealerValue) {
            cout << "Tu castigi! Felicitari!" << endl;
            playerWins++;
        } else if (playerValue < dealerValue) {
            cout << "Dealer-ul castiga!" << endl;
            dealerWins++;
        } else {
            cout << "Este remiza!" << endl;
        }

        // Întrebăm jucătorul dacă dorește să mai joace o rundă
        cout << "Doresti să mai joci o runda? (da/nu): ";
        string playAgain;
        cin >> playAgain;

        if (playAgain != "da") {
            clearConsole();
            cout << "La revedere! La urmatoarea data!" << endl;
            cout << "Scorul final:" << endl;
            cout << "Runde castigate de tine: " << playerWins << endl;
            cout << "Runde castigate de dealer: " << dealerWins << endl;
            break;
        }
    }

    return 0;
}
