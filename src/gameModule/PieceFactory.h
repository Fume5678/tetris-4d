#pragma once

namespace gameModule {
    class Piece;

    class PieceFactory {
        PieceFactory();
    public:
        ~PieceFactory();

        static PieceFactory* getInstance();
        Piece* buildFigure( char c);
    private:
        static PieceFactory* instance;
    };
} // namespace gameModule