// Program: main.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
// Ziad Mohammed Ibrahim, 20211044, function {1,2,3,4,6}
// abdallah mohamed abd el fattah, 20210219, function {5,6,7,8,9,a,b,c} + RGB_function {3,6,9,c}
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
unsigned char image2[SIZE][SIZE];
void loadImage(unsigned char image[SIZE][SIZE]);
void saveImage();
void saveImage2();
void BW_Filter();
void Merge_Filter();
void DL_ImageFilter();
void Invert_Filter();
void Rotate_image();
void Flip_Image();
void Detect_Image_Edges();
void Blur_Image();
void Shrink_Image();
void  Enlarge_Image();
void MirrorHalf_Image();
void Shuffle_Image();
//_________________________________________RGB_________________________________________
unsigned char imageRGB[SIZE][SIZE][RGB];
unsigned char imageRGB2[SIZE][SIZE][RGB];
void saveImageRGB();
void saveImageRGB2();
void loadImageRGB (unsigned char imageRGB[SIZE][SIZE][RGB]);
void Merge_Filter_RGB();
void DL_ImageFilter_RGB();
void Shrink_Image_RGB();
void Blur_Image_RGB();



int main()
{
    loadImageRGB(imageRGB);
    Merge_Filter_RGB();
    saveImageRGB();
   /* int RGB_or_GRAY_SCALE;
    cout << "1-Gray_Scale\n"
            "2-RGB"<<endl;

    cin >> RGB_or_GRAY_SCALE;
    if(RGB_or_GRAY_SCALE == 1){
        int choice{};
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
            switch(choice){
                case 1 :
                    loadImage();
                    BW_Filter();
                    saveImage();
                    break;
                case 2 :
                    loadImage();
                    Invert_Filter();
                    saveImage();
                    break;
                case 3:
                    loadImage();
                    Merge_Filter();
                    saveImage();
                    break;
                case 4 :
                    loadImage();
                    Flip_Image();
                    saveImage();
                    break;
                case 5 :
                    loadImage();
                    DL_ImageFilter();
                    saveImage();
                    break;
                case 6 :
                    loadImage();
                    Rotate_image();
                    saveImage();
                    break;
                case 7 :
                    loadImage();
                    Detect_Image_Edges();
                    saveImage();
                    break;
                case 8 :
                    loadImage();
                    Enlarge_Image();
                    saveImage2();
                    break;
                case 9 :
                    loadImage();
                    Shrink_Image();
                    saveImage2();
                    break;
                case 10 :
                    loadImage();
                    MirrorHalf_Image();
                    saveImage();
                    break;
                case 11 :
                    loadImage();
                    Shuffle_Image();
                    saveImage();
                    break;
                case 12 :
                    loadImage();
                    //i called the function more than once to make the blur more efficient
                    Blur_Image();
                    Blur_Image();
                    Blur_Image();
                    saveImage2();
                    break;
                case 13 :
                    saveImage();
                    break;
                case 0 :
                    return 0;
                default:
                    return 1;
            }
        }
    }
    else
    {
        int n;

        cout <<
             "1 - Merge Filter\n"
             "2 - Darken and Lighten Image\n"
             "3 - Shrink Image\n"
             "4 - Blur Image \n"
             "0 - Exit" << endl;
        switch (n) {
            case 1:
                loadImageRGB();
                Merge_Filter_RGB();
                saveImageRGB();
                break;
            case 2:
                loadImageRGB();
                DL_ImageFilter_RGB();
                saveImageRGB();
                break;
            case 3:
                loadImageRGB();
                Shrink_Image_RGB();
                saveImageRGB2();
                break;
            case 4:
                loadImageRGB();
                //too add more blur to photo u need to call the function more than once
                Blur_Image_RGB();
                Blur_Image_RGB();
                Blur_Image_RGB();
                saveImageRGB();
                break;
            case 0:
                return 0;
        }
    }


*/
    return 0;
}

//_________________________________________
void loadImage (unsigned char image[SIZE][SIZE]) {
    char imageFileName[100];
    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;
    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}
void loadImageRGB (unsigned char imageRGB[SIZE][SIZE][RGB]) {
    char imageFileName[300];
    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;
    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, imageRGB);
}
void BW_Filter(){
    long avg{};
    for (int i{}; i < SIZE; i++){
        for (int j{}; j < SIZE; j++)
            avg += image[i][j];
    }
    avg /= (SIZE*SIZE);

    for (int i{}; i < SIZE; i++){
        for (int j{}; j < SIZE; j++){
            if (image[i][j] > avg)
                image[i][j] = 255;
            else
                image[i][j] = 0;

        }
    }
}
void Invert_Filter() {
    long avg{};
    for (int i{}; i < SIZE; i++) {
        for (int j{}; j < SIZE; j++)
            avg += image[i][j];
    }
    avg /= (SIZE * SIZE);
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
void Merge_Filter(){
    unsigned char image2[SIZE][SIZE];
    loadImage(image2);
    for (int i{}; i < SIZE; i++) {
        for (int j{}; j < SIZE; j++) {
            image[i][j] = (image[i][j] + image2[i][j]) /2;
        }
    }
}
void Flip_Image(){
    const int c = SIZE / 2;
    int vertically{255};
    int horizontally{255};
    int choice; cin >> choice;
    if (choice ==1)
        horizontally = c;
    else vertically = c ;
    for (int x{}; x < horizontally; x++){
        for (int y{}; y < vertically;y++){
            int temp = image[x][y];
            if (choice == 1){
                image[x][y] = image[SIZE-x][y];
                image[SIZE-x][y] = temp;
            }
            else{
                image[x][y] = image[x][SIZE-y];
                image[x][SIZE-y]= temp;
            }

        }
    }
}
void DL_ImageFilter() {
    int darker_or_lighter;
    cout << "1.Darker\n2.lighter\nchoice number"<<endl;
    cin >> darker_or_lighter;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if(darker_or_lighter == 1)image[i][j] = image[i][j] / 2;
            else image[i][j] = min(image[i][j]+50, 255);
        }
    }
}
void Detect_Image_Edges() {
    unsigned char image2[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image2[i][j] = image[i][j];
        }
    }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if( image2[i][j + 1] - image[i][j] >= 30) image[i][j] = 0;
                else if(abs(image2[i][j + 1] - image[i][j]) < 30) image[i][j] = 255;
            }
        }
}
void Blur_Image(){
    for (int i = 0; i < SIZE ; i ++) {
        for (int j = 0; j < SIZE  ; j ++) {
            image[i][j] = (image[i+1][j+1] + image[i+1][j] + image[i][j+1] + image[i][j+2]  + image[i+1][j+2] + image[i+2][j] + image[i+2][j+1]
                           + image[i+2][j+2]  + image[i][j]) / 9 ;
        }
    }


}
void Shrink_Image(){
    int shrink;
    cout <<"choose 2 for 1/2\n"
           "choose 3 for 1/3 \n"
           "choose 4 for 1/4 \n"
           "!!Choose denominator!!"<<endl;
    cout << "Enter shrink factor : ";
    cin >> shrink;
        for(int i = 0; i < SIZE ; i ++) {
            for (int j = 0; j < SIZE  ; j ++) {
                image2[i/shrink][j/shrink] = (image[i][j] + image[i+1][j] + image[i][j+1] + image[i+1][j+1]) / 4 ;
            }
        }
}

void Enlarge_Image() {
    int quarter, x=0 , y=0 ,X_SIZE = 0, Y_SIZE = 0;
    cout << "Enter the quarter you want 1,2,3,4: ";
    cin >> quarter;
    if (quarter == 1) {
        for (int i = 0, x = 0; x < SIZE / 2; i += 2, x++) {
            for (int j = 0, y = 0; y < SIZE / 2; j += 2, y++) {
                image2[i][j] = image[x][y];
                image2[i + 1][j] = image[x][y];
                image2[i][j + 1] = image[x][y];
                image2[i + 1][j + 1] = image[x][y];
            }
        }
    }
    if (quarter == 2) {
        for (int i = 0, x = 0; x < SIZE / 2; i += 2, x++) {
            for (int j = 0, y = 128; y < SIZE; j += 2, y++) {
                image2[i][j] = image[x][y];
                image2[i + 1][j] = image[x][y];
                image2[i][j + 1] = image[x][y];
                image2[i + 1][j + 1] = image[x][y];
            }
        }
    }
    if (quarter == 3) {
        for (int i = 0, x = 128; x < SIZE; i += 2, x++) {
            for (int j = 0, y = 0; y < SIZE / 2; j += 2, y++) {
                image2[i][j] = image[x][y];
                image2[i + 1][j] = image[x][y];
                image2[i][j + 1] = image[x][y];
                image2[i + 1][j + 1] = image[x][y];
            }
        }
    }
    if (quarter == 4) {
        for (int i = 0, x = 128; x < SIZE; i += 2, x++) {
            for (int j = 0, y = 128; y < SIZE; j += 2, y++) {
                image2[i][j] = image[x][y];
                image2[i + 1][j] = image[x][y];
                image2[i][j + 1] = image[x][y];
                image2[i + 1][j + 1] = image[x][y];
            }
        }
    }
}
void MirrorHalf_Image(){
    int choice;
    cout <<"1-Half Right\n2-Half left \n3-Half upper\n4-Half bottom\n";
    cin >> choice;
    switch (choice) {
        case 1:
            for(int i = 0; i < SIZE ; i ++) {
                for (int j = 0; j < SIZE / 2 ; j++) {
                    image[i][j] = image[i][SIZE - j];
                }
            }
            break;
        case 2:
            for(int i = 0; i < SIZE ; i ++) {
                for (int j = 0; j < SIZE / 2 ; j++) {
                    image[i][SIZE - j] = image[i][j];
                }
            }
            break;
        case 3:
            for(int i = 0; i < SIZE / 2; i ++) {
                for (int j = 0; j < SIZE ; j++) {
                    image[SIZE - i][j] = image[i][j];
                }
            }
            break;
        case 4:
            for(int i = 0; i < SIZE / 2; i ++) {
                for (int j = 0; j < SIZE ; j++) {
                    image[SIZE - i][j] = image[i][j];
                }
            }
            break;
    }
}

void Shuffle_Image()
{
    int i_start, i_end, j_start, j_end, old_i_start, old_i_end, old_j_start, old_j_end;
    // to copy the array to another one
    for (int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            image2[i][j] = image[i][j];
        }
    }
    // to set the order of the images
    char order[4];
    for (int i = 0; i < 4; i++)
    {
        cout << "put the order: ";
        cin >> order[i];
    }
    // to shuffle as the given order
    for (int i = 0; i < 4; i++)
    {
        // set the first quarter from the new image
        if(i == 0)
        {
            i_start = j_start = 0;
            i_end = j_end = SIZE/2;
        }else if(i == 1)// set the second quarter from the new image
        {
            i_start = 0;
            i_end = SIZE/2;
            j_start = SIZE/2;
            j_end = SIZE;
        }else if(i == 2)// set the third quarter from the new image
        {
            i_start = SIZE/2;
            i_end = SIZE;
            j_start = 0;
            j_end = SIZE/2;
        }else if(i == 3)// set the fourth quarter from the new image
        {
            i_start = SIZE/2;
            i_end = SIZE;
            j_start = SIZE/2;
            j_end = SIZE;
        }
        if(order[i] == '1')// set the first quarter from the old image
        {
            old_i_start = old_j_start = 0;
            old_i_end = old_j_end = SIZE/2;
        }else if (order[i] == '2')// set the second quarter from the old image
        {
            old_i_start = 0;
            old_i_end = SIZE/2;
            old_j_start = SIZE/2;
            old_j_end = SIZE;
        }else if (order[i] == '3')// set the third quarter from the old image
        {
            old_i_start = SIZE/2;
            old_i_end = SIZE;
            old_j_start = 0;
            old_j_end = SIZE/2;
        }else if (order[i] == '4')// set the fourth quarter from the old image
        {
            old_i_start = SIZE/2;
            old_i_end = SIZE;
            old_j_start = SIZE/2;
            old_j_end = SIZE;
        }
        // copy the chosen quarter from the old image to the quarter of the new image sequenial
        for (int k1 = i_start, k2 = old_i_start; k1 < i_end; k1++, k2++)
        {
            for(int l1 = j_start, l2 = old_j_start; l1 < j_end; l1++, l2++)
            {
                image[k1][l1] = image2[k2][l2];
            }
        }

    }

}
//_________________________________________RGB_________________________________________

void Merge_Filter_RGB(){
    unsigned char image2[SIZE][SIZE][RGB];
    char imageFileName[300];
    // Get gray scale image file name
    cout << "Enter the second source image file name: ";
    cin >> imageFileName;
    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, imageRGB2);
    for (int i{}; i < SIZE; i++) {
        for (int j{}; j < SIZE; j++) {
            for (int n = 0; n < RGB ; ++n) {
                imageRGB[i][j][n] = (imageRGB[i][j][n] + imageRGB2[i][j][n]) /2;
            }
        }
    }
}

void DL_ImageFilter_RGB(){
    int darker_or_lighter;
    cout << "1.Darker\n2.lighter\nchoice number"<<endl;
    cin >> darker_or_lighter;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int n = 0; n < RGB; ++n) {
                if(darker_or_lighter == 1)imageRGB[i][j][n] = imageRGB[i][j][n] / 2;
                else imageRGB[i][j][n] = min(imageRGB[i][j][n]+50, 255);
            }
        }
    }
}

void Shrink_Image_RGB(){
    int shrink;
    cout <<"choose 2 for 1/2\n"
           "choose 3 for 1/3 \n"
           "choose 4 for 1/4 \n"
           "!!Choose denominator!!"<<endl;

    cout << "Enter shrink factor : ";
    cin >> shrink;
    for(int i = 0; i < SIZE ; i ++) {
        for (int j = 0; j < SIZE  ; j ++) {
            for (int n = 0; n < RGB ; ++n) {
                imageRGB2[i/shrink][j/shrink][n] = (imageRGB[i][j][n] + imageRGB[i+1][j][n] + imageRGB[i][j+1][n] + imageRGB[i+1][j+1][n]) / 4 ;
            }

        }
    }
}

void Blur_Image_RGB(){
    for (int i = 0; i < SIZE ; i ++) {
        for (int j = 0; j < SIZE  ; j ++) {
            for (int n = 0; n < RGB ; ++n) {
                imageRGB[i][j][n] = (imageRGB[i+1][j+1][n] + imageRGB[i+1][j][n] + imageRGB[i][j+1][n] + imageRGB[i][j+2][n]  +
                        imageRGB[i+1][j+2][n] + imageRGB[i+2][j][n] + imageRGB[i+2][j+1][n]+ imageRGB[i+2][j+2][n]  + imageRGB[i][j][n]) / 9 ;
            }
        }
    }
}





//_________________________________________SAVING_FUNCTIONS_________________________________________
void saveImage() {
        char imageFileName[100];
        // Get gray scale image target file name
        cout << "Enter the target image file name: ";
        cin >> imageFileName;
        // Add to it .bmp extension and load image
        strcat(imageFileName, ".bmp");
        writeGSBMP(imageFileName, image);
}
void saveImage2() {
        char imageFileName[100];
        // Get gray scale image target file name
        cout << "Enter the target image file name: ";
        cin >> imageFileName;
        // Add to it .bmp extension and load image
        strcat(imageFileName, ".bmp");
        writeGSBMP(imageFileName, image2);
}

//_________________________________________RGB_________________________________________
void saveImageRGB2() {
    char imageFileName[100];
    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeRGBBMP(imageFileName, imageRGB2);
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
