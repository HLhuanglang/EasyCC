#include <algorithm> // std::find_if_not
#include <cctype>    // std::tolower, std::isspace
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <utility> // std::move
#include <vector>

std::vector<std::string_view> split(std::string_view str,
                                    std::string_view delim) {
    std::vector<std::string_view> out;

    std::string_view::size_type start = 0;
    std::string_view::size_type end = str.find(delim);

    while (end != std::string_view::npos) {
        out.push_back(str.substr(start, end - start));

        start = end + delim.length();
        end = str.find(delim, start);
    }

    out.push_back(str.substr(start, end - start));

    return out;
}

std::string_view trim(std::string_view str) {
    auto isspace = [](auto c) {
        return std::isspace(c);
    };

    const auto *start = std::find_if_not(str.begin(), str.end(), isspace);
    const auto *end = std::find_if_not(str.rbegin(), str.rend(),
                                       isspace)
                          .base();

    return {start, std::string_view::size_type(end - start)};
}

std::string to_lower_case(std::string_view str) {
    std::string out;
    std::transform(str.begin(), str.end(), std::back_inserter(out),
                   [](unsigned char c) {
                       return std::tolower(c);
                   });
    return out;
}

// In C++ we cannot rely on garbage collection to clean up our pointer
// messes for us. Instead of having to worry about calling delete
// every time we're done with some heap memory, we can dump this job
// onto std::shared_ptr. This function lets us use a '*' in our
// metaprogram to indicate that we actually want a smart pointer.
std::string fix_pointer(std::string_view field) {
    std::ostringstream out;
    std::string_view type = split(field, " ")[0];
    std::string_view name = split(field, " ")[1];
    bool close_bracket = false;

    if (type.substr(0, 12) == "std::vector<") {
        out << "std::vector<";
        type = type.substr(12, type.length() - 13); // ignores closing '>'
        close_bracket = true;
    }

    if (type.back() == '*') {
        type.remove_suffix(1);
        out << "std::shared_ptr<" << type << ">";
    } else {
        out << type;
    }

    if (close_bracket) {
        out << ">";
    }
    out << " " << name;

    return out.str();
}

void define_visitor(
    std::ofstream &writer, std::string_view base_name,
    const std::vector<std::string_view> &types) {
    writer << "struct " << base_name << "Visitor {\n";

    for (std::string_view type : types) {
        std::string_view type_name = trim(split(type, ":")[0]);
        writer << "  virtual std::any visit_" << to_lower_case(type_name) << "_" << to_lower_case(base_name) << "(std::shared_ptr<" << type_name << "> " << to_lower_case(base_name) << ") = 0;\n";
    }

    writer << "  virtual ~" << base_name << "Visitor() = default;\n";
    writer << "};\n";
}

void define_type(std::ofstream &writer, std::string_view base_name, std::string_view class_name, std::string_view filed_list) {
    writer << "struct " << class_name << ": " << base_name << ", public std::enable_shared_from_this<" << class_name << "> {\n";

    // Constructor.
    writer << "  " << class_name << "(";

    std::vector<std::string_view> fields = split(filed_list, ", ");
    writer << fix_pointer(fields[0]);

    for (int i = 1; i < fields.size(); ++i) {
        writer << ", " << fix_pointer(fields[i]);
    }

    writer << ")\n"
           << "    : ";

    // Store parameters in fields.
    std::string_view name = split(fields[0], " ")[1];
    writer << name << "{std::move(" << name << ")}";

    for (int i = 1; i < fields.size(); ++i) {
        name = split(fields[i], " ")[1];
        writer << ", " << name << "{std::move(" << name << ")}";
    }

    writer << "\n"
           << "  {}\n";

    // Visitor pattern.
    writer << "\n"
              "  std::any accept("
           << base_name << "Visitor& visitor)"
                           " override {\n"
                           "    return visitor.visit_"
           << to_lower_case(class_name) << "_" << to_lower_case(base_name) << "(shared_from_this());\n"
                                                                              "  }\n";

    // Fields.
    writer << "\n";
    for (std::string_view field : fields) {
        writer << "  const " << fix_pointer(field) << ";\n";
    }

    writer << "};\n\n";
}

void define_ast(
    const std::string &outputDir, const std::string &base_name,
    const std::vector<std::string_view> &types) {
    std::string path = outputDir + "/" + to_lower_case(base_name) + ".h";
    std::ofstream writer{path};

    writer << "#pragma once\n"
              "\n"
              "#include <any>\n"
              "#include <memory>\n"
              "#include <utility>  // std::move\n"
              "#include <vector>\n"
              "#include \"token.h\"\n"
              "\n";

    // Forward declare the AST classes.
    for (std::string_view type : types) {
        std::string_view class_name = trim(split(type, ": ")[0]);
        writer << "struct " << class_name << ";\n";
    }

    // Visitor.
    writer << "\n";
    define_visitor(writer, base_name, types);

    // The base class.
    // C++ does not allow virtual methods to be templated. That means
    // multiple accept signatures are out -- at least if we don't want
    // to over complicate things. An alternative is to use std::any,
    // which holds values of any type in a type-safe way. Classes
    // implementing the base class are then required to cast the return
    // value to the expected type inside their member functions.
    writer << "\n"
              "struct "
           << base_name << " {\n"
                           "  virtual std::any accept("
           << base_name << "Visitor& visitor) = 0;\n"
                           "};\n\n";

    // The AST classes.
    for (std::string_view type : types) {
        std::string_view class_name = trim(split(type, ": ")[0]);
        std::string_view fields = trim(split(type, ": ")[1]);
        define_type(writer, base_name, class_name, fields);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: generate_ast <output directory>\n";
        std::exit(64);
    }
    std::string output_dir = argv[1];

    // clang-format off
    define_ast(output_dir, "Expr", {
        "Binary   : Expr* m_left, Token m_op, Expr* m_right", 
        "Grouping : Expr* m_expression", 
        "Literal  : std::any m_value", 
        "Unary    : Token m_op, Expr* m_right"});
    // clang-format on
}
