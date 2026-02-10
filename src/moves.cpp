#include "moves.hpp"

std::vector<Move> MoveGenerator::generate_pseudo_legal_moves(const Board &board,
                                                             int square) {

  const Piece *piece = board.get_piece(square);
  std::vector<Move> moves;

  if (!piece)
    return moves;

  if (piece->get_side() != board.get_turn())
    return moves;


  switch (piece->get_type()) {
  case PieceType::Pawn:
    generate_pawn_moves(board, square, moves);
    break;

  case PieceType::Knight:
    generate_knight_moves(board, square, moves);
    break;

  case PieceType::Bishop:
    generate_bishop_moves(board, square, moves);
    break;

  case PieceType::Rook:
    generate_rook_moves(board, square, moves);
    break;

  case PieceType::Queen:
    generate_queen_moves(board, square, moves);
    break;

  case PieceType::King:
    generate_king_moves(board, square, moves);
    break;

  default:
    break;
  }

  return moves;
}

void MoveGenerator::generate_pawn_moves(const Board &board, int square,
std::vector<Move> &moves) {

}

void MoveGenerator::generate_knight_moves(const Board &board, int square,
                                          std::vector<Move> &moves) {
  const Piece *piece = board.get_piece(square);

  static const std::array<int, 8> knight_offsets = {-17, -15, -10, -6,
                                                    6,   10,  15,  17};

  int file = Board::file(square);
  int rank = Board::rank(square);

  for (int offset : knight_offsets) {
    int target = square + offset;

    if (target < 0 || target >= 64)
      continue;

    int target_file = Board::file(target);
    int target_rank = Board::rank(target);

    // check if knight wrapped around the board
    if (std::abs(target_file - file) > 2 || std::abs(target_rank - rank) > 2) {
      continue;
    }

    const Piece *target_piece = board.get_piece(target);

    // can't capture own piece
    if (target_piece && target_piece->get_side() == piece->get_side()) {
      continue;
    }

    moves.emplace_back(square, target);
  }
}

void MoveGenerator::generate_bishop_moves(const Board &board, int square,
                                          std::vector<Move> &moves) {
  static const std::vector<int> directions = { -9, 9, -7, 7 };

  generate_sliding_moves(board, square, directions, moves);
}

void MoveGenerator::generate_rook_moves(const Board &board, int square,
                                        std::vector<Move> &moves) {
  static const std::vector<int> directions = {-8, 8, -1, 1};

  generate_sliding_moves(board, square, directions, moves);
}

void MoveGenerator::generate_queen_moves(const Board &board, int square,
std::vector<Move> &moves) {
}

void MoveGenerator::generate_king_moves(const Board &board, int square,
std::vector<Move> &moves) {
}

void MoveGenerator::generate_sliding_moves(const Board &board, int square,
                                           const std::vector<int> &directions,
                                           std::vector<Move> &moves) {
  const Piece *piece = board.get_piece(square);
  if (!piece)
    return;

  for (int dir : directions) {
    int target = square + dir;

    int from_file = Board::file(square);

    while (target >= 0 && target < 64) {
      int target_file = Board::file(target);

      // wrapping
      if (std::abs(dir) == 1 && std::abs(target_file - from_file) > 1) {
        break;
      }

      const Piece *target_piece = board.get_piece(target);

      // empty square
      if (!target_piece || target_piece->get_side() == Side::None) {
        moves.emplace_back(square, target);

        target += dir;
        continue;
      }

      if (target_piece->get_side() == piece->get_side()) {
        break;
      }

      // hit enemy piece! can capture but can't continue
      moves.emplace_back(square, target);
      break;
    }
  }
}
