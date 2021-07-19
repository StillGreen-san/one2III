cppcheck --project=build/compile_commands.json --enable=all --inconclusive --inline-suppr | Where-Object { $_ -match '[\w\\\/.]+:\w+:\w+:' }
