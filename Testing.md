Test the test cases by first compiling the program (g++ denoise.cpp -o denoise) and then running the commands below. The test case of a generated matrix and then the denoised file of the matrix are available in the tests folder.

First, you must generate a noisy file using the command:

./denoise generate #ROWS #COLS

This will create a file named noisy_image.txt with the randomly generated matrix.

Next, you can run the main function using the command:

./denoise INPUTFILE OUTPUTFILENAME filtertype numberOfIterations

Note: The only filter type offered is mean, and it only supports 1 iteration.

The program will also print in the terminal the file that it read and the denoised file for easy viewing.

//=============Test case 1========================
//Test 1: run first command to generate a 6x6 matrix:
./denoise generate 6 6
//This generates a file named noisy_image12.txt

//Test 2: run command to denoise the file
./denoise noisy_image12.txt output12.txt mean 1
//This generates a file named output12.txt

//==========Test case 2===========================
//All generated matricies are salt and pepper matricies

//=============Test case 3: validate edge behavior=======
//edge behavior can be validated either manualy or using the diff tool:
diff noisy_image12.txt output12.txt

