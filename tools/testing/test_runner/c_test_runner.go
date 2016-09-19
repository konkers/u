package main

import (
	"fmt"
	"os"
	"os/exec"
)

func init() {
	addTestType("c_test", runCTest)
}

func runCTest(run *TestRun) {
	cmd := exec.Command(run.Binary)
	output, _ := cmd.Output()
	run.Message = string(output)

	if cmd.ProcessState.Success() {
		run.Status = TEST_PASS
	} else {
		run.Status = TEST_FAIL
		fmt.Fprintln(os.Stderr, run.Message)
	}
}
