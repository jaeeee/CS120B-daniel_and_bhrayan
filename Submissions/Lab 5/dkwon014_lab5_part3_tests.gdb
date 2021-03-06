# Test file for lab5_part3


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly,
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
test "PINA: 0x00, PINB: 0x00 => PORTC: 0"
# Set inputs
setPINA 0x00
setPINB 0x00
# Continue for several ticks
continue 2
# Set expect values
expectPORTC 0
# Check pass/fail
checkResult

test "PINA: 0xFE, PORTC: 0, state = WAIT1"
setPINA 0xFE
continue 2
expectPORTC 0
expect state WAIT1
checkResult

test "PINA: 0xFE, PORTC: 0, state = WAIT1"
setPINA 0xFE
continue 2
setPINA 0xFE
continue 2
expectPORTC 0
expect state WAIT1
checkResult

test "PINA: 0x01, PORTC: 0x15, state = SET1"
set state = WAIT1
setPINA 0x01
continue 2
expectPORTC 0x15
expect state SET1
checkResult

test "PINA: 0xFE, PORTC: 0, state = WAIT2"
set state = SET1
setPINA 0xFE
continue 2
expectPORTC 0x15
expect state WAIT2
checkResult

test "PINA: 0x01 PORTC: 0x29, state = SET2"
set state = WAIT2
setPINA 0x01
continue 2
expectPORTC 0x29
expect state SET2
checkResult

test "PINA: 0xFE, PORTC: 0x29, state = WAIT3"
set state = SET2
setPINA 0xFE
continue 2
expectPORTC 0x29
expect state WAIT3
checkResult

test "PINA: 0x01, PORTC: 0x33, state = SET3"
set state = WAIT3
setPINA 0x01
continue 2
expectPORTC 0x33
expect state SET3
checkResult

test "PINA: 0xFE, PORTC: 0x33, state = WAIT4"
set state = SET3
setPINA 0xFE
continue 2
expectPORTC 0x33
expect state WAIT4
checkResult

test "PINA: 0x01, PORTC: 0x0C, state = SET4"
set state = WAIT4
setPINA 0x01
continue 2
expectPORTC 0x0C
expect state SET4
checkResult

test "PINA: 0xFE, PORTC: 0x)C, state = WAIT5"
set state = SET4
setPINA 0xFE
continue 2
expectPORTC 0x0C
expect state WAIT5
checkResult

test "PINA: 0x01, PORTC: 0x2D, state = SET5"
set state = WAIT5
setPINA 0x01
continue 2
expectPORTC 0x2D
expect state SET5
checkResult

test "PINA: 0xFE, PORTC: 0x2D, state = WAIT6"
set state = SET5
setPINA 0xFE
continue 2
expectPORTC 0x2D
expect state WAIT6
checkResult






# Add tests below

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
