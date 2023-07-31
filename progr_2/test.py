from subprocess import PIPE, Popen

total_passes = 0
total_fails = 0
for n in range(1,26):
    inputFile = f'./test_cases/salaries/input{n}.txt'
    outputFile = f'./test_cases/salaries/output{n}.txt'
    f = open(outputFile)
    output = f.read()
    command = "./salaries < " + inputFile
    process = Popen(command, shell=True, stdout=PIPE, stderr=PIPE)
    producedOutput, err = process.communicate()

    if output == producedOutput.decode("utf-8"):
        print(f'+++ Testcase {n} passed!')
        total_passes = total_passes + 1
    else:
        print(f'--- Testcase {n} failed!')
        print(f'Expected Output:\n{output}')
        print(f'Produced Output:\n{producedOutput.decode("utf-8")}')
        total_fails = total_fails + 1

print("--------------")
print("Total Passes: ", total_passes)
print("Total Fails: ", total_fails)
