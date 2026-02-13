#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
using namespace std;

int** image; //the image globally
int rows;
int cols;
//====================================================================================
int generate_file(string filename, int row, int col) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file for writing: " << filename << endl;
        return 1;
    }
    
    outFile << row << " " << col << endl; // Write the dimensions of the image to the file
   
    // Generate a 5x5 image with random pixel values between 0 and 255
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int pixelValue = rand() % 256; // Random value between 0 and 255
            outFile << pixelValue << " ";
        }
        outFile << endl;
    }
    outFile.close();
    return 0;
}

//==========================================================================
int read_file(char* filename) {
    //reading input from file
    ifstream inFile(filename);
    //throw an error
    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        return 1;
    }

    //reading number of rows and columns
    inFile >> rows >> cols;

    //creating pointers for matrix
    image = new int*[rows];
    for (int i = 0; i < rows; i++) {
        image[i] = new int[cols];
    }

    //read from input and put into memory matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            inFile >> image[i][j];
        }
    }

    //close the file as good sane person does
    inFile.close();

    // Print the image to verify it was read correctly
    cout << "Matrix read from file:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
   // cout << "matrix available in: " << argv[1] << endl;

    return 0;
}
//==========================================================================
//read 3 by 3 sections of the image and apply mean filter to denoise the image
void denoiser(int** noisyImage, int** denoisedImage, int rows, int cols) {
   /*
    cout << "in the call: " << endl;
    //debugging
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << noisyImage[i][j] << " ";
        }
        cout << endl;
    }
        */

    //main loop
    //Chosen border handling: ignore border, start at (1,1) and to to (1, n-1)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int sum = 0;
            int count = 0;
           
            // Iterate over the 3x3 neighborhood
            
            for (int di =-1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    
                    int ni = i + di;
                    int nj = j + dj;
                    
                    // Check for valid neighbor indices
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                        //cout << "ni is: " << noisyImage[ni][nj] << endl;
                        if (ni == 0 || ni == rows-1 || nj == 0 || nj == cols-1) {
                            //cout << "coordinates: (" << ni << "," << nj << ")  " << "value: " << noisyImage[ni][nj] << endl;
                            //take the value and set it to the current pixel in the denoised image
                            denoisedImage[i][j] = noisyImage[i][j];
                        }
                        else {
                            sum += noisyImage[ni][nj];
                            count++;

                        }
                    }
                }
            }
           if (!(i == 0 || i == rows-1 || j == 0 || j == cols-1)) {
                //take the value and set it to the current pixel in the denoised image
                denoisedImage[i][j] = sum / count; // Assign average to denoised image
                //cout << "coordinates: (" << i << "," << j << ")  " << "value: " << noisyImage[i][j] << endl;
            } 
        }
    }
}
//==========================================================================
int denoised_image_to_file(int** denoisedImage, string filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file for writing: " << filename << endl;
        return 1;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            outFile << denoisedImage[i][j] << " ";
        }
        outFile << endl;
    }
    outFile.close();
    return 0;
}
//====================================================================================

int main(int argc, char* argv[]) {
    
    if (argv[1] == string("generate")) {
        generate_file("noisy_image.txt", std::atoi(argv[2]), std::atoi(argv[3]));
        return 0;
    }
        
    // Extract filename, filterType, and iterations from argv
    string filename = argv[1];
    string outputfile = argv[2];
    string filterType = argv[3];
    int iterations = std::atoi(argv[4]);
    cout << "filename: " << filename << " outputfile: " << outputfile << " filterType: " << filterType << " iterations: " << iterations << endl;
    
    //Did not do the median filter, only mean filter available, throw error
    if (filterType != "mean") {
        cerr << "Unsupported filter type: " << filterType << ". Only 'mean' is supported." << endl;
        return 1;
    }

    if (argc < 4) {
        cerr << "Usage: " << argv[0] << " <input_file> <filter_type> <iterations>" << endl;
        return 1;
    }

    //read file
    int result = read_file(argv[1]);
    if (result != 0) {
        return result; // Exit if there was an error reading the file
    }

    //create a new matrix to store the result of denoiser
    int** denoisedImage;
     
    //creating blank matrix to put values in
    denoisedImage = new int*[rows];
    for (int i = 0; i < rows; i++) {
        denoisedImage[i] = new int[cols];
    }
    
    //call the denoiser
    /*
    int** updated = new int*[rows];
    for (int i = 0; i < rows; i++) {
        temp[i] = new int[cols];
    }
        */

        denoiser(image, denoisedImage, rows, cols);


    //write the denoised image to file  
    result = denoised_image_to_file(denoisedImage, outputfile);
    
    if (result != 0) {
        return result; // Exit if there was an error writing the file
    }

    // Print the denoised image
    
    cout << "Denoised image:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << denoisedImage[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Denoised image written to file: " << outputfile << endl;
        

    return 0;
}