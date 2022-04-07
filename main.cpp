// Program: main.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
// Ziad Mohammed Ibrahim, 20211044, function {1,2,3,4,6}
// abdallah mohamed abd el fattah, 20210219, function {5}
// Author:
// Date:    ///////////////
// Version: 1.0

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];

void loadImage(unsigned char image[SIZE][SIZE]);

void saveImage();

void BW_Filter();

void Merge_Filter();

void DL_ImageFilter();

void Invert_Filter();

void Rotate_image();

void Flip_Image();


int main() {
    //int choice{};
    loadImage(image);
    while (true){
        cout << "1- Black & White Filter\n"
                "2- Invert Filter\n"
                "3- Merge Filter\n"
                "4- Flip Image\n"
                "5- Darken and Lighten Image\n"
                "6- Rotate Image\n"
                "7- Detect Image Edges\n"
                "8- Enlarge Image\n"
                "9- Shrink Image\n"
                "10- Mirror 1/2 Image\n"
                "11- Shuffle Image\n"
                "12- Blur Image\n"
                "13- Save the image to a file\n"
                "0- Exit" << endl;
        int choice; cin >> choice;
        switch(choice){
            case 1 :
                BW_Filter();
                break;
            case 2 :
                Invert_Filter();
                break;
            case 3:
                Merge_Filter();
                break;
            case 4 :
                Flip_Image();
                break;
            case 5 :
                DL_ImageFilter();
                break;
            case 6 :
                Rotate_image();
                break;
//            case 7 :
//                Detect_Image_Edges();
//                break;
//            case 8 :
//                Enlarge_Image();
//                break;
//            case 9 :
//                Shrink_Image();
//                break;
//            case 10 :
//                MirrorHalf_Image();
//                break;
//            case 11 :
//                Shuffle_Image();
//                break;
//            case 12 :
//                Blur_Image();
//                break;
            case 13 :
                saveImage();
                break;
            case 0 :
                return 0;
        }
    }
    return 0;
}


//_________________________________________
void loadImage(unsigned char image[SIZE][SIZE]) {
    char imageFileName[100];
    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;
    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

void BW_Filter() {
    long avg{};
    for (int i{}; i < SIZE; i++) {
        for (int j{}; j < SIZE; j++)
            avg += image[i][j];
    }
    avg /= (SIZE * SIZE);

    for (int i{}; i < SIZE; i++) {
        for (int j{}; j < SIZE; j++) {
            if (image[i][j] > avg)
                image[i][j] = 255;
            else
                image[i][j] = 0;

        }
    }
}

void Invert_Filter() {
    for (int i{}; i < SIZE; i++) {
        for (int j{}; j < SIZE; j++) {
            if (image[i][j] == 0)
                image[i][j] = 255;
            else if (image[i][j] == 255)
                image[i][j] = 0;
            else
                image[i][j] = 255 - image[i][j];
        }
    }
}

void Merge_Filter() {
    unsigned char image2[SIZE][SIZE];
    loadImage(image2);
    for (int i{}; i < SIZE; i++) {
        for (int j{}; j < SIZE; j++) {
            image[i][j] = (image[i][j] + image2[i][j]) / 2;
        }
    }
}

void Flip_Image() {
    const int c = SIZE / 2;
    int vertically{255};
    int horizontally{255};
    int choice;
    cin >> choice;
    cout << "1-To flip it horizontally\n2-To flip it vertically\n";
    if (choice == 1)
        horizontally = c;
    else vertically = c;
    for (int x{}; x < horizontally; x++) {
        for (int y{}; y < vertically; y++) {
            int temp = image[x][y];
            if (choice == 1) {
                image[x][y] = image[SIZE - x][y];
                image[SIZE - x][y] = temp;
            } else {
                image[x][y] = image[x][SIZE - y];
                image[x][SIZE - y] = temp;
            }

        }
    }
}

void DL_ImageFilter() {
    int darker_or_lighter;
    cout << "1.Darker\n2.lighter\nchoice number" << endl;
    cin >> darker_or_lighter;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (darker_or_lighter == 1)image[i][j] = image[i][j] / 2;
            else image[i][j] = min(image[i][j] + 50, 255);
        }
    }
}

void Rotate_image() {
    int angle;
    cin >> angle;

    for (int i{1}; i <= angle / 90; i++) {
        for (int i = 0; i < SIZE; i += 1) {
            for (int j = i + 1; j < SIZE; j += 1)
                swap(image[i][j], image[j][i]);
        }
        for (int i{}; i < SIZE; i++) {
            for (int j{}; j < SIZE / 2; j++)
                swap(image[i][j], image[i][SIZE - 1 - j]);
        }
    }

}

void saveImage() {
    char imageFileName[100];
    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}
