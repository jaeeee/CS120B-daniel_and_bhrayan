# Test file for lab6_part2


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0xFF => expect PORTB: 0x01"
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
#       Example: printPORTB d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

test " PINA : 0xFF, => PORTB= 0x01, state= LIGHT_1"
set state = START
setPINA  0xFF
continue 1
expect state LIGHT_1
expectPORTB 0x01
checkResult

test " PINA : 0xFF, => PORTB= 0x01, state= LIGHT_2"
set state = LIGHT_1
setPINA  0xFF
continue 1
expect state LIGHT_2
expectPORTB 0x02
checkResult

test " PINA : 0x01, => PORTB= 0x01, state= PAUSE"
set state = LIGHT_2
setPINA  0xFE
continue 1
expect state PAUSE
expectPORTB 0x02
checkResult

test " PINA : 0xFF, => PORTB= 0x01, state= LIGHT_2"
set state = PAUSE
setPINA  0xFF
continue 1
expect state LIGHT_2
expectPORTB 0x02
checkResult

test " PINA : 0xFF, => PORTB= 0x04, state= LIGHT_3"
set state = LIGHT_2
setPINA  0xFF
continue 1
expect state LIGHT_3
expectPORTB 0x04
checkResult
# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
