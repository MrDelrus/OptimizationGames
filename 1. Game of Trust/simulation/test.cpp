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

class A : public Participant { // Paste there your implementation
public:
    explicit A(int) {}
    void StartNewGame() override {}
    Move MakeMove() override {
        return Move::SPLIT;
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

class SplitCat : public Participant {
public:
    explicit SplitCat(int);
    void StartNewGame() override;
    Move MakeMove() override;
    void GetOpponentMove(Move move) override;
};
class StealCat : public Participant {
public:
    explicit StealCat(int);
    void StartNewGame() override;
    Move MakeMove() override;
    void GetOpponentMove(Move move) override;
};
class Grudger : public Participant {
public:
    explicit Grudger(int);
    void StartNewGame() override;
    Move MakeMove() override;
    void GetOpponentMove(Move move) override;
private:
    bool believe;
};
class CopyCat : public Participant {
public:
    explicit CopyCat(int);
    void StartNewGame() override;
    Move MakeMove() override;
    void GetOpponentMove(Move move) override;
private:
    optional<Move> last;
};

template <typename FirstCat, typename SecondCat>
void TEST_GENERAL();

template <typename YourCat>
void TEST1() {
    cout << "Start test versus ALL COOPERATE" << endl;
    TEST_GENERAL<YourCat, SplitCat>();
    cout << "Test passed!\n" << endl;
}

template <typename YourCat>
void TEST2() {
    cout << "Start test versus ALL CHEAT" << endl;
    TEST_GENERAL<YourCat, StealCat>();
    cout << "Test passed!\n" << endl;
}

template <typename YourCat>
void TEST3() {
    cout << "Start test versus Grudger" << endl;
    TEST_GENERAL<YourCat, Grudger>();
    cout << "Test passed!\n" << endl;
}

template <typename YourCat>
void TEST4() {
    cout << "Start test versus Copycat" << endl;
    TEST_GENERAL<YourCat, CopyCat>();
    cout << "Test passed!\n" << endl;
}

template <typename YourCat>
void TEST_ALL() {
    TEST1<YourCat>();
    TEST2<YourCat>();
    TEST3<YourCat>();
    TEST4<YourCat>();
}

}  // namespace testing

int main() {

    testing::TEST_ALL<A>();

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
int simulate(int iters) {
    int wins = 0;
    for (int iter = 0; iter < iters; ++iter) {
        Simulation<FirstCat, SecondCat> sim;
        sim.Setup();
        auto result = sim.Run();
        if (result.first > result.second) ++wins;
    }
    return wins;
}

template <typename FirstCat, typename SecondCat>
void TEST_GENERAL() {
    static const int iters = 20;
    static const int threshold = 12;
    if (simulate<FirstCat, SecondCat>(iters) < threshold) {
        throw std::runtime_error("You lost!");
    }
}

// CATS IMPLEMENTATIONS

// SplitCat

SplitCat::SplitCat(int) {}
void SplitCat::StartNewGame() {}
Move SplitCat::MakeMove() {
    return Move::SPLIT;
}
void SplitCat::GetOpponentMove(Move) {}

// StealCat

StealCat::StealCat(int) {}
void StealCat::StartNewGame() {}
Move StealCat::MakeMove() {
    return Move::STEAL;
}
void StealCat::GetOpponentMove(Move) {}

// Grudger

Grudger::Grudger(int) {}
void Grudger::StartNewGame() {
    believe = true;
}
Move Grudger::MakeMove() {
    if (believe) {
        return Move::SPLIT;
    }
    return Move::STEAL;
}
void Grudger::GetOpponentMove(Move move) {
    if (move == Move::STEAL) {
        believe = false;
    }
}

// CopyCat

CopyCat::CopyCat(int) {}
void CopyCat::StartNewGame() {
    last.reset();
}
Move CopyCat::MakeMove() {
    if (last.has_value()) {
        return last.value();
    }
    return Move::SPLIT;
}
void CopyCat::GetOpponentMove(Move move) {
    last.emplace(move);
}

}  // namespace testing
