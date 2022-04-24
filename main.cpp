// Program: main.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
// Ziad Mohammed Ibrahim, 20211044,{half the funcions}
// abdallah mohamed abd el fattah, 20210219,{the other half}
// Version: 1.0

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];

void loadImage(unsigned char image[SIZE][SIZE]);

void saveImage();

void BW_Filter();

void Merge_Filter();

void DL_ImageFilter();

void Invert_Filter();

void Rotate_image();

void Flip_Image();

void Shrink_Image();

void Enlarge_Image();

void MirrorHalf_Image();

void Detect_Image_Edges();

void Blur_Image();

void Shuffle_Image();

//---------------------RGB-------------------------
unsigned char imageRGB[SIZE][SIZE][RGB];
unsigned char imageRGB2[SIZE][SIZE][RGB];

void saveImageRGB();

void loadImageRGB(unsigned char imageRGB[SIZE][SIZE][RGB]);

void BW_Filter_RGB();

void Merge_Filter_RGB();

void DL_ImageFilter_RGB();

void Invert_Filter_RGB();

void Rotate_image_RGB();

void Flip_Image_RGB();

void Shrink_Image_RGB();

void Enlarge_Image_RGB();

void MirrorHalf_Image_RGB();

void Detect_Image_Edges_RGB();

void Blur_Image_RGB();

void Shuffle_Image_RGB();

void Detect_Image_Edges_RGB();

int main() {
    int RGB_or_GRAY_SCALE;
    cout << "1-Gray_Scale\n"
            "2-RGB" << endl;
    cin >> RGB_or_GRAY_SCALE;
    (RGB_or_GRAY_SCALE == 1 ? loadImage(image) : loadImageRGB(imageRGB));

    while (true) {
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
        int choice;
        cin >> choice;
        switch (choice) {
            case 1 :
                (RGB_or_GRAY_SCALE == 1 ? BW_Filter() : BW_Filter_RGB());
                break;
            case 2 :
                (RGB_or_GRAY_SCALE == 1 ? Invert_Filter() : Invert_Filter_RGB());
                break;
            case 3:
                (RGB_or_GRAY_SCALE == 1 ? Merge_Filter() : Merge_Filter_RGB());
                break;
            case 4 :
                (RGB_or_GRAY_SCALE == 1 ? Flip_Image() : Flip_Image_RGB());
                break;
            case 5 :
                (RGB_or_GRAY_SCALE == 1 ? DL_ImageFilter() : DL_ImageFilter_RGB());
                break;
            case 6 :
                (RGB_or_GRAY_SCALE == 1 ? Rotate_image() : Rotate_image_RGB());
                break;
            case 7 :
                (RGB_or_GRAY_SCALE == 1 ? Detect_Image_Edges() : Detect_Image_Edges_RGB());
                break;
            case 8 :
                (RGB_or_GRAY_SCALE == 1 ? Enlarge_Image() : Enlarge_Image_RGB());
                break;
            case 9 :
                (RGB_or_GRAY_SCALE == 1 ? Shrink_Image() : Shrink_Image_RGB());
                break;
            case 10 :
                (RGB_or_GRAY_SCALE == 1 ? MirrorHalf_Image() : MirrorHalf_Image_RGB());
                break;
            case 11 :
                (RGB_or_GRAY_SCALE == 1 ? Shuffle_Image() : Shuffle_Image_RGB());
                break;
            case 12 :
                (RGB_or_GRAY_SCALE == 1 ? Blur_Image() : Blur_Image_RGB());
                break;
            case 13 :
                (RGB_or_GRAY_SCALE == 1 ? saveImage() : saveImageRGB());
                break;
            case 0 :
                return 0;
        }
    }

    return 0;
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
    loadImage(image2);
    for (int i{}; i < SIZE; i++) {
        for (int j{}; j < SIZE; j++) {
            image[i][j] = (image[i][j] + image2[i][j]) / 2;
        }
    }
}

void Flip_Image() {
    const int c = SIZE / 2;
    int choice;
    cout << "1-To flip it horizontally\n2-To flip it vertically\n";
    cin >> choice;
    int vertically = (choice == 2 ? c : 255);
    int horizontally = (choice == 1 ? c : 255);
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

void Enlarge_Image() {
    int quarter;
    cout << "Choose quarter to enlarge\n";
    cin >> quarter;

    int ROW = (quarter < 3 ? 0 : SIZE / 2);
    int COL = (quarter % 2 != 0 ? 0 : SIZE / 2);
    int x[]{0, 1, 0, 1};
    int y[]{0, 0, 1, 1};
    for (int i{}, k{}; i < SIZE; k++, i += 2) {
        for (int j{}, z{}; j < SIZE; z++, j += 2) {
            for (int g{}; g < 4; g++)
                image2[i + x[g]][j + y[g]] = image[k + ROW][z + COL];

        }
    }
    for (int i{}; i < SIZE; i++) {
        for (int j{}; j < SIZE; j++)
            image[i][j] = image2[i][j];
    }
}


void Shrink_Image() {
    int shrink;
    cout << "choose 2 for 1/2\n"
            "choose 3 for 1/3 \n"
            "choose 4 for 1/4 \n"
            "!!Choose denominator!!" << endl;
    cout << "Enter shrink factor : ";
    cin >> shrink;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            image2[i / shrink][j / shrink] =
                    (image[i][j] + image[i + 1][j] + image[i][j + 1] + image[i + 1][j + 1]) / 4;
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            image[i][j] = image2[i][j];
    }
}

void DL_ImageFilter() {
    int darker_or_lighter;
    cout << "1.Darker\n2.lighter\n"<< endl;
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
    cout << "Choose angle to rotate the image : ";
    for (int a{1}; a <= angle / 90; a++) {
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

void MirrorHalf_Image() {
    cout << "1-Half Right\n2-Half left \n3-Half upper\n4-Half bottom\n";
    int quarter;
    cin >> quarter;
    int ROW = (quarter < 3 ? SIZE : SIZE / 2);
    int COL = (quarter < 3 ? SIZE / 2 : SIZE);
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (quarter == 1 || quarter == 4)
                image[i][j] = (quarter == 1 ? image[i][SIZE - j] : image[SIZE - i][j]);
            else if (quarter == 2)
                image[i][SIZE - j] = image[i][j];
            else
                image[SIZE - i][j] = image[i][j];
        }
    }

}

void Detect_Image_Edges() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image2[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image2[i][j + 1] - image[i][j] >= 30) image[i][j] = 0;
            else if (abs(image2[i][j + 1] - image[i][j]) < 30) image[i][j] = 255;
        }
    }
}

void Blur_Image() {
    for (int k{}; k < 4; k++) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++)
                image[i][j] = (image[i + 1][j + 1] + image[i + 1][j] + image[i][j + 1] + image[i][j + 2] +
                               image[i + 1][j + 2] +
                               image[i + 2][j] + image[i + 2][j + 1] + image[i + 2][j + 2] + image[i][j]) / 9;

        }
    }
}

void Shuffle_Image() {
    int i_start{}, i_end, j_start, j_end, old_i_start, old_j_start;

    // to copy the array to another one
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            image2[i][j] = image[i][j];
    }
    // to set the order of the images
    char order[4];
    cout << "put the order: ";
    for (int i = 0; i < 4; i++)
        cin >> order[i];
    // to shuffle as the given order
    for (int i = 0; i < 4; i++) {
        // set the first quarter from the new image
        if (i == 0) {
            i_start = j_start = 0;
            i_end = j_end = SIZE / 2;
        } else if (i == 1)// set the second quarter from the new image
        {
            i_start = 0;
            i_end = SIZE / 2;
            j_start = SIZE / 2;
            j_end = SIZE;
        } else if (i == 2)// set the third quarter from the new image
        {
            i_start = SIZE / 2;
            i_end = SIZE;
            j_start = 0;
            j_end = SIZE / 2;
        } else if (i == 3)// set the fourth quarter from the new image
        {
            i_start = SIZE / 2;
            i_end = SIZE;
            j_start = SIZE / 2;
            j_end = SIZE;
        }
        if (order[i] == '1')// set the first quarter from the old image
        {
            old_i_start = old_j_start = 0;
        } else if (order[i] == '2')// set the second quarter from the old image
        {
            old_i_start = 0;
            old_j_start = SIZE / 2;
        } else if (order[i] == '3')// set the third quarter from the old image
        {
            old_i_start = SIZE / 2;
            old_j_start = 0;
        } else if (order[i] == '4')// set the fourth quarter from the old image
        {
            old_i_start = SIZE / 2;
            old_j_start = SIZE / 2;
        }
        // copy the chosen quarter from the old image to the quarter of the new image sequenial
        for (int k1 = i_start, k2 = old_i_start; k1 < i_end; k1++, k2++) {

            for (int l1 = j_start, l2 = old_j_start; l1 < j_end; l1++, l2++)
                image[k1][l1] = image2[k2][l2];
        }

    }

}
//--------------------RGB-------------------------

void BW_Filter_RGB() {
    long avg{};
    for (int i{}; i < SIZE; i++) {
        for (int j{}; j < SIZE; j++) {
            for (int r{}; r < RGB; r++) {
                avg = (imageRGB[i][j][r] * 0.299) + (imageRGB[i][j][r + 1] * 0.587) +
                      (imageRGB[i][j][r + 2] * 0.114);
                imageRGB[i][j][r] = avg;
                if (imageRGB[i][j][0] > 127)
                    imageRGB[i][j][r] = 255;
                else
                    imageRGB[i][j][r] = 0;
            }
        }

    }
}

void Invert_Filter_RGB() {
    for (int i{}; i < SIZE; i++) {
        for (int j{}; j < SIZE; j++) {
            for (int r{}; r < RGB; r++) {
                if (imageRGB[i][j][r] == 0)
                    imageRGB[i][j][r] = 255;
                else if (imageRGB[i][j][r] == 255)
                    imageRGB[i][j][r] = 0;
                else
                    imageRGB[i][j][r] = 255 - imageRGB[i][j][r];
            }
        }
    }
}

void Merge_Filter_RGB() {
    loadImageRGB(imageRGB2);
    for (int i{}; i < SIZE; i++) {
        for (int j{}; j < SIZE; j++) {
            for (int r{}; r < RGB; r++)
                imageRGB[i][j][r] = (imageRGB[i][j][r] + imageRGB2[i][j][r]) / 2;
        }
    }
}

void Flip_Image_RGB() {
    const int c = SIZE / 2;
    int choice;
    cout << "1-To flip it horizontally\n2-To flip it vertically\n";
    cin >> choice;
    int vertically = (choice == 2 ? c : 255);
    int horizontally = (choice == 1 ? c : 255);
    for (int x{}; x < horizontally; x++) {
        for (int y{}; y < vertically; y++) {
            for (int r{}; r < RGB; r++) {
                int temp = imageRGB[x][y][r];
                if (choice == 1) {
                    imageRGB[x][y][r] = imageRGB[SIZE - x][y][r];
                    imageRGB[SIZE - x][y][r] = temp;
                } else {
                    imageRGB[x][y][r] = imageRGB[x][SIZE - y][r];
                    imageRGB[x][SIZE - y][r] = temp;
                }
            }


        }
    }
}

void Enlarge_Image_RGB() {
    int quarter;
    cout << "Choose quarter to enlarge\n";

    cin >> quarter;

    int ROW = (quarter < 3 ? 0 : SIZE / 2);
    int COL = (quarter % 2 != 0 ? 0 : SIZE / 2);
    int x[]{0, 1, 0, 1};
    int y[]{0, 0, 1, 1};
    for (int i{}, k{}; i < SIZE; k++, i += 2) {
        for (int j{}, z{}; j < SIZE; z++, j += 2) {
            for (int r{}; r < RGB; r++) {
                for (int g{}; g < 4; g++)
                    imageRGB2[i + x[g]][j + y[g]][r] = imageRGB[k + ROW][z + COL][r];
            }
        }
    }
    for (int i{}; i < SIZE; i++) {
        for (int j{}; j < SIZE; j++) {
            for (int r{}; r < RGB; r++)
                imageRGB[i][j][r] = imageRGB2[i][j][r];
        }
    }
}

void Shrink_Image_RGB() {
    int shrink;
    cout << "choose 2 for 1/2\n"
            "choose 3 for 1/3 \n"
            "choose 4 for 1/4 \n"
            "!!Choose denominator!!" << endl;

    cout << "Enter shrink factor : ";
    cin >> shrink;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int n = 0; n < RGB; ++n) {
                imageRGB2[i / shrink][j / shrink][n] =
                        (imageRGB[i][j][n] + imageRGB[i + 1][j][n] + imageRGB[i][j + 1][n] +
                         imageRGB[i + 1][j + 1][n]) / 4;
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int n = 0; n < RGB; ++n)
                imageRGB[i][j][n] = imageRGB2[i][j][n];

        }
    }
}

void DL_ImageFilter_RGB() {
    int darker_or_lighter;
    cout << "1.Darker\n2.lighter\nchoice number" << endl;
    cin >> darker_or_lighter;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int n = 0; n < RGB; ++n) {
                if (darker_or_lighter == 1)imageRGB[i][j][n] = imageRGB[i][j][n] / 2;
                else imageRGB[i][j][n] = min(imageRGB[i][j][n] + 50, 255);
            }
        }
    }
}

void Rotate_image_RGB() {
    int angle;
    cout << "Choose angle to rotate the image : ";

    cin >> angle;

    for (int a{1}; a <= angle / 90; a++) {
        for (int i = 0; i < SIZE; i += 1) {
            for (int j = i + 1; j < SIZE; j += 1) {
                for (int r{}; r < RGB; r++)
                    swap(imageRGB[i][j][r], imageRGB[j][i][r]);

            }

        }
        for (int i{}; i < SIZE; i++) {
            for (int j{}; j < SIZE / 2; j++) {
                for (int r{}; r < RGB; r++)
                    swap(imageRGB[i][j][r], imageRGB[i][SIZE - 1 - j][r]);
            }
        }
    }

}

void Blur_Image_RGB() {
    for (int k{}; k < 4; k++) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int n = 0; n < RGB; ++n) {
                    imageRGB[i][j][n] = (imageRGB[i + 1][j + 1][n] + imageRGB[i + 1][j][n] + imageRGB[i][j + 1][n] +
                                         imageRGB[i][j + 2][n] +
                                         imageRGB[i + 1][j + 2][n] + imageRGB[i + 2][j][n] +
                                         imageRGB[i + 2][j + 1][n] +
                                         imageRGB[i + 2][j + 2][n] + imageRGB[i][j][n]) / 9;
                }
            }
        }
    }
}

void Detect_Image_Edges_RGB() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int n = 0; n < RGB; ++n)
                imageRGB2[i][j][n] = imageRGB[i][j][n];
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int n = 0; n < RGB; ++n) {
                if (imageRGB2[i][j + 1][n] - imageRGB[i][j][n] >= 30) imageRGB[i][j][n] = 0;
                else if (abs(imageRGB2[i][j + 1][n] - imageRGB[i][j][n]) < 30) imageRGB[i][j][n] = 255;
            }
        }
    }
}

void Shuffle_Image_RGB() {
    int i_start{}, i_end, j_start, j_end, old_i_start, old_j_start;

    // to copy the array to another one
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int r{}; r < RGB; r++)
                imageRGB2[i][j][r] = imageRGB[i][j][r];
        }
    }
    // to set the order of the images
    char order[4];
    cout << "put the order: ";
    for (int i = 0; i < 4; i++)
        cin >> order[i];
    // to shuffle as the given order
    for (int i = 0; i < 4; i++) {
        // set the first quarter from the new image
        if (i == 0) {
            i_start = j_start = 0;
            i_end = j_end = SIZE / 2;
        } else if (i == 1)// set the second quarter from the new image
        {
            i_start = 0;
            i_end = SIZE / 2;
            j_start = SIZE / 2;
            j_end = SIZE;
        } else if (i == 2)// set the third quarter from the new image
        {
            i_start = SIZE / 2;
            i_end = SIZE;
            j_start = 0;
            j_end = SIZE / 2;
        } else if (i == 3)// set the fourth quarter from the new image
        {
            i_start = SIZE / 2;
            i_end = SIZE;
            j_start = SIZE / 2;
            j_end = SIZE;
        }
        if (order[i] == '1')// set the first quarter from the old image
        {
            old_i_start = old_j_start = 0;
        } else if (order[i] == '2')// set the second quarter from the old image
        {
            old_i_start = 0;
            old_j_start = SIZE / 2;
        } else if (order[i] == '3')// set the third quarter from the old image
        {
            old_i_start = SIZE / 2;
            old_j_start = 0;
        } else if (order[i] == '4')// set the fourth quarter from the old image
        {
            old_i_start = SIZE / 2;
            old_j_start = SIZE / 2;
        }
        // copy the chosen quarter from the old image to the quarter of the new image sequenial
        for (int k1 = i_start, k2 = old_i_start; k1 < i_end; k1++, k2++) {
            for (int l1 = j_start, l2 = old_j_start; l1 < j_end; l1++, l2++) {
                for (int r{}; r < RGB; r++)
                    imageRGB[k1][l1][r] = imageRGB2[k2][l2][r];
            }

        }

    }

}

void MirrorHalf_Image_RGB() {
    cout << "1-Half Right\n2-Half left \n3-Half upper\n4-Half bottom\n";
    int quarter;
    cin >> quarter;
    int ROW = (quarter < 3 ? SIZE : SIZE / 2);
    int COL = (quarter < 3 ? SIZE / 2 : SIZE);
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            for (int r{}; r < RGB; r++) {
                if (quarter == 1 || quarter == 4)
                    imageRGB[i][j][r] = (quarter == 1 ? imageRGB[i][SIZE - j][r] : imageRGB[SIZE - i][j][r]);
                else if (quarter == 2)
                    imageRGB[i][SIZE - j][r] = imageRGB[i][j][r];
                else
                    imageRGB[SIZE - i][j][r] = imageRGB[i][j][r];
            }

        }
    }

}

void loadImage(unsigned char image[SIZE][SIZE]) {
    char imageFileName[100];
    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;
    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

void loadImageRGB(unsigned char imageRGB[SIZE][SIZE][RGB]) {
    char imageFileName[300];
    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;
    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, imageRGB);
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

void saveImageRGB() {
    char imageFileName[100];
    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeRGBBMP(imageFileName, imageRGB);

}
