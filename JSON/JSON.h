#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <variant>
#include <exception>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>

namespace JSON {
	class JsonValue {
	public:
		using JsonObject = std::unordered_map<std::string, JsonValue>;
		using JsonArray = std::vector<JsonValue>;
		using Type = std::variant<
			JsonObject,
			JsonArray,
			std::string,
			std::nullptr_t
			/*bool,
			double,
			int*/
		>;

	private:
		Type m_value;

	public:
		// Constructors
		JsonValue() = default;
		explicit JsonValue(const JsonArray& arr);
		explicit JsonValue(const JsonObject& obj);
		explicit JsonValue(int val);
		explicit JsonValue(double val);
		explicit JsonValue(bool val);
		explicit JsonValue(const std::string& str);
		explicit JsonValue(const char* str);
		explicit JsonValue(std::nullptr_t);

		~JsonValue() = default;

		// copy, move constructors
		JsonValue(const JsonValue& jObj);
		JsonValue(JsonValue&& jObj) noexcept;

		// copy, move assignments
		JsonValue& operator=(const JsonValue& jObj);
		JsonValue& operator=(JsonValue&& jObj) noexcept;

		bool isInt() const;
		bool isDouble() const;
		bool isBool() const;
		bool isString() const;
		bool isArray() const;
		bool isObject() const;

		int asInt() const;
		double asDouble() const;
		bool asBool() const;
		const std::string& asString() const;
		JsonArray asArray() const;
		JsonObject asObject() const;

		JsonValue operator[](const std::string& key) const;
		JsonValue operator[](size_t index) const;  // for arrays

		const Type& getValue() const;

		static std::vector<std::string> tokenize(const std::string& str);
		static JsonValue parse(const std::string& str);
		static JsonValue parseValue(const std::vector<std::string>& tokens, size_t& index);

		static JsonValue array(const std::vector<JsonValue>& el);
		static JsonValue object(const std::unordered_map<std::string, JsonValue>& el);
	
		// Helper functions
		static bool isValidToken(const std::string& token);

		static std::ostream& print_array(std::ostream& os, const JsonArray& arr);
		static std::ostream& print_object(std::ostream& os, const JsonObject& obj);

	private:
		static JsonObject parseObject(const std::vector<std::string>& tokens, size_t& index);
		static JsonArray parseArray(const std::vector<std::string>& tokens, size_t& index);
	};

	std::ostream& operator<<(std::ostream& os, const JsonValue& value);
}
