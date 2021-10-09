#pragma once

namespace gameModule {
    class Piece;

    class PieceFactory {
        PieceFactory();
    public:
        ~PieceFactory();

        static PieceFactory* getInstance();
        static void buildFigure(Piece* piece, char c);
    private:
        static PieceFactory* instance;
    };
} // namespace gameModule