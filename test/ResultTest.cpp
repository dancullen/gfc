#include "gfcpp/Result.hpp"

#include "catch2/catch.hpp"

#include <string>

using gfcpp::Result;

static Result<int> shouldSucceed(void)
{
    return 42;
}

static Result<int> shouldFail(void)
{
    return Result<int>("some failure occurred");
}

static std::string alsoShouldSucceed(void)
{
    auto result = shouldSucceed();
    if (result.err != "")
    {
        return "Error: something faled. Details: " + result.err;
    }
    return "";
}

TEST_CASE("Basic tests", "[gfcpp]")
{
    auto data = shouldSucceed();
    CHECK("" == data.err);
    CHECK(42 == data.value);
    CHECK(!data.isErr());
    CHECK(data.isOk());

    data = shouldFail();
    CHECK(data.err != "");
    CHECK(data.isErr());
    CHECK(!data.isOk());

    CHECK("" == alsoShouldSucceed());
}

/**
 * Data allows us to test our Result class with a more complex data type
 * than simple primitives like ints and bools and floats.
 */ 
struct Data
{
    std::string name = "dan";
    int age = 10;
};

TEST_CASE("Complex datatype", "[gfcpp]")
{
    Result<Data> d("failure");
    CHECK("failure" == d.err);
    d = Data();
    CHECK("dan" == d.value.name);
    CHECK(10 == d.value.age);
}
