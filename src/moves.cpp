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
  const Piece *piece = board.get_piece(square);
  if (!piece)
    return;

  Side side = piece->get_side();
  int direction = (side == Side::White) ? -1 : 1;
  int start_rank = (side == Side::White) ? 6 : 1;

  int file = Board::file(square);
  int rank = Board::rank(square);

  int forward_one = square + (direction * 8);
  if (forward_one >= 0 && forward_one < 64) {
    const Piece *target = board.get_piece(forward_one);

    if (!target) {

      int target_rank = Board::rank(forward_one);
      PieceType promo = (target_rank == 0 || target_rank == 7)
                            ? PieceType::Queen
                            : PieceType::None;

      moves.emplace_back(square, forward_one, promo);

      if (rank == start_rank) {
        int forward_two = square + (direction * 16);
        const Piece *target_two = board.get_piece(forward_two);

        if (!target_two) {
          moves.emplace_back(square, forward_two);
        }
      }
    }
  }

  std::array<int, 2> capture_offsets = {direction * 8 - 1, direction * 8 + 1};

  for (int offset : capture_offsets) {
    int target = square + offset;

    if (target < 0 || target >= 64)
      continue;

    int target_file = Board::file(target);

    if (std::abs(target_file - file) != 1)
      continue;

    const Piece *target_piece = board.get_piece(target);

    if (target_piece && target_piece->get_side() != side) {
      int target_rank = Board::rank(target);

      PieceType promo = (target_rank == 7 || target_rank == 0)
                            ? PieceType::Queen
                            : PieceType::None;
      moves.emplace_back(square, target, promo);
    }
  }

  // TODO: En passant
}

void MoveGenerator::generate_knight_moves(const Board &board, int square,
                                          std::vector<Move> &moves) {
  const Piece *piece = board.get_piece(square);
  if (!piece)
    return;

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
  static const std::vector<int> directions = {-9, 9, -7, 7};

  generate_sliding_moves(board, square, directions, moves);
}

void MoveGenerator::generate_rook_moves(const Board &board, int square,
                                        std::vector<Move> &moves) {
  static const std::vector<int> directions = {-8, 8, -1, 1};

  generate_sliding_moves(board, square, directions, moves);
}

void MoveGenerator::generate_queen_moves(const Board &board, int square,
                                         std::vector<Move> &moves) {}

void MoveGenerator::generate_king_moves(const Board &board, int square,
                                        std::vector<Move> &moves) {}

void MoveGenerator::generate_sliding_moves(const Board &board, int square,
                                           const std::vector<int> &directions,
                                           std::vector<Move> &moves) {
  const Piece *piece = board.get_piece(square);
  if (!piece)
    return;

  for (int dir : directions) {
    int target = square + dir;

    while (target >= 0 && target < 64) {
      int from_file = Board::file(target - dir); // File of previous square
      int target_file = Board::file(target);

      // Check for horizontal wrapping (moving left/right shouldn't jump rows)
      if (std::abs(dir) == 1 && std::abs(target_file - from_file) > 1) {
        break;
      }

      const Piece *target_piece = board.get_piece(target);

      // Empty square - can move here and continue sliding
      if (!target_piece) {
        moves.emplace_back(square, target);
        target += dir;
        continue;
      }

      // Hit own piece - stop here
      if (target_piece->get_side() == piece->get_side()) {
        break;
      }

      // Hit enemy piece - can capture but can't continue
      moves.emplace_back(square, target);
      break;
    }
  }
}
