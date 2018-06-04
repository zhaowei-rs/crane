#include <cassert>
#include <string>
#include <iostream>
#include <list>
#include <set>
#include <unordered_map>
#include <algorithm>
#include "test_apis.h"
#include "../json11.h"

#define JSON11_TEST_ASSERT(b) assert(b)

using namespace json11;
using std::string;

void test_json11()
{
	const string simple_test =
		R"({"k1":"v1", "k2":42, "k3":["a",123,true,false,null]})";

	string err;
	const auto json = Json::parse(simple_test, err);

	std::cout << "k1: " << json["k1"].string_value() << "\n";
	std::cout << "k3: " << json["k3"].dump() << "\n";

	for (auto &k : json["k3"].array_items()) {
		std::cout << "    - " << k.dump() << "\n";
	}

	string comment_test = R"({
      // comment /* with nested comment */
      "a": 1,
      // comment
      // continued
      "b": "text",
      /* multi
         line
         comment
        // line-comment-inside-multiline-comment
      */
      // and single-line comment
      // and single-line comment /* multiline inside single line */
      "c": [1, 2, 3]
      // and single-line comment at end of object
    })";

	string err_comment;
	auto json_comment = Json::parse(
		comment_test, err_comment, JsonParse::COMMENTS);
	JSON11_TEST_ASSERT(!json_comment.is_null());
	JSON11_TEST_ASSERT(err_comment.empty());

	comment_test = "{\"a\": 1}//trailing line comment";
	json_comment = Json::parse(
		comment_test, err_comment, JsonParse::COMMENTS);
	JSON11_TEST_ASSERT(!json_comment.is_null());
	JSON11_TEST_ASSERT(err_comment.empty());

	comment_test = "{\"a\": 1}/*trailing multi-line comment*/";
	json_comment = Json::parse(
		comment_test, err_comment, JsonParse::COMMENTS);
	JSON11_TEST_ASSERT(!json_comment.is_null());
	JSON11_TEST_ASSERT(err_comment.empty());

	string failing_comment_test = "{\n/* unterminated comment\n\"a\": 1,\n}";
	string err_failing_comment;
	auto json_failing_comment = Json::parse(
		failing_comment_test, err_failing_comment, JsonParse::COMMENTS);
	JSON11_TEST_ASSERT(json_failing_comment.is_null());
	JSON11_TEST_ASSERT(!err_failing_comment.empty());

	failing_comment_test = "{\n/* unterminated trailing comment }";
	json_failing_comment = Json::parse(
		failing_comment_test, err_failing_comment, JsonParse::COMMENTS);
	JSON11_TEST_ASSERT(json_failing_comment.is_null());
	JSON11_TEST_ASSERT(!err_failing_comment.empty());

	failing_comment_test = "{\n/ / bad comment }";
	json_failing_comment = Json::parse(
		failing_comment_test, err_failing_comment, JsonParse::COMMENTS);
	JSON11_TEST_ASSERT(json_failing_comment.is_null());
	JSON11_TEST_ASSERT(!err_failing_comment.empty());

	failing_comment_test = "{// bad comment }";
	json_failing_comment = Json::parse(
		failing_comment_test, err_failing_comment, JsonParse::COMMENTS);
	JSON11_TEST_ASSERT(json_failing_comment.is_null());
	JSON11_TEST_ASSERT(!err_failing_comment.empty());

	failing_comment_test = "{\n\"a\": 1\n}/";
	json_failing_comment = Json::parse(
		failing_comment_test, err_failing_comment, JsonParse::COMMENTS);
	JSON11_TEST_ASSERT(json_failing_comment.is_null());
	JSON11_TEST_ASSERT(!err_failing_comment.empty());

	failing_comment_test = "{/* bad\ncomment *}";
	json_failing_comment = Json::parse(
		failing_comment_test, err_failing_comment, JsonParse::COMMENTS);
	JSON11_TEST_ASSERT(json_failing_comment.is_null());
	JSON11_TEST_ASSERT(!err_failing_comment.empty());

	std::list<int> l1{ 1, 2, 3 };
	std::vector<int> l2{ 1, 2, 3 };
	std::set<int> l3{ 1, 2, 3 };
	JSON11_TEST_ASSERT(Json(l1) == Json(l2));
	JSON11_TEST_ASSERT(Json(l2) == Json(l3));

	std::map<string, string> m1{ { "k1", "v1" },{ "k2", "v2" } };
	std::unordered_map<string, string> m2{ { "k1", "v1" },{ "k2", "v2" } };
	JSON11_TEST_ASSERT(Json(m1) == Json(m2));

	// Json literals
	const Json obj = Json::object({
		{ "k1", "v1" },
		{ "k2", 42.0 },
		{ "k3", Json::array({ "a", 123.0, true, false, nullptr }) },
		});

	std::cout << "obj: " << obj.dump() << "\n";
	JSON11_TEST_ASSERT(obj.dump() == "{\"k1\": \"v1\", \"k2\": 42, \"k3\": [\"a\", 123, true, false, null]}");

	JSON11_TEST_ASSERT(Json("a").number_value() == 0);
	JSON11_TEST_ASSERT(Json("a").string_value() == "a");
	JSON11_TEST_ASSERT(Json().number_value() == 0);

	JSON11_TEST_ASSERT(obj == json);
	JSON11_TEST_ASSERT(Json(42) == Json(42.0));
	JSON11_TEST_ASSERT(Json(42) != Json(42.1));

	const string unicode_escape_test =
		R"([ "blah\ud83d\udca9blah\ud83dblah\udca9blah\u0000blah\u1234" ])";

	const char utf8[] = "blah" "\xf0\x9f\x92\xa9" "blah" "\xed\xa0\xbd" "blah"
		"\xed\xb2\xa9" "blah" "\0" "blah" "\xe1\x88\xb4";

	Json uni = Json::parse(unicode_escape_test, err);
	JSON11_TEST_ASSERT(uni[0].string_value().size() == (sizeof utf8) - 1);
	JSON11_TEST_ASSERT(std::memcmp(uni[0].string_value().data(), utf8, sizeof utf8) == 0);

	Json my_json = Json::object{
		{ "key1", "value1" },
	{ "key2", false },
	{ "key3", Json::array{ 1, 2, 3 } },
	};
	std::string json_obj_str = my_json.dump();
	std::cout << "json_obj_str: " << json_obj_str << "\n";
	JSON11_TEST_ASSERT(json_obj_str == "{\"key1\": \"value1\", \"key2\": false, \"key3\": [1, 2, 3]}");

	class Point {
	public:
		int x;
		int y;
		Point(int x, int y) : x(x), y(y) {}
		Json to_json() const { return Json::array{ x, y }; }
	};

	std::vector<Point> points = { { 1, 2 },{ 10, 20 },{ 100, 200 } };
	std::string points_json = Json(points).dump();
	std::cout << "points_json: " << points_json << "\n";
	JSON11_TEST_ASSERT(points_json == "[[1, 2], [10, 20], [100, 200]]");
}