#pragma once

#include "board.hpp"
#include "types.hpp"
#include <vector>

struct Move {
  int from;
  int to;

  Move(int from, int to) : from{from}, to{to} {}

  PieceType promotion = PieceType::None;
};

class MoveGenerator {
public:
  // Generate all pseudo-legal moves for a piece at the given square
  static std::vector<Move> generate_pseudo_legal_moves(const Board &board,
                                                       int square);

  // Generate all legal moves for a piece
  static std::vector<Move> generate_legal_moves(const Board &board, int square);

  // Check if a specific move is legal
  static bool is_legal(const Board &board, const Move &move);

  // Check if the current side is in check
  static bool is_in_check(const Board &board, Side side);

  // Check if a square is attacked by the given side
  static bool is_square_attacked(const Board &board, int square,
                                 Side attacking_side);

private:
  // Helper functions for generating moves for specific piece types
  static void generate_pawn_moves(const Board &board, int square,
                                  std::vector<Move> &moves);
  static void generate_knight_moves(const Board &board, int square,
                                    std::vector<Move> &moves);
  static void generate_bishop_moves(const Board &board, int square,
                                    std::vector<Move> &moves);
  static void generate_rook_moves(const Board &board, int square,
                                  std::vector<Move> &moves);
  static void generate_queen_moves(const Board &board, int square,
                                   std::vector<Move> &moves);
  static void generate_king_moves(const Board &board, int square,
                                  std::vector<Move> &moves);

  // Helper for sliding pieces (bishop, rook, queen)
  static void generate_sliding_moves(const Board &board, int square,
                                     const std::vector<int> &directions,
                                     std::vector<Move> &moves);

private:
};
