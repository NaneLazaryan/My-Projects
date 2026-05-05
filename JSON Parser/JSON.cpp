#include "JSON.h"

using namespace JSON;

// Constructors
JsonValue::JsonValue(const JsonArray& arr) : m_value(arr) {}
JsonValue::JsonValue(const JsonObject& obj) : m_value(obj) {}
JsonValue::JsonValue(int val) : m_value(boost::lexical_cast<std::string>(val)) {}
JsonValue::JsonValue(double val) : m_value(boost::lexical_cast<std::string>(val)) {}
JsonValue::JsonValue(bool val) { m_value = val ? "true" : "false"; }
JsonValue::JsonValue(const std::string& str) : m_value(str) {}
JsonValue::JsonValue(const char* str) { m_value = "\"" + std::string(str) + "\""; }
JsonValue::JsonValue(std::nullptr_t) : m_value(nullptr) {}

// For constructing Json array
JsonValue JsonValue::array(const std::vector<JsonValue>& el) {
	return JsonValue(JsonArray(el));
}

// For constructing Json object
JsonValue JsonValue::object(const std::unordered_map<std::string, JsonValue>& el) {
	return JsonValue(JsonObject(el));
}

// copy, move constructors
JsonValue::JsonValue(const JsonValue& jObj) : m_value(jObj.m_value) {}
JsonValue::JsonValue(JsonValue&& jObj) noexcept : m_value(std::move(jObj.m_value)) {}

// copy, move assignments
JsonValue& JsonValue::operator=(const JsonValue& jObj) { 
	m_value = jObj.m_value; 
	return *this;
}
JsonValue& JsonValue::operator=(JsonValue&& jObj) noexcept { 
	m_value = std::move(jObj.m_value); 
	return *this;
}

const JsonValue::Type& JsonValue::getValue() const {
	return m_value;
}

// Check m_value's type
bool JsonValue::isInt() const {
	try {
		std::string value = std::get<std::string>(m_value);
		boost::lexical_cast<int>(value);
		return true;
	}
	catch (const boost::bad_lexical_cast&) {
		return false;
	}
}

bool JsonValue::isDouble() const {
	try {
		std::string value = std::get<std::string>(m_value);
		boost::lexical_cast<double>(value);
		return true;
	}
	catch (const boost::bad_lexical_cast&) {
		return false;
	}
}

bool JsonValue::isBool() const {
	if (!std::holds_alternative<std::string>(m_value))
		return false;

	const std::string& value = std::get<std::string>(m_value);
	return value == "true" || value == "false";
}

bool JsonValue::isString() const {
	return (std::holds_alternative<std::string>(m_value) && !isInt() && !isDouble() && !isBool());
}

bool JsonValue::isArray() const {
	return std::holds_alternative<JsonArray>(m_value);
}

bool JsonValue::isObject() const {
	return std::holds_alternative<JsonObject>(m_value);
}

// Get m_value as:
int JsonValue::asInt() const {
	if (!isInt()) throw std::bad_variant_access();
	return boost::lexical_cast<int>(std::get<std::string>(m_value));
}

double JsonValue::asDouble() const {
	if (!isDouble()) throw std::bad_variant_access();
	return boost::lexical_cast<double>(std::get<std::string>(m_value));
}

bool JsonValue::asBool() const {
	if (!isBool()) throw std::bad_variant_access();

	const std::string& value = std::get<std::string>(m_value);
	return value == "true";
}

const std::string& JsonValue::asString() const {
	if(!isString()) throw std::bad_variant_access();
	return std::get<std::string>(m_value);
}

JsonValue::JsonArray JsonValue::asArray() const {
	return std::get<JsonArray>(m_value); 
}

JsonValue::JsonObject JsonValue::asObject() const {
	return std::get<JsonObject>(m_value);  
}

JsonValue JsonValue::operator[](const std::string& key) const {
	if (isObject()) {
		const JsonObject& obj = std::get<JsonObject>(m_value);
	
		auto it = obj.find(key);
		if (it == obj.end()) 
			throw std::runtime_error("Key '" + key + "' not found in JSON object");

		auto &[k, value] = *it;
		return value;
	}
	else if (isArray()) {  //  for example: arr["1"]
		try {
			size_t index = boost::lexical_cast<size_t>(key);
			const JsonArray& arr = std::get<JsonArray>(m_value);
			if (index >= arr.size()) 
				throw std::runtime_error("Array index " + std::to_string(index) + " out of bounds");

			return arr[index];
		}
		catch (const boost::bad_lexical_cast&) {
			throw std::runtime_error("Invalid array index: " + key);
		}
	}
	
	throw std::runtime_error("Cannot use operator[] on non-object/non-array JSON value");
}

// operator[] for arrays
JsonValue JsonValue::operator[](size_t index) const {
	if (!isArray()) 
		throw std::runtime_error("Cannot use operator[] with index on non-array JSON value");

	const JsonArray& arr = std::get<JsonArray>(m_value);
	if (index >= arr.size()) 
		throw std::runtime_error("Array index " + std::to_string(index) + " out of bounds");

	return arr[index];
}

std::vector<std::string> JsonValue::tokenize(const std::string& str) {
	std::vector<std::string> tokens;
	std::string current;
	bool inString = false;
	bool escape = false;

	for (char c : str) {
		if (inString) {
			if (escape) {
				if (c == '"' || c == '\\') {
					current += c;
				} else {
					current += '\\';
					current += c;
				}
				escape = false;
			}
			else if (c == '\\') {
				escape = true;
			}
			else if (c == '"') {
				inString = false;
				tokens.push_back('"' + current + '"');
				current.clear();
			}
			else {
				current += c;
			}
		}
		else {
			if (c == '"') {
				inString = true;
			}
			else if (c == '[' || c == ']' || c == '{' || c == '}' || c == ':' || c == ',') {
				if (!current.empty()) {  
					tokens.push_back(current);
					current.clear();
				}
				tokens.push_back(std::string(1, c));
			}
			else if (std::isspace(c)) {  // Skip all whitespace
				if (!current.empty()) {
					tokens.push_back(current);
					current.clear();
				}
				
			}
			else {
				current += c;
			}
		}
	}

	if (!current.empty()) {
		tokens.push_back(current);
	}

	return tokens;
}

bool JsonValue::isValidToken(const std::string& token) {
	if (token.empty()) return false;

	if (token.front() == '"' && token.back() == '"') return true;
	if (token == "true" || token == "false") return true;
	if (token == "null") return true;

	bool hasDecimal = false;
	bool hasDigit = false;
	for (char c : token) {
		if (c == '-' && !hasDigit) continue;
		if (c == '.' && !hasDecimal) {
			hasDecimal = true;
			continue;
		}
		if (!std::isdigit(c)) return false;
		hasDigit = true;
	}
	if (hasDigit) return true;

	return false;
}

// Parse string to JsonObject 
JsonValue JsonValue::parse(const std::string& str) {
	std::vector<std::string> tokens = tokenize(str);
	size_t index = 0;
	
	if (tokens.empty()) {
		throw std::runtime_error("Empty JSON string");
	}

	return parseValue(tokens, index);
}

JsonValue JsonValue::parseValue(const std::vector<std::string>& tokens, size_t& index) {
	if (index >= tokens.size()) {
		throw std::runtime_error("Unexpected end of JSON");
	}

	const std::string& token = tokens[index];
	
	if (token == "{") {
		return JsonValue(parseObject(tokens, index));
	}
	else if (token == "[") {
		return JsonValue(parseArray(tokens, index));
	}
	else if (token == "true" || token == "false") {
		index++;
		return JsonValue(token);
	}
	else if (token == "null") {
		index++;
		return JsonValue(nullptr);
	}
	else if (token.front() == '"' && token.back() == '"') {
		index++;
		return JsonValue(token);
	}
	else {
		try {
			if (token.find('.') != std::string::npos) {
				boost::lexical_cast<double>(token); // Just validate
			} else {
				boost::lexical_cast<int>(token); // Just validate
			}
			index++;
			return JsonValue(token);
		}
		catch (const boost::bad_lexical_cast&) {
			throw std::runtime_error("Invalid JSON value: " + token);
		}
	}
}

JsonValue::JsonObject JsonValue::parseObject(const std::vector<std::string>& tokens, size_t& index) {
	JsonObject obj;
	index++;

	bool expectKey = true; 

	while (index < tokens.size() && tokens[index] != "}") {
		if (expectKey) {
			// Key should be a string
			if (tokens[index].front() != '"' || tokens[index].back() != '"') {
				throw std::runtime_error("Object key must be a string");
			}
			std::string key = tokens[index].substr(1, tokens[index].length() - 2); // Remove quotes
			index++;     

			if (index >= tokens.size() || tokens[index] != ":") {
				throw std::runtime_error("Expected ':' after object key");
			}
			index++;    

			// Parse value
			JsonValue value;
			if (tokens[index] == "{") {
				value.m_value = parseObject(tokens, index);
			}
			else if (tokens[index] == "[") {
				value.m_value = parseArray(tokens, index);
			}
			else if (isValidToken(tokens[index])) {
				value.m_value = tokens[index];
				index++;
			}
			else {
				throw std::runtime_error("Invalid value in object: " + tokens[index]);
			}

			obj[key] = value;
			expectKey = false;
		}
		else {
			if (tokens[index] != ",") {
				throw std::runtime_error("Expected comma or '}' in object");
			}
			index++;
			expectKey = true;
		}
	}

	if (index >= tokens.size() || tokens[index] != "}") {
		throw std::runtime_error("Expected '}' to close object");
	}
	index++;

	return obj;
}


JsonValue::JsonArray JsonValue::parseArray(const std::vector<std::string>& tokens, size_t& index) {
	JsonArray arr;
	index++;

	bool expectValue = true;  

	while (index < tokens.size() && tokens[index] != "]") {
		if (expectValue) {
			JsonValue value;
			if (tokens[index] == "{") {
				value.m_value = parseObject(tokens, index);
			}
			else if (tokens[index] == "[") {
				value.m_value = parseArray(tokens, index);
			}
			else if (isValidToken(tokens[index])) {
				value.m_value = tokens[index];
				index++;
			}
			else {
				throw std::runtime_error("Invalid value in array: " + tokens[index]);
			}

			arr.push_back(value);
			expectValue = false;
		}
		else {
			if (tokens[index] != ",") {
				throw std::runtime_error("Expected comma or ']' in array");
			}
			index++;
			expectValue = true;
		}
	}

	if (index >= tokens.size() || tokens[index] != "]") {
		throw std::runtime_error("Expected ']' to close array");
	}
	index++;

	return arr;
}

std::ostream& JsonValue::print_array(std::ostream& os, const JsonArray& arr) {
	os << "[";
	bool first = true;
	for (const auto& el : arr) {
		if (!first) os << ", ";  // Do not put a comma before the first element
		os << el;
		first = false;
	}
	os << "]";
	return os;
}

std::ostream& JsonValue::print_object(std::ostream& os, const JsonObject& obj) {
	os << "{";
	bool first = true;
	for (const auto& [key, val] : obj) {
		if (!first) os << ", ";  // Do not put a comma before the first element
		os << key << ": " << val;  
		first = false;
	}
	os << "}";
	return os;
}

std::ostream& JSON::operator<<(std::ostream& os, const JsonValue& js) {
	std::visit([&os](auto&& arg) {
		using T = std::decay_t<decltype(arg)>;  // remove const, &, ... without copy
		if constexpr (std::is_same_v<T, std::string>) {
			if (arg == "true" || arg == "false") os << arg;
			else {
				// try to print as number
				try {
					if (arg.find('.') != std::string::npos) {
						double val = boost::lexical_cast<double>(arg);
						os << val;
					}
					else {
						int val = boost::lexical_cast<int>(arg);
						os << val;
					}
				}
				catch (const boost::bad_lexical_cast&) {
					os << arg;
				}
			}
			
		}
		else if constexpr (std::is_same_v<T, JsonValue::JsonArray>)
			JsonValue::print_array(os, arg);
		else if constexpr (std::is_same_v<T, JsonValue::JsonObject>)
			JsonValue::print_object(os, arg);
		else if constexpr (std::is_same_v<T, std::nullptr_t>)
			os << "null";
		}, js.getValue());
	return os;
}
