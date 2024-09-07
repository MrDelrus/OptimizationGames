#include <bits/stdc++.h>
using namespace std;

enum class Move {
    STEAL = 0,
    SPLIT = 1,
};

class Participant {
public:
    virtual void StartNewGame() = 0;
    virtual Move MakeMove() = 0;
    virtual void GetOpponentMove(Move) = 0;
    virtual ~Participant() = default;
};

// participants

class FirstCat : public Participant { // Paste there your implementation
public:
    explicit FirstCat(int) {}
    void StartNewGame() override {}
    Move MakeMove() override {
        return Move::SPLIT;
    }
    void GetOpponentMove(Move) override {}
};

class SecondCat : public Participant { // Paste there your implementation
public:
    explicit SecondCat(int) {}
    void StartNewGame() override {}
    Move MakeMove() override {
        return Move::STEAL;
    }
    void GetOpponentMove(Move) override {}
};

// opponents (baselines)

namespace testing {

template <typename CatFirst, typename CatSecond>
class Simulation {
public:
    void Setup();
    pair<int, int> Run();
private:
    vector<int> permutation;
    vector<shared_ptr<Participant>> participants;
};

template <typename FirstCat, typename SecondCat>
void simulate(int iters = 5'000);

}  // namespace testing

int main() {

    testing::simulate<FirstCat, SecondCat>();

    return 0;
}

namespace testing {

const int PARTICIPANTS_COUNT = 10;

template <typename FirstCat, typename SecondCat>
void Simulation<FirstCat, SecondCat>::Setup() {
    participants.resize(2 * PARTICIPANTS_COUNT);
    vector<int> p(2 * PARTICIPANTS_COUNT);
    for (int i = 0; i < 2 * PARTICIPANTS_COUNT; ++i) {
        p[i] = i;
    }
    shuffle(p.begin(), p.end(), std::mt19937(std::random_device()()));
    for (int i = 0; i < PARTICIPANTS_COUNT; ++i) {
        participants[i] = make_shared<FirstCat>(p[i]);
    }
    for (int i = PARTICIPANTS_COUNT; i < 2 * PARTICIPANTS_COUNT; ++i) {
        participants[i] = make_shared<SecondCat>(p[i]);
    }
}

template <typename FirstCat, typename SecondCat>
pair<int, int> Simulation<FirstCat, SecondCat>::Run() {
    const int GAMES_COUNT = PARTICIPANTS_COUNT * (2 * PARTICIPANTS_COUNT - 1);
    vector<pair<int, int>> games;
    games.reserve(GAMES_COUNT);
    for (int i = 0; i < 2 * PARTICIPANTS_COUNT; ++i) {
        for (int j = i + 1; j < 2 * PARTICIPANTS_COUNT; ++j) {
            games.emplace_back(i, j);
        }
    }
    shuffle(games.begin(), games.end(), std::mt19937(std::random_device()()));
    std::random_device rd;
    std::mt19937 gen(rd());
    uniform_int_distribution<int> distribution(3, 7);
    vector<int> score(2 * PARTICIPANTS_COUNT, 0);
    for (int i = 0; i < GAMES_COUNT; ++i) {
        int firstIndex = games[i].first;
        int secondIndex = games[i].second;
        auto firstPlayer = participants[firstIndex];
        auto secondPlayer = participants[secondIndex];

        firstPlayer->StartNewGame();
        secondPlayer->StartNewGame();
        int roundsCount = distribution(gen);
        for (int round = 0; round < roundsCount; ++round) {
            Move firstMove = firstPlayer->MakeMove();
            Move secondMove = secondPlayer->MakeMove();
            if (firstMove == Move::SPLIT) {
                score[firstIndex] -= 1;
                score[secondIndex] += 3;
            }
            if (secondMove == Move::SPLIT) {
                score[firstIndex] += 3;
                score[secondIndex] -= 1;
            }
            firstPlayer->GetOpponentMove(secondMove);
            secondPlayer->GetOpponentMove(firstMove);
        }
    }
    int scoreA = 0;
    for (int i = 0; i < PARTICIPANTS_COUNT; ++i) {
        scoreA += score[i];
    }
    int scoreB = 0;
    for (int i = PARTICIPANTS_COUNT; i < 2 * PARTICIPANTS_COUNT; ++i) {
        scoreB += score[i];
    }
    return {scoreA, scoreB};
}

template <typename FirstCat, typename SecondCat>
void simulate(int iters) {
    int wins = 0;
    int loses = 0;
    for (int iter = 0; iter < iters; ++iter) {
        Simulation<FirstCat, SecondCat> sim;
        sim.Setup();
        auto result = sim.Run();
        if (result.first > result.second) ++wins;
        else if (result.first < result.second) ++loses;
    }
    cout << "Score : " << wins << " - " << loses << endl;
    if (wins + loses < iters) {
        cout << "Other " << iters - wins - loses << " games are ties" << endl;
    }
}


}  // namespace testing

