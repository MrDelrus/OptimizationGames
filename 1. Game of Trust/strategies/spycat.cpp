class A : public Participant { // Spycat
public:
    explicit A(int number) {}
    void StartNewGame() override {
        current_turn = 0;
        believe = true;
    }
    Move MakeMove() override {
        if (!believe) return Move::STEAL;
        if (current_turn == 0) return Move::STEAL;
        if (current_turn == 1) return Move::SPLIT;
        return Move::SPLIT;
    }
    void GetOpponentMove(Move move) override {
        if (current_turn == 0 && move == Move::SPLIT) believe = false;
        if (current_turn == 1 && move == Move::STEAL) believe = false;
        if (current_turn >= 2 && move == Move::STEAL) believe = false;
        current_turn += 1;
    }
private:
    int current_turn;
    bool believe;
};
