// :::::::::::::::::::::::::::::::::::::::::::::: Test :::::::::::::::::::::::::::::::::::::::::::::::::::

#include <iostream>
#include "JSON.h"

int main() {
    using namespace JSON;

    // Create JSON object using the object() and array() methods
    JsonValue jsonObj = JsonValue::object({
        {"name", JsonValue("Elina")},
        {"age", JsonValue(21)},
        {"is_student", JsonValue(true)},
        {"scores", JsonValue::array({JsonValue(95), JsonValue(87), JsonValue(78)})},
        {"address", JsonValue::object({
            {"city", JsonValue("Yerevan")},
            {"zip", JsonValue(1234)}
        })}
    });

    std::cout << "Original JSON Object:\n" << jsonObj << "\n";

    // Accessing values with operator[]
    std::cout << "\n-------- Accessing values --------\n";
    std::cout << "age: " << jsonObj["age"] << '\n';
    std::cout << "is_student: " << jsonObj["is_student"] << '\n';

    JsonValue::JsonObject addr = jsonObj["address"].asObject();
    for (auto& [key, value] : addr) {
        std::cout << key << ": " << value << '\n';
    }

    try {
        std::cout << jsonObj["surname"] << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    
    // Accessing array
    if (jsonObj.asObject().count("scores") && jsonObj.asObject().at("scores").isArray()) {
        auto scores = jsonObj.asObject().at("scores").asArray();
        std::cout << "Scores: ";
        for (size_t i = 0; i < scores.size(); i++) {
            std::cout << scores[i].asInt() << " ";
        }
        std::cout << "\n";
    }

    // Parse a JSON-like string
    std::string jsonStr1 = R"({   "project": "Compiler", "done":     false, "team members": 3, "team": ["Alice", "Bob"]})";
    std::cout << "\nOriginal JSON-like string:\n " << jsonStr1 << "\n";
    JsonValue parsed1 = JsonValue::parse(jsonStr1);
    std::cout << "\nParsed JSON from string:\n" << parsed1 << "\n";

    std::cout << "\n-------- Type Checking --------\n";
    try {
        if (parsed1.asObject().at("team members").isInt()) {
            std::cout << "Team members is an integer: " << parsed1.asObject().at("team members").asInt() << "\n";
        }
        if (parsed1.asObject().at("done").isBool()) {
            std::cout << "Done is a bool: " << std::boolalpha << parsed1.asObject().at("done").asBool() << "\n";
        }
        if (parsed1.asObject().at("project").isString()) {
            std::cout << "Project is a string: " << parsed1.asObject().at("project").asString() << "\n";
        }
    }
    catch (const std::exception& e) {
        std::cout << "Exception during value access: " << e.what() << "\n";
    }
    
    std::string jsonStr2 = R"({
           "DocumentType": 1,
           "No.": "S-ORD101001",
            "SellToCustNo": "10000",
            "PostingDate": "2023-04-02",
            "Lines": [
                {
                    "LineNo": 10000,
                    "Type": 2,
                    "No": "1996-S",
                    "Quantity": 12,
                    "UnitPrice": 1397.3
                },
                {
                    "LineNo": 20000,
                    "Type": 2,
                    "No": "1900-S",
                    "Quantity": 4,
                    "UnitPrice": 192.8
                }
            ]            
        })";

    JsonValue parsed2 = JsonValue::parse(jsonStr2);
    std::cout << "\nParsed JSON from string:\n" << parsed2 << "\n\n";

    // Parse simple values
    std::cout << "\n-------- Parsing simple values --------\n";

    std::string str = R"("Hello")";
    JsonValue parsedStr = JsonValue::parse(str);
    std::cout << "Testing simple string: " << parsedStr << std::endl;
    std::string numStr = "52.3";
    JsonValue parsedNum = JsonValue::parse(numStr);
    std::cout << "Testing number: " << parsedNum << std::endl;

    std::string boolStr = "true";
    JsonValue parsedBool = JsonValue::parse(boolStr);
    std::cout << "Testing boolean: " << parsedBool << std::endl;

    std::string nullStr = "null";
    JsonValue parsedNull = JsonValue::parse(nullStr);
    std::cout << "Testing null: " << parsedNull << std::endl;

    // Parse empty structures
    std::string emptyObjStr = "{}";
    JsonValue parsedObj = JsonValue::parse(emptyObjStr);
    std::cout << "Testing empty object: " << parsedObj << std::endl;

    std::string emptyArrayStr = "[]";
    JsonValue parsedArr = JsonValue::parse(emptyArrayStr);
    std::cout << "Testing empty array: " << parsedArr << std::endl;

    
    
    // Parse invalid inputs
    std::cout << "\n-------- Parsing Invalid JSON Strings --------\n";

    std::vector<std::string> invalidInputs = {
        R"({  missing_colon  : "value"})",
        R"(["extra comma",, "value"])",
        R"([unquoted, values, here])"
    };

    for (const auto& input : invalidInputs) {
        try {
            std::cout << "Trying to parse: " << input << "\n";
            JsonValue result = JsonValue::parse(input);
            std::cout << "Parsed: " << result << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
        std::cout << "\n";
    }

    std::cout << "\n-------- Testing Escaped Quotes in Strings --------\n";
    
    std::vector<std::string> escapedQuote = {
        R"({"message": "He said \"Hello World\""})",
        R"({"path": "C:\\Program Files\\App\\config.json"})"
    };

    for (const auto& input : escapedQuote) {
        try {
            std::cout << "Trying to parse: " << input << "\n";
            JsonValue result = JsonValue::parse(input);
            std::cout << "Parsed: " << result << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
        std::cout << "\n";
    }

    return 0;
}
