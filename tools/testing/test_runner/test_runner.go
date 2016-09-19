package main

import (
	"encoding/json"
	"flag"
	"fmt"
)

type TestStatus int

const (
	TEST_PASS TestStatus = 0
	TEST_FAIL            = 1
)

type TestRun struct {
	Name    string     `json:"name"`
	Binary  string     `json:"binary"`
	Type    string     `json:"type"`
	Status  TestStatus `json:"status"`
	Message string     `json:"message"`
}

type testFunc func(run *TestRun)

var (
	testTypes = make(map[string]testFunc)
	testType  = flag.String("type", "",
		"Test type to run.  Valid values: c_test.")
	testName   = flag.String("name", "", "Test name.")
	testBinary = flag.String("binary", "", "Binary to execute for test.")
)

func addTestType(testType string, testFunc testFunc) {
	testTypes[testType] = testFunc
}

func newTestRun(name string, binary string, testType string) *TestRun {
	if _, ok := testTypes[testType]; !ok {
		panic(fmt.Sprintf("Unknown test type: %s\n", testType))
	}
	return &TestRun{
		Name:   name,
		Binary: binary,
		Type:   testType,
	}
}

func main() {
	flag.Parse()

	// TODO(konkers): Check cmd line params.
	test := newTestRun(*testName, *testBinary, *testType)
	testTypes[test.Type](test)

	output, _ := json.MarshalIndent(test, "", "  ")
	fmt.Println(string(output))
}
