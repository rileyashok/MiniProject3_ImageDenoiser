Copilot helped with writing some of the code and functions that I did not know how they worked. For example, I was unsure how to create and work with files. I used comments to guide copilot to do what I wanted, and then tested to make sure that it actually did as expected. Copilot also helped with some of the logic that I did not understand, such as the mean neighborhood filters.
I worked on a lot of the main logic of the program, as well as the main function calling functions, and some of the matrix handling independent of copilot. I also verified all copilot code by running tests of specific functions. I first verfied its ability to read the file by creating several noisy files manually, and then running the program to see if it could read it and print it out. 
One bug that copilot introduced that I had to fix was deleting and corrupting the file. Copilot, at the end of the read file function, deleted the file to "conserve dynamic memory." However, this introduced many problems, as with no usable file being sent to the other functions, the rest of the code created noisy, corrupted files. To fix this, I had to go through the code and search for the parts where copilot introduced a line to delete the file or lines in the file, and then delete them.

Example terminal output for a 10x10 matrix:
filename: noisy_image.txt outputfile: output.txt filterType: mean iterations: 1
Matrix read from file:
103 198 105 115 81 255 74 236 41 205 
186 171 242 251 227 70 124 194 84 248 
27 232 231 141 118 90 46 99 51 159 
201 154 102 50 13 183 49 88 163 90 
37 93 5 23 88 233 94 212 171 178 
205 198 155 180 84 17 14 130 116 65 
33 61 220 135 112 233 62 161 65 225 
252 103 62 1 126 151 234 220 107 150 
143 56 92 42 236 176 59 251 50 175 
60 84 236 24 219 92 2 26 254 67 
Denoised image:
103 198 105 115 81 255 74 236 41 205 
186 219 211 201 149 112 103 99 107 248 
27 188 174 152 127 102 104 99 113 159 
201 136 114 85 104 101 121 108 130 90 
37 117 106 77 96 86 113 115 146 178 
205 122 118 111 122 104 128 113 142 65 
33 133 123 119 115 114 135 123 133 225 
252 99 85 114 134 154 171 134 142 150 
143 78 59 93 122 163 181 153 157 175 
60 84 236 24 219 92 2 26 254 67 
Denoised image written to file: output.txt
