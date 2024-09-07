class A : public Participant { // Grudger
public:
    explicit A(int number) {}
    void StartNewGame() override {
        believe = true;
    }
    Move MakeMove() override {
        if (believe) {
            return Move::SPLIT;
        }
        return Move::STEAL;
    }
    void GetOpponentMove(Move move) override {
        if (move == Move::STEAL) {
            believe = false;
        }
    }
private:
    bool believe;
};
