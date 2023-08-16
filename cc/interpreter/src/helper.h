#ifndef __EASYCC_HELPER_H
#define __EASYCC_HELPER_H

// 表达式 1 + 2 * 3 -4
// AST树
//     -
//    / \
//   +   4
//  / \
// 1   *
//    / \
//   2   3
// 预期输出(- ((+ 1,(* 2,3)),4)

#include "expr.h"
#include <any>
#include <cassert>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <type_traits>

class AstPrinter : public ExprVisitor {
 public:
    std::string print(const std::shared_ptr<Expr> &expr) {
        return std::any_cast<std::string>(expr->accept(*this));
    }

    std::any visit_binary_expr(std::shared_ptr<Binary> expr) override {
        return _parenthesize(expr->m_op.m_lexeme,
                             expr->m_left, expr->m_right);
    }

    std::any visit_grouping_expr(
        std::shared_ptr<Grouping> expr) override {
        return _parenthesize("group", expr->m_expression);
    }

    std::any visit_literal_expr(std::shared_ptr<Literal> expr) override {
        const auto &value_type = expr->m_value.type();

        if (value_type == typeid(nullptr)) {
            return "nil";
        } else if (value_type == typeid(std::string)) {
            return std::any_cast<std::string>(expr->m_value);
        } else if (value_type == typeid(double)) {
            return std::to_string(std::any_cast<double>(expr->m_value));
        } else if (value_type == typeid(int)) {
            return std::to_string(std::any_cast<int>(expr->m_value));
        } else if (value_type == typeid(bool)) {
            return std::any_cast<bool>(expr->m_value) ? "true" : "false";
        }

        return "Error in visitLiteralExpr: literal type not recognized.";
    }

    std::any visit_unary_expr(std::shared_ptr<Unary> expr) override {
        return _parenthesize(expr->m_op.m_lexeme, expr->m_right);
    }

 private:
    template <class... E>
    std::string _parenthesize(std::string_view name, E... expr) {
        assert((... && std::is_same_v<E, std::shared_ptr<Expr>>));

        std::ostringstream builder;

        builder << "(" << name;
        ((builder << " " << print(expr)), ...);
        builder << ")";

        return builder.str();
    }
};

#endif // !__EASYCC_HELPER_H
