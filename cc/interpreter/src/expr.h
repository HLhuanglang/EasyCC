#pragma once

#include "token.h"
#include <any>
#include <memory>
#include <utility> // std::move
#include <vector>

struct Binary;
struct Grouping;
struct Literal;
struct Unary;

struct ExprVisitor {
    virtual std::any visit_binary_expr(std::shared_ptr<Binary> expr) = 0;
    virtual std::any visit_grouping_expr(std::shared_ptr<Grouping> expr) = 0;
    virtual std::any visit_literal_expr(std::shared_ptr<Literal> expr) = 0;
    virtual std::any visit_unary_expr(std::shared_ptr<Unary> expr) = 0;
    virtual ~ExprVisitor() = default;
};

struct Expr {
    virtual std::any accept(ExprVisitor &visitor) = 0;
};

struct Binary : Expr, public std::enable_shared_from_this<Binary> {
    Binary(std::shared_ptr<Expr> m_left, Token m_op, std::shared_ptr<Expr> m_right)
        : m_left{std::move(m_left)}, m_op{std::move(m_op)}, m_right{std::move(m_right)} {}

    std::any accept(ExprVisitor &visitor) override {
        return visitor.visit_binary_expr(shared_from_this());
    }

    const std::shared_ptr<Expr> m_left;
    const Token m_op;
    const std::shared_ptr<Expr> m_right;
};

struct Grouping : Expr, public std::enable_shared_from_this<Grouping> {
    Grouping(std::shared_ptr<Expr> m_expression)
        : m_expression{std::move(m_expression)} {}

    std::any accept(ExprVisitor &visitor) override {
        return visitor.visit_grouping_expr(shared_from_this());
    }

    const std::shared_ptr<Expr> m_expression;
};

struct Literal : Expr, public std::enable_shared_from_this<Literal> {
    Literal(std::any m_value)
        : m_value{std::move(m_value)} {}

    std::any accept(ExprVisitor &visitor) override {
        return visitor.visit_literal_expr(shared_from_this());
    }

    const std::any m_value;
};

struct Unary : Expr, public std::enable_shared_from_this<Unary> {
    Unary(Token m_op, std::shared_ptr<Expr> m_right)
        : m_op{std::move(m_op)}, m_right{std::move(m_right)} {}

    std::any accept(ExprVisitor &visitor) override {
        return visitor.visit_unary_expr(shared_from_this());
    }

    const Token m_op;
    const std::shared_ptr<Expr> m_right;
};
